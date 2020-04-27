# /etc/group文件 
+ 文件作用:存储用户的组信息 
+ 文件内容格式:group_name:Password:GroupID,GroupList
    + group_name: It is the name of group. If you run ls -l command, you will see this name printed in the group field.
    + Password: Generally password is not used, hence it is empty/blank. It can store encrypted password. This is useful to implement privileged groups.
    + Group ID (GID): Each user must be assigned a group ID. You can see this number in your /etc/passwd file.
    + Group List: It is a list of user names of users who are members of the group. The user names, must be separated by commas.
