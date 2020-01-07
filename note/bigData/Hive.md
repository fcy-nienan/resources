Hive为什么需要mysql?
hive只是个工具，包括它的数据分析，依赖于mapreduce，它的数据管理，依赖于外部系统
在应用层面我们可以把hive堪称一个mysql数据库

数据存储在hdfs上,数据库的一些元数据存储在其他存储介质中
查询依赖mapreduce

默认的元数据存储在自动的Derby数据库中,但同时只能有一个会话

hive以调试模式启动
hive -hiveconf hive.root.logger=DEBUG,console








执行Hive前, 须先启动metastore服务, 否则会报错 
hive --service metastore

hive的日志
HIVE自身翻译成为MR之前的解析错误
Hadoop文件系统的错误
YARN调度过程中的错误




nvl函数
	nvl(value,default_value);return the default_value if the value is null else the value;
	select nvl(null,123)-->result=123;
	select nvl('nie',456)-->result=nie;
concat函数
	concat('nie','nan','fcy')-->result=nienanfcy
	concat_ws(',','nie','nan','fcy')-->result=nie,nan,fcy
	
不能直接向分区表加载数据，必须在加载数据之前明确加载到哪一个分区中，也就是子文件夹中。
insert into table test PARTITION(username='admin') select starttime, endtime, title from test2 where username = 'admin';


hive有hive on mapreduce 和 hive on spark

mapreduce=map+reduce
spark=job,dag,stage,task


hive命令行显示当前数据库
select current_database();
查看当前表所有分区
show partitions table_name;



ROW FORMAT?
INPUTFORMAT?
OUTPUTFORMAT?

将数据根据某个字段动态插入分区表
set hive.exec.dynamic.partition.mode = nonstrict
insert into table tableName partition(date) select * from tableOther;
显示表结构
desc tableName

显示表详细结构
desc formatted tableName
# 创建分区表
    create table tableName(
    id string,
    name string,
    password string
    date string)
    partitioned by (date)
    row format delimited by ',' terminated by '\t'
    
    create table  person(name string,work_locations array<string>)
    ROW FORMAT DELIMITED
    FIELDS TERMINATED BY '\t'
    COLLECTION ITEMS TERMINATED BY ',';
    
    create table score(name string, score map<string,int>)  
    ROW FORMAT DELIMITED 
    FIELDS TERMINATED BY '\t'  
    COLLECTION ITEMS TERMINATED BY ','   
    MAP KEYS TERMINATED BY ':';
    
    CREATE TABLE test(id int,course struct<course:string,score:int>)
    ROW FORMAT DELIMITED
    FIELDS TERMINATED BY '\t'
    COLLECTION ITEMS TERMINATED BY ',';
    
    create table test1(id int,a MAP<STRING,ARRAY<STRING>>)
    row format delimited fields terminated by '\t'   
    collection items terminated by ',' 
    MAP KEYS TERMINATED BY ':';

    1 english:80,90,70
    2 math:89,78,86
    3 chinese:99,100,82
    
    LOAD DATA LOCAL INPATH '/home/hadoop/test1.txt' OVERWRITE INTO TABLE test1;
    

    