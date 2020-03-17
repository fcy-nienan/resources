# frm,MYD,MYI
    frm是表的schema
    MYD是数据文件
    MYI是索引
    *.frm是描述了表的结构，*.MYD保存了表的数据记录，*.MYI则是表的索引
# 命令
    alter table tableName add column id int;
    为没有id的表赋值一个递增id
    create table tt as 
    select @rownum:=@rownum+1 as id,
    username,
    password,
    email,
    cardno from new12306;
    
    alter table tt rename to new12306;
    
    show variables like '%secure%';
    
    select * from new12306 into outfile '12306.txt' 
    fields terminated by ',' enclosed by '"'
    lines terminated by '\r\n';
    默认位置为mysql当前库中的表数据文件路径
    
    ERROR 1290 (HY000): The MySQL server is running with the –secure-file-priv option so it cannot execute this statement.
    设置安全目录:secure-file-priv="D:/"
# mysql的事务
    默认是自动提交
    如果要手动提交的话需要 start transaction
    savepoint是一个保存点
    然后可以rollback to savepoint name
    InnoDB supports the SQL statements SAVEPOINT, ROLLBACK TO SAVEPOINT, 
    RELEASE SAVEPOINT and the optional WORK keyword for ROLLBACK.
    
    The SAVEPOINT statement sets a named transaction savepoint with a name of the identifier.
     If the current transaction has a savepoint with the same name, 
     the old savepoint is deleted and a new one is set.
    
    The ROLLBACK TO SAVEPOINT statement rolls back a transaction to the named savepoint 
    without terminating the transaction. 
    Modifications that the current transaction made to rows after the savepoint 
    was set are undone in the rollback, 
    but InnoDB does not release the row locks that were stored in memory after the savepoint.
    
    https://www.w3resource.com/mysql/mysql-transaction.php
    
    
    设置事务隔离级别
    SET [GLOBAL | SESSION] TRANSACTION
        transaction_characteristic [, transaction_characteristic] ...
    	
    transaction_characteristic:      
        ISOLATION LEVEL level    
      | READ WRITE    
      | READ ONLY    
    
    level:       
      REPEATABLE READ     
      | READ COMMITTED     
      | READ UNCOMMITTED     
      | SERIALIZABLE
      
    With the GLOBAL keyword, the statement applies globally for all subsequent sessions. Existing sessions are unaffected.
    With the SESSION keyword, the statement applies to all subsequent transactions performed within the current session.
    Without any SESSION or GLOBAL keyword, the statement applies to the next (not started) transaction performed within the current session.
    加了GLOBAL,随后的所有session都是该级别,已经存在的不受影响
    加了SESSION,当前的session之后的所有session都是该级别
    啥都没加就是下一个session是设置的隔离级别 
# mysql的日志
    bin日志,数据改动的记录
    redo日志,数据写之前记录
    undo日志,数据写之后记录
    
    为啥要有这些日志,写的操作时包裹在事务中的,
    有可能发生事务写入前崩溃了,事务写入后崩溃了      1212而无人管很多方面v,基本你要我如何答题郭敬明v购买决策过后就明白你
    1
    2写之前记录一下,写入redo日志
    3写入数据,写入数据库
    4写之后记录一下,写入undo日志
    5
    详细考虑一下这几个时间段
    1,系统崩溃,不管,数据啥也没改变
    2,写完了系统崩溃
# mysql for loop
    ITERATE can appear only within LOOP, REPEAT, and WHILE statements. ITERATE means “start the loop again.”


    CREATE PROCEDURE insertData(p1 INT)
    BEGIN
        label1: LOOP
            SET p1 = p1 + 1;
            IF p1 < 10 THEN
                ITERATE label1;
            END IF;
            LEAVE label1;
        END LOOP label1;
        SET @x = p1;
    END;