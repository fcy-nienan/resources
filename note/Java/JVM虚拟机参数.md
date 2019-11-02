+ -XX:+HeapDumpOnOutOfMemoryError在发生内存溢出的时候生成内存快照
+ -XX:HeapDumpPath指定内存快照的文件路径
+ -XX:OnOutOfMemoryError在发生内存溢出的时候执行相应的指令
+ -XX:InitialCodeCacheSize初始化JIT编译的代码缓存大小
+ -XX:ReservedCodeCacheSize保留的代码缓存大小
+ -XX:+UseCodeCacheFlushing当代码缓存空间不够的时候丢弃掉一部分已经存在的内容
+ -XX:SoftRefLRUPolicyMSPerMB=50每兆空间无其他引用的软引用离上一次被引用多久才会被回收


