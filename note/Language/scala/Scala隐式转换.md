# 隐式转换是什么
>通过隐式转换，程序员可以在编写Scala程序时故意漏掉一些信息，
让编译器去尝试在编译期间自动推导出这些信息来，这种特性可以极大的减少代码量，
忽略那些冗长，过于细节的代码

从表面上看有点想c++的运算符重载,直接对象+实际调用的是重载的某个方法  
2020/2/20:隐式转换可以认为是
函数有一个隐式参数,这个隐式参数表明调用这个函数的时候可以不用传入这个参数
但是,这个这个参数是少不了的
通过implicit申明一个隐式变量相当于将这个变量放在了另一个命名空间
然后这个命名空间距离当前函数调用最近
那么调用一个不带这个隐式参数的函数时他会自动从这个最近的隐式空间中去寻找这个变量
# 怎么使用隐士转换
## 隐式参数
方法可以具有 隐式 参数列表，由参数列表开头的 implicit 关键字标记。  
如果参数列表中的参数没有像往常一样传递， Scala 将查看它是否可以获得正确类型的隐式值，  
如果可以，则自动传递。  

Scala 将查找这些参数的位置分为两类       
* Scala 在调用包含有隐式参数块的方法时，将首先查找可以直接访问的隐式定义和隐式参数 (无前缀)。  
* 然后，它在所有伴生对象中查找与隐式候选类型相关的有隐式标记的成员

定义一个函数,使用implicit关键字修饰参数username  
```
scala> def fun(implicit username:String)="姓名:"+username
fun: (implicit username: String)String
```
指定参数调用该函数
```
scala> fun("fcy")
res0: String = 姓名:fcy
```
不加参数会直接报错
```
scala> fun
<console>:9: error: could not find implicit value for parameter username: String
              fun
              ^
```
申明一个隐式变量并直接通过函数名调用函数,发现直接使用了我们申明的隐式变量
```
scala> implicit val name="nienan"
name: String = nienan

scala> fun
res2: String = 姓名:nienan
```
再次申明一个隐式变量并直接通过函数名调用函数,发现直接报错了
```
scala> implicit val t="fcy"
t: String = fcy

scala> fun
<console>:11: error: ambiguous implicit values:
 both value name of type => String
 and value t of type => String
 match expected type String
              fun
              ^
```
很明显,当编译器向上找一个隐式变量时找到了两个,无法确定使用哪个
隐式转换必须无歧义,所以参数最好使用自定义的类,不要使用常用的基础类型
## 其他还有方法和类的隐式转换,以后写