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

# 查看建表语句  desc table_name

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
# 导入导出
    exp zxmdapp/passwd@10.180.178.4:1522/cisdb file=~/security_user.dmp
    imp zxmdapp/passwd@10.180.178.4:1522/cisdb file=~/security_user.dmp
# 外键删除出错
    这是因为在建立外键关联的时候妹纸设置级联删除，也就是
    在设置外键的时候没有加上on delete cascade限定