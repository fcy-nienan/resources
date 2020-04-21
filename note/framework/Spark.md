# spark参数
1. num-executors		executor的数量
2. executor-memory	executor的内存
3. executor-cores	executor中task的数量
4. driver-memory		driver端的内存，如果是collect一类的action则需要调大点
5. spark.default.parallelism    默认并行度
6. spark.storage.memoryFraction
7. spark.shuffle.memoryFraction
8. spark.serializer=org.apache.spark.serializer.KryoSerializer   更改默认的序列化机制(默认是Java的序列化)
# 理解
每个Worker上存在一个或多个CoarseGrainedExecutorBackend进程，
每个进程包含一个Executor对象，该对象持有一个线程池，每个线程可以执行一个Task
(5+4)/9     9:当前stage的task的数量，5：已完成的task数量，4：等待执行的task数量。

RDD分为两种操作
transfer和action
转换和具体的操作
shuffle操作
shuffle是Spark将多个分区的数据重新分组重新分布数据的机制。
shuffle是一个复杂且代价较高的操作，它需要完成将数据在executor和机器节点之间进行复制的工作
通过action触发job
通过宽窄依赖划分stage
# 多个不同stage之间可以同时执行吗?
    不可以,stage之间是有执行顺序的,只有上一个执行完了才能执行下一个
# 根据宽窄依赖划分stage,那比如reduceByKey是在哪一个stage中
    textFile=>flatMap=>map=>reduceByKey=>foreach(println)
    stage1:textFile=>flatMap=>map
    stage2:reduceByKey
    那最后的foreach(println)算是什么算子?
    如果最后不是foreach(println)而是count呢?
    在spark UI中查看DAG划分的stage中并没有foreach()和count出现
    倒是在job页面显示了foreach和count
    也就是说foreach和count是action,触发job,并不在stage中的算子中
# spark是如何做到只在action操作才提交的?
    我们调用的方法是spark自己的api,它可以在特定的action方法中加上提交的代码
      def map[U: ClassTag](f: T => U): RDD[U] = withScope {
        val cleanF = sc.clean(f)
        new MapPartitionsRDD[U, T](this, (context, pid, iter) => iter.map(cleanF))
      }
      def collect(): Array[T] = withScope {
        val results = sc.runJob(this, (iter: Iterator[T]) => iter.toArray)
        Array.concat(results: _*)
      }
     上面的runJob会触发job提交
# 两种stage
ShuffleMapStage
ResultStage
Each Stage can either be a shuffle map stage, 
in which case its tasks' results are input for  other stage(s),
or a result stage,
in which case its tasks directly compute a Spark action
每个stage可以是一个shuffleMapStage,他们的task的输出是其他stage的输入
或者一个resultStage,他们的输出就是直接计算spark的action

Each Stage also has a firstJobId, identifying the job that first submitted the stage.  
When FIFOscheduling is used, 
this allows Stages from earlier jobs to be computed first or recovered
faster on failure.
每个stage还有一个job编号，标识这第一次提交这个stage的job，
当使用FIFO队列，允许计算最早的stage，或者出现故障的时候更快的恢复

# stage的元素
id                      
    stage的id
rdd[]                   
    此stage运行的rdd   shuffle map stage:it's the rdd we run map tasks on 
    for a result stage, it's the target RDD than we ran an action on
parents:List[Stage]
    此stage依赖的stage
firstJobId
    提交这个stage的job id
callSite
    CallSite represents a place in user code. It can have a short and a long form
    这东西代表一个用户代码的位置,它可以有一个长短格式
# 两种Task
    A Spark job consists of one or more stages. 
    The very last stage in a job consists of multiple ResultTasks, 
    while earlier stages consist of ShuffleMapTasks. 
    A ResultTask executes the task and sends the task output back to the driver application. 
    A ShuffleMapTask executes the task and divides the task output to 
    multiple buckets (based on the task's partitioner).
# RDD,DataFrame,DataSet
RDD是最早的概念
DataFrame是spark1.3之后提出的概念,加上了schema
DataSet是spark1.6之后提出的概念
RDD转换为DataFrame
	val df=deptRDD.toDF();
	df.createOrReplaceTempView("dept");
	spark.sql("select * from dept").show();
RDD本身就是一个抽象出的概念，
其本质与Hadoop MapReduce处理时输入输出的key-value，Flink的dataset没有本质区别。
处理时，仍然使用iterator一边载入部分数据，(读取一部分处理一部分)
一边执行运算（每个partition的实现内部实际就是一个iterator），没必要纠结这个概念
# yarn memory
num-executors 16
executor-cores 10
executor-memory 36
driver-memory 3
driver-core 3
16*36=556G  556*1024=569344
actually: 
    16Containers 161Cores 656384M
    656384M/1024=641G
# core,task
如果资源不够需要分批运行  
    如果有四个Map任务需要运行,只有两个core,那么需要分两批运行

每个Task根据提供的分区器进行分区，然后每个分区产生一个小文件
优化1: File Consolidation 文件合并
    后来优化可以在同个个executor中的task将小文件合并到一个文件中,然后reducer端根据相应的索引获取数据
    但如果下游stage的分区数N很大,那么还是会产生N个文件
优化2: sort Shuffle 只产生一个文件 
    根据partition ID排序,每个分区内部再按照key排序,同时会生成一个索引文件记录每个partition的大小和偏移量
优化3: 文件格式变为二进制,再序列化的二进制数据上进行排序,提供了对外内存供使用
    分区数不能超过一定大小(2^24-1),shuffle阶段不能有aggregate操作
优化4: 统一优化2和优化3,自动选择合适的方式
# 在1M的内存中对100亿条记录进行排序
    假设1M内存能装1亿条记录
    那么我们需要取100次并把每次排序的结果输出到一个文件中
    然后将这100个文件merge成一个全局有序的大文件,如何合并?
    可以堆排序,好像还有归并排序
# 为什么需要分区
    减少网络数据传输.spark将RDD进行分区,然后对每个分区进行运算,在网络中传输的可以是每个分区的结果
    当然如果需要进行shuffle那么必要的网络IO还是少不了的
    容错性
        某个分区失败不影响其他分区的数据,恢复时只需要重新计算该分区的数据就行
# shuffle
    shuffle的根本原因还是相同的key在不同的Map端,按照key做一些操作的时候不得不进行shuffle,
    也就是将所有节点的key拉到一个reducer中来
    每个stage的最后一部就是将数据分区并且写入磁盘,还要上报分区数据到Master
    master在启动新的stage的时候会将分区信息发送给task,这样task就知道去哪读数据了
    
    下一个stage什么时候开始fetch数据?是等待所有task执行玩还是有执行玩的就fetch?
    全部执行完
    那全部执行完后是边获取边执行还是全部获取后在开始?
    边获取边执行
    获取的数据存放在哪里?
    这个肯定有一个shuffle buffer,内存+磁盘,这个空间不够肯定还会spill数据到磁盘,内存使用Map
    怎么知道数据在哪?
    从driver端获取分区信息
    spark puts the data on HDDs only once during shuffles ,MR do it 2 times
# task和分区
D:\\data\\目录下有三个文件
    2020/01/08  23:56       634,776,175 12306.txt   605M 
    2020/01/07  12:34         8,100,002 data.txt    7.7M
    2020/01/07  12:34         8,100,002 data1.txt   7.7M
sc.textFile("D:\\data\\").count
最后生成了21个task
    605/32=18.9=19个task
    其他两个文件各一个，总共21个
    32M一个分区这个是看版本的
sc.textFile("D:\\data\\",10).count
    当只剩下两个7.7M的文件的时候,text File加了个参数,然后还很有了10个task
    但是奇怪的是只有两个task读了全文件，其他都是读取文件的一部分，并且records都是0
# task总数
    一个程序有多个job
    一个job有多个stage
    一个stage有多个task
    总task数量=jobNum*stageNum*taskNum;就是所有task相加的数量
# RDD
属性
* a list of partitions    一系列分区
* a function for computing each split    算子
* a list of dependencies on other rdds   父依赖
* optionally a partitioner for key-value rdds   分区器
* optionally a list of preferred location to compute each slit on   计算优先位置
# 如果用户直接运行bin/spark-sql命令。会导致我们的元数据有两种状态：
1. in-memory状态:如果SPARK-HOME/conf目录下没有放置hive-site.xml文件，元数据的状态就是in-memory
2. hive状态：如果我们在SPARK-HOME/conf目录下放置了，hive-site.xml文件，那么默认情况下spark-sql的元数据的状态就是hive.
# spark-shell
spark-shell --name fcy local[6]   6个线程
# Spark相关概念
## overview
    spark提供了两种抽象:RDD和共享变量
* RDD(resilient distributed dataset)    
    1. 一个可以并行操作的跨集群节点的数据集合
    2. 由Hadoop文件系统或者其他支持Hadoop文件系统的或者一个客户端的Scala集合创建
    3. RDD自动从故障节点恢复(数据丢失了可以重新计算)
    4. RDD的两种创建方式
        1. 并行化你的集合
            ```
           val data = Array(1, 2, 3, 4, 5)
           val distData = sc.parallelize(data)
           ```
        2. 引用一个外部的存储系统,例如HDFS,Hbase或者任何一个提供了Hadoop的InputFormat
            ```
           scala> val distFile = sc.textFile("data.txt")
           distFile: org.apache.spark.rdd.RDD[String] = data.txt MapPartitionsRDD[10] at textFile at <console>:26
           ```
     5. Shuffle Operations
        1. shuffle read and shuffle write
            1. shuffle read: total shuffle bytes and records read(includes both data read locally and data read from remote executors)
            2. shuffle write: bytes and records written to disk in order to be read by a shuffle in a future stage
            
        2. Operations which can cause a shuffle include repartition operations like repartition and coalesce, ‘ByKey operations (except for counting) like groupByKey and reduceByKey, and join operations like cogroup and join.
        3. Shuffle operation is used in Spark to re-distribute data across multiple partitions. It is a costly and complex operation. 
        In general a single task in Spark operates on elements in one partition. 
        To execute shuffle, we have to run an operation on all elements of all partitions.
        It is also called all-to- all operation     
* shared variables  
    **正常情况下spark在每一个节点的task上都运行一个实例,但有时候我们需要在多个节点的多个task间共享变量,spark
    提供两种类型的变量广播变量和累加变量**
    1. broadcast variable
        在每个节点上缓存一份并使用
        正常情况下是task每次请求一个值
        广播变量使得在开始的时候就将需要的值发送到了executor端
        然后每个task都可以直接使用而不用通过网络请求了
    2. accumulators variable
        只能累加或者做汇总的变量
## 运行模式
    local本地多线程模式
    standlone spark自己的模式(spark自己管理资源)
    yarn-client 以yarn客户端的模式提交作业
    yarn-cluster 以yarn集群的模式提交作业
## 相关术语
1. Application  
   User program built on Spark. Consists of a driver program and executors on the cluster
2. Application Jar
   A jar containing the user's Spark application. In some cases users will want to create an "uber jar" containing their application along with its dependencies. The user's jar should never include Hadoop or Spark libraries, however, these will be added at runtime
3. Cluster Manager
   An external service for acquiring resources on the cluster (e.g. standalone manager, Mesos, YARN)
4. Driver Program  
   The process running the main() function of the application and creating the SparkContext
5. Deploy Mode  
   Distinguishes where the driver process runs. In "cluster" mode, the framework launches the driver inside of the cluster. In "client" mode, the submitter launches the driver outside of the cluster
6. Worker Node  
   Any node that can run application code in the cluster
7. Executor  
    A process launched for an application on a worker node, that runs tasks and keeps data in memory or disk storage across them. Each application has its own executors.
8. Task  
    A unit of work that will be sent to one executor
9. Job  
    A parallel computation consisting of multiple tasks that gets spawned in response to a Spark action (e.g. save, collect); you'll see this term used in the driver's logs.
10. Stage  
    Each job gets divided into smaller sets of tasks called stages that depend on each other (similar to the map and reduce stages in MapReduce); you'll see this term used in the driver's logs. 
# 新手
下面两者的类型不同
val rdd=sc.parallelize(1 to 10):Rdd[Int]
val rdd=sc.parallelize(Array(1 to 10)):Rdd[Range.Inclusive]
在spark UI上有些task是skipped的,这种状况是所需要的数据已经计算过了并且存在
    val rdd1=sc.parallelize(1 to 10)
    val rdd2=rdd1.map(e=>(e,1))
    rdd1.count
    rdd2.count//这步计算的时候
# spark-sql join
    去重的并集
    select * from a union select * from b;
    没去重的并集
    select * from a union all select * from b;
    差集
    select * from a except select * from b;

    streamlter buildlter
    两张表
    streamlter为大表
    buildlter为小表
    遍历streamlter,每次取出streamlter中的一条数据,根据join条件计算keyA
    然后取buildlter中查找所有满足join条件的keyB
    最后经过过滤得到最后的结果
    buildlter需要是一个查找性能较优的数据结果
    sort merge join
    broadcast join
    hash join  
# 相关类数据结构
## task
=======
# spark相关接口
## RDD
    SparkContext
    List[Partition]
    Seq[Dependency]
    Partitioner
    id
    name
    StorageLevel存储级别
    creationSite创建这个RDD的用户的代码
    RDDOperationScope
    RDDCheckpointData
    doCheckpointCalled:Boolean
## Partition
    trait Partition extends Serializable {
      /**
       * Get the partition's index within its parent RDD
       */
      def index: Int
    
      // A better default implementation of HashCode
      override def hashCode(): Int = index
    }
    index
    
    HashPartitioner
    RangePartitioner
## Dependency
    abstract class Dependency[T] extends Serializable {
      def rdd: RDD[T]
    }
    相关子类
    NarrowDependency窄依赖
        OneToOneDependency
        RangeDependency
        PruneDependency
    ShuffleDependency宽依赖
## CallSite
    case class CallSite(shortForm: String, longForm: String)
    长短格式的表示用户的代码
    shortForm:
        map at DemoFunction.scala:20
    longForm:
        org.apache.spark.rdd.RDD.map(RDD.scala:323)\n
        LeetCode.ScalaAdvanced.DemoFunction$.main(DemoFunction.scala:20)\n
        LeetCode.ScalaAdvanced.DemoFunction.main(DemoFunction.scala)\n
## StorageLevel
    用几个布尔值表示存储在哪
    class StorageLevel private(
        private var _useDisk: Boolean,
        private var _useMemory: Boolean,
        private var _useOffHeap: Boolean,
        private var _deserialized: Boolean,
        private var _replication: Int = 1)
      extends Externalizable {
## Stage
    private[scheduler] abstract class Stage(
        val id: Int,
        val rdd: RDD[_],
        val numTasks: Int,
        val parents: List[Stage],
        val firstJobId: Int,
        val callSite: CallSite)
    extends Logging {
    唯一id
    @param id Unique stage ID  
    该stage运行的RDD
    @param rdd RDD that this stage runs on: for a shuffle map stage, it's the RDD we run map tasks
       on, while for a result stage, it's the target RDD that we ran an action on
    该stage的task数量
    @param numTasks Total number of tasks in stage; result stages in particular may not need to
       compute all partitions, e.g. for first(), lookup(), and take().
    依赖的父stage
    @param parents List of stages that this stage depends on (through shuffle dependencies).
    该stage距离最近的jobID
    @param firstJobId ID of the first job this stage was part of, for FIFO scheduling.
    与该stage关联的用户程序的位置
    @param callSite Location in the user program associated with this stage: either where the target
# Task
    private[spark] abstract class Task[T](
        val stageId: Int,
        val stageAttemptId: Int,
        val partitionId: Int,
        internalAccumulators: Seq[Accumulator[Long]]) extends Serializable {
    @param stageId id of the stage this task belongs to
    @param partitionId index of the number in the RDD
    该task属于哪一个stage,该task计算的数据在RDD的哪一个分区
    Task持有的信息只有stageID和分区ID
    哪个stage的哪个分区上
    两种Task
        ShuffleMapTask
        ResultTask
    map(e=>(e,1))
    reduceByKey((x,y)=>x+y)
    count
    执行map函数的是那种Task？
    执行reduceByKey的是哪种Task?
    执行count的是哪种Task？
    下面的Task我统一说线程了，反正还是用的Java的线程池TreadPoolExecutor来提交任务
    之所以会有上面的疑问是我之前理解的Task错了，
    我之前是认为执行Map的用一类线程，然后执行完Map函数后就终止这个线程
    实际是一个线程执行Map函数，然后如果后面有flat Map一类的transform算子时还是用这个线程执行
    所以可以说一个Stage是一组线程的集合，每个线程执行多个transform算子
    所以有两种Task,一个是执行Transform算子一类的Task,
    这类Task的最后的输出是shuffle需要的数据,这类Task当碰到宽依赖时终止
    这类Task不执行宽依赖的那个算子,比如map--flatMap--reduceByKey--count
    有两个stage
    stage1:map--flatMap
    stage2:reduceByKey
    
    action算子是在driver执行还是在worker端执行?
    reduce((x,y)=>x+y) 实验后发现是先在每个worker端的Task中都执行了这个函数
    然后在driver端将所有worker端的结果组成一个RDD然后又执行了这个函数
    在reduce的源码中也可以看到case Some(value)=>Some(f(value,taskResult.get))
    f是我们提供给reduce的函数
    val mergeResult = (index: Int, taskResult: Option[T]) => {
          if (taskResult.isDefined) {
            jobResult = jobResult match {
              case Some(value) => Some(f(value, taskResult.get))
              case None => taskResult
            }
          }
        }
        
# spark数据本地行
    本地缓存
    本地磁盘
    其他机器
# spark参数
spark.sql.shuffle.partitions
    在spark-sql中的参数，join时的分区数
spark.default.parallelism
    is only working for raw RDD and is ignored when working DataFrame
    spark使用rdd的参数,textFile方法就用了这个参数的默认值读取文件
# 资源申请和job执行
    是等待所有资源全部充足之后才开始执行还是有一部分就申请一部分?
    后者,有一部分申请一部分,然后等待资源
    应该又相应的参数设置这个等待的时间
# RDD的弹性
    容错
    task失败重试
    内存和磁盘都可以存储
    数据分片,小合并大,大分化小
# RDD的缺点
    粗粒度写
    不支持细粒度的写和更新
# RDD的宽窄依赖
    宽依赖:一个RDD的一个分区的数据到达了多个子RDD的多个分区
    窄依赖:一个RDD的一个分区的数据到达了一个RDD的一个分区，多个RDD的多个分区到达了一个RDD的一个分区
    宽依赖:一父多子
    窄依赖:一父一子或者多父一子
# 如何使用cache缓存
    shuffle后最后使用缓存持久化一下，网络传输开销大
# 进度条显示的是啥
    [Stage7:===========>                              (14174 + 5) / 62500]
    val total = s.numTasks()
    val header = s"[Stage ${s.stageId()}:"
    val tailer = s"(${s.numCompletedTasks()} + ${s.numActiveTasks()}) / $total]"
# spark那些代码在本地执行，哪些会被序列化为任务
