# scala的for语法
## for有四种写法
+ for loop with ranges  
+ for loop with collections 
+ for loop with yield   
+ for loop with filters 
### for loop with ranges
```
for ( i <- range ){
    statement(s)
}
```
### for loop with collections
```
for ( i <- collections ){
    statement(s)
}
```
### for loop with filters
```
for ( i <- List 
    if conditions1;
    if conditions2;
```