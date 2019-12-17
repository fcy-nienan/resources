+ Table
+ Region
+ Store
+ MemStore FileStore Block
+ Region和Store是一对多的关系,分别对于Region的ColumnFamily
+ Store是一个抽象的概念，具体的是MemStore和FileStore
+ scan 'prop_veh_manags',{LIMIT=>1}
+ count 'prop_veh_manags'
+ desc 'prop_veh_manags'
+ get 'tableName','rowKey',{
+ hbase hbck 'prop_veh_manags'查看hbase健康状况
