dfs.datanode.https.address	0.0.0.0:9865	The datanode secure http server address and port.
dfs.namenode.https-address	0.0.0.0:9871	The namenode secure http server address and port.


dfs.namenode.http-address	0.0.0.0:9870	The address and the base port where the dfs namenode web ui will listen on.


dfs.namenode.secondary.http-address	0.0.0.0:9868	The secondary namenode http server address and port.
dfs.namenode.secondary.https-address	0.0.0.0:9869	The secondary namenode HTTPS server address and port.


dfs.datanode.address	0.0.0.0:9866	The datanode server address and port for data transfer.datanode之间数据传输的端口
dfs.datanode.http.address	0.0.0.0:9864	The datanode http server address and port. http端口
dfs.datanode.ipc.address	0.0.0.0:9867	The datanode ipc server address and port.  


dfs.namenode.lifeline.rpc-address		NameNode RPC lifeline address. This is an optional separate RPC address that can be used to isolate health checks and liveness to protect against resource exhaustion in the main RPC handler pool. In the case of HA/Federation where multiple NameNodes exist, the name service ID is added to the name e.g. dfs.namenode.lifeline.rpc-address.ns1. The value of this property will take the form of nn-host1:rpc-port. If this property is not defined, then the NameNode will not start a lifeline RPC server. By default, the property is not defined.

dfs.namenode.servicerpc-address		RPC address for HDFS Services communication. BackupNode, Datanodes and all other services should be connecting to this address if it is configured. In the case of HA/Federation where multiple namenodes exist, the name service id is added to the name e.g. dfs.namenode.servicerpc-address.ns1 dfs.namenode.rpc-address.EXAMPLENAMESERVICE The value of this property will take the form of nn-host1:rpc-port. If the value of this property is unset the value of dfs.namenode.rpc-address will be used as the default.

dfs.namenode.rpc-address		RPC address that handles all clients requests. In the case of HA/Federation where multiple namenodes exist, the name service id is added to the name e.g. dfs.namenode.rpc-address.ns1 dfs.namenode.rpc-address.EXAMPLENAMESERVICE The value of this property will take the form of nn-host1:rpc-port. The NameNode's default RPC port is 8020.

yarn.resourcemanager.webapp.address	${yarn.resourcemanager.hostname}:8088	The http address of the RM web application. If only a host is provided as the value, the webapp will be served on a random port.
yarn.resourcemanager.webapp.https.address	${yarn.resourcemanager.hostname}:8090	The https address of the RM web application. If only a host is provided as the value, the webapp will be served on a random port.


hdfs学习

edits_inprogress_0000000000000000001
fsimage_0000000000000000000
fsimage_0000000000000000000
seen_txid
VERSION

有fsimage文件,edits_inprogress文件
都是namenode的元信息

数据文件放在Dir\tmp\dfs\data\current\BP-1881367948-169.254.34.124-1562521903562\current\finalized\subdir0\subdir0目录下


分块是严格按照快大小分的




上传的文件为什么放在tmp目录下而不是指定的datanode目录下?




、HDFS页面：50070

2、YARN的管理界面：8088

3、HistoryServer的管理界面：19888

4、Zookeeper的服务端口号：2181

5、Mysql的服务端口号：3306

6、Hive.server1=10000

7、Kafka的服务端口号：9092

8、azkaban界面：8443

9、Hbase界面：16010,60010

10、Spark的界面：8080

11、Spark的URL：7077


hdfs查看命令行日志 HADOOP_ROOT_LOGGER=DEBUG,console hadoop fs -ls /

查看已使用容量
hadoop fs -du -h /



# HDFS相关数据结构信息
# FileStatus    
    Interface that represents the client side information for a file.
    是不是可以理解为Linux的inode节点的概念,存储文件的元信息
    代表客户端的文件信息(文件的一些元数据和安全信息)
    元数据包括:文件名,大小,是否目录,相关时间,存储策略,符号链接
    权限:类似Linux权限
# BlockLocation  
    Represents the network location of a block, information about the hosts
    that contain block replicas, and other block metadata (E.g. the file
    offset associated with the block, length, whether it is corrupt, etc).
    代表一个块在网络中的信息,BlockLocation(offset: 0, length: BLOCK_SIZE,hosts: {"host1:9866", "host2:9866, host3:9866"})
    private String[] hosts; // Datanode hostnames
    private String[] cachedHosts; // Datanode hostnames with a cached replica
    private String[] names; // Datanode IP:xferPort for accessing the block
    private String[] topologyPaths; // Full path name in network topology
    private String[] storageIds; // Storage ID of each replica
    private StorageType[] storageTypes; // Storage type of each replica
    private long offset;  // Offset of the block in the file
    private long length;
    private boolean corrupt;
    文件所在ip地址,主机名,每块一个id,网络拓扑结构的全路径,存储类型(磁盘或者内存等),偏移量,是否损坏,还有一系列的安全(认证信息)
## 以上两个基础结构就是文件的本身信息文件块在网络中的信息
    将其分离一下就是下面几个信息
    文件元数据(metedata)
    权限
    网络地址   
    存储方式(虽然定义了一系列的枚举值,但默认是磁盘)
<<<<<<< HEAD
# Secondary NameNode
周期性的合并edit到fimage,较少namenode启动时间
Secondary namenode is just a helper for Namenode.
It gets the edit logs from the namenode in regular intervals and applies to fsimage.
Once it has new fsimage, it copies back to namenode.
Namenode will use this fsimage for the next restart, which will reduce the startup time.
Secondary Namenode's whole purpose is to have a checkpoint in HDFS. Its just a helper node for namenode. That’s why it also known as checkpoint node.
# standby namenode
当activeNameNode挂了的时候自动切换到standby namenode
merging fsimage and edits-log files. (Secondary-namenode's work)
receive online updates of the file system meta-data, apply them to its memory state and persist them on disks just like the name-node does.
Thus at any time the Backup node contains an up-to-date image of the namespace both in memory and on local disk(s).
Cluster will switch over to the new name-node (this standby-node) if the active namenode dies.
# Checkpoint Node
周期性的创建检查点,从activeNameNode下载fsimage和edit log并合并他们,然后再上传到activiNameNode
# BackupNode
功能和checkpoint node差不多
但他不需要从activeNameNode下载元数据
=======
# InputFormat
>InputFormat</code> describes the input-specification for a Map-Reduce job.
* 描述了一个MR任务的输入规范?
# InputSplit
>InputSplit</code> represents the data to be processed by an individual {@link Mapper}. 
* 代表由单个的Mapper处理的数据
# RecordReader  
>The record reader breaks the data into key/value pairs for input to the {@link Mapper}
* 将数据切分为key/value对作为Mapper的输入
# Mapper
* Mapper的核心方法,主要看run方法,从context中获取一行记录,然后对其调用我们自己写的map方法,setup和cleanup方法只调用一次
```
    public class Mapper<KEYIN, VALUEIN, KEYOUT, VALUEOUT> {
    
      /**
       * The <code>Context</code> passed on to the {@link Mapper} implementations.
       */
      public abstract class Context
        implements MapContext<KEYIN,VALUEIN,KEYOUT,VALUEOUT> {
      }
      
      /**
       * Called once at the beginning of the task.
       */
      protected void setup(Context context
                           ) throws IOException, InterruptedException {
        // NOTHING
      }
    
      /**
       * Called once for each key/value pair in the input split. Most applications
       * should override this, but the default is the identity function.
       */
      @SuppressWarnings("unchecked")
      protected void map(KEYIN key, VALUEIN value, 
                         Context context) throws IOException, InterruptedException {
        context.write((KEYOUT) key, (VALUEOUT) value);
      }
    
      /**
       * Called once at the end of the task.
       */
      protected void cleanup(Context context
                             ) throws IOException, InterruptedException {
        // NOTHING
      }
      
      /**
       * Expert users can override this method for more complete control over the
       * execution of the Mapper.
       * @param context
       * @throws IOException
       */
      public void run(Context context) throws IOException, InterruptedException {
        setup(context);
        try {
          while (context.nextKeyValue()) {
            map(context.getCurrentKey(), context.getCurrentValue(), context);
          }
        } finally {
          cleanup(context);
        }
      }
    }
```
# Reducer
    同样有setup和cleanup方法,在run方法中也可以看出只调用一次,另外reducer处理的value是一个迭代器
    默认使用的是HashPartitioner哈希分区,将相同的key分配到了一个reducer处理
    source: java go java scala go c scala
    Map:    (java,1),(go,1),(java,1),(scala,1),(go,1),(c,1),(scala,1)
    HasPartitioner: (java,(1,1)),(go,(1,1)),(scala,(1,1)),(c,(1))
    Reducer:    reducer的输入就是上述结果的输出
## 如果不设置的话默认就是哈希分区器 
```
    /**
       * Get the {@link Partitioner} class for the job.
       *
       * @return the {@link Partitioner} class for the job.
       */
      @SuppressWarnings("unchecked")
      public Class<? extends Partitioner<?,?>> getPartitionerClass() 
         throws ClassNotFoundException {
        return (Class<? extends Partitioner<?,?>>) 
          conf.getClass(PARTITIONER_CLASS_ATTR, HashPartitioner.class);
      }
```
## 哈希分区器也简单,就是使用key的hashcode AND 整型的最大值然后根据reducer的数量取余
```
    /** Partition keys by their {@link Object#hashCode()}. */
    @InterfaceAudience.Public
    @InterfaceStability.Stable
    public class HashPartitioner<K, V> extends Partitioner<K, V> {
    
      /** Use {@link Object#hashCode()} to partition. */
      public int getPartition(K key, V value,
                              int numReduceTasks) {
        return (key.hashCode() & Integer.MAX_VALUE) % numReduceTasks;
      }
    
    }
```
```
    public class Reducer<KEYIN,VALUEIN,KEYOUT,VALUEOUT> {
    
      /**
       * The <code>Context</code> passed on to the {@link Reducer} implementations.
       */
      public abstract class Context 
        implements ReduceContext<KEYIN,VALUEIN,KEYOUT,VALUEOUT> {
      }
    
      /**
       * Called once at the start of the task.
       */
      protected void setup(Context context
                           ) throws IOException, InterruptedException {
        // NOTHING
      }
    
      /**
       * This method is called once for each key. Most applications will define
       * their reduce class by overriding this method. The default implementation
       * is an identity function.
       */
      @SuppressWarnings("unchecked")
      protected void reduce(KEYIN key, Iterable<VALUEIN> values, Context context
                            ) throws IOException, InterruptedException {
        for(VALUEIN value: values) {
          context.write((KEYOUT) key, (VALUEOUT) value);
        }
      }
    
      /**
       * Called once at the end of the task.
       */
      protected void cleanup(Context context
                             ) throws IOException, InterruptedException {
        // NOTHING
      }
    
      /**
       * Advanced application writers can use the 
       * {@link #run(org.apache.hadoop.mapreduce.Reducer.Context)} method to
       * control how the reduce task works.
       */
      public void run(Context context) throws IOException, InterruptedException {
        setup(context);
        try {
          while (context.nextKey()) {
            reduce(context.getCurrentKey(), context.getValues(), context);
            // If a back up store is used, reset it(备份存储,重置它?)
            //This method is called when the reducer moves from one key to another.
            //resetBackupStore方法干啥的？当一个reducer从一个键移动到另一个调用该方法
            Iterator<VALUEIN> iter = context.getValues().iterator();
            if(iter instanceof ReduceContext.ValueIterator) {
              ((ReduceContext.ValueIterator<VALUEIN>)iter).resetBackupStore();        
            }
          }
        } finally {
          cleanup(context);
        }
      }
    }
```
## 分区器在哪里别调用呢,shuffle的那一部分是如何处理的呢?

# MapReducer的过程
## Input Files
输入文件格式可以是任意的,一行一行的日志文件或者日志文件
## InputFormat
InputFormat定义了如何拆分和读取这些文件。可以以文件或者一些对象作为输入,数据的来源很多
可以在各类文件系统的文件中,数据库中,网络中,文件的格式也大不相同
所以在此层做了一个抽象
InputFormat会生成InputSplit

Input Format的两个方法
List<InputSplit> getSplit(JobContext context)
RecordReader createRecordReader(InputSplit split,TaskAttemptContext con)
## InputSplit
它代表可以被单个Mapper任务处理的数据,对于每一个InputSplit会创建一个map task
这个就是文件的一部分数据,在Map Reduce层面被单独的一个Mapper处理的数据
他只是个数据的逻辑表示,看其实现类也只是记录了一些start,len等信息
也就是该部分数据从哪开始，到哪结束，在哪里
The main thing to focus is that InputSplit doesn’t contain actual data; it is just a reference to the data

## RecordReader
它和InputSplit通信直到完成文件的读取。并且将数据转换为适合Mapper读取的key-value对。
默认情况下使用TextInputFormat。它为每一行赋值一个字节偏移量。然后这些key-value对会被发送
到mapper被进一步处理
Input Split只是数据，但MapperReducer处理的是键值对，所以需要将数据
转化为key-value格式，Record Reader做的就是这个工作

A RecordReader converts the byte-oriented view of the input to a record-oriented view for the Mapper and Reducer tasks for processing.
将面向字节的视图转换为面向记录的视图

Now before processing starts, it needs to know on which data to process. So, InputFormat class helps to achieve this. This class selects the file from HDFS that is the input to the map function. It is also responsible for creating the input splits.  Also, divide them into records. It divides the data into the number of splits (typically 64/128mb) in HDFS. This is known as InputSplit. InputSplit is the logical representation of data. In a MapReduce job, execution number of map tasks is equal to the number of InputSplits.

Although it is not mandatory for RecordReader to stays in between the boundaries created by the inputsplit to generate key-value pairs it usually stays. Also, custom implementation can even read more data outside of the inputsplit.
It is more than iterator over the records. The map task uses one record to generate key-value pair which it passes to the map function. We can also see this by using the mapper’s run function given below:
    public void run(Context context ) throws IOException, InterruptedException{
        setup(context);
        while(context.nextKeyValue()){
            map(context.setCurrentKey(),context.getCurrentValue(),context)
        }
        cleanup(context);
    }
Although it is not mandatory for RecordReader to stays in between the boundaries created by the inputsplit to generate key-value pairs it usually stays. Also, custom implementation can even read more data outside of the inputsplit.
Then, after running setup(), the nextKeyValue() will repeat on the context. This populates the key and value objects for the mapper. By way of context, framework retrieves key-value from record reader. Then pass to the map() method to do its work. Hence, input (key-value) to the map function processes as per the logic mentioned in the map code. When the record gets to the end of the record, the nextKeyValue() method returns false.

## Mapper
它处理由RecordReader产生的记录并且生成中间的key-value对。
Hadoop并不存储Mapper的输出到HDFS上，Mapper将输出传递给COmbiner被进一步处理
## Combiner
这是一个小型的Reducer,在本地对Mapper的输出执行聚合操作，它尽可能的缩小
在Mapper和Reducer中间传输的数据，Combiner的输出作为Partitioner的输入
## Partitioner
分区器将Combiner的输出作为输入,然后根据key计算hash值,对该值取余,
最后在每个分区存在这相同的key,在那之后,每个分区的数据发送到一个Reducer

The important thing to notice is that the framework creates partitioner only when there are many reducers.

## Shuffling and Sorting
The process of transferring data from the mappers to reducers is shuffling
从mapper传输数据到reducer的过程是shuffle
 It is also the process by which the system performs the sort
还有对key进行排序
他不对values进行排序，values是任意顺序的
那可以对values进行排序吗？
可以的，这个是Secondary Sorting in MapReduce技术，在传递数据给
Reducer之前对values进行排序
The important thing to note is that shuffling and sorting in Hadoop MapReduce are will not take place at all if you specify zero reducers (setNumReduceTasks(0)). If reducer is zero, then the MapReduce job stops at the map phase. And the map phase does not include any kind of sorting (even the map phase is faster).
      if (conf.getNumReduceTasks() == 0) {
        mapPhase = getProgress().addPhase("map", 1.0f);
      } else {
        // If there are reducers then the entire attempt's progress will be 
        // split between the map phase (67%) and the sort phase (33%).
        mapPhase = getProgress().addPhase("map", 0.667f);
        sortPhase  = getProgress().addPhase("sort", 0.333f);
      }    
## Reducer
框架将Reducer的输出存储在HDFS上
## RecordWriter
将Reducer的输出写入到文件中
## OutputFormat
定义了RecordWriter写这些key-value对的方式。提供了在HDFS上写文件的实例。

键值不是数据的固有属性
Keys value is not the intrinsic properties of the data
In MapReduce job execution, before sending data to the mapper, first convert it into key-value pairs
在发送数据到Mapper之前将数据转化为键值对

InputSplit – It is the logical representation of data which InputFormat generates. In MapReduce program it describes a unit of work that contains a single map task

In MapReduce job execution, the map function processes a certain key-value pair. Then emits a certain number of key-value pairs. The Reduce function processes the values grouped by the same key

Map Input by default takes the line offset as the key. The content of the line is value as Text. We can modify them; by using the custom input format.
## Map Only Job in MapReduce
Map-Only job in the Hadoop is the process in which mapper does all tasks. No task is done by the reducer. Mapper’s output is the final output.
Map做所有的工作
How to avoid Reduce Phase in MapReduce?
如何避免Reduce阶段？
By setting job.setNumreduceTasks(0) in the configuration in a driver we can avoid reduce phase.
优点是啥?
In MapReduce job execution in between map and reduces phases there is key, sort and shuffle phase. Shuffling –Sorting are responsible for sorting the keys in ascending order. Then grouping values based on the same keys. This phase is very expensive. If reduce phase is not required, we should avoid it. As avoiding reduce phase would eliminate sorting and shuffle phase as well. Therefore, this will also save network congestion. The reason is that in shuffling, an output of the mapper travels to reduce. And when the data size is huge, large data needs to travel to the reducer.

The output of the mapper is written to local disk before sending to reduce. But in map only job, this output is directly written to HDFS. This further saves time as well reduces cost.
在Map和Reduce之间有一个Shuffling和Sort的过程
这个过程消耗的资源非常昂贵，磁盘IO，网络IO
如果Reducer阶段不存在,那么自然可以避免Shuffle发生
>>>>>>> tmp
