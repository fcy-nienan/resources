# Join实现  
* full join  
* inner join  
* left join  
* right join  
下面两个之前一直有疑惑,后来查找资料发现是和left join 和right join 一样的效果的  
>This in essence means that there is no difference 
as to the result expected whether a left join is used or a left outer join is used.
The result will be similar, unless the environment is in the Microsoft SQL server.
The outer keyword can be used or even omitted without worry 
as the results do not differ in any way
Read more: Difference between Left Join and Left Outer Join | Difference Between http://www.differencebetween.net/technology/software-technology/difference-between-left-join-and-left-outer-join/#ixzz6BH0v0Jtg
* left outer join(实际就是left join)
* right outer join(实际就是right join)
# 
自己思考一下join如何写
数据有A表和B表,还有一个on的条件函数f(rowA,rowB),另外存储结果的容器L
inner join
for(rowA in A){
    for(rowB in B){
        if(f(rowA,rowB)){
            L.add(rowA,rowB)
        }
    }
}
left join
for(rowA in A){
    for(rowB in B){
        if(f(rowA,rowB)){
        
# spark-sql的三种join实现
* Broadcast Join
* Shuffle Hash Join
* Sort Merge Join