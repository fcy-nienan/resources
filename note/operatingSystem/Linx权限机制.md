# /etc/group文件 
+ 文件作用:存储用户的组信息 
+ 文件内容格式:group_name:Password:GroupID,GroupList
    + group_name: It is the name of group. If you run ls -l command, you will see this name printed in the group field.
    + Password: Generally password is not used, hence it is empty/blank. It can store encrypted password. This is useful to implement privileged groups.
    + Group ID (GID): Each user must be assigned a group ID. You can see this number in your /etc/passwd file.
    + Group List: It is a list of user names of users who are members of the group. The user names, must be separated by commas.
# /etc/passwd文件
+ 文件作用:存储所有的用户信息
+ 文件内容格式:
    >Each line contains seven attributes or fields: 
    name, password, user ID, group ID, gecos, home directory and shell. 
    Each attribute is separated from the adjacent attributes by colons but with no spaces
    用户名:密码:用户ID:组ID:描述:主目录:shell
    密码默认是x
    若此处shell为：/sbin/nologin,则代表这个用户不能登录
# /etc/shadow文件
+ 文件作用:存储用户的真实密码
+ 文件内容格式:
    username: passwd: lastchg: min: max: warn: inactive: expire: flag 
    登录名”是与/etc/passwd文件中的登录名相一致的用户账号
    口令”字段存放的是加密后的用户口令字，长度为13个字符。如果为空，则对应用户没有口令，登录时不需要口令；如果含有不属于集合{./0-9A-Za-z}中的字符，则对应的用户不能登录。
    最后一次修改时间”表示的是从某个时刻起，到用户最后一次修改口令时的天数。时间起点对不同的系统可能不一样。例如在SCOLinux中，这个时间起点是1970年1月1日。
    最小时间间隔”指的是两次修改口令之间所需的最小天数。
    最大时间间隔”指的是口令保持有效的最大天数。
    警告时间”字段表示的是从系统开始警告用户到用户密码正式失效之间的天数。
    不活动时间”表示的是用户没有登录活动但账号仍能保持有效的最大天数。
    失效时间”字段给出的是一个绝对的天数，如果使用了这个字段，那么就给出相应账号的生存期。期满后，该账号就不再是一个合法的账号，也就不能再用来登录了。

# rwx权限认识
当前测试用户jboss,dcosuser
所属用户组jboss5,dcos

    /etc/passwd文件
    jboss:x:1001:1002::/home/jboss:/bin/bash
    dcosuser:x:1002:1003::/home/dcosuser:/bin/bash

    /etc/group文件
    jboss5:x:1002:
    dcos:x:1003:
    
    测试项:rwx的子集(LeetCode中78题)
    r
    w
    x
    rw
    rx
    rwx(不测)
    wx
    目录中的文件全部777权限
### R权限
    [root@fcy home]# ll
    total 8
    drwxr--r-- 2 dcosuser dcos   4096 Feb 25 02:02 dcosuser
    
    R权限只能读取到文件名,文件其他信息无法读取到
    [jboss@fcy home]$ ll dcosuser/
    ls: cannot access dcosuser/1.txt: Permission denied
    total 0
    -????????? ? ? ? ?            ? 1.txt
    
    有R权限且文件权限是777为啥不能查看文件内容?
    [jboss@fcy home]$ cat dcosuser/1.txt
    cat: dcosuser/1.txt: Permission denied
    
    [jboss@fcy home]$ date > dcosuser/1.txt
    -bash: dcosuser/1.txt: Permission denied
    
    [jboss@fcy home]$ touch dcosuser/2.txt
    touch: cannot touch 'dcosuser/2.txt': Permission denied
# W权限
    [root@fcy home]# ll
    total 8
    drwxr---w- 2 dcosuser dcos   4096 Feb 25 02:02 dcosuser

    [jboss@fcy home]$ ll dcosuser/
    ls: cannot open directory dcosuser/: Permission denied
    
    [jboss@fcy home]$ cat dcosuser/1.txt
    cat: dcosuser/1.txt: Permission denied
    
    [jboss@fcy home]$ date > dcosuser/1.txt
    -bash: dcosuser/1.txt: Permission denied
    
    有W权限为啥不能新建文件?
    [jboss@fcy home]$ touch dcosuser/2.txt
    touch: cannot touch 'dcosuser/2.txt': Permission denied
# X权限
    [root@fcy home]# ll
    total 8
    drwxr----x 2 dcosuser dcos   4096 Feb 25 02:02 dcosuser
    
    [jboss@fcy home]$ ll dcosuser/
    ls: cannot open directory dcosuser/: Permission denied
    
    只有X权限为啥还能查看文件内容
    [jboss@fcy home]$ cat dcosuser/1.txt
    Tue Feb 25 02:52:04 CST 2020
    
    [jboss@fcy home]$ touch dcosuser/2.txt
    touch: cannot touch 'dcosuser/2.txt': Permission denied
    
    只有X权限为啥还能写入成功?
    [jboss@fcy home]$ date > dcosuser/1.txt
    
    [jboss@fcy home]$ sh dcosuser/2.sh
    sdf
# RW权限
    [root@fcy home]# ll
    total 8
    drwxr--rw- 2 dcosuser dcos   4096 Feb 25 02:02 dcosuser
    
    [jboss@fcy home]$ ll dcosuser/
    ls: cannot access dcosuser/1.txt: Permission denied
    total 0
    -????????? ? ? ? ?            ? 1.txt
    
    [jboss@fcy home]$ cat dcosuser/1.txt 
    cat: dcosuser/1.txt: Permission denied
    
    [jboss@fcy home]$ touch dcosuser/2.txt
    touch: cannot touch 'dcosuser/2.txt': Permission denied
    
    [jboss@fcy home]$ rm -rf dcosuser/1.txt 
    rm: cannot remove 'dcosuser/1.txt': Permission denied
# RX权限
    这个RX权限倒还好理解
    [jboss@fcy home]$ ll
    total 8
    drwxr--r-x 2 dcosuser dcos   4096 Feb 25 02:55 dcosuser
    
    [jboss@fcy home]$ ll dcosuser/
    total 4
    -rwxrwxrwx 1 dcosuser dcos 29 Feb 25 02:52 1.txt
    
    [jboss@fcy home]$ cat dcosuser/1.txt 
    Tue Feb 25 02:52:41 CST 2020
    
    [jboss@fcy home]$ date > dcosuser/1.txt 
    
    [jboss@fcy home]$ touch dcosuser/2.txt
    touch: cannot touch 'dcosuser/2.txt': Permission denied
# WX权限
    [jboss@fcy home]$ ll
    total 8
    drwxr---wx 2 dcosuser dcos   4096 Feb 25 02:55 dcosuser
    
    [jboss@fcy home]$ ll dcosuser/
    ls: cannot open directory dcosuser/: Permission denied
    
    [jboss@fcy home]$ ll dcosuser/1.txt
    -rwxrwxrwx 1 dcosuser dcos 29 Feb 25 03:00 dcosuser/1.txt
    
    [jboss@fcy home]$ cat dcosuser/1.txt
    Tue Feb 25 03:00:19 CST 2020
    
    [jboss@fcy home]$ date > dcosuser/1.txt
    
    [jboss@fcy home]$ touch dcosuser/2.txt
    
网络上大都是这样的描述:  
If you have read permission for a directory, you may list ls the directories contents.  
If you have write permission for a directory, you can create new entries (files/folders/etc).  
If you have execute permission for a directory, you may change chdir into that directory.  
>https://stackoverflow.com/questions/15355958/what-does-the-x-mean-in-rwx-on-a-directory

>"Execute" is the traversal permission on a directory. 
>It allows you to access files and folders within the directory.

>If you can read a directory, you can list the contents.

>If you can write a directory, you can make new files and folders within it.

>If you can "execute" a directory, you can move through the hierarchy, 
>even if you don't know what's inside.

但感觉还是有些地方说不通,可能只是一个笼统的归纳吧

这个链接有些作用  
https://www.unix.com/tips-and-tutorials/19060-unix-file-permissions.html

# 遇到的问题
## /usr/bin/id: cannot find name for user ID 1002
    这个问题是因为普通用户没有权限读取/etc/passwd和/etc/group文件造成，添加权限即可。
    chmod 644 /etc/passwd
    chmod 644 /etc/group
## SecureCRT超时自动断开
    Options->Session Options->Terminal->Anti-idle->勾选Send protocol NO-OP
# 使用的命令
usermod -a -G jboss dcos 将jboss用户添加到dcos组
useradd jboss           增加用户
userdel jboss           删除用户
groupadd jboss5         
groupadd dcos           新增组
gpasswd -d jboss jboss5 删除组内用户
usermod -g jboss dcos   更改用户组信息
whoami                  我是谁