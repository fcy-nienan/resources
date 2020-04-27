
# mysql将数据导入文件
    SELECT * FROM passwd INTO OUTFILE '/tmp/runoob.txt'
    FIELDS TERMINATED BY ',' ENCLOSED BY '"'
    LINES TERMINATED BY '\r\n';
# leetcode习题
+ 查询结果的第几行通过limit 1,1获取
+ 查询结果为NULL通过函数IFNULL
+ 列选择中用if: select a.Score,sum(if(b.Score>=a.Score,1,0)) as Rank
## 查询第二高的薪水
    select IFNULL((select distinct(Salary) from employee order by Salary desc limit 1,1),null) as SecondHighestSalary
## 第N高的薪水
    CREATE FUNCTION getNthHighestSalary(N INT) RETURNS INT
    BEGIN
    set N=N-1;
      RETURN (
          select DISTINCT(Salary)  
                          from employee  
                          order by Salary desc limit N,1
      );
    END
## 分数排名
    select a.Score, sum(if(b.Score>=a.Score,1,0)) as Rank from Scores a, (select distinct Score from Scores ) b group by a.id order by a.Score desc;
    group by后表的数据并没有消失,还是可以在那个if中使用,可以理解为groupby之后成了一行数据,但是没其中的列中存在其他
    数据,但是显示给用户的是第一个数据
    
    select score,(select count(DISTINCT(score)) from Scores where score>=s.score) 
    from Scores s order by score desc;
        这种方式虽然很简单，但是 在select语句中使用子查询来生成rank，相当于对每一条记录都需要查询一次scores表，查询次数为 （记录条数^2），会很慢，而且在数据量稍大的情况下真的可取吗
    
    select distinct Num as ConsecutiveNums
    from (
      select Num,
        case
          when @prev = Num then @count := @count + 1
          when (@prev := Num) is not null then @count := 1
        end as CNT
      from Logs, (select @prev := null,@count := null) as t
    ) as temp
    where temp.CNT >= 3

## 从不订购的客户
    select a.Name as Customers from Customers a left join Orders b on a.id=b.CustomerId
    where b.CustomerId is null
## 部门工资最高的员工
    select b.Name as Department,a.Name as Employee , a.Salary as Salary
    from Employee a inner join Department b on b.id=a.DepartmentId 
    and a.Salary = (select max(Salary) as Salary from Employee 
                   where departmentId=b.id)		   
## 部门工资前三高的员工
    SELECT 
    P2.Name AS Department,P3.Name AS Employee,P3.Salary AS Salary
    FROM Employee AS P3
    INNER JOIN Department AS P2
    ON P2.Id = P3.DepartmentId 
    WHERE (
        SELECT COUNT(DISTINCT Salary)
        FROM Employee AS P4
        WHERE P3.DepartmentId = P4.DepartmentId
        AND P4.Salary >= P3.Salary
    ) <= 3
    ORDER BY DepartmentId,Salary DESC
        如果没有where子查询得出的结果是按部门排序的多条记录,通过子查询在表中查找同部门中大于等于该条记录
        薪水的数据条数,数据条数<=3才能筛选出来
     select
            d.Name Department, e1.Name Employee, e1.Salary Salary
        from 
            Employee e1, Employee e2, Department d 
        where     
            e1.DepartmentId = e2.DepartmentId
        and 
            e2.Salary >= e1.Salary
        and
            e1.DepartmentId = d.Id
        group by
            e1.Name
        having count(distinct e2.Salary) <= 3
        order by
            d.Name, e1.Salary desc 
## 删除重复的电子邮箱
    delete p1 from Person p1,Person p2 where p1.id>p2.id and p1.Email=p2.Email
        不能先select出同一表中的某些值，再update这个表(在同一语句中) 
    create table tmp as select min(id) as col1 from blur_article group by title;
    delete from blur_article where id not in (select col1 from tmp); 
    drop table tmp;
        通过创建临时表实现
    delete from Person where id not in (select id from (select min(id) as id from Person group by Email) as a)
        虽然不能先select在update,但可以通过上面的方式实现     
## 上升的温度
    select w.id from Weather w,Weather w2 
     where w.RecordDate=date_add(w2.RecordDate,INTERVAL 1 DAY) 
    and w.Temperature>w2.Temperature
## 换座位
    select 
    if((mod(id,2)=1 and id=(select max(id) from seat)),id,if(mod(id,2)=1,id+1,id-1)) as id,student 
    from seat order by id;
    
    select (case
          when mod(id,2)!=0 and id!=counts then id+1
          when mod(id,2)!=0 and id=counts then id
          else id-1 end)as id,student
          from seat,(select count(*)as counts from seat)as seat_counts
                    order by id;
                    
    select 
        (case when id % 2 = 0 then id - 1
            when id % 2 = 1 and id <> c.cnt then id + 1
            else id
         end) as id, student
    from 
        seat,
        (select count(id) as cnt from seat) as c
    order by id
## 体育馆的人流量
    select distinct d.id,d.date,d.people from stadium a , stadium b , stadium c, stadium d
    where a.people>=100 and b.people>=100 and c.people>=100 
     and a.id+1=b.id and b.id+1=c.id and d.id in (a.id,b.id,c.id)   
## 交换工资
    update salary set sex = 
        case 
            when sex = 'f' then 'm'
            else 'f'
        end
    update salary set sex=
        case sex when 'f' then 'm'
        else 'f'
        end
## 超过5名学生的课
    select class from courses group by class having count(distinct student)>=5
# mysql函数示例
## 相关日期函数
+ 字符串转化为日期str_to_date('2018-12-12','%Y-%m-%d');
+ 当前日期curDate()
+ 当前时间curtime()
+ date_add(now(),interval 1 day)为当前日期加上一天
+ date_add(now(),interval '1 1:1:1' day_second)为当前日期加上一天一小时一分钟一秒
+ hour(now())返回当前日期的小时
+ day(now())返回当前日期的日
+ year(now())返回当前日期的年
+ monthname(now())当前月份的名字
+ minute(now())分钟
+ week(now())周
## 字符串函数
    id name parent_id
    1	test  0
    2	test2 0
    3	test3 1
    4 	test4 1
### select concat(id,name,parent_id) from table;
    1test0
    2test20
    3test31
    4test41
### select concat_ws(',',id,name,parent_id) from table;
    1,test,0
    2,test2,0
    3,test3,1
    4,test4,1
### select parent_id,group_concat(id),group_concat(name) from table;
    0	1,2		test,test2
    1   3,4     test3,test4
### find_in_set(str,strlist);
    在strlist列表中返回str的下标
    select find_in_set('b','a','c','b','d');
    结果  3



# 左连接 
#### 表fcy_a
     id  tel 
     1    2  
     1    3  
     1    4  
#### 表fcy_b
     id  tel 
     1    2  
     1    3   
#### select * from fcy_a t1 left join fcy_b t2
    1   2   1   2 
    1   2   1   3 
    1   3   1   2 
    1   3   1   3 
    1   4   1   2 
    1   4   1   3 
#### select * from fcy_a t1 left join fcy_b t2 on t1.id=t2.id and t1.tel=t2.tel
    1   2   1   2
    1   3   1   3
    1   4   1   null
#### select * from fcy_a t1 left join fcy_b t2 on t1.id=t2.id and t1.tel=t2.tel and t2.tel is null
    1   2   1   null
    1   3   1   null
    1   4   1   null
#### 在笛卡尔集上通过on中的所有条件进行筛选,这里并不是一个条件就生成一个临时表的(我之前就是这样错误的认识)


# MySQL中SELECT语句的基本语法是
    SELECT?[STRAIGHT_JOIN]?[SQL_SMALL_RESULT]?
    
    [SQL_BIG_RESULT]?[HIGH_PRIORITY]?
    
    [DISTINCTDISTINCTROWALL]?select_list
    
    ?[INTO?{OUTFILEDUMPFILE}?''file_name''?export_options]?
    
    [FROM?table_references?
    
    [WHERE?where_definition]?
    
    [GROUP?BY?col_name,...]?
    
    [HAVING?where_definition]
    
    ?[ORDER?BY?{unsighed_integercol_nameformura}?[ASCDESC],...]?
    
    [LIMIT?[offset,]?rows]?[PROCEDURE?procedure_name]]?

STRAIGHT_JOIN:直接连接
SQL_SMALL_RESULT:小数据集
SQL_BIG_RESULT:大数据集
从这个基本语法可以看出，最简单的SELECT语句是SELECT?select_list，
实际上利用这个最简单的SELECT语句，你也可以完成许多你期待的功能
，首先你能利用它进行MySQL所支持的任何运算，例如：SELECT?1+1，
它将返回2；其次，你也能利用它给变量赋值，而在PHP中，运用SELECT语句的这种功能，
你就可以自由地运用MySQL的函数为PHP程序进行各种运算，并赋值给变量。
在很多的时候，你会发现MySQL拥有许多比PHP更为功能强大的函数。?
STRAIGHT_JOIN、SQL_SMALL_RESULT、SQL_BIG_RESULT、HIGH_PRIORITY
是MySQL对ANSISQL92的扩展。如果优化器以非最佳次序联结表，使用STRAIGHT_JOIN可以加快查询。
SQL_SMALL_RESULT和SQL_BIG_RESULT是一组相对的关键词。
它们必须与GROUPBY、DISTINCT或DISTINCTROW一起使用。
SQL_SMALL_RESULT告知优化器结果会很小，要求MySQL使用临时表存储最终的表而不是使用排序；
反之，SQL_BIG_RESULT告知优化器结果会很小，要求MySQL使用排序而不是做临时表。
HIGH_PRIORITY将赋予SELECT比一个更新表的语句更高的优先级，使之可以进行一次优先的快速的查询。
以上四个关键词的使用方法的确比较晦涩。幸运的是，在绝大多数情况下，
在MySQL中我们完全可以选择不使用这四个关键词。
DISTINCT、DISTINCTROW对查询返回的结果集提供了一个最基本但是很有用的过滤。
那就是结果集中只含非重复行。在这里要注意的是，对关键词DISTINCT、DISTINCTROW来说，
空值都是相等的，无论有多少NULL值，只选择一个。而ALL的用法就有画蛇添足之嫌了。
它对结果集的产生没有任何影响。
INTO{OUTFILEDUMPFILE}''file_name''export_options，将结果集写入一个文件。
文件在服务器主机上被创建，并且不能是已经存在的。语句中的export_options部分的
语法与用在LOADDATAINFILE语句中的FIELDS和LINES子句中的相同，
我们将在MySQL进阶_LOAD?DATA篇中详细讨论它。而OUTFILE与DUMPFILE的关键字的区别是：
后前只写一行到文件，并没有任何列或行结束。







mysql中使用full join出错
select * from t full join m on t.id=m.id;
unknown column t.id in on clause

原因：FULL JOIN is not supported by MySQL. It's because full is recognized as alias to t table. 