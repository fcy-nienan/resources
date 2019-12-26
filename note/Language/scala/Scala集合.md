多重继承的棱形问题
A有一个方法f()
B和C都继承A并且都实现了f方法
然后D继承B和C并且没有重写f方法,那么D该使用哪个方法

函数

闭包

柯里化

模式匹配
# scala的Seq是什么?
    在Java的术语中,Seq是一个Java的List并且List是一个Java的LinkedList
    Seq是一个特质,List是一个实现
    Note that there are actually three of them: 
    collection.Seq, 
    collection.mutable.Seq and collection.immutable.Seq, 
    and it is the latter one that is the "default" imported into scope
    
    There's also GenSeq and ParSeq. 
    The latter methods run in parallel where possible, 
    while the former is parent to both Seq and ParSeq, 
    being a suitable generalization for when parallelism of a code doesn't matter.
    They are both relatively newly introduced, 
    so people doesn't use them much yet

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
```
List
    ::
    {{{1 :: List(2, 3) = List(2, 3).::(1) = List(1, 2, 3)}}}
    :::
    {{{List(1, 2) ::: List(3, 4) = List(3, 4).:::(List(1, 2)) = List(1, 2, 3, 4)}}}
    reverse_:::
    {{{List(1, 2) .reverse_::: List(3, 4) = List( 4,3,1,2)}}}
    isEmpty
    prepended
    prependedAll
    appendedAll
    head
        List(1,2,3,4,5) head=1
    tail
        List(1,2,3,4,5) tail=List(2,3,4,5)
    take   
        List(1,2,3,4,5) take(2)=List(1,2) 
    slice
        List(1,2,3,4,5) slice(2,4)=List(3,4)
    takeRight
        List(1,2,3,4,5) taskRight(2)=List(4,5)
    splitAt
        List(1,2,3,4,5) splitAt(2)=(List(1,2),List(3,4,5))
    updated
        List(1,2,3,4,5) updated(2,100)=List(1,2,100,4,5)
    map
        List(1,2,3,4,5) map(e=>e+1)=List(2,3,4,5,6)
    collect
    flatMap
        List(1,2,3,4,5) flatMap(e=>Array(e,e+100))=List(1,101,2,102,3,103,4,104,5,105)
    takeWhile
        List(1,2,3,4,5) takeWhile(e=>e>0)=List(1,2,3,4,5)
        List(1,2,3,4,5) takeWhile(e=>e>1)=List()
        while (!these.isEmpty && p(these.head)) {
           b += these.head
           these = these.tail
        }
    foreach
        遍历
    reverse
        List(1,2,3,4,5) reverse=List(5,4,3,2,1)
    foldRight
        List(1,2,3,4,5) foldRight(2)((sum,i)=>sum*i)=240
        List(1,2,3,4,5) foldRight(0)((sum,i)=>sum+i)=15
    length
    lengthCompare
    forall
        List(1,2,3,4,5) forall(e=>e>1)=false
        List(1,2,3,4,5) forall(e=>e>=1)=true
    exists
        exists(p: A => Boolean): Boolean
        List(1,2,3,4,5) exists(e=>e>=1)=true
    contains
        contains[A1 >: A](elem: A1): Boolean
    find
        find(p: A => Boolean): Option[A]
    last
        List(1,2,3,,4,5) last=5
    corresponds
    className
    mapConserve
    filter
        List(1,2,3,4,5) filter(e=>e>1)=List(2,3,4,5)
    filterNot
        List(1,2,3,4,5) filterNot(e=>e>1)=List(1)
    distinct
    addString
        List(1,2,3,4,5) addString(new StringBuilder("11"))=1112345
    apply
        List(1,2,3,4,5) apply(3)=4
    drop
        List(1,2,3,4,5) drop(3)=List(4,5)
    dropRight
        List(1,2,3,4,5) droRight(3)=List(1,2)
    endsWith
        List(1,2,3,4,5) endsWith(4,5)=true
                        endsWith(1,4,5)=false
    indexOf
        List(1,2,3,4,5) indexOf(5)=4
    interest
        List(1,2,3,4,5) interest(List(3,4,5,6,7,8))=List(3,4,5)
    max
    min
    mkString
        将给定的字符填充在list的每个元素中
        List(1,2,3) mkString("99")=1992993
    sorted
    startsWith
        同endsWith
    sum
    toMap
    toArray
    toSeq
    toSet
    toString
    toBuffer
```