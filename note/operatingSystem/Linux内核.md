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
    
    