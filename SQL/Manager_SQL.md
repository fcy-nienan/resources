mysql远程登录:mysql -u root -p -h 120.79.158.25 -P 3306

mysql的连接方式有两种：

1.tcp/ip方式
先说说这种方式，这个方式是在tcp/ip上建立一个网络连接请求，
即MySQL服务器和客户端不再同一个服务器上，需要通过网络（IP）形式去连接。
但是这种连接需要mysql服务器给这台客户端IP进行授权，否则不可以连接。
如mysql服务器是192.168.10.230，客户端IP是192.168.10.220
授权：grant all on *.* to 'root'@'192.168.10.220' identified by '123456';
连接：mysql -uroot -h192.168.2.230 -p ? ? ? ? ? ? ##-h是指定连接服务器
这种方式是不需要在客户端安装mysql的，即mysql的服务器安装完成后，就默认建立了一个和任何客户端进行连接的通道。
2.socket方式
这种方式必须是客户端和mysql服务器在同一台服务器上，使用localhost的方式去连接，
这样就会用到套接字文件socket，即主机名是localhost的服务器，
客户端通过套接字文件mysql.sock文件连接到服务器，
如果这个文件删除就不能连接。

mysql设置远程登录，修改host字段为'%'

centos7安装mysql
直接用yum -y install mysql mysql-server会出现No package mysql-server available错误
可以先键入下面两个命令
	wget http://repo.mysql.com/mysql-community-release-el7-5.noarch.rpm
	rpm -ivh mysql-community-release-el7-5.noarch.rpm
然后在安装mysql
	yum -y install mysql mysql-server

开启mysql
	systemctl start mysqld
进入mysql
	mysql -uroot
改密码
	set password for root@localhost=password('123');
	mysqldadmin -uroot -p123456 password 123;
	update user set password=password('123') where user='root' and host='localhost';
	flush privileges;
忘记密码
	关闭mysql
	进入mysql的bin目录
	打开cmd
	键入 mysqld --skip-grant-tables,意思是跳过权限认证
	然后新开一个cmd
	然后进入mysql修改密码
	最后需要刷新权限:flush privileges;
mysql的默认配置文件
	F:\mysql\bin\mysqld --defaults-file="F:\mysql\my-default.ini" MySQL
	在注册表中修改ImagePage的值为以上值
	最后的MYSQL是服务名称

cmd链接远程数据库    mysql -uroot -proot -h120.79.158.25 -P3306 -Ddatabasename
		P,D要大写
mysql导出SQL文件(将数据库导出为SQL文件)
		mysqldump -uroot -p shopping > shop.sql
1.将数据库mydb导出到e:\mysql\mydb.sql文件中：
打开开始->运行->输入cmd    进入命令行模式
c:\>mysqldump -h localhost -u root -p mydb >e:\mysql\mydb.sql
然后输入密码，等待一会导出就成功了，可以到目标文件中检查是否成功。
2.将数据库mydb中的mytable导出到e:\mysql\mytable.sql文件中：
c:\>mysqldump -h localhost -u root -p mydb mytable>e:\mysql\mytable.sql
3.将数据库mydb的结构导出到e:\mysql\mydb_stru.sql文件中：
c:\>mysqldump -h localhost -u root -p mydb --add-drop-table >e:\mysql\mydb_stru.sql
四.从外部文件导入数据到数据库中：
从e:\mysql\mydb2.sql中将文件中的SQL语句导入数据库中：
1.从命令行进入mysql，然后用命令CREATE DATABASE mydb2;创建数据库mydb2。
2.退出mysql 可以输入命令exit；或者quit；
3.在CMD中输入下列命令：
c:\>mysql -h localhost -u root -p mydb2 < e:\mysql\mydb2.sql
然后输入密码，就OK了。


alter table command modify `status` int default 0 comment 'execute status'

修改字段名和属性
alter table tablename change test test1 varchar(32);
修改类型
alter table tablename modify test varchar(32);



1. 查看profiling的状态，1为开启，默认处于关闭状态

SELECT @@profiling;



2. 开启
SET profiling = 1;


3. 执行sql语句



4. 显示 profiles的信息，格式看着不爽的可以在后面加上\G

show profiles;
show profiles\G;



5. 具体查看某一次的就可以通过指定query_id的方式

show profile for query 2;

show profile block io,cpu for query 2;

