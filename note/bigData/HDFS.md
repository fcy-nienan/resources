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
* FileStatus    
    Interface that represents the client side information for a file.
    代表客户端的文件信息(文件的一些元数据和安全信息)
    元数据包括:文件名,大小,是否目录,相关时间,存储策略,符号链接
    权限:类似Linux权限
* BlockLocation  
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
* Mapper
    Mapper的核心方法,主要看run方法,从context中获取一行记录,然后对其调用我们自己写的map方法
    setup和cleanup方法只调用一次
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
* Reducer
    
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
            // If a back up store is used, reset it
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
## 以上两个基础结构就是文件的本身信息文件块在网络中的信息
    将其分离一下就是四方面的信息
    文件元数据(metedata)
    权限
    网络地址   
    存储方式(虽然定义了一系列的枚举值,但默认是磁盘)