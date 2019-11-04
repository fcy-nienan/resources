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


