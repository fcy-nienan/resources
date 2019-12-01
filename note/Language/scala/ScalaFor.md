# scala的for语法
## for有四种写法
+ for loop with ranges  
+ for loop with collections 
+ for loop with yield   
+ for loop with filters 
### for loop with ranges(最基础的遍历方式)
```
for ( i <- range ){
    statement(s)
}
```
+ 下面代码会输出0到10(包括10),输出范围[0,10]
```for ( i <- 0 to 10 ){
   println(i)
}
```
+ 下面代码会输出0到9(不输出10),输出范围[0,10)
```
for ( i <- 0 until 10 ){
   println(i)
}
```
### for loop with collections(语法糖遍历List)
```
for ( i <- collections ){
    statement(s)
}
```
### for loop with filters(带有条件的遍历)
```
for ( i <- List 
    if conditions1;
    if conditions2;
    if conditions3;...){
    statement(s)
}
```
### for loop with yield(将for遍历的结果作为一个集合返回)
```
for ( i <- List ) yield variable
```