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