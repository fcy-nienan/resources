	1.num-executors		executor的数量
　　2.executor-memory	executor的内存
　　3.executor-cores	executor中task的数量
　　4.driver-memory		driver端的内存，如果是collect一类的action则需要调大点
　　5.spark.default.parallelism
　　6.spark.storage.memoryFraction
　　7.spark.shuffle.memoryFraction

driver  worker  executor  job  stage  task
每个Worker上存在一个或多个CoarseGrainedExecutorBackend进程，每个进程包含一个Executor对象，该对象持有一个线程池，每个线程池可以执行一个Task

  （5+4）/9:

  9:当前stage的task的数量，5：已完成的task数量，4：等待执行的task数量。

RDD分为两种操作
transfer和action
转换和具体的操作

shuffle操作
shuffle是Spark将多个分区的数据重新分组重新分布数据的机制。
shuffle是一个复杂且代价较高的操作，它需要完成将数据在executor和机器节点之间进行复制的工作

在Yarn的NodeManager节点上启动一个map task或者reduce task，
在物理上启动的是一个jvm进程；而Spark的task是Executor进程中的一个线程。

通过action出发job
通过宽窄以来划分stage


job,stage,task
job是我们提交的应用程序
stage是根据我们提交的程序中的宽窄依赖划分的
task是根据输入数据的分区数指定的

多个不同stage之间可以同时执行吗?
不可以,stage之间是有执行顺序的,只有上一个执行完了才能执行下一个



select * from a union select * from b;
去重的并集
select * from a union all select * from b;
没去重的并集
select * from a except select * from b;
差集



distinct	去重	(k,v),去重时相同的key不同的value是不同的数据,只有key和value都相同才去掉
map			映射
filter		过滤		rdd1.filter(_._2>2)  		rdd.filter(x => x._2==2)

join		内连接
for(t:data1){
	for(s:data2){
		if(t.k==s.k){
			t.k,(t.v,s.v)
		}
	}
}
leftOuterJoin		左外连接
rightOuterJoin		又外连接

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
Intel(R) Core(TM) i5-5200U CPU @ 2.20GHz

电脑物理CPU个数		1
每个CPU的核数		2
核只不支持超线程	2

处理器数量				2
每个处理器的内核数量	2



centos是基于redHat的

this should work


一个程序有多个job
一个job有多个stage
一个stage有多个task

总task数量=jobNum*stageNum*taskNum;就是所有task相加的数量


RDD
属性
a list of partitions
a function for computing each split
a list of dependencies on other rdds
optionally a partitioner for key-value rdds
optionally a list of preferred location to compute each slit on
分区
算子
父依赖
分区器
计算优先位置




现在回头看，RDD本身就是一个Berkeley的博士们在写论文时，抽象出的概念，
其本质与Hadoop MapReduce处理时输入输出的key-value，Flink的dataset没有本质区别。
处理时，任然使用iterator一边载入部分数据，
一边执行运算（每个partition的实现内部实际就是一个iterator），没必要纠结这个概念

如果用户直接运行bin/spark-sql命令。会导致我们的元数据有两种状态：

1、in-memory状态:

  如果SPARK-HOME/conf目录下没有放置hive-site.xml文件，元数据的状态就是in-memory

2、hive状态：

 如果我们在SPARK-HOME/conf目录下放置了，hive-site.xml文件，那么默认情况下

 spark-sql的元数据的状态就是hive.






# spark-shell

  spark-shell --name fcy local[6]

  --master MASTER_URL         spark://host:port, mesos://host:port, yarn,
                              k8s://https://host:port, or local (Default: local[*]).
  --deploy-mode DEPLOY_MODE   Whether to launch the driver program locally ("client") or
                              on one of the worker machines inside the cluster ("cluster")
                              (Default: client).
  --class CLASS_NAME          Your application's main class (for Java / Scala apps).
  --name NAME                 A name of your application.
  --jars JARS                 Comma-separated list of jars to include on the driver
                              and executor classpaths.
  --packages                  Comma-separated list of maven coordinates of jars to include
                              on the driver and executor classpaths. Will search the local
                              maven repo, then maven central and any additional remote
                              repositories given by --repositories. The format for the
                              coordinates should be groupId:artifactId:version.
  --exclude-packages          Comma-separated list of groupId:artifactId, to exclude while
                              resolving the dependencies provided in --packages to avoid
                              dependency conflicts.
  --repositories              Comma-separated list of additional remote repositories to
                              search for the maven coordinates given with --packages.
  --py-files PY_FILES         Comma-separated list of .zip, .egg, or .py files to place
                              on the PYTHONPATH for Python apps.
  --files FILES               Comma-separated list of files to be placed in the working
                              directory of each executor. File paths of these files
                              in executors can be accessed via SparkFiles.get(fileName).

  --conf PROP=VALUE           Arbitrary Spark configuration property.
  --properties-file FILE      Path to a file from which to load extra properties. If not
                              specified, this will look for conf/spark-defaults.conf.

  --driver-memory MEM         Memory for driver (e.g. 1000M, 2G) (Default: 1024M).
  --driver-java-options       Extra Java options to pass to the driver.
  --driver-library-path       Extra library path entries to pass to the driver.
  --driver-class-path         Extra class path entries to pass to the driver. Note that
                              jars added with --jars are automatically included in the
                              classpath.

  --executor-memory MEM       Memory per executor (e.g. 1000M, 2G) (Default: 1G).

  --proxy-user NAME           User to impersonate when submitting the application.
                              This argument does not work with --principal / --keytab.

  --help, -h                  Show this help message and exit.
  --verbose, -v               Print additional debug output.
  --version,                  Print the version of current Spark.

 Cluster deploy mode only:
  --driver-cores NUM          Number of cores used by the driver, only in cluster mode
                              (Default: 1).

 Spark standalone or Mesos with cluster deploy mode only:
  --supervise                 If given, restarts the driver on failure.
  --kill SUBMISSION_ID        If given, kills the driver specified.
  --status SUBMISSION_ID      If given, requests the status of the driver specified.

 Spark standalone and Mesos only:
  --total-executor-cores NUM  Total cores for all executors.

 Spark standalone and YARN only:
  --executor-cores NUM        Number of cores per executor. (Default: 1 in YARN mode,
                              or all available cores on the worker in standalone mode)

 YARN-only:
  --queue QUEUE_NAME          The YARN queue to submit to (Default: "default").
  --num-executors NUM         Number of executors to launch (Default: 2).
                              If dynamic allocation is enabled, the initial number of
                              executors will be at least NUM.
  --archives ARCHIVES         Comma separated list of archives to be extracted into the
                              working directory of each executor.
  --principal PRINCIPAL       Principal to be used to login to KDC, while running on
                              secure HDFS.
  --keytab KEYTAB             The full path to the file that contains the keytab for the
                              principal specified above. This keytab will be copied to
                              the node running the Application Master via the Secure
                              Distributed Cache, for renewing the login tickets and the
                              delegation tokens periodically.



































RDD是最早的概念

DataFrame是spark1.3之后提出的概念

DataSet是spark1.6之后提出的概念


DataFrame转换为RDD

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
## 算子
* reduce归约操作
* reduceByKey对所有相同的key做归约操作
* groupByKey


