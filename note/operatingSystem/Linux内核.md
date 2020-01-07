SMP对称多处理器架构
多个CPU共享主存和硬件资源
操作系统维护任务队列,每个处理器轮流处理
由于多个CPU共享资源,所以在每一个共享的环节都会成为瓶颈,扩展性差
由硬件和软件的锁机制去解决共享问题

read系统调用发生了什么?

Linux 内核有个机制叫OOM killer（Out-Of-Memory killer），该机制会监控那些占用内存过大，尤其是瞬间很快消耗大量内存的进程，为了防止内存耗尽而内核会把该进程杀掉


Linux进程知识
进程状态

#proc下各个目录文件详解
attr
autogroup
auxv
cgroup
clear_refs
cmdline     完整命令行
comm
coredump_filter
cpuset
cwd         工作目录
environ     当前进程的环境变量
exe         当前进程的可执行文件
fd          当前进程打开的文件列表
fdinfo
gid_map
io
limits      当前进程启动的受限制资源
loginuid
map_files
maps        当前进程关联的每个可执行文件和相关库文件在内存中的映射区域及访问权限列表
mem
mountinfo
mounts
mountstats
net
ns
numa_maps
oom_adj
oom_score
oom_score_adj
pagemap
personality
projid_map
root
sched
schedstat
sessionid
setgroups
smaps
stack
stat        当前进程运行的状态信息(可读性不好)
statm
status      当前进程运行的状态信息(可读性号)
syscall
task        当前进程中的所有线程
timers
uid_map
wchan
# MMAP原理
    传统的read调用数据的过程:磁盘-->内核pageCache-->用户空间
    MMAP调用数据的过程:磁盘-->内核pageCache
    read调用对我们来说只是将数据从内核复制到了用户空间
    而MMAP中我们可以直接读取pageCache的数据,直接操作内核中的数据
    相当于少了一个数据中转过程
    
    mmap比read快（高效率）的原因在于：read是系统调用，在通过了一系列函数调用后会返回用户空间。
    mmap也是系统调用，对于隐射后的地址是可以直接操作的。不再需要任何系统级别的功能来完成数据拷贝
    
    另外,映射这个词是内核中的地址空间和磁盘的数据的映射,建立映射的过程是不加载数据的
    只有当第一次访问的时候(比如Java中的get方法)造成缺页异常才开始读取数据到内存中
    读取也不是只读取一两个字节,而是按页的大小读取的
    
    映射的数据长度是页大小的整数倍,如果只填了6000,页大小4096,那么会有两页,前6000有数据,后2192没有数据
    读取后2192不会报错,但数据都是0
    
    如果文件大小为8000,映射了6000,生成了两页,那后面的能读取吗？
    6000,8000,8192
    前6000肯定能读取,6000--8000是填充0还是读取磁盘的原有数据?,8000-8192肯定都是0
    也就是对于不映射的区域,我磁盘有数据,内核读取的时候是读取原始数据还是填充0?
    
    相关操作
        Java:
        get()访问一个字节(引发缺页异常)
        force()将映射的内容更新到磁盘
        C:
        mmap返回的是指针,直接通过指针操作数据
        msync()
    
# sync
    传统的write系统调用只是将数据写入到了内核，此时数据还在内存中
    依靠操作系统的脏页回写将数据更新到磁盘上,write调用并不会等待回写完毕后才返回
    那么有什么办法可以调用write后立刻将数据同步到磁盘呢?(防止系统宕机造成数据丢失)
    调用fsync方法可以，在Java中是调用FileInputStream.getFD().sync()方法
    fsync阻塞直到所有脏页都回写到了磁盘才返回
      