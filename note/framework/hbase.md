+ Table
+ Region
+ Store
+ MemStore FileStore Block
+ Region和Store是一对多的关系,分别对于Region的ColumnFamily
+ Store是一个抽象的概念，具体的是MemStore和FileStore
+ scan 'prop_veh_manags',{LIMIT=>1}
+ count 'prop_veh_manags'
+ desc 'prop_veh_manags'
+ get 'tableName','rowKey',{COLUMN=>'family:column'}
+ hbase hbck 'prop_veh_manags'查看hbase健康状况

# 从数据的角度分析
一个表多个region
一个region代表多少行数据
最开始只有一个region
然后会慢慢的分裂,分裂后HMaster出于负载均衡的考虑会将
新生成的Region分配给其他RegionServer管理
但此时给RegionServer管理的Region不在其本地
直到下一次Major Compaction发生将数据下载到本地

一个region有多个Store,所以一个region上有多个MemStore和更多个FileS tore
每个Store代表一个列族
每个Store又包含一个MemStore和0个或者多个FileS tore

整个表横向分割有了Region的概念
一个Region纵向分割有了Store的概念(column family)
Store又由两部分组成
    MemStore:存于内存的一部分数据
    FileStore:存于磁盘的一部分数据


# 从物理架构角度分析
一个HMaster
多个RegionServer
每个Region Server管理多个Region
每个Region Server
    Region Server管理的
    有一个WAL,写入到MemStore时先写入到WAL中
    一个Block Cache读缓存,满时读取频率最低的数据被换出(LFU)
    MemStore
    StoreFile(HFile):

# 如何查询
有一个Meta Table保存在Zookeeper上,里面存了所有Region的信息
这个表的结构类似于
key:rowKey,regionId
value:regionServer
一个类似于Map的结构
可以通过rowKey查找到具体在哪个region Server上

# 写数据
先写入WAL,然后再写入MemStore
MemStore达到指定大小flush到磁盘

# 合并
## Minor Compaction
将几个小的HFile合并为一个大的HFile
## Major Compaction
将所有的HFile合并为一个HFile,并删除过期的Cell
Major Compaction期间该Region不可访问

# 核心结构
底层数据结构是LSM树


# 其他零碎
hbase shell中可以直接写ruby
HDFS的/hbase目录有关于hbase的一些信息
WAL日志存储在HDFS上

# 预分区
最初只有一个Region
当插入的数据越来越多的时候Region会分裂
rowkey默认是字典序
我们往hbase中插入数据的时候只在最后一个Region上插入(最后的排序rowkey)
此时会造成热点问题,RegionTooBushException
我们肯定想在插入的时候将数据均匀的插入到每个Region
所以可以在建表的时候提前分好区
然后在插入的时候就可以多台服务器并行插入了,各自负责各自region的rowkey范围的插入

# command
    创建表
    
    create '表名称', '列名称1','列名称2','列名称N'
    
    添加记录      
    
    put '表名称', '行名称', '列名称:', '值'
    
    查看记录
    
    get '表名称', '行名称'
    
    查看表中的记录总数
    
    count  '表名称'
    
    删除记录
    
    delete  '表名' ,'行名称' , '列名称'
    
    删除一张表
    
    先要屏蔽该表，才能对该表进行删除，第一步 disable '表名称' 第二步  drop '表名称'
    
    查看所有记录
    
    scan "表名称"  
    
    查看某个表某个列中所有数据
    
    scan "表名称" , ['列名称:']
    
    更新记录 
    
    就是重写一遍进行覆盖