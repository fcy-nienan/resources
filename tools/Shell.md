# vim

    vim查找上一个N,查找下一个n
    vim清空所有内容 dg   Esc+Shift+:+%d
    vim全局替换     :%s#ttt#kkk     将所有的ttt替换为kkk      #作为分隔符 %代表全局替换 s代表替换
    :set ff=unix
# shell输出带颜色
```
red=`tput setaf 1`
green=`tput setaf 2`
reset=`tput sgr0`
echo "${red}red text ${green}green text${reset}"
```
# 查看占用端口

lsof -i:3000

# 编码格式

    在vim中敲命令:set fileencoding即可显示当前文件编码格式
    在vim中敲命令:set fileencoding=utf-8即可将当前文件编码改为utf-8
    通过iconv命令将文件由GBK转为utf-8(必须指定原始文件和目标文件的编码格式和原始文件名和目标文件名)
    iconv -f GBK -t UTF-8 file1 -o file2
    如果控制台乱码先查看登录控制台的软件是否有编码格式的设置,
    如果不存在或者设置了并且重新连接了也无效可以通过export LANG=en_US.UTF-8命令设置      
# locale

    代表某一地域内的人们的语言习惯和传统
    /etc/sysconfig/i18n/
    /usr/lib/locale/
    /usr/share/i18n/locales/
    /usr/share/i18n/charmaps/
    locale -a 查看所有字符集
    locale      查看与之有关的变量
    LANG
    LC_CTYPE    分类
    LC_NUMERIC  数字
    LC_COLLATE  比较和排序习惯
    LC_TIME     时间显示格式
    LC_MONETARY 货币单位
    LC_MESSAGES 信息
    LC_NAME     姓名书写方式
    LC_ADDRESS  地址书写方式
    LC_TELEPHONE    电话号码书写方式
    LC_MEASUREMENT  度量衡
    LC_PAPER        纸张尺寸大小
    LC_ALL
# 基础语法

    判断上一条命令是否执行成功 $?
    获取上一条命令执行结果 dir=`pwd` 或者dir=$(pwd)
    清空文件
    cat /dev/null > wordcount
    :>wordcount
    显示文件的全部信息(可显示换行)cat -v filename
    Linux文件权限后面的一个加号和一个点
    -rwx--xr-x+ root root    #只有ACL，没有selinux上下文
    -rw-r--r--. root root    #只有selinux上下文，没有ACL
    -rwxrwxr--+ root root    #有selinux上下文，有ACL
    修改配置文件以防重启后恢复selinux状态
    vi /etc/sysconfig/selinux
    SELINUX=disabled 
    在线关闭selinux
    setenforce 0
    查看状态
    [root@localhost ~]# /usr/sbin/sestatus -v
    SELinux status:                 disabled
    
    产生core文件 ulimit -c unlimited
    -eq     ==
    -ne     !=
    -gt     >
    -lt     <
    -ge     >=
    -le     <=
    
    0   标准输入
    1   标准输出
    2   错误输出
    ls a.txt 1>success.txt 2>error.txt  将标准输出输出到success.txt文件,标准错误输出到error.txt
    其中1可以省略,所以可以写成 ls a.txt > success.txt 2>error.txt
    
    ls a.txt b.txt 1>success.txt 2>&1 将标准错误和标准输出输出到success.txt文件
    如果写成了
    ls a.txt b.txt 2>&1 2>success.txt   则会将标准错误输出到控制台上
    也就是从最靠近最终输入的写起
# df命令

    df -h
    df -T 显示文件系统类型
    查看当前目录空间占用空间大小 du -h --max-depth=0
    删除特定文件 rm -rf A-[0-9][0-9][0-9].zip
# 切分大文件
    split -l 100 bigfile prefix
    split -b 10m bigfile prefix
# 查看Linux虚拟机内存和处理器信息
    cat /proc/cpuinfo
    cat /proc/meminfo
# find命令

    find . -type f -size -3k -exec ls -l {} \;  查找大小3k以内的文件并显示
    find . -type f -size +3k -exec ls -l {} \;  查找大小3k以上的文件并显示
    find ./ -mmin +2 2分钟以上的文件
# cat命令
    cat -v 显示特殊字符
    cat -n 显示行号
# 删除vim中的^M字符
	:e ++ff=dos
	:set ff=unit
	:wq
# tail命令
    tail -f file
    tail -10 file显示最后十行数据
# uptime命令
    查看上一次重启时间
    cat /proc/uptime
# head命令
    head -10 file显示前10行数据
# tr命令
    tr a-z A-Z
    tr -s ' '压缩多个空格为一个空格
    tr -s ' ' '\n'先用换行符替换空格,然后再压缩连续的换行符
    tr -s ' ' 将 将重复的空格以一个空格显示,tr -s 't' 将重复的t以一个t显示
    tr ':' '\n'  将字符串中的冒号替换位换行符,可以造成split(":")的效果
    tr -d '0-9'  将字符串中的数字删除掉
# echo
    单引号将全部当作字符串输出
    双引号中可以加变量
# 统计hive中所有分区数据大小
    work.txt中是所有分区字段信息
    cat work.txt | while read line
    do
    b=`hadoop fs -ls /user/hive/warehouse/mdmg.db/workdate=${line} | awk -F ' ' '{print $5} 
    | awk '{a+=$1}END{print a}'`
    a=`echo ${a}+${b} | bc`
    done
# Linux输出结果逆序

    ll -t | tac
# tail当前目录最新文件

    tail -f `ll -t | awk "NR==2" | tr -s ' ' | cut -d ' ' -f 9`
    awk "NR==2"输出第二行数据
    ll -t 按日期排序
    tr -s ' ' 压缩空格
    cut -d ' ' -f 9 以空格分割字符并且截取第九列
# sort命令
    sort -r逆序输出
    sort file 以ASCII排序
    sort -u 排序并去重
    sort -nk 2 -t: file  将文件每一行的内容以:分割,对第二列进行排序,以数字的形式
    ls | sort -n -k2 
# ps命令
    ps aux
    查看当前系统进程的uid,pid,stat,pri, 以uid号排序.
    ps -eo pid,stat,pri,uid –sort uid
    查看当前系统进程的user,pid,stat,rss,args, 以rss排序.
    ps -eo user,pid,stat,rss,args –sort rss
    ps aux --sort -rss倒序
    ps aux --sort rss正序
    ps --forest     显示进程的父子关系
    ps -T -p <pid>查看指定进程的所有线程
    stat取值含义
    	D      //无法中断的休眠状态（通常 IO 的进程）；
    	R      //正在运行可中在队列中可过行的；
    	S      //处于休眠状态；
    	T      //停止或被追踪；
    	W      //进入内存交换 （从内核2.6开始无效）；
    	X      //死掉的进程 （基本很少见）；
    	Z      //僵尸进程；
    	<      //优先级高的进程
    	N      //优先级较低的进程
    	L      //有些页被锁进内存；
    	s      //进程的领导者（在它之下有子进程）；
    	l      //多线程，克隆线程（使用 CLONE_THREAD, 类似 NPTL pthreads）；
    	+      //位于后台的进程组；
# Linux的内存
top命令显示的内存包括系统分配的缓存
ps命令显示实际的内存
>top includes what's cached in buffers and whatnot. PS does not. If you want your actual usage by the application, use ps. If you want the total used by the application including what the system reserves for it .. use top
>

1. VIRT is the virtual size of a process, which is the sum of the memory it is actually using, memory it has mapped into itself (for instance a video cards’s RAM for the X server), files on disk that have been mapped into it (most notably shared libraries), and memory shared with other processes. VIRT represents how much memory the process is able to access at the present moment

   虚拟内存空间总和.

   首先要知道每个进程都有一个虚拟内存空间,这是一个逻辑空间.

   这个virtual就代表占用这个空间的总大小,heap,文件映射(mmap)等等

2. RES is the resident size, which is an accurate representation of how much actual physical memory a process is consuming. (This number corresponds directly to top‘s %MEM column.) This amount will virtually always be less than the VIRT size, since most programs depend on the C library.

   这个才是实际占用的的物理内存

3. SHR indicates how much of the VIRT size is actually sharable, so it includes memory and libraries that could be shared with other processes. In the case of libraries, it does not necessarily mean that the entire library is resident. For example, if a program only uses a few functions in a library, the whole library is mapped and counted in VIRT and SHR, but only the parts of the library file that contain the functions being used are actually loaded in and counted under RES.

   这个是共享内存,和其他进程.dll

# 终端类型

    1.串行端口终端（/dev/ttySn）
    2.伪终端（/dev/pty/）
    3.控制终端（/dev/tty）
    4.控制台终端（/dev/ttyn, /dev/console）
# ldd
    打印程序以来的共享库
# netstat命令

    netstat -ntlp
# ssh-keygen

	指定生成目录
	ssh-keygen -t rsa -b 4096 -C "your_email@example.com" -f $HOME/.ssh/id_rsa

# strings命令

    在要给二进制文件中查找指定字符串
# strace命令    跟踪程序运行时的系统调用
    strace常用来跟踪进程执行时的系统调用和所接收的信号。
    在Linux世界，进程不能直接访问硬件设备，当进程需要访问硬件设备(比如读取磁盘文件，接收网络数据等等)时，
    必须由用户态模式切换至内核态模式，通过系统调用访问硬件设备。
    strace可以跟踪到一个进程产生的系统调用,包括参数，返回值，执行消耗的时间。
    也可以跟踪正在运行的进程的系统调用
    strace -T -tt -e trace=all -p pid
    
    execve("/usr/bin/ls", ["ls", "-l", "123.txt"], [/* 22 vars */]) = 0
    execve系统调用名称
    括号内的时系统调用参数
    =0是系统调用返回的值
# ltrace命令   跟踪调用了那些glibc函数
    ltrace ls -l 123.txt
# proc目录

> > https://tldp.org/LDP/Linux-Filesystem-Hierarchy/html/proc.html

    cmdline
    /proc/PID/cmdline
    输入的完整命令行信息
    Command line arguments.
    
    /proc/PID/cpu
    Current and last cpu in which it was executed.
    
    /proc/PID/cwd
    启动程序的时候当前工作目录
    Link to the current working directory.
    
    /proc/PID/environ
    环境变量信息
    Values of environment variables.
    
    /proc/PID/exe
    当前程序的完整目录,一个链接
    Link to the executable of this process.
    
    /proc/PID/fd
    拥有的文件描述符
    Directory, which contains all file descriptors.
    
    /proc/PID/maps
    Memory maps to executables and library files.
    
    /proc/PID/mem
    Memory held by this process.
    
    /proc/PID/root
    Link to the root directory of this process.
    
    /proc/PID/stat
    Process status.
    
    /proc/PID/statm
    Process memory status information.
    
    /proc/PID/status
    Process status in human readable form.
# linux中shell相关

    查看所有shell   cat /etc/shells
    查看当前使用的  sehll echo $SHELL
    更换当前shell       chsh
    zsh的文件 .zshrc
    bash的文件 .bashrc
# man命令
    1：可执行的程序或 shell 命令
    2：系统调用（由内核提供的函数）
    3：库调用（在程序的库内的函数）
    4：特殊文件（通常出现在 /dev）
    man 1 ls
    man 1 strace
    man 2 execve

# pmap命令
    显示进程内存中的地址映射
# ss命令
    ss 列出所有的连接，包括tcp连接、udp连接、unix socket、raw socket
    ss -t 列出所有tcp连接
    ss -tl 列出所有处于监听状态的tcp连接
    ss -u 列出所有的udp连接
    ss -p 列出连接时显示进程名字和pid
    ss -s 统计socket
    
    找出某个进程监听的端口号: ss -ltp | grep pro_name
    找出某个端口号被哪个进程占用: ss -p | grep port_num
    列出某个端口上的tcp连接：ss -tenp | grep port_num
# tee 
    Usage: tee [OPTION]... [FILE]...
    Copy standard input to each FILE, and also to standard output.
# awk命令
    awk '{print $1,$2}'  显示第一列和第二列
    awk -F ':' '{print $1 $2}'  以':'做为分隔符
    awk 'BEGIN{count=0;print "start count"}{count++;print $0}END{print "total user num is:" count}' /etc/passwd
    awk 'NR==1{print $1}'显示第一行的第一列
    awk '$2=="yellow"{print $1}' file1.txt  带条件输出
    awk '$3&gt;5 {print $1, $2}' colours.txt
    ls -S | awk '{a+=$5}END{print a "m"}'   累加列

# sysctl一些内核参数,通过该命令可以查询,更新相关的变量值
    文件路径:/etc/sysctl.conf
    屏蔽别人 ping 你的主机      net.ipv4.icmp_echo_ignore_all = 1
    执行以下命令使变动立即生效
    /sbin/sysctl -p
    
    /sbin/sysctl -w net.ipv4.route.flush=1
    
    输出所有变量  sysctl -a
# iostat命令

    iostat -d 2 6    每隔两秒输出io信息,总共输出6次
# vmstat命令
    vmstat -d 2 6    每隔两秒输出cpu信息,总共输出6此
# od命令
    输出文件的二进制内容
    od -to1 fileName    八进制(一字节作为一个单元)
    od -to2 fileName    八进制(两字节作为一个单元)
    od -td1 fileName    十进制(一字节作为一个单元)
    od -td2 fileName    十进制(两字节作为一个单元)
    od -tx1 fileName    十六进制(一字节作为一个单元)
    od -tx2 fileName    十六进制(两字节作为一个单元)
# xxd命令
    输出原始二进制信息(od命令可能和大小端字节序有关)
    xdd fileName
# read命令
    cat file.txt | while read line
    do
        echo "$line"
    done
# shell同步和异步
    sh start.sh &   异步运行
    正常在shell中调用其他脚本是同步运行
    使用wait可以等待其他shell脚本运行结束
# nl命令
    类似于cat+vim的set nu
    输出文件并带上行号
# shell中的特殊符号
    $0	当前脚本的文件名
    $n	传递给脚本或函数的参数。n 是一个数字，表示第几个参数。例如，第一个参数是$1，第二个参数是$2。
    $#	传递给脚本或函数的参数个数。
    $*	传递给脚本或函数的所有参数。
    $@	传递给脚本或函数的所有参数。被双引号(" ")包含时，与 $* 稍有不同。
    $?	上个命令的退出状态，或函数的返回值。
    $$	当前Shell进程ID。对于 Shell 脚本，就是这些脚本所在的进程ID。
    $PPID   当前进程得父ID 
# 链接
    ln filename linkname
    ln -s filename linkname
# 设置进程得优先级
    nice
    renice
# grep命令
    grep -n                 输出时带上行号
    grep -v                 反向选择
    grep -i                 忽略大小写
    grep -Po 'A(?=a)'       加Po参数支持断言,匹配A并且A后面是a
    grep -Po 'A(?!a)'       匹配A,并且A后面不是a
    grep -Po '(?<=A)a'      匹配a,并且a前面是A
    grep -Po '(?<!A)a'      匹配a,并且a前面不是A
    nl data | grep 'go$'    输出以go开头的行
    nl data | grep '^c++'   输出以c++开头的行
# dirname
    去除文件名中的非目录部分
# shell中的算数运算
    echo $[2400/40]
    let k=8*8
    let t=$k/32
# ulimit命令
    限制当前会话的系统资源
    相关的系统资源有
    -H	设置硬资源限制，一旦设置不能增加。	ulimit – Hs 64；限制硬资源，线程栈大小为 64K。
    -S	设置软资源限制，设置后可以增加，但是不能超过硬资源设置。	ulimit – Sn 32；限制软资源，32 个文件描述符。
    -a	显示当前所有的 limit 信息。	ulimit – a；显示当前所有的 limit 信息。
    -c	最大的 core 文件的大小， 以 blocks 为单位。	ulimit – c unlimited； 对生成的 core 文件的大小不进行限制。
    -d	进程最大的数据段的大小，以 Kbytes 为单位。	ulimit -d unlimited；对进程的数据段大小不进行限制。
    -f	进程可以创建文件的最大值，以 blocks 为单位。	ulimit – f 2048；限制进程可以创建的最大文件大小为 2048 blocks。
    -l	最大可加锁内存大小，以 Kbytes 为单位。	ulimit – l 32；限制最大可加锁内存大小为 32 Kbytes。
    -m	最大内存大小，以 Kbytes 为单位。	ulimit – m unlimited；对最大内存不进行限制。
    -n	可以打开最大文件描述符的数量。	ulimit – n 128；限制最大可以使用 128 个文件描述符。
    -p	管道缓冲区的大小，以 Kbytes 为单位。	ulimit – p 512；限制管道缓冲区的大小为 512 Kbytes。
    -s	线程栈大小，以 Kbytes 为单位。	ulimit – s 512；限制线程栈的大小为 512 Kbytes。
    -t	最大的 CPU 占用时间，以秒为单位。	ulimit – t unlimited；对最大的 CPU 占用时间不进行限制。
    -u	用户最大可用的进程数。	ulimit – u 64；限制用户最多可以使用 64 个进程。
    -v	进程最大可用的虚拟内存，以 Kbytes 为单位。	ulimit – v 200000；限制最大可用的虚拟内存为 200000 Kbytes。
# shell传递参数
    $1 $2 $3
# shell字符串相关操作
    #截取字符串
    ${string:start:len}
    获取字符串长度
    ${#string}
    ${file/e/k}将file字符串中的第一个e替换为k
    
    name=hello.world.txt.20200229
    从左边开始一直到.删除掉
    echo #{name#*.}   // world.txt.2020.229
    从左边开始一直到最后一个.删除掉
    echo ${name##*.}  // 20200229
    从右边开始到第一个.删除掉
    echo ${name%.*}   // hello.world.txt
    从右边开始到最后一个.删除掉
    echo ${name%%.*}  // hello
    expr substr $name 1 3 // hel

# shell循环
    for((i=0;i<10;i++))
    do
    echo $i
    done
    
    while [ true ]
    do
        if [ ${num} -gt 3 ];then
            echo ${num}
            continue
        else
            break
        fi
    done
# shell函数
    cutDemo(){
            ls | cut -b 3-5
            ls | cut -b -3
            ls | cut -b -3,3-
    }
    echo 'execute cutDemo function...'
    cutDemo
    echo 'cutDemo function finished...'
    
    cut -d' ' -f 1   以空格作为分隔符并且取第一列
# shell双引号和单引号
    [root@fcy shell]# name=fcy
    [root@fcy shell]# echo 'hello $name'
    hello $name
    [root@fcy shell]# echo "hello $name"
    hello fc
    双引号中变量输出值,单引号中变量名无效
# shell数组
    array=(1 2 3 4 5 6 7 8)
    输出第一个元素
    echo ${array[0]}
    输出所有元素
    echo ${array[*]}
    echo ${array[@]}
    输出数组长度
    echo ${#array[*]}
    echo ${#array[@]}
# lscpu查看服务器cpu相关信息
    更详细的信息: cat /proc/cpuinfo
    大小端
    32or64
    cpu核数
    1)CPU总核数 	= 物理CPU个数 * 每颗物理CPU的核数 
    		2)逻辑CPU总数 = 物理CPU个数 * 每颗物理CPU的核数 * 超线程数
    		3)多核超线程：
    			1>多个物理CPU：	物理CPU间通过总线进行通信，效率比较低。
    			1>多核CPU：		不同的核通过L2 cache进行通信，存储和外设通过总线与CPU通信。
    			2>超线程：		每个核有两个逻辑的处理单元，两个处理单元共享一个核的资源。
    CPU(s):                1    1个cpu
    Thread(s) per core:    1    每个核的逻辑核(线程数)
    Core(s) per socket:    1    每个插槽的cpu核数
    Socket(s):             1    cpu插槽
# 压缩文件和目录
    zip 123.zip 123.txt压缩文件
    zip -r 123.zip 123压缩目录
# 显示指定命令的类型
	type -a ruby    在path中查找并显示可执行文件的路径
# 查看当前环境变量

    env
# 查找特定文件并删除
    格式:find   path   -option   [   -print ]   [ -exec   -ok   command ]   {} \;
    find ./ -mtime +32 -name *.java -exec rm -rf {}
    find ./ -mtime -1 -name *.java -exec rm -rf {}
    find ./ -mtime 1 -name *.java -exec rm -rf {}
    find ./ -mtime +1 -name *.java -exec rm -rf {}
    find /cpic/jtzxmd -type d -exec mkdir -p /home/jtaom{} \;   复制目录结构
    find / -name java -type f 2>/dev/null   将大量出现的Permission Denied重定向到另一个目录
    find / -name "TR-*.xlsx" 会递归搜索指定目录下的子目录
    find . -name "*.html" -or -name "*.ts" -or -name "*.scss" -or -name "*.css" |xargs grep -v "^$"|wc -l  统计代码行数(空白行不统计)
# shell文件的三个时间
    atime(access time)   最后访问时间
    ctime(change time)   最后变更时间(文件属性,文件的metadata被修改时)
    mtime(modify time)   最后修改时间
    
    ll显示的时mtime文件内容修改时间
# stat filename查看文件信息

# shell控制语句
    if [ $num -gt 1 ]
    then
    
    else
    
    fi
    if [ 1 -eq 1
    if ((1==1));then
        echo "true"
    fi
    if ((1==1)) && ((2==2));then
        echo "true"
    fi
    
    -f file        是否是一个文件
    -x file        文件是否可执行
    -r file　　　　　用户可读为真
    -w file　　　　　用户可写为真
    -x file　　　　　用户可执行为真
    -f file　　　　　文件为正规文件为真
    -d file　　　　　文件为目录为真
    -c file　　　　　文件为字符特殊文件为真
    -b file　　　　　文件为块特殊文件为真
    -s file　　　　　文件大小非0时为真
    -t file　　　　　当文件描述符(默认为1)指定的设备为终端时为真
# top -H -p <pid>查看指定进程的线程信息
    top中相关参数含义
    VIRT    所有使用的未使用的内存总和
    RES     实际使用的内存量
    SHR     和其他进程共享的内存

# free命令详解
                  total        used        free      shared  buff/cache   available
    Mem:           972M        437M        409M        7.6M        125M        379M
    Swap:          2.0G        264K        2.0G
    free表示真正空闲的内存
    echo 1 > /proc/sys/vm/drop_caches当然，这个文件可以设置的值分别为1、2、3。它们所表示的含义为：echo 1 > /proc/sys/vm/drop_caches：表示清除 page cache。echo 2 > /proc/sys/vm/drop_caches：表示清除回收 slab 分配器中的对象（包括目录项缓存和 inode 缓存）。slab 分配器是内核中管理内存的一种机制，其中很多缓存数据实现都是用的 page cache。echo 3 > /proc/sys/vm/drop_caches：表示清除 page cache 和 slab 分配器中的缓存对象。
    free -h -s 3     每3秒显示内存信息
    free 命令中的信息都来自于 /proc/meminfo 文件
    buff/cache
    A buffer is something that has yet to be "written" to disk. A cache is something that has been "read" from the disk and 
    stored for later use.
        buff是缓冲,还未写入到磁盘的脏数据
        cache是方便读取
# id显示当前用户的一些信息

    当前用户名,用户id,组名,组id,加入的所有组,所有组id
# 查看进程端口信息
      ss -tnlp  
        ss：可以用于转储套接字统计信息。
    netstat -tnlp  
        netstat：可以显示打开的套接字列表。
    lsof -i P
        lsof：可以列出打开的文件。
        lsof -u test      用户打开的文件
        lsof -p pid        进程号为pid的进程打开的文件
        lsof -c pro_name          进程名开头为pro_name打开的文件
        lsof -i tcp         列出所有的tcp连接
        lsof -i udp        列出所有的udp连接
        lsof -i tcp:4600       列出占用4600端口的tcp连接
        lsof -i udp:4600        列出占用4600端口的udp连接
        lsof -i :4600          列出占用4600端口连接
    fuser 22/tcp
        fuser：可以列出那些打开了文件的进程的进程 ID。  
        还可以显示信号量等其他信息
# Inode节点
    sync 命令将所有未写的系统缓冲区写到磁盘中，包含已修改的 i-node、已延迟的块 I/O 和读写映射文件)
     inode中包含了文件大小、属主、归属的用户组、读写权限等信息。不只是用vi修改文件，只要文件被改变了，inode的值就会变。
     磁盘分为许多个INode节点
     每个iNode节点都有编号
     INode节点信息
     stat查看文件的INode信息
    File		'Dockerfile'		文件名
    Size		'422'				文件大小
    Blocks		'8'					文件块
    IO Block	'4096'				
    Device		'fd01h/64769d'		设备
    Inode		2108221				Inode号
    Links		1					链接数
    Access		(0644/-rw-r--r--)	访问权限
    Uid			(0/root)			用户id
    Gid			(0/root)			组id
    Access		2018-11-22 21:45:09	上次访问时间
    Modify							上次修改时间
    Change							元数据的修改时间
    Birth							创建时间
    目录也是一种文件,结构简单,就是一系列目录项列表,每个目录项由两部分组成
    所包含文件的文件名
    改文件名对于的inode号码
    硬连接
    在inode节点的链接上加一,然后以另一个文件名访问该节点的数据,该该文件的内容修改会影响所有的文件名,但是删除一个文件名,并不一定会删除该文件,只是把该inode节点的链接数减一,如果该inode节点的链接数为0,则系统会回收该节点,但是并不会清楚该节点的数据,只有当其他数据需要存储在该节点的时候这里的数据才会被覆盖掉
    目录文件的链接数
    	创建一个目录的时候,会默认生成两个目录项, .和..,
    	前者的inode就是当前目录文件的inode号码
    	后者的inode就是当前目录的父目录的inode号码
    	等同于硬连接
    	所以一个目录的硬链接总数等于其子目录项加上2
    软链接就是文件的内容是是另一个文件的路径,相当于windows下的快捷方式
    系统indoe是有限的,所以可能系统空间还够但不能存放数据,
    文件夹太多了,每创建一个文件都需要一个inode节点
    由于每个文件都必须有一个inode，因此有可能发生inode已经用光，但是硬盘还未存满的情况。这时，就无法在硬盘上创建新文件。
# rpm命令
    rpm -qa|grep -i mysql   查找系统的有关于mysql的文件
    rpm -e -nodeps 包名删除mysql有关软件
    rpm -qa|grep -i mysql来确认系统中是否还含有mysql相关的文件
    rpm -ql php71-php-fpm-7.1.2-1.el6.remi.x86_64    yum 安装的程序 安装到哪里了？
# 开机自启动
	将shell脚本的路径添加到/etc/rc.local文件中
# 服务相关目录

    /etc/init.d/   chkconfig命令就是对其进行增删改查
    chkconfig --list
    chkconfig --add
    chkconfig --del
# 特殊符号无效
    在一些控制台上我们使用Backspace或者上下箭头无效的时候
    1、使用Ctrl+Backspace
    2、使用stty命令重新定义
    stty命令
    eof : 输入结束
    erase : 向后删除字符，
    intr : 中断当前程序
    kill : 删除整条命令
    quit :退出当前程序
    start : 启动屏幕输出
    stop :停止屏幕输出；
    susp : terminal stop当前程序。
# rev命令
    字符串反转
    反转字符串
    echo 'A B C D' | rec

# seq命令
    生成数
    seq start
    seq start,end
    seq start,inc,end
    seq 10
    seq -f "str%g" 9 11     生成str9,str10,str11,也可以固定位数
    替换\n成\r\n  sed -e 's/$/\r/' 1pnet.txt >dos.txt
# sed命令
    匹配并替换
    sed接受[0-2]个地址参数
    0   will be executed for all input lines which match that address
    1   will only be exected for input lines which match that address
    2   will only be exected for input lines which match the inclusive range of lines starting from 
        the first lines and continuing to the second lines 
    地址的语法是:add1,add2
    地址1的行一定会被执行,尽管地址2选择了一个更早的行，并且如果地址2是要给正则，他不会测试地址1匹配的行数
    
    地址的表示形式
        number      匹配第几行
        first~last  1~2表示匹配1,3,5,7...行,从第一行开始递增
        $           匹配最后一行
        /regex/     正则匹配
    sed也接受两地址参数
        0,addr2
        add1,+N 匹配第一个地址，并且之后的N行  1,+3d  将会删除第一行和第一行后面的三行,也就是1,4d
        add1,~N 匹配第一个地址，直到遇到第一个行数是N的倍数
        也就是if(lineNumber%N==0)matched
        左边是输入,存为1.txt执行'sed 1,~2d 1.txt'则会有右边的结果
           1       
           2       3   
           3       4   
           4======>5   
           5       6   
           6       7   
           7
    替换  	s	    [address]s/pattern/replacement/flags	替换匹配的内容
    删除	    d	    [address]d	            删除匹配的行
    插入	    i	    [line-address]i\text	在匹配行的前方插入文本
    追加	    a	    [line-address]a\text	在匹配行的后方插入文本
    行替换	c	    [address]c\text	        将匹配的行替换成文本text
    打印行	p	    [address]p	            打印在模式空间中的行
    打印行号	=	    [address]=	            打印当前行行号
    打印行	l	    [address]l	            打印在模式空间中的行，同时显示控制字符
    转换字符	y	    [address]y/SET1/SET2/	将SET1中出现的字符替换成SET2中对应位置的字符
    读取下一行n	    [address]n	            将下一行的内容读取到模式空间
    读文件	r	    [line-address]r file	将指定的文件读取到匹配行之后
    写文件	w	    [address]w file	        将匹配地址的所有行输出到指定的文件中
    退出	    q	    [line-address]q	        读取到匹配的行之后即退出
    
    sed '/^\s*\n$/d' data     删除文件中的空行 ^表示文件开头,$表示文件结尾,\s表示空格,/d表示删除
    sed -n 18p fileName 查看第18行数据
    sed -n '1,8p' fileName 查看第1-8行数据
# sort命令
    根据某一分隔符分割，根据第二列去重
    sort -n -k 2 -t : Plan.txt
# 修改ssh端口
	修改/etc/ssh/sshd_config文件
	Port 22
	Port 521314
	执行命令 service ssh restart
	然后就可以通过521314端口去登录了,当然22端口也行
# Linux防火墙
	iptables和firewalld
	service iptables status
	
	systemctl status firewalld
	service firewalld start
	service firewalld stop
	service firewalld restart
	
	firewall-cmd --list-all
	firewall-cmd --permanent --add-port=80/tcp
	firewall-cmd --permanent --remove-port=80/tcp
	firewall-cmd --query-port=80/tcp
# vfstp 
	配置文件目录 /etc/vsftpd
	文件目录  /var/ftp
# netstat 命令显示的:::*

	::: 这三个: 的前两个”::“，是“0:0:0:0:0:0:0:0”的缩写，相当于IPv6的“0.0.0.0”，就是本机的所有IPv6地址，第三个:是IP和端口的分隔符

# crontab

# 关键信息
```
/var/spool/cron目录
/var/log/cron 日志
输出日志到某个目录
* * * * * echo "123" >> ~/mylog.log 2>&1
之前忘了给脚本授权,导致permission denied
分 ， 0-59
时 ， 0-23
日 ， 1-31
月 ， 1-12
星期 ， 0-7 ( 0 和 7 均表示星期天 )
执行命令
```
# 样例

每分钟执行脚本：

```
* * * * * /path/to/my/script
* * * * * ps -ef > /1.txt
```

每小时第 3 和第 15 分钟执行脚本：

```
3,15 * * * * /path/to/my/script
```

上午 8 时到 11 时的第 3 和 15 分钟执行脚本：

```
3,15 8-11 * * * /path/to/my/script
```

每隔两天上午 8 时到 11 时的第 3 和 15 分钟执行脚本：

```
3,15 8-11 */2 * * /path/to/my/script
```

每周一上午 8 时到 11 时的第 3 和 15 分钟执行脚本：

```
3,15 8-11 * * 1 /path/to/my/script
```

每晚 21:30 执行脚本：

```
30 21 * * * /path/to/my/script
```

每月 1 、 10 、 22 日的 4:45 执行脚本：

```
45 4 1,10,22 * * /path/to/my/script
```

每周六、周日的 1:10 执行脚本：

```
10 1 * * 6,0 /path/to/my/script
```

每天 18 时到 23 时之间，每隔 30 分钟执行脚本：

```
0,30 18-23 * * * /path/to/my/script
```

每周六 23 时执行脚本：

```
0 23 * * 6 /path/to/my/script
```


​	