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

