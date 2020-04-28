# useServerPrepStmts=false&rewriteBatchedStatements=true
    在MySQL中批量插入的时候可以加上上述两个参数缩短一些插入时间
# 使用上述参数
## mysql.url=jdbc:mysql://127.0.0.1:3306/fcy?useServerPrepStmts=false&rewriteBatchedStatements=true  
    23:51:24.784 [pool-1-thread-1] INFO Faker.BatchInsert - fcy.batch表已存在!  
    insert into fcy.batch values(0,?,?,?,?,?,?,?,?,?,?)  
    23:51:31.805 [pool-1-thread-1] INFO Faker.BatchInsert - start commit batch count:50000  
    23:51:32.643 [pool-1-thread-1] INFO Faker.BatchInsert - end commit batch count:50000  
    23:51:38.505 [pool-1-thread-1] INFO Faker.BatchInsert - start commit batch count:100000  
    23:51:39.485 [pool-1-thread-1] INFO Faker.BatchInsert - end commit batch count:100000  
    23:51:45.167 [pool-1-thread-1] INFO Faker.BatchInsert - start commit batch count:150000  
    23:51:45.863 [pool-1-thread-1] INFO Faker.BatchInsert - end commit batch count:150000  
    23:51:51.589 [pool-1-thread-1] INFO Faker.BatchInsert - start commit batch count:200000  
    23:51:52.478 [pool-1-thread-1] INFO Faker.BatchInsert - end commit batch count:200000  
    23:51:58.384 [pool-1-thread-1] INFO Faker.BatchInsert - start commit batch count:250000  
    23:51:59.227 [pool-1-thread-1] INFO Faker.BatchInsert - end commit batch count:250000  
    23:52:05.352 [pool-1-thread-1] INFO Faker.BatchInsert - start commit batch count:300000  
    23:52:06.476 [pool-1-thread-1] INFO Faker.BatchInsert - end commit batch count:300000  
    23:52:12.527 [pool-1-thread-1] INFO Faker.BatchInsert - start commit batch count:350000  
    23:52:13.389 [pool-1-thread-1] INFO Faker.BatchInsert - end commit batch count:350000  
    23:52:19.067 [pool-1-thread-1] INFO Faker.BatchInsert - start commit batch count:400000  
    23:52:19.945 [pool-1-thread-1] INFO Faker.BatchInsert - end commit batch count:400000  
    23:52:25.615 [pool-1-thread-1] INFO Faker.BatchInsert - start commit batch count:450000  
    23:52:26.455 [pool-1-thread-1] INFO Faker.BatchInsert - end commit batch count:450000  
    23:52:32.332 [pool-1-thread-1] INFO Faker.BatchInsert - start commit batch count:500000  
    23:52:33.218 [pool-1-thread-1] INFO Faker.BatchInsert - end commit batch count:500000  
    23:52:38.854 [pool-1-thread-1] INFO Faker.BatchInsert - start commit batch count:550000  
    23:52:39.601 [pool-1-thread-1] INFO Faker.BatchInsert - end commit batch count:550000  
    23:52:45.457 [pool-1-thread-1] INFO Faker.BatchInsert - start commit batch count:600000  
    23:52:46.352 [pool-1-thread-1] INFO Faker.BatchInsert - end commit batch count:600000  
    23:52:52.042 [pool-1-thread-1] INFO Faker.BatchInsert - start commit batch count:650000  
    23:52:53.447 [pool-1-thread-1] INFO Faker.BatchInsert - end commit batch count:650000    
    23:53:00.700 [pool-1-thread-1] INFO Faker.BatchInsert - start commit batch count:700000   
    23:53:01.679 [pool-1-thread-1] INFO Faker.BatchInsert - end commit batch count:700000  
    23:53:07.510 [pool-1-thread-1] INFO Faker.BatchInsert - start commit batch count:750000  
    23:53:08.460 [pool-1-thread-1] INFO Faker.BatchInsert - end commit batch count:750000  
    23:53:14.445 [pool-1-thread-1] INFO Faker.BatchInsert - start commit batch count:800000  
    23:53:15.396 [pool-1-thread-1] INFO Faker.BatchInsert - end commit batch count:800000  
    23:53:21.306 [pool-1-thread-1] INFO Faker.BatchInsert - start commit batch count:850000  
    23:53:21.930 [pool-1-thread-1] INFO Faker.BatchInsert - end commit batch count:850000  
    23:53:27.923 [pool-1-thread-1] INFO Faker.BatchInsert - start commit batch count:900000  
    23:53:28.764 [pool-1-thread-1] INFO Faker.BatchInsert - end commit batch count:900000      
    23:53:34.718 [pool-1-thread-1] INFO Faker.BatchInsert - start commit batch count:950000    
    23:53:35.597 [pool-1-thread-1] INFO Faker.BatchInsert - end commit batch count:950000  
    23:53:41.357 [pool-1-thread-1] INFO Faker.BatchInsert - start commit batch count:1000000   
    23:53:41.995 [pool-1-thread-1] INFO Faker.BatchInsert - end commit batch count:1000000   
    count : 1000000 -- commitThreshold : 50000 -- time : 137    

插入100万数据,提交阈值5万,消耗时间137秒
# 不使用上述参数
## mysql.url=jdbc:mysql://127.0.0.1:3306/fcy
    23:57:28.578 [pool-1-thread-1] INFO Faker.BatchInsert - fcy.batch表已存在!  
    insert into fcy.batch values(0,?,?,?,?,?,?,?,?,?,?)  
    23:57:35.956 [pool-1-thread-1] INFO Faker.BatchInsert - start commit batch count:50000  
    23:57:40.214 [pool-1-thread-1] INFO Faker.BatchInsert - end commit batch count:50000  
    23:57:45.963 [pool-1-thread-1] INFO Faker.BatchInsert - start commit batch count:100000  
    23:57:50.260 [pool-1-thread-1] INFO Faker.BatchInsert - end commit batch count:100000  
    23:57:56.091 [pool-1-thread-1] INFO Faker.BatchInsert - start commit batch count:150000  
    23:58:00.039 [pool-1-thread-1] INFO Faker.BatchInsert - end commit batch count:150000  
    23:58:05.521 [pool-1-thread-1] INFO Faker.BatchInsert - start commit batch count:200000  
    23:58:09.610 [pool-1-thread-1] INFO Faker.BatchInsert - end commit batch count:200000  
    23:58:15.185 [pool-1-thread-1] INFO Faker.BatchInsert - start commit batch count:250000  
    23:58:19.176 [pool-1-thread-1] INFO Faker.BatchInsert - end commit batch count:250000  
    23:58:24.734 [pool-1-thread-1] INFO Faker.BatchInsert - start commit batch count:300000  
    23:58:28.957 [pool-1-thread-1] INFO Faker.BatchInsert - end commit batch count:300000  
    23:58:34.755 [pool-1-thread-1] INFO Faker.BatchInsert - start commit batch count:350000  
    23:58:39.462 [pool-1-thread-1] INFO Faker.BatchInsert - end commit batch count:350000  
    23:58:45.359 [pool-1-thread-1] INFO Faker.BatchInsert - start commit batch count:400000  
    23:58:49.335 [pool-1-thread-1] INFO Faker.BatchInsert - end commit batch count:400000  
    23:58:54.983 [pool-1-thread-1] INFO Faker.BatchInsert - start commit batch count:450000  
    23:58:58.967 [pool-1-thread-1] INFO Faker.BatchInsert - end commit batch count:450000  
    23:59:04.900 [pool-1-thread-1] INFO Faker.BatchInsert - start commit batch count:500000  
    23:59:08.945 [pool-1-thread-1] INFO Faker.BatchInsert - end commit batch count:500000  
    23:59:14.763 [pool-1-thread-1] INFO Faker.BatchInsert - start commit batch count:550000  
    23:59:19.243 [pool-1-thread-1] INFO Faker.BatchInsert - end commit batch count:550000  
    23:59:25.026 [pool-1-thread-1] INFO Faker.BatchInsert - start commit batch count:600000  
    23:59:29.572 [pool-1-thread-1] INFO Faker.BatchInsert - end commit batch count:600000  
    23:59:35.355 [pool-1-thread-1] INFO Faker.BatchInsert - start commit batch count:650000  
    23:59:39.553 [pool-1-thread-1] INFO Faker.BatchInsert - end commit batch count:650000  
    23:59:45.238 [pool-1-thread-1] INFO Faker.BatchInsert - start commit batch count:700000  
    23:59:49.337 [pool-1-thread-1] INFO Faker.BatchInsert - end commit batch count:700000    
    23:59:54.981 [pool-1-thread-1] INFO Faker.BatchInsert - start commit batch count:750000  
    23:59:59.380 [pool-1-thread-1] INFO Faker.BatchInsert - end commit batch count:750000  
    00:00:05.283 [pool-1-thread-1] INFO Faker.BatchInsert - start commit batch count:800000  
    00:00:09.301 [pool-1-thread-1] INFO Faker.BatchInsert - end commit batch count:800000  
    00:00:14.915 [pool-1-thread-1] INFO Faker.BatchInsert - start commit batch count:850000  
    00:00:18.860 [pool-1-thread-1] INFO Faker.BatchInsert - end commit batch count:850000  
    00:00:24.429 [pool-1-thread-1] INFO Faker.BatchInsert - start commit batch count:900000  
    00:00:28.457 [pool-1-thread-1] INFO Faker.BatchInsert - end commit batch count:900000  
    00:00:34.654 [pool-1-thread-1] INFO Faker.BatchInsert - start commit batch count:950000  
    00:00:38.480 [pool-1-thread-1] INFO Faker.BatchInsert - end commit batch count:950000  
    00:00:44.143 [pool-1-thread-1] INFO Faker.BatchInsert - start commit batch count:1000000   
    00:00:48.375 [pool-1-thread-1] INFO Faker.BatchInsert - end commit batch count:1000000   
    count : 1000000 -- commitThreshold : 50000 -- time : 199 

插入100万数据,提交阈值5万,消耗时间199秒
# 原理:mysql重写提交的语句
将
insert into x values (a1)
...
insert into x values (an)
重写成
insert into x values (a1),...,(an)

## 参考
https://stackoverflow.com/questions/2993251/jdbc-batch-insert-performance
# 是否需要关闭Statement和ResultSet
>The reason I say its good practice... For example, if for some reason you are using a "primitive" type of database pooling and you call connection.close(), the connection will be returned to the pool and the ResultSet/Statement will never be closed and then you will run into many different new problems!

	如果在使用连接池的时候你只调用了connection.close()方法而没有关闭Statement和ResultSet
	那么你将会遇到许多不同的新问题
>You should close ResultSet and Statement explicitly because Oracle has problems previously with keeping the cursors open even after closing the connection. If you don't close the ResultSet (cursor) it will throw an error like Maximum open cursors exceeded

    这个我也碰到过，在Oracle中没关闭statement和resultSet后抛出异常
