scala是单继承
var和val的区别
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
　5、自动从scala.Product中继承一些函数;
　　6、case class构造函数的参数是public级别的，我们可以直接访问；
支持模式匹配；

自动加了一些特性


.map(x=>{

(x._1,x._2._1._1,x._2._1._2,x._2._1._3,x._2._1._4,x._2._1._5,x._2._1._6,x._2._1._7,x._2._2)

}).filter(_._9==None).saveAsTextFile("C://work//data//result.txt")

var t=range(10,20,2)创建区间数组10-20,间隔2