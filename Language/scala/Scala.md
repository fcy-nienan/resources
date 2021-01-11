# scala编程思想

    一切皆对象
    函数是一等公民
    
    提供了许多可以少些代码的语法糖
    从"如何少些代码同时又能满足编译器的要求"出发看待这些语法糖
    
    Java不是一门纯粹的OO语言(基本数据类型)
    2
# scala是单继承
# var和val的区别
    一个可变一个不可变
scala没有static的概念
有类和对象
object不能带参数,伴生对象只能和类在同一个文件中并且名称相同,可以互相访问私有成员

scala的Trait相当于Java的接口,并且可以定义属性和方法,这和Java后来的版本一样,也可以在接口中定义属性和方法
也可以实现多个接口

scala中的with相当于java中的implement

case class
初始化的时候可以不用new，当然你也可以加上，普通类一定需要加new；
toString的实现更漂亮；
默认实现了equals 和hashCode；
默认是可以序列化的，也就是实现了Serializable ；
自动从scala.Product中继承一些函数;
case class构造函数的参数是public级别的，我们可以直接访问；
支持模式匹配；


var t=range(10,20,2)创建区间数组10-20,间隔2

# 闭包和可序列化
    Scala中的闭包最终还是翻译成了Java中的一个匿名对象
    这也是spark中一些算子可以接受闭包并扔到executor中执行的前提之一
# 疑问

    我很好奇Scala不可变集合是否是通过链表实现的
    但是debug中并没有发现集合对象中有相应的next和prev等指针
# def和val和var

>https://stackoverflow.com/questions/4437373/use-of-def-val-and-var-in-scala

    def定义方法
    val定义一个固定的变量
    var定义一个可变的变量
    至于有时候看着def似乎能定义变量那其实是定义方法,只是有很多语法糖
# scala中的apply,update,unapply

    下面三个方法都需要定义在半生类对象中
    
    val list=List(1,2,3,4,5)
    上述实际上是调用了List的apply方法,不用写new
    
    val array=Array(1,2,3,4,5)
    array(2)=10
    上述赋值实际调用的是Array的update方法
    
    val value=User("fcy","nienan")
    println(value)
    val User(name)=value
    println(name)
    实际调用的是val name=User.unapply(value)
    也就是在一个对象中抽取指定变量
# scala不定参数
    def apply(x:Int*){
    
    }
# scala参数默认值
    def apply(x:Int,y:Int=3){
    
    }
# 执行外部命令
	import sys.process._
	var cmd="cp -r /user /txt/" !
	(源自交接过程中龙哥和他们关于bug的讨论,看了一下,创建文件的时候目录不在,然后IO异常,无意中发现了scala写shell竟然这么方便)
# 柯里化

```
def add (x,y) 
	return x + y
end
```
可以把它看做一个函数: f(x,y) = x + y
当只给定一个参数x = 3 的时候，这个函数应该变成 f(y) = 3 + y
# 高阶函数
函数可以理解为从参数到结果的一种映射
比如T1->T2
每个函数都符合这种定义
只不过T1或者T2是比较复杂的类型(对象，函数)
如果T1或者T2是函数
那么T1->T2这个函数可以看做高阶函数

# 类型的别名
基本数据类型就那些，但在实际问题中存在许多有n个n中基本类型组合而成的模型，这个模型可能在其领域是基础模型，这时如果我们不对这个模型进行一个命名处理起来是非常麻烦的，通过对这种模型定义一个大的类型，能让我们更方便的解决实际问题。