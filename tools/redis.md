+ getset 设置新值并返回旧值,如果值不存在返回(nil)

+ setlen 返回字符串长度

+ append


redis-server --service-uninstall    移除服务

redis-server --service-install redis.windows.conf    安装为服务



redis设置密码		config set requirepass 121212

查看运行中的Redis配置信息   登录进去后执行  info Server



# redis切换数据库

```

127.0.0.1:6379> select 1 # 默认0号数据库，切换到1号数据库

OK

127.0.0.1:6379[1]> select 2 # 切换到2号数据库

OK

127.0.0.1:6379[2]> select 3 # 切换到3号数据库

OK

127.0.0.1:6379[3]> select 0 # 切换到默认数据库

OK

127.0.0.1:6379> 

```
命令行中的6379后面的[1][2][3]就是几号数据库，不需要命令行查看