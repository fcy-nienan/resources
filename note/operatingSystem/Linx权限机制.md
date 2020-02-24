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

    drwxr--r-- 2 1002 dcos   4096 Feb 24 17:16 dcosuser
    drwx------ 2 1001 jboss5 4096 Feb 24 17:16 jboss
现在jboss用户需要访问dcosuser目录，可以看到只有一个r权限
