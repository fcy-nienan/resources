# block

```ruby
def test_block
	puts "start"                          # start
	yield("arguments") if block_given?    # arguments
	yield("fcy") if block_given?          # fcy
	puts "end"                            # end
end

test_block {|x| puts x}

test_block do |x| puts x end

[1,2,3].each do |num|
  puts num                                # 1,2,3
end
```
	通过在调用方法的时候加上一段代码块(do...end形式或者{}括号形式)
	然后在方法体使用yield调用,通过block_given?方法检测block是否存在
# proc

```ruby
p = Proc.new do 
  puts "test"
end
p.call                      # test

x = proc { puts "test" }	# test
x.call			

def show(&p)
  puts p.class   # Proc
  p.call         # test    
  yield          # test
end
p = Proc.new do 
  puts "test"
end
show &p
```
和block非常相似,但有以下几点不同
+ block不可以被存储,proc可以,并且proc是个对象
+ 可以传递多个proc参数到一个方法


我们可以通过&操作符将proc转为block
```ruby
proc = Proc.new { |x|  puts x }
3.times &proc    # 0,1,2
```
比如在项目中经常看到的map(&:to_s)
实际可以理解为 map &:to_s.to_proc
map方法需要的是一个block,但是:to_s返回的不是一个Proc对象,ruby会自动将他进行转换一下

# lambda
更像是一个匿名函数,同样可以被存储
其实也差不多,都是某个关键字后面加个块,然后通过call调用,打印它的类可以发现是Proc
```ruby
lb = lambda {|name| puts "hello #{name} , I am a lambda!" }
lb1 = ->(name) { puts "hello #{name} , I am a lambda!"  }
lb.call "fcy"     # hello fcy , I am a lambda!
lb1.call "fcy"    # hello fcy , I am a lambda!
puts lb.class     # Proc
puts lb1.class    # Proc
```
和proc有两个不同的地方
+ lambda会检查参数个数,不合法会抛异常,proc不会,proc会传nil
+ lambda中return和proc中return是不同的

  

+ proc会传nil
```ruby
p = Proc.new do |a,b| 
  puts a,b
  puts "b is nil" if b.nil?
end
p.call 1,2    # 1,2
p.call 1      # 1   b is nil
```
+ 再来看下lambda,首先会检测参数个数

```ruby
p = lambda { |x,y| puts x*y }
p.call 1,2 # 2
p.call 1   # ArgumentError: wrong number of arguments (given 1, expected 2)
```
+ lambda中return会返回上一层
```ruby
lam = lambda { return 1 }
def show lam
  puts "start"        # start
  puts lam.call * 2   # 2
  puts "end"          # end
end
show lam
```
+ proc中return会报错LocalJumpError:unexpected return
proc的return返回并不是从它调用的地方放回,而是它定义的地方
```ruby
p = Proc.new do 
  return 1
end
p.call  # LocalJumpError: unexpected return

虽然在方法里面调用,但是定义还是在外面
p = Proc.new { return 1; }
def show(p)
	p.call  # LocalJumpError: unexpected return
end
show(p)

在定义的地方返回,也即在show方法中直接就返回了,后面的end也不会输出
def show
  puts "start"                 # start
  p = Proc.new { return 1; }   
  puts p.call                  # 1
  puts "end"
end
show

这个地方的返回比较诡异,如果是定义的地方返回那么不应该抛出异常啊,
但是一步步分析可以发现调用getProc的时候其实已经返回了一个proc对象的,
调用完成之后getProc的栈帧也就不存在了,此时再返回肯定就报错了
def getProc
  Proc.new { return self; }
end
def invokeProc
  p = getProc
  p.call   # LocalJumpError
end
def show 
  p "start"    # start
  invokeProc   
  p "end"
end
show

这里就比较明显能看出proc是在其定义的地方返回了
在一开始就定义了一个proc,然后调用其他方法传递这个proc给嵌套的函数
最后执行的时候直接从最外层的函数返回了,几个end字符串也就不会输出了
def create_proc
  a_proc = Proc.new do
    puts 'executing proc'    # executing proc
    return
  end
  pass_on_proc(a_proc)
  puts "end method"
end
def pass_on_proc(a_proc)
  puts "start pass"          # start pass
  call_proc(a_proc)
  puts "end pass"
end
def call_proc(a_proc)
  puts "start call"          # start call
  a_proc.call 
  puts "end call"
end
create_proc

如果换成lambda可以清晰的看出两者的区别
def create_proc
  a_proc = lambda do
    puts 'executing proc'    # executing proc
    return
  end
  pass_on_proc(a_proc)
  puts "end method"          # end method
end
def pass_on_proc(a_proc)
  puts "start pass"          # start pass
  call_proc(a_proc)
  puts "end pass"            # end pass
end
def call_proc(a_proc) 
  puts "start call"          # start call
  a_proc.call 
  puts "end call"            # end call
end
create_proc
```
# 给我的感受

block和proc更像是往某个地方插入一段代码,一段代码的参数并不需要严格校验也不应该在其中返回
而lambda更像是一个回调函数,函数需要严格的参数,函数中返回并不影响外层的函数

## 作用域

作用域是命名和值的绑定关系的有效范围

关于去哪查找变量的值有两种方式
词法作用域:去定义的地方查找这个变量(静态的,编译时就确定了的)
动态作用域:去调用的地方查找这个变量(动态的,运行时才能确定下来)

## ruby中的作用域门

当使用下列关键字的时候会创建一个新的作用域
+ class
+ module
+ def
```
x1 = 1
p local_variables  # [:x1]
module Fcy
  x2 = 2
  p local_variables  # [:x2]
  class FcyClass
    x3 = 3
    p local_variables  # [:x3]
    def fcy_method
      x4 = 4
      p local_variables  # [:x4]
    end
  end
end
fcy = Fcy::FcyClass.new
fcy.fcy_method

就像打开一扇一扇层层递进的门,进了门就看不到门外的东西了
```
## 存在相应的规则那肯定也有打破这种规则的方法
+ Class.new
+ Module.new
+ define_method
```
x1 = 1
p local_variables  # [:x1]
FcyModule = Module.new do 
  x2 = 2
  p local_variables  # [:x2,:x1]
  FcyClass = Class.new do 
    x3 = 3
    p local_variables  # [:x3,:x2,:x1]
    define_method(:fcy_method) do 
      x4 = 4
      p local_variables   # [:x4,:x3,:x2,:x1]
    end
  end
end
fcy_class = FcyClass.new
fcy_class.fcy_method
调用方法发现外层定义的变量在里面也能看到
```
block也可以捕获当前环境的变量,
```
hello = "Hello World"
def call
	yield
end
call { p hello }       # Hello World
```
如果想隔离这份可见性,可以加指定的形参
```
hello ='Hello World'
2.times do |i; hello|
  p i
  hello = '456'
end
p hello  # Hello World
输出:
"Hello World"
```

ruby是词法作用域
### ruby
```
静态作用域
def foo
  x = 1
  yield
end
x = 2
foo{ p x}  # 2

如果是动态作用域,相同的代码应该输出1
```
### JavaScript也是词法作用域
```
动态作用域(如果是动态作用域的话,应该是输出inner)
var testValue = 'outer';
function foo() {
  console.log(testValue);		// "inner"
}
function bar() {
  var testValue = 'inner';
  foo();
}
bar();
静态作用域
var testValue = 'outer';
function foo() {
  console.log(testValue);		// "outer"
}
function bar() {
  var testValue = 'inner';
  foo();
}

bar();
```
# 参考
>https://medium.com/swlh/returning-from-a-ruby-proc-beware-of-where-you-land-a29add7ddd9d