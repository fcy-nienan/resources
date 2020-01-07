# ssh免登录原理
    .ssh目录下有三个文件:id_rsa,id_rsa.pub,known_hosts,authorized_keys
    分别用来存放私钥,公钥,已经访问过的主机公钥信息,登陆其他系统需要的公钥信息
    登陆其他系统的时候使用公钥登陆,authorized_keys文件可以存放多个主机的公钥信息
