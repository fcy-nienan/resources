# sqlplus使用
    登录sqlplus zxmd/Cpic\@4321@10.186.72.158:1521/cisdb
    导入数据@E:\\1.sql
    alter table table_name drop column field_name


    sqlplus /nolog
    conn user/passwd@ip:port/service
    如果密码含有英文则可以将其用双引号括起来
    conn user/"pass@pass"@ip:port/service
    
    sqlplus控制台乱码
    select userenv('language') from dual
    export NLS_LANG='$RESULT'
    
    sqlplus输出不友好
        设置不输出标题头:set heading off;
        setting wrap will not your data and it will display properly !
        也就是这个字段时varchar(255),如果不设置这个他会输出255个字符,设置了之后就会只输出有值的部分
        set warp off;
        set linesize 160;
# how oracle works?
    you want to get data with a filter and rownum=2,
    first Oracle executes the sql with filter and get the first record,
    give it the rownum 1,
    and then compare it the rownum filter rownum=2, which doesn't match, so discard record,
    then get second record, give it rownum=1(if the first record is matched then the rownum will  be 2)  too, then do the compare............
    
    When assigning ROWNUM to a row,
    Oracle starts at 1 and only only increments the value when a row is selected;
    that is, when all conditions in the WHERE clause are met.
    Since our condition requires that ROWNUM is greater than 2,
    no rows are selected and ROWNUM is never incremented beyond 1.
    
    https://docs.oracle.com/cd/B14117_01/server.101/b10759/pseudocolumns008.htm
    
    https://blogs.oracle.com/oraclemagazine/on-rownum-and-limiting-results
# 导入导出
    exp zxmdapp/passwd@10.180.178.4:1522/cisdb file=~/security_user.dmp
    imp zxmdapp/passwd@10.180.178.4:1522/cisdb file=~/security_user.dmp
# 外键删除出错
    这是因为在建立外键关联的时候没有设置级联删除，也就是
    在设置外键的时候没有加上on delete cascade限定
# 序列号
    create sequence zxmd.seq_v_activity_id
    minvalue 1
    maxvalue 99999999
    start with 1000
    increment by 1
    cache 200;
    
    create or replace synonym zxmdapp.seq_v_activity_id for zxmd.seq_v_activity
    
    grant select on seq_v_activity_id to zxmdapp
# Oracle分区

    oracle有三种分区方式
    range,list,hash
    范围分区,列表分区,哈希分区
    还有复合分区
    range+list
    range+hash
    其他不行,只能这两种符合分区
    select * from user_tab_partitions where table_name='';
    
    查询某一分区数据
    select * from table partition(partitionName)
    
    create table cd_oracle(
    cd_id string,
    sub_company string,
    sup_company string,
    final_date string)
    partition by range(sub_company) subpartition by list(final_date)
    (
        partition part_3010100 values less than values('4010100')
        (
            partition part_3010100_01 values('01'),
            partition part_3010100_02 values('02')
        ),
        partition part_4010100 values less than values('5010100')
        (   
            partition part_3010100_01 values('01'),
            partition part_3010100_02 values('02')
        )
    )
# oracle 命令
    查看所有表空间信息
    select * from dba_tablespace;
    查看临时表空间
    select * from dba_temp_files;
    查看所有表空间大小
    select * from dba_data_files;
# Oracle连接数
    --当前连接数
    select count(*) from v$process;


​    
    --允许最大连接数 （默认是150）
    select value from v$parameter where name = 'processes';
    
    alter system set processes = 300 scope =spfile; 
# oracle maximum open cursor exceeded
    关闭prepareSment和ResultSet 
# jdbc占位符
    update table set name=? ,age=? where id=?
    jdbc会自动为占位符加上单引号，所以如果是字符串类型的话不需要特殊处理
    那其他数字类型的加了占位符会相等吗？能成功赋值吗？
# 查询正在执行的sql和session

    SELECT b.sid oracleID,
           b.username 登录Oracle用户名,
           b.serial#,
           spid 操作系统ID,
           paddr,
           sql_text 正在执行的SQL,
           b.machine 计算机名
    FROM v$process a, v$session b, v$sqlarea c
    WHERE a.addr = b.paddr
       AND b.sql_hash_value = c.hash_value
       
    查询oracle的连接数
    select count(*) from v$session;
    查询oracle当前的的并发连接数
    select count(*) from v$session where status='ACTIVE';
    查询允许的最大连接数
    select value from v$parameter where name = 'processes';
# java.sql.SQLException: 批处理中出现错误: batch must be either executed or cleared
    应该是使用executeBatch
    而我错误的写成了executeUpdate
# dba_data_files表信息
    https://docs.oracle.com/cd/B19306_01/server.102/b14237/statviews_3083.htm#REFRN23049
# 查看Oracle定义的函数源码
    SELECT * FROM  USER_PROCEDURES;
    SELECT * FROM USER_SOURCE WHERE NAME = 'COMPUTERFEE';
# oracle按照中文拼音排序
    nlssort (name ,nsl_sort='schinese_pinyin_m');
# oracle查看from后面的是表还是视图
    select * from all_objects;
# 查看建视图语句
    select * from user_views 
# 连接字符串
    select id||'-'||name||'-' from user;
    select  
# 查看建表语句
    select dbms_metadata.get_ddl('TABLE','EMPLOYEES') from dual;
# char和varchar和varchar2
    char是定长的
    varchar是标准的sql类型,变长
    varchar2是Oracle的类型,变长