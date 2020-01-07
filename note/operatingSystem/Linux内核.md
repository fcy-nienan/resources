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
    
    优点肯定是读取更快了
    但并不是所有地方都一定要用mmap,任何一种技术都有其适用场景
>>mmap对变长文件不适合,如果更新文件的操作很多，mmap避免两态拷贝的优势就被摊还，最终还是落在了大量的脏页回写及由此引发的随机IO上.　所以在随机写很多的情况下，mmap方式在效率上不一定会比带缓冲区的一般写快.
    
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
    fdatasync和fsync差不多，
    but do not flush modified metadata unless  that  metadata  is
    needed  in order to allow a subsequent data retrieval to be correctly handled
    fdatasync不刷新更新一类的元数据,比如Linux的几个时间
    除非需要这个元数据以便正确处理后续的数据检索,比如文件长度一类的元数据需要更新
    msync:synchronize a file with a memory map
    这个是mmap的将数据同步到磁盘
    flushes changes made to the in-core copy of a file that was mapped into memory using mmap(2)
    back to disk
    将由mmap建立的映射数据的改动刷新到磁盘
# Linux数据结构
## file
    Each open file, socket etcetera is represented by a file data structure.
    struct file {
      mode_t f_mode;
      loff_t f_pos;
      unsigned short f_flags;
      unsigned short f_count;
      unsigned long f_reada, f_ramax, f_raend, f_ralen, f_rawin;
      struct file *f_next, *f_prev;
      int f_owner;         /* pid or -pgrp where SIGIO should be sent */
      struct inode * f_inode;
      struct file_operations * f_op;
      unsigned long f_version;
      void *private_data;  /* needed for tty driver, and maybe others */
    };
## files_struct
    The files_struct data structure describes the files that a process has open.
    struct files_struct {
      int count;
      fd_set close_on_exec;
      fd_set open_fds;
      struct file * fd[NR_OPEN];
    };
## inode
    The VFS inode data structure holds information about a file or directory on disk.
    struct inode {
        kdev_t                       i_dev;
        unsigned long                i_ino;
        umode_t                      i_mode;
        nlink_t                      i_nlink;
        uid_t                        i_uid;
        gid_t                        i_gid;
        kdev_t                       i_rdev;
        off_t                        i_size;
        time_t                       i_atime;
        time_t                       i_mtime;
        time_t                       i_ctime;
        unsigned long                i_blksize;
        unsigned long                i_blocks;
        unsigned long                i_version;
        unsigned long                i_nrpages;
        struct semaphore             i_sem;
        struct inode_operations      *i_op;
        struct super_block           *i_sb;
        struct wait_queue            *i_wait;
        struct file_lock             *i_flock;
        struct vm_area_struct        *i_mmap;
        struct page                  *i_pages;
        struct dquot                 *i_dquot[MAXQUOTAS];
        struct inode                 *i_next, *i_prev;
        struct inode                 *i_hash_next, *i_hash_prev;
        struct inode                 *i_bound_to, *i_bound_by;
        struct inode                 *i_mount;
        unsigned short               i_count;
        unsigned short               i_flags;
        unsigned char                i_lock;
        unsigned char                i_dirt;
        unsigned char                i_pipe;
        unsigned char                i_sock;
        unsigned char                i_seek;
        unsigned char                i_update;
        unsigned short               i_writecount;
        union {
            struct pipe_inode_info   pipe_i;
            struct minix_inode_info  minix_i;
            struct ext_inode_info    ext_i;
            struct ext2_inode_info   ext2_i;
            struct hpfs_inode_info   hpfs_i;
            struct msdos_inode_info  msdos_i;
            struct umsdos_inode_info umsdos_i;
            struct iso_inode_info    isofs_i;
            struct nfs_inode_info    nfs_i;
            struct xiafs_inode_info  xiafs_i;
            struct sysv_inode_info   sysv_i;
            struct affs_inode_info   affs_i;
            struct ufs_inode_info    ufs_i;
            struct socket            socket_i;
            void                     *generic_ip;
        } u;
    }; 
## mem_map_t
    The mem_map_t data structure (also known as page) is used to hold information about each page of physical memory.
    typedef struct page {
      /* these must be first (free area handling) */
      struct page        *next;
      struct page        *prev;
      struct inode       *inode;
      unsigned long      offset;
      struct page        *next_hash;
      atomic_t           count;
      unsigned           flags;     /* atomic flags, some possibly 
                                       updated asynchronously */
      unsigned           dirty:16,
                         age:8;
      struct wait_queue  *wait;
      struct page        *prev_hash;
      struct buffer_head *buffers;
      unsigned long      swap_unlock_entry;
      unsigned long      map_nr;    /* page->map_nr == page - mem_map */
    } mem_map_t;
## mm_struct
    The mm_struct data structure is used to describe the virtual memory of a task or process.
    struct mm_struct {
      int count;
      pgd_t * pgd;
      unsigned long context;
      unsigned long start_code, end_code, start_data, end_data;
      unsigned long start_brk, brk, start_stack, start_mmap;
      unsigned long arg_start, arg_end, env_start, env_end;
      unsigned long rss, total_vm, locked_vm;
      unsigned long def_flags;
      struct vm_area_struct * mmap;
      struct vm_area_struct * mmap_avl;
      struct semaphore mmap_sem;
    }; 
# task_struct
    Each task_struct data structure describes a process or task in the system.
    struct task_struct {
    /* these are hardcoded - don't touch */
      volatile long        state;          /* -1 unrunnable, 0 runnable, >0 stopped */
      long                 counter;
      long                 priority;
      unsigned             long signal;
      unsigned             long blocked;   /* bitmap of masked signals */
      unsigned             long flags;     /* per process flags, defined below */
      int errno;
      long                 debugreg[8];    /* Hardware debugging registers */
      struct exec_domain   *exec_domain;
    /* various fields */
      struct linux_binfmt  *binfmt;
      struct task_struct   *next_task, *prev_task;
      struct task_struct   *next_run,  *prev_run;
      unsigned long        saved_kernel_stack;
      unsigned long        kernel_stack_page;
      int                  exit_code, exit_signal;
      /* ??? */
      unsigned long        personality;
      int                  dumpable:1;
      int                  did_exec:1;
      int                  pid;
      int                  pgrp;
      int                  tty_old_pgrp;
      int                  session;
      /* boolean value for session group leader */
      int                  leader;
      int                  groups[NGROUPS];
      /* 
       * pointers to (original) parent process, youngest child, younger sibling,
       * older sibling, respectively.  (p->father can be replaced with 
       * p->p_pptr->pid)
       */
      struct task_struct   *p_opptr, *p_pptr, *p_cptr, 
                           *p_ysptr, *p_osptr;
      struct wait_queue    *wait_chldexit;  
      unsigned short       uid,euid,suid,fsuid;
      unsigned short       gid,egid,sgid,fsgid;
      unsigned long        timeout, policy, rt_priority;
      unsigned long        it_real_value, it_prof_value, it_virt_value;
      unsigned long        it_real_incr, it_prof_incr, it_virt_incr;
      struct timer_list    real_timer;
      long                 utime, stime, cutime, cstime, start_time;
    /* mm fault and swap info: this can arguably be seen as either
       mm-specific or thread-specific */
      unsigned long        min_flt, maj_flt, nswap, cmin_flt, cmaj_flt, cnswap;
      int swappable:1;
      unsigned long        swap_address;
      unsigned long        old_maj_flt;    /* old value of maj_flt */
      unsigned long        dec_flt;        /* page fault count of the last time */
      unsigned long        swap_cnt;       /* number of pages to swap on next pass */
    /* limits */
      struct rlimit        rlim[RLIM_NLIMITS];
      unsigned short       used_math;
      char                 comm[16];
    /* file system info */
      int                  link_count;
      struct tty_struct    *tty;           /* NULL if no tty */
    /* ipc stuff */
      struct sem_undo      *semundo;
      struct sem_queue     *semsleeping;
    /* ldt for this task - used by Wine.  If NULL, default_ldt is used */
      struct desc_struct *ldt;
    /* tss for this task */
      struct thread_struct tss;
    /* filesystem information */
      struct fs_struct     *fs;
    /* open file information */
      struct files_struct  *files;
    /* memory management info */
      struct mm_struct     *mm;
    /* signal handlers */
      struct signal_struct *sig;
    #ifdef __SMP__
      int                  processor;
      int                  last_processor;
      int                  lock_depth;     /* Lock depth. 
                                              We can context switch in and out
                                              of holding a syscall kernel lock... */  
    #endif   
    };