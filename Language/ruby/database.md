# postgresql

brew install postgresql -v

启动：
pg_ctl -D /usr/local/var/postgres -l /usr/local/var/postgres/server.log start

关闭：
pg_ctl -D /usr/local/var/postgres stop -s -m fast

新建一个数据库用户

createuser weixinadmin -P
为这个用户新建一个数据库

createdb weixindb -O weixinadmin -E UTF8 -e
用这个用户访问数据库

psql -U weixinadmin -d weixindb -h 127.0.0.1

dropdb -h 127.0.0.1 -p 5432 -U mozhou mozhou_uat

查看所有表信息

​	select * from pg_tables;

​	select * from pg_tables where schemaname='public'

查看表结构

​	\d table_name