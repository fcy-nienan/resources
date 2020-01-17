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
