多重继承的棱形问题
A有一个方法f()
B和C都继承A并且都实现了f方法
然后D继承B和C并且没有重写f方法,那么D该使用哪个方法
Map
```
var a=Map()
var b=Map(1->2,2->3,3->4)
b+=4->5
```
Set
```
    var set:Set[Int]=Set();
    set=Set(1,2,3,4,5)
    println(set.head)//返回第一个元素5
    println(set.tail)//返回剩余的元素Set(1,2,3,4)
    println(set.isEmpty)//false

    求全集
    var set1=Set(1,2,3,4,5)
    var set2=Set(2,3,4,5,6)
    var set3=set1++set2
    set3=set1.++(set2)
    println(set3)//Set(5,1,6,2,3,4)

    最大值和最小值
    var set4=Set(1,2,3,4,5)
    println(set4.max)//5
    println(set4.min)//1

    求交集
    var set5=Set(1,2,3,4,5)
    var set6=Set(2,3,4,5,6)
    var set7=set5.&(set6)
    set7=set5.intersect(set6)
    println(set7)//Set(5,2,3,4)

    java的add
    set7+=4
    set7+=8
    println(set7)//HashSet(5,2,3,8,4)

    java的remove
    set7-=2
    set7-=3
    set7-=1
    println(set7)//5,8,4
```