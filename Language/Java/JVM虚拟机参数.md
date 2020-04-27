+ -XX:+HeapDumpOnOutOfMemoryError在发生内存溢出的时候生成内存快照
+ -XX:HeapDumpPath指定内存快照的文件路径
+ -XX:OnOutOfMemoryError在发生内存溢出的时候执行相应的指令
+ -XX:InitialCodeCacheSize初始化JIT编译的代码缓存大小
+ -XX:ReservedCodeCacheSize保留的代码缓存大小
+ -XX:+UseCodeCacheFlushing当代码缓存空间不够的时候丢弃掉一部分已经存在的内容
+ -XX:SoftRefLRUPolicyMSPerMB=50每兆空间无其他引用的软引用离上一次被引用多久才会被回收
+ -XX:+PrintGC 输出GC日志
+ -XX:+PrintGCDetails 输出GC的详细日志
+ -XX:+PrintGCTimeStamps 输出GC的时间戳（以基准时间的形式）
+ -XX:+PrintGCDateStamps 输出GC的时间戳（以日期的形式，如 2013-05-04T21:53:59.234+0800）
+ -XX:+PrintHeapAtGC 在进行GC的前后打印出堆的信息
+ -Xloggc:../logs/gc.log 日志文件的输出路径
+ XX:+MaxTenuringThreshold对象存活多少次gc进入老年代,默认15
+ java -verbose:class		查看类加载情况
+ java -verbose:gc			查看GC运行情况
+ java -verbose:jni			查看JNI运行情况
+ -javaagent  符合规范的写一些在主方法之前运行的代码
+ -Xms                    堆初始化内存
+ -Xmx                    堆最大内存
+ -Xmn                    新生代的内存大小
+ -Xss                    线程堆栈大小
+ -XX:NewSize             新生代初始值
+ -XX:MaxNewSize          新生代最大值
+ -XX:SurvivorRatio=8     Eden区和Survivor的比值8:1:1
+ -XX:PermSize            方法区初始值
+ -XX:MaxPermSize         方法区最大值
+ -XX:MetaspaceSize
+ -XX:MaxMetaspaceSize
+ -XX:NewRatio=4          新生代与老年代1:4
+ -XX:PretenureSizeThreshold对象超过多大直接进老年代
+ -XX:+UseSerialGC	    串行垃圾回收器
+ -XX:+UseParallelGC	并行垃圾回收器
+ -XX:+UseConcMarkSweepGC	并发标记扫描垃圾回收器
+ -XX:ParallelCMSThreads=	并发标记扫描垃圾回收器 =为使用的线程数量
+ -XX:+UseG1GC	        G1垃圾回收器
+ -XX:+UseCMSCompactAtFullCollection:打开对年老代的压缩.可能会影响性能,但是可以消除碎片
+ -Djava.compiler=none关闭jit编译
+ -XX:+UseCMSCompactAtFullCollection：使用并发收集器时，开启对年老代的压缩
+ -XX:CMSFullGCsBeforeCompaction=0：上面配置开启的情况下，这里设置多少次Full GC后，对年老代进行压缩
+ -XX:+DisableExplicitGC可以让System.gc()不起作用。
+ -XX:+PrintFlagsInitial与-XX:+PrintFlagsFinal  打印默认参数值
+ -XX:+PrintCommandLineFlags参数
+ 开启(-XX:+UseCompressedOops) 可以压缩指针。 
+ 关闭(-XX:-UseCompressedOops) 可以关闭压缩指针。 
+ -Djava.compiler=none关闭JIT编译
+ -XX:+PrintCompilation参数，你可以在log文件中看到方法被JIT编译时的信息
+ -ea开启断言
+ -XX:+TraceClassLoading打印加载的类
+ -XX:hashCode选择使用哪种hash算法
