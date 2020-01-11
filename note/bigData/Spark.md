# spark参数
1. num-executors		executor的数量
2. executor-memory	executor的内存
3. executor-cores	executor中task的数量
4. driver-memory		driver端的内存，如果是collect一类的action则需要调大点
5. spark.default.parallelism    默认并行度
6. spark.storage.memoryFraction
7. spark.shuffle.memoryFraction
# 理解
每个Worker上存在一个或多个CoarseGrainedExecutorBackend进程，每个进程包含一个Executor对象，该对象持有一个线程池，每个线程池可以执行一个Task
(5+4)/9     9:当前stage的task的数量，5：已完成的task数量，4：等待执行的task数量。

RDD分为两种操作
transfer和action
转换和具体的操作

shuffle操作
shuffle是Spark将多个分区的数据重新分组重新分布数据的机制。
shuffle是一个复杂且代价较高的操作，它需要完成将数据在executor和机器节点之间进行复制的工作

在Yarn的NodeManager节点上启动一个map task或者reduce task，
在物理上启动的是一个jvm进程；而Spark的task是Executor进程中的一个线程。

通过action触发job
通过宽窄依赖划分stage


job,stage,task
job是我们提交的应用程序
stage是根据我们提交的程序中的宽窄依赖划分的
task是根据输入数据的分区数指定的

多个不同stage之间可以同时执行吗?
不可以,stage之间是有执行顺序的,只有上一个执行完了才能执行下一个
根据宽窄依赖划分stage,那比如reduceByKey是在哪一个stage中
textFile=>flatMap=>map=>reduceByKey=>foreach(println)
stage1:textFile=>flatMap=>map
stage2:reduceByKey
那最后的foreach(println)算是什么算子?
如果最后不是foreach(println)而是count呢?
在spark UI中查看DAG划分的stage中并没有foreach()和count出现
倒是在job页面显示了foreach和count
也就是说foreach和count是action,触发job,并不在stage中的算子中
* spark是如何做到只在action操作才提交的?
    我们调用的方法是spark自己的api,它可以在特定的action方法中加上提交的代码
      def map[U: ClassTag](f: T => U): RDD[U] = withScope {
        val cleanF = sc.clean(f)
        new MapPartitionsRDD[U, T](this, (context, pid, iter) => iter.map(cleanF))
      }
      def collect(): Array[T] = withScope {
        val results = sc.runJob(this, (iter: Iterator[T]) => iter.toArray)
        Array.concat(results: _*)
      }
两种stage
ShuffleMapStage
ResultStage
Each Stage can either be a shuffle map stage, 
in which case its tasks' results are input for * other stage(s), or a result stage,
in which case its tasks directly compute a Spark action
每个stage可以是一个shuffleMapStage,他们的task的输出是其他stage的输入
或者一个resultStage,他们的输出就是一个计算spark的action
 
 
RDD是最早的概念
DataFrame是spark1.3之后提出的概念
DataSet是spark1.6之后提出的概念
RDD转换为DataFrame
	val df=deptRDD.toDF();
	df.createOrReplaceTempView("dept");
	spark.sql("select * from dept").show();

num-executors 16
executor-cores 10
executor-memory 36
driver-memory 3
driver-core 3
16*36=556G  556*1024=569344
actually: 
    16Containers 161Cores 656384M
    656384M/1024=641G

task的个数有什么决定
一个Stage分区数

spark通过textFile读取一个文件一直到结束的流程
# CPU核
    电脑物理CPU个数		1
    每个CPU的核数		2
    核只不支持超线程	2
    处理器数量				2
    每个处理器的内核数量	2
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
    现在回头看，RDD本身就是一个Berkeley的博士们在写论文时，抽象出的概念，
    其本质与Hadoop MapReduce处理时输入输出的key-value，Flink的dataset没有本质区别。
    处理时，任然使用iterator一边载入部分数据，(读取一部分处理一部分)
    一边执行运算（每个partition的实现内部实际就是一个iterator），没必要纠结这个概念
# 如果用户直接运行bin/spark-sql命令。会导致我们的元数据有两种状态：
1. in-memory状态:如果SPARK-HOME/conf目录下没有放置hive-site.xml文件，元数据的状态就是in-memory
2. hive状态：如果我们在SPARK-HOME/conf目录下放置了，hive-site.xml文件，那么默认情况下spark-sql的元数据的状态就是hive.
# spark-shell
spark-shell --name fcy local[6]
# Spark相关概念
## overview
    spark提供了两种抽象:RDD和共享变量
* RDD(resilient distributed dataset)    
    1. 一个可以并行操作的跨集群节点的数据集合
    2. 由Hadoop文件系统或者其他支持Hadoop文件系统的或者一个客户端的Scala集合创建
    并且
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
## 算子
* map(fun(e))
* filter(fun(e))
* flatMap(fun(e):Array[Int])
    参数是一个返回数组的函数
    flatMap(e=>e.split(" "))
* mapPartitions(fun(Iterator[Int]):Iterator[Int])
    参数是一个函数,该函数接收一个能遍历一个分区数据的迭代器并且返回一个分区
    def function(iter:Iterator[Int]):Iterator[Int]={
    
    }
* mapPartitionsWithIndex(fun(Int,Iterator[Int]):Iterator[Int])
    作用同mapPartitions,不同点在于传入的参数多了一个当前分区索引值
    def function(index:Int,iter:Iterator[Int]):Iterator[Int]={
    
    }
* sample(withReplacement,fraction,seed)
    数据抽样,去除一部分数据
    sample(false,0.5,1)
* union
    数据不去重(sql中的union是去重的)
    rdd.union(rdd1)
* intersection
    两个rdd的交集并去重且无序返回
* distinct(numPartitions)
    map(x => (x, null)).reduceByKey((x, y) => x, numPartitions).map(_._1)
    去重
    scala> val rdd=sc.parallelize(1 to 100,5)
    rdd: org.apache.spark.rdd.RDD[Int] = ParallelCollectionRDD[0] at parallelize at <console>:24
    
    scala> rdd.distinct(10).collect
    res0: Array[Int] = Array(100, 80, 30, 50, 40, 90, 70, 20, 60, 10, 41, 61, 81, 21, 71, 11, 51, 1, 91, 31, 52, 82, 22, 32, 92, 62, 42, 72, 12, 2, 13,
     53, 73, 93, 33, 23, 63, 83, 3, 43, 84, 34, 4, 54, 14, 24, 64, 74, 44, 94, 15, 55, 25, 95, 65, 35, 75, 45, 85, 5, 96, 56, 76, 16, 66, 46, 36, 6, 86
    , 26, 47, 77, 97, 27, 57, 37, 17, 67, 7, 87, 28, 48, 98, 8, 18, 38, 58, 88, 78, 68, 19, 39, 29, 79, 59, 89, 69, 9, 49, 99)
    两个stage
    stage0 distinct task 5  这个是读取数据的任务数
    stage1 collect  task 10 这个是distinct后的任务数
    distinct(10),这个10可以认为生成的分区数,将去重后的数据分成了10个分区
    去重前从1-100中
    第一个任务选择被10整除的数据x%10=0
    然后第二个任务选择除以10余1的数据x%10=1
    以此类推
* groupByKey(numPartitions)
   When called on a dataset of (K, V) pairs, returns a dataset of (K, Iterable<V>) pairs
   res4: Array[(Int, Int)] = Array((1,1), (2,1), (3,1), (4,1), (5,1), (6,1), (7,1), (8,1), (92,1), (3,1), (4,1), (5,1), (6,1), (7,1))
   groupByKey(3).collect 
   res7: Array[(Int, Iterable[Int])] = Array((6,CompactBuffer(1, 1)), (3,CompactBuffer(1, 1)), (4,CompactBuffer(1, 1)), (1,CompactBuffer(1)), (7,Compa
   ctBuffer(1, 1)),(92,CompactBuffer(1)), (8,CompactBuffer(1)), (5,CompactBuffer(1, 1)), (2,CompactBuffer(1)))
   将数据分组,numTasks作用同上
* reduceByKey(fun(e1,e2):e3,numPartitions)
   res4: Array[(Int, Int)] = Array((1,1), (2,1), (3,1), (4,1), (5,1), (6,1), (7,1), (8,1), (92,1), (3,1), (4,1), (5,1), (6,1), (7,1))
   reduceByKey((e1,e2)=>e1+e2,3).collect
   res9: Array[(Int, Int)] = Array((6,2), (3,2), (4,2), (1,1), (7,2), (92,1), (8,1), (5,2), (2,1))
   聚合操作
* aggregateByKey

* sortByKey

* join

* leftOuterJoin

* rightOuterJoin

* fullOuterJoin

* cogroup

* cartesian笛卡尔积

* pipe

* coalesce

* repartition

* repartitionAndSortWithinPartitions
    根据partitioner进行分区并在每个分区中按照key进行排序
## Action
* reduce(fun(e1,e2):e3)
* collect
    将数据汇集到driver节点上来,结果是一个数组
* collectPartitions
    将数据汇集到driver节点上来,为每一个分区产生一个数组,结果是要给二维数组
* count():Long
* first()
* taskSample(withReplacement,num,seed)
    该方法需要将所有的数据都拉到driver端
* take(n)
* takeOrdered(n,[ordering])
    返回前几行数据并且排序
* saveAsTextFile(path)
    val rdd=sc.parallelize(1 to 100,5)
    rdd.saveAsTextFile("D:/data/3")
    生成的文件
    2020/01/11  23:13                12 .part-00000.crc
    2020/01/11  23:13                12 .part-00001.crc
    2020/01/11  23:13                12 .part-00002.crc
    2020/01/11  23:13                12 .part-00003.crc
    2020/01/11  23:13                12 .part-00004.crc
    2020/01/11  23:13                 8 ._SUCCESS.crc
    2020/01/11  23:13                51 part-00000
    2020/01/11  23:13                60 part-00001
    2020/01/11  23:13                60 part-00002
    2020/01/11  23:13                60 part-00003
    2020/01/11  23:13                61 part-00004
* saveAsSequenceFile(path)
* saveAsObjectFile(path)
* countByKey()
* foreach(fun(e))

    





* reduce归约操作
* reduceByKey对所有相同的key做归约操作
* groupByKey
去重的并集
select * from a union select * from b;
没去重的并集
select * from a union all select * from b;
差集
select * from a except select * from b;
distinct	去重	(k,v),去重时相同的key不同的value是不同的数据,只有key和value都相同才去掉
filter		过滤		rdd1.filter(_._2>2)  		rdd.filter(x => x._2==2)
groupBy(Function)
按照给定的函数进行分组
groupBy(_%2)按照模2的值进行分组,所以只有两组,一组的值为0,另一个为1
groupByKey
	for(s:data){
		if(map[s.key]!=null){
			map[s.key]=(map[s.key],s.value)
		}else{
			map[s.key]=(map[s.key])
		}
	}
cogroup		两个数据共同的分组
		先把两个数据集的所有key去重得到不同的值
		在每一个不同的值后面加上帝一个数据集中和他相同的值
		在第二个数据及中加上和他讲通的值
		rdd1(List((tom,1),(jerry,2),(jerry,3),(shuke,4)
		rdd2(List((tom,1),(jerry,4),(kitty,5))
		rdd1.cogroup(rdd2)
		
		tom,jerry,shuke,kitty
		
		tom,(1),(1)
		jerry,(2,3),(4)
		shuke,(4),()
		kitty,(),(5)
mapValues		对value进行map操作不对key操作
reduce		reduce将RDD中元素前两个传给输入函数，产生一个新的return值，新产生的return值与RDD中下一个元素（第三个元素）组成两个元素，再被传给输入函数，直到最后只有一个值为止。
Cartesian笛卡尔积
1、Except返回两个结果集的差（即从左查询中返回右查询没有找到的所有非重复值）。
Returns a new Dataset containing rows in this Dataset but not in another Dataset.
* def textFile(
        path: String,
        minPartitions: Int = defaultMinPartitions): RDD[String] = withScope {
    def defaultMinPartitions: Int = math.min(defaultParallelism, 2)
    没指定的话分区为默认并行度和2的最小值,通常是2
    但第一个参数path也可以用目录,那么如果目录下又多个文件分区数如何算?
    不指定分区参数的情况下
    1. 一个605M两个7M的文件最后有了21个Task
    605/32~=18.9=19
    两个文件各一个Task
    2. 单独两个7M的文件最后有了2个Task
    也就是一个文件只要不达到spark的读取一个分区的最大数据那么就一个分区
    如果达到了就将该文件划分为多个分区
    如果指定了分区数为3
    表现行为暂时未得出规律------源码在computeSize相关方法和HDFS计算splitSize中,InputFormat的getSplits
    