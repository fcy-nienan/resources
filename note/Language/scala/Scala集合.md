# 多重的棱形问题
    A有一个方法f()
    B和C都继承A并且都实现了f方法
    然后D继承B和C并且没有重写f方法,那么D该使用哪个方法
# 函数

# 闭包

# 柯里化
* 柯里化从直观上看就是将一个接收多个参数的函数改造为只接收一个参数
  并且返回一个函数，返回的函数接收其他参数，一直到接收最后一个参数
* 可以惰性求值,知道所有的参数到齐后才能得到最终的结果
  中间过程得到的只是一个函数的地址
  2019-12-30:有点疑问?执行addSugar(1)的时候返回的是一个函数,那我的那个变量存储在哪里,毕竟我返回的只是一个函数啊
  通过在jvisualvm中查看内存发现其实返回的是一个对象.
  我之前的理解就是这应该返回的就是一个函数,然后函数的话
  在C中应该就是一个函数地址,并没有存储变量的空间
* 还有一些其他的特性待研究
* Methods with multiple parameter sections can be used to assist local type inference, by using parameters in the first section to infer type arguments that will provide an expected type for an argument in the subsequent section. foldLeft in the standard library is the canonical example of this  
  柯里化在Scala中引入是为了支持类型推断?暂时不太理解
* For fluent API.Another use for multiple parameter section methods is to create an API that looks like a language construct. The caller can use braces instead of parentheses
* Curried Functions.Curried functions (or simply, functions that return functions) more easily be applied to N argument lists.
* Multi Stage Computation.
```
 def main(args: Array[String]): Unit = {
    println(add(1,2))//3
    println(addSugar(1))//Curring$$$Lambda$3/1355531311@f5f2bb7
    println(addSugar(1)(2))//3
    println(addThree(1))//Curring$$$Lambda$4/1690716179@3ecf72fd
    println(addThree(1)(2))//Curring$$$Lambda$5/564160838@7a92922
    println(addThree(1)(2)(3))//6
  }
  /*正常的add函数*/
  def add(x:Int,y:Int):Int=x+y
  /*语法糖的格式*/
  def addSugar(x:Int)=(b:Int)=>{
    x+b
  }
  /*不加语法糖的格式*/
  def addNoSugar(x:Int):Int=>Int=(b:Int)=>x+b
  /*
  * 下面的函数是一个接收两个参数并且返回一个函数的函数
  */
  def test(x:Int,y:String):String=>List[String]=(y:String)=>List(y)
  /*
  * addThree是一个函数,该函数接收一个Int类型参数,并且返回一个B
  * B是一个函数,该函数接收一个Int类型参数,并且返回一个C
  * C是一个函数,该函数接收一个Int类型参数,并且返回一个Int类型参数
  */
  def addThree(x:Int):(Int)=>(Int)=>(Int)={
    (b:Int)=>{
      (c:Int)=>{
        x+b+c
      }
    }
  }
  /*省略一些括号*/
  def addThreeSugar(x:Int):Int=>Int=>Int=(b:Int)=>(c:Int)=>x+b+c;
```
# 模式匹配
# scala中的一些特殊符号
    泛型 <:  >:  eg: def fun1[A<:Closeable,B](closeable:A):B=>{}
    协变和逆变   +T -T
    视界
    广义类型约束符号
    +，-，*，/都是函数，比如 1+2，实质上是对象1上调用+函数，传入的参数是2，等价于(1).+(2)
    _N 访问元组的第几个元素 var x=(1,2,3,4,5) x._5=5
    ->    // Automatically imported method
    ||=   // Syntactic sugar
    ++=   // Syntactic sugar/composition or common method
    <=    // Common method
    _._   // Typo, though it's probably based on Keyword/composition
    ::    // Common method
    :+=   // Common method
### Keywords/reserved symbols
    // Keywords
    <-  // Used on for-comprehensions, to separate pattern from generator
    =>  // Used for function types, function literals and import renaming
    
    // Reserved
    ( )        // Delimit expressions and parameters
    [ ]        // Delimit type parameters
    { }        // Delimit blocks
    .          // Method call and path separator
    // /* */   // Comments
    #          // Used in type notations
    :          // Type ascription or context bounds
    <: >: <%   // Upper, lower and view bounds
    <? <!      // Start token for various XML elements
    " """      // Strings
    '          // Indicate symbols and characters
    @          // Annotations and variable binding on pattern matching
    `          // Denote constant or enable arbitrary identifiers
    ,          // Parameter separator
    ;          // Statement separator
    _*         // vararg expansion
    _          // Many different meanings
    import scala._    // Wild card -- all of Scala is imported
    import scala.{ Predef => _, _ } // Exception, everything except Predef
    def f[M[_]]       // Higher kinded type parameter
    def f(m: M[_])    // Existential type
    _ + _             // Anonymous function placeholder parameter
    m _               // Eta expansion of method into method value
    m(_)              // Partial function application
    _ => 5            // Discarded parameter
    case _ =>         // Wild card pattern -- matches anything
    f(xs: _*)         // Sequence xs is passed as multiple parameters to f(ys: T*)
    case Seq(xs @ _*) // Identifier xs is bound to the whole matched sequence
### Automatically imported methods
    // Not necessarily in this order
    import _root_.java.lang._      // _root_ denotes an absolute path
    import _root_.scala._
    import _root_.scala.Predef._
    class <:<
    class =:=
    object <%<
    object =:=
### Common methods
### Syntactic sugars/composition
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

# Map
```
var a=Map()
var b=Map(1->2,2->3,3->4)
b+=4->5
```
# Set
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
# List
```
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
    :+   List(1,2,3,4) :+ 5 = List(1,2,3,4,5)
    sum
    toMap
    toArray
    toSeq
    toSet
    toString
    toBuffer
```
# mutable Collection
scala.collection.ArrayBuffer
    An ArrayBuffer buffer holds an array and a size. 
    Most operations on an array buffer have the same speed as for an array, 
    because the operations simply access and modify the underlying array. 
    Additionally, array buffers can have data efficiently added to the end. 
    Appending an item to an array buffer takes amortized constant time. 
    Thus, array buffers are useful for efficiently building up a large collection 
    whenever the new items are always added to the end
    和ArrayList差不多
    val buff=new ArrayBuffer
    buff+=3
scala.collection.ListBuffer
    A ListBuffer is like an array buffer except that 
    it uses a linked list internally instead of an array. 
    If you plan to convert the buffer to a list once it is built up, 
    use a list buffer instead of an array buffer
    相当于LinkedList
    val buff=new LinkedList
    buff+=3