分布式和集群
分布式一致性
CAP
数据一致性
最终一致性
柔性事务
两阶段提交
三阶段提交
消息一致性
缓存击穿
缓存穿透
缓存雪崩
数据库事务隔离级别
负载均衡

cpu更新内存中的数据到磁盘(页缓存)
    write-through
    write-back
    write-post

# 三阶段提交
	canCommit
		类似于两阶段提交的准备阶段
	prepareCommit
		记录undo日志和redo日志
	doCommit
		执行真正的事务操作
# 分布式锁
	需要考虑的问题
	任何时间点机器都可能宕机,我们如果要开发稳定的程序的话需要考虑
	锁超时
	锁重入
	多线程


​	
