Hive为什么需要mysql?
hive只是个工具，包括它的数据分析，依赖于mapreduce，它的数据管理，依赖于外部系统
在应用层面我们可以把hive堪称一个mysql数据库

数据存储在hdfs上,数据库的一些元数据存储在其他存储介质中


默认的元数据存储在自动的Derby数据库中,但同时只能有一个会话
# hive架构
User Interface  用户接口
MetaData        元数据存储
Sql Engine      sql引擎
MapReduce(Spark Rdd)        执行引擎
HDFS Storage                底层存储

JobTracker
TaskTracker
    Map
    Reducer
# 分区,分桶,动态分区
    分桶是更具某一列取模
    id,score
    1,  10
    2,  20
    2,  30
    4,  40
    如果当前有两个分区
    分区一 1,10
    分区二 2,20
           2,30
           4,35
    HDFS上存储的文件(假如一行数据一个文件):
        partition1/(1,10)
        partition2/(2,20)   partition2(2,30) partition3(4,35)
     然后又按照score分桶分为两个桶score%2
     那么会产生四个文件
        partiont1/(1,10) partition1/()
        partition2/(2,20),(2,30)   partition2(4,35)
    也就是根据分桶的字段取模
    也可以理解为reducer的个数
    
    create table score(id bigint,score bigint)
    partitioned by (workdate string)
    clustered by (score) sorted by (score desc) into 2 buckets
    row formatted dilimited
    fields terminated by '\t'

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
set hive.exec.dynamic.partition =true（默认false）,表示开启动态分区功能
set hive.exec.dynamic.partition.mode = nonstrict,表示允许所有分区都是动态的，否则必须有静态分区字段
insert into table tableName partition(date) select * from tableOther;
显示表结构
desc tableName

显示表详细结构
desc formatted tableName

# DataFrame.registerTempTable()
    为什么要注册临时表？
    通过DATa Frame的一些函数同样可以操作数据进行sql类似的查询
    什么时候需要注册临时表呢？
    还是说注册了临时表会比使用DATa Frame的函数操作效率更高？
    
    注册临时表的原因是你还有另一种选择可以对这些数据进行操作
    注册了临时表后我们可以通过SQL查询来进行操作
    sql有sql的特性，函数有函数的特性，各有优势
    效率相差不大

# 创建分区表
    create table tableName(
    id string,
    name string,
    password string)
    partitioned by (date string)
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
    
# hive命令
>https://cwiki.apache.org/confluence/display/Hive/GettingStarted
## DML
load data local inpath 'path' overwrite into table fcy;
local指明从本地文件系统加载,忽略他的话从HDFS上
overwrite指明已经存在的数据会被删除,忽略的话就是追加数据
load data inpath 'path' into table fcy partitioned (workdate='2019-12-12')
加载数据进表的某个分区

SQL

    hive> INSERT OVERWRITE TABLE events SELECT a.* FROM profiles a;
    hive> INSERT OVERWRITE TABLE events SELECT a.* FROM profiles a WHERE a.key < 100;
    hive> INSERT OVERWRITE LOCAL DIRECTORY '/tmp/reg_3' SELECT a.* FROM events a;
    hive> INSERT OVERWRITE DIRECTORY '/tmp/reg_4' select a.invites, a.pokes FROM profiles a;
    hive> INSERT OVERWRITE DIRECTORY '/tmp/reg_5' SELECT COUNT(*) FROM invites a WHERE a.ds='2008-08-15';
    hive> INSERT OVERWRITE DIRECTORY '/tmp/reg_5' SELECT a.foo, a.bar FROM invites a;
    hive> INSERT OVERWRITE LOCAL DIRECTORY '/tmp/sum' SELECT SUM(a.pc) FROM pc1 a;
# DDL

    CREATE TABLE pokes (foo INT, bar STRING);
    
    CREATE TABLE invites (foo INT, bar STRING) PARTITIONED BY (ds STRING);
    
    craete table fcy like fcy1;复制表结构
    
    create table fcy as select * from fcy1;
    
    SHOW TABLES;
    
    SHOW TABLES '.*s';
     
    DESCRIBE invites;
    
    hive> ALTER TABLE events RENAME TO 3koobecaf;
    hive> ALTER TABLE pokes ADD COLUMNS (new_col INT);
    hive> ALTER TABLE invites ADD COLUMNS (new_col2 INT COMMENT 'a comment');
    hive> ALTER TABLE invites REPLACE COLUMNS (foo INT, bar STRING, baz INT COMMENT 'baz replaces new_col2');
    ALTER TABLE invites REPLACE COLUMNS (foo INT COMMENT 'only keep the first column');
    
    增加分区
    ALTER TABLE c02_clickstat_fatdt1 ADD 
    PARTITION (dt='20131202') location '/user/hive/warehouse/c02_clickstat_fatdt1/part20131202' 
    PARTITION (dt='20131203') location '/user/hive/warehouse/c02_clickstat_fatdt1/part20131203';
    
    删除分区
    ALTER TABLE c02_clickstat_fatdt1 DROP PARTITION (dt='20101202');
    
    重命名表
    ALTER TABLE table_name RENAME TO new_table_name
    
    修改列信息
    ALTER TABLE table_name CHANGE [COLUMN] col_old_name col_new_name column_type [COMMENT col_comment] [FIRST|AFTER column_name]
    
    增加或者替换列
    ALTER TABLE table_name ADD|REPLACE COLUMNS (col_name data_type [COMMENT col_comment], ...)
    
    创建视图
    CREATE VIEW [IF NOT EXISTS] view_name [ (column_name [COMMENT column_comment], ...) ]
    [COMMENT view_comment]
    [TBLPROPERTIES (property_name = property_value, ...)]
    AS SELECT ...
    
    查看分区信息
    DESCRIBE EXTENDED page_view PARTITION (ds='2013-08-08');
    
    导出数据
    FROM src
      INSERT OVERWRITE TABLE dest1 SELECT src.* WHERE src.key < 100
      INSERT OVERWRITE TABLE dest2 SELECT src.key, src.value WHERE src.key >= 100 and src.key < 200
      INSERT OVERWRITE TABLE dest3 PARTITION(ds='2013-04-08', hr='12') SELECT src.key WHERE src.key >= 200 and src.key < 300
      INSERT OVERWRITE LOCAL DIRECTORY '/tmp/dest4.out' SELECT src.value WHERE src.key >= 300;
    
    SELECT (ds|hr)?+.+ FROM sales
    
    SHOW FUNCTIONS;
    
    DESCRIBE FUNCTION <function_name>;
    
    explode打散
    collecton_list组合
    
    DROP TABLE pokes;
    
    CREATE TABLE u_data (
      userid INT,
      movieid INT,
      rating INT,
      unixtime STRING)
    ROW FORMAT DELIMITED
    FIELDS TERMINATED BY '\t'
    STORED AS TEXTFILE;
    
    
    如果文件数据是纯文本，可以使用 STORED AS TEXTFILE。如果数据需要压缩，使用 STORED AS SEQUENCE

    
    CREATE TABLE apachelog (
      host STRING,
      identity STRING,
      user STRING,
      time STRING,
      request STRING,
      status STRING,
      size STRING,
      referer STRING,
      agent STRING)
    ROW FORMAT SERDE 'org.apache.hadoop.hive.serde2.RegexSerDe'
    WITH SERDEPROPERTIES (
      "input.regex" = "([^]*) ([^]*) ([^]*) (-|\\[^\\]*\\]) ([^ \"]*|\"[^\"]*\") (-|[0-9]*) (-|[0-9]*)(?: ([^ \"]*|\".*\") ([^ \"]*|\".*\"))?"
    )
    STORED AS TEXTFILE;
    
# Metadata Store
    hive使用内嵌的一个Derby数据库存储元数据
    同一时间只能又一个Connection