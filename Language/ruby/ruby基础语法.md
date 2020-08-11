# alias关键字

重命名方法

alias :newName :oldName

```ruby
class Entry
  def helloworld
    puts "hello"
  end
  alias :hello :helloworld
end
Entry.new.hello # hello
Entry.new.helloworld # hello
```

# 方法

​	Fcy.class

​	Fcy.instance_methods

​	Fcy.instance_variables

​	Fcy.methods.grep /^re/ 

​	Class.new		运行时创建一个类

​	Module#constants返回当前范围内的所有常量

​	所有以大写字母开头的是常量

​	常量可以被修改，scope不同

​	对象就是一组实例变量外加一个只想其类的引用

​	类就是一个对象外加一组实例方法和一个对其超类的引用

​	Class类是Module类的子类

​	load每次调用都运行加载的模块，load加载后其中的常量会污染当前的作用域，通过

​	load('met.rb',true)会创建一个匿名模块，加载完该模块被销毁

​	require是导入类库，不会销毁其中的类，导入你希望得到的

​	

​	ActiveRecord通过内省机制查看类的名字，因为类名是Movie，ActiveRecord会自动将其映射到名为movies的表中

​	自动定义两个同名的属性和相应的访问器

​	运行时动态地创建了相应的方法



# 元编程是编写能在运行时操作语言构建的代码



​	其他语言给予我们在运行时的控制权

​	能写代码的代码？

​	动态元编程

​	静态元编程



ruby中的Class关键字代表着打开一个类，打开一个类之后你可以对其中的属性方法进行操作

他的确可以创建一个不存在的类，但你可以把它当作一个令人愉快的副作用	



一个对象仅仅包含它的实例变量以及一个对自身类的引用

方法存放在类中



# 如何查找方法？

对象只有class方法，没有superclass方法

类对象有class方法和superclass方法

接受者和祖先连

​	接受者就是调用这个方法的类

​	祖先链就是这个类一直向上调用superclass

ruby首先在接受者的类中查找，然后再顺着祖先链接向上查找

```ruby
irb(main):125:0> Fcy.ancestors
=> [Fcy, Object, Kernel, BasicObject]
```

莫名出现了Kernel？

当把一个模块包含在一个类（或者模块）中时，ruby会把这个模块加入到这个类的祖先链中



include的逻辑是 if exists ignore else include



Object包含了Kernel模块，所以Kernel就进入了每个对象的祖先链，所以任何对象都可以调用Kernel模块的方法，这使得print就像一个关键字



私有方法只能通过隐性的接受者调用，public对外公开，private的只能在自己内部调用



main 处于顶层上下文

```ruby
irb(main):128:0> self
=> main
irb(main):129:0> self.class
=> Object
irb(main):130:0> 
```



java中的一些无趣且重复的契约方法



动态调用方法send或者public_send

```ruby
irb(main):134:0> class Fcy
irb(main):135:1> def hello
irb(main):136:2> puts "sdfjsdlfkjsd"
irb(main):137:2> end
irb(main):138:1> end
=> :hello
irb(main):139:0> Fcy.new.hello
sdfjsdlfkjsd
=> nil
irb(main):140:0> Fcy.new.send(:hello)
sdfjsdlfkjsd
=> nil
irb(main):141:0> 
```

动态定义方法

​	define_method

```ruby
irb(main):149:0> class Fcy
irb(main):150:1> define_method :helloworld do |args|
irb(main):151:2* args*3
irb(main):152:2> end
irb(main):153:1> end
=> :helloworld
irb(main):155:0> Fcy.new.helloworld 3
=> 9
```

# 覆写method_missing方法

当调用一个对象不存在的方法时,会自动调用该对象的methods_missing方法,我们可以覆写他

# block_given?返回当前方法是否包含代码块



# 作用域

​	既要提供常见的作用域模型,又要提供可以打破常规作用域模型的方法

纵横交叉,常规纵的可以,那么也应该提供横向的

使得可以自由组合,衍变无数种可能

# defined?

​	是否定义了某某某方法，变量