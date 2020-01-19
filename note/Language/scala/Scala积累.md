cleaner.foreach(_.registerBroadcastForCleanup(bc))
this.type

asInstanceOf


在Java中null是一个关键字
而在Scala中鼓励使用Ooption
使用getOrElse(defaultValue)返回默认值
//可以先用get, get 出来的东西是个 Option[A], 再做判断
```
var finalResult = 0 //0默认值

(map1.get(key1), map2.get(key2)) match {

  case (Some(value1), Some(value2)) =>

    //都找到了, 可以愉快的相加了

    finalResult = value1.a + value2.a

  case (None, Some(value2)) =>

    //第一个找不到, 第二个找到了怎么办的代码

  case (Some(value1), None) =>

    //第一个找到了, 第二个找不到怎么办的代码

  case _=>

    //其他情况

}
```
# Option
# Some    
    ```
    Class `Some[A]` represents existing values of type
    final case class Some[+A](value: A) extends Option[A] {
      def get: A = value
    }
    ```
# None
    ```
    This case object represents non-existent values.
    case object None extends Option[Nothing] {
      def get: Nothing = throw new NoSuchElementException("None.get")
    }
    ```
# Any
    所有类的根类,类似于Java的Object
# AnyRef
    所有引用类型的根类
# Nothing
    任何类型的子类型
# Null
    任何引用类型的子类型
# AnyVal
```
    AnyVal is the root class of all ''value types'', which describe values
    not implemented as objects in the underlying host system. Value classes
    are specified in Scala Language Specification, section 12.2.
    The standard implementation includes nine `AnyVal` subtypes:
    [[scala.Double]], [[scala.Float]], [[scala.Long]], [[scala.Int]], [[scala.Char]],
    [[scala.Short]], and [[scala.Byte]] are the ''numeric value types''.
    [[scala.Unit]] and [[scala.Boolean]] are the ''non-numeric value types''.
    abstract class AnyVal extends Any {
      def getClass(): Class[_ <: AnyVal] = null
    }
```
    AnyVal是所有值类型的根类
    在计算机中所有的数据都是二进制
    我们认为的划分了int,float,double,char,boolean等值类型
    而AnyVal是所有这些类型的根类
    标准实现包括九个子类型
    数字值类型double,float,long,int,char,short,byte
    非数字值类型unit,boolean
    unit类型类似于Java的void
    Unit is a subtype of [[scala.AnyVal]]. There is only one value of type
    Unit, (), and it is not represented by any object in the underlying
    runtime system. A method with return type `Unit` is analogous to a Java
    method which is declared `void`.
# asInstanceOf和isInstanceOf和classOf
| java | scala |
| :---- | :--- |
| obj.isInstanceOf[C] | obj instanceof C |
| obj.asInstanceOf[C] | (C)obj |
| classOf[C] | C.class |

# 集合
1. List(1,2,3) is "magic syntax" to call the apply method in the companion object of 
trait or class List.
直接val list=List(1,2,3)这种语法实际上是调用了其伴生对象的apply方法
2. For both immutable and mutable collections, :+ and +: create new collections. 
If you want mutable collections that automatically grow, use the += and +=: methods 
defined by collection.mutable.Buffer.
不管可变还是不可变的集合,:+和+: 都会创建一个新的集合
如果你需要可变集合自动增长,使用定义在Buffer中的+=和+=:方法
3. 3 :: List(1,2)
::这种时中缀运算符
The associativity of an operator is determined by the operator’s last character. 
Operators ending in a colon ‘:’ are right-associative. All other operators are left- associative
