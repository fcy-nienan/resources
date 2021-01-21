# block

```
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
# proc

```
p = Proc.new do 
  puts "test"
end
p.call   # test
```

```
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
block是不能单独存在的,不能存在变量中,必须挂在方法后面,proc可以存储在一个变量中


可以通过&操作符将proc转为block
```
proc = Proc.new { |x|  puts x }
3.times &proc    # 0,1,2
```
比如在项目中经常看到的map(&:to_s)
实际可以理解为 map &:to_s.to_proc
map方法需要的是一个block,但是:to_s返回的不是一个Proc对象,ruby会自动将他进行转换一下

# lambda
打印它的类也是Proc
```
lb = lambda {|name| puts "hello #{name} , I am a lambda!" }
lb1 = ->(name) { puts "hello #{name} , I am a lambda!"  }
lb.call "fcy"     # hello fcy , I am a lambda!
lb1.call "fcy"    # hello fcy , I am a lambda!
puts lb.class     # Proc
puts lb1.class    # Proc
```
> One difference is in the way they handle arguments. Creating a proc using `proc {}` and `Proc.new {}` are equivalent. However, using `lambda {}` gives you a proc that checks the number of arguments passed to it. From `ri Kernel#lambda`:
> In addition, using return inside a lambda returns the value of that lambda, but using return in a proc returns from the enclosing block.

lambda会检查参数,proc会传nil,并且在lambda中return和proc不同
+ proc会传nil
```
p = Proc.new do |a,b| 
  puts a,b
  puts "b is nil" if b.nil?
end
p.call 1,2    # 1,2
p.call 1      # 1   b is nil
```
+ 再来看下lambda,首先会检测参数个数

```
p = lambda { |x,y| puts x*y }
p.call 1,2 # 2
p.call 1   # ArgumentError: wrong number of arguments (given 1, expected 2)
```
+ lambda中return会返回上一层
```
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

```
p = Proc.new do 
  return 1
end
p.call  # LocalJumpError: unexpected return

p = Proc.new { return 1; }
def show(p)
	p.call  # LocalJumpError: unexpected return
end
show(p)


def show
  puts "start"                 # start
  p = Proc.new { return 1; }   
  puts p.call                  # 1
  puts "end"
end
show

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


def create_proc
  a_proc = Proc.new do
    puts 'executing proc'    # executing proc
    return
  end
  pass_on_proc(a_proc)
  puts "end method"
end
def pass_on_proc(a_proc)
  call_proc(a_proc)
end
def call_proc(a_proc)
  a_proc.call 
end
create_proc


```
# 给我的感受
block和proc更像是往某个地方插入一段代码,一段代码参数并不需要严格校验也不应该在其中返回
而lambda更像是一个回调函数,函数需要严格的参数,函数中返回并不影响外层的函数

## 作用域
可以认为是变量可见性的隔离,变量的有效范围
	如果所有变量的命名都在一个空间中,那么迟早会出现命名冲突
	通过作用域我们可以控制变量名字的有效范围
有两种作用域:词法作用域和动态作用域
>>When a variable is **lexically scoped**, the system looks to where the function is **defined** to find the value for a free variable. When a variable is **dynamically scoped**, the system looks to where the function is **called** to find the value for the free variable.


词法作用域:去定义的地方查找这个变量(静态的,编译时就确定了的)
动态作用域:去调用的地方查找这个变量(动态的,运行时才能确定下来)

ruby是词法作用域

### 和作用域相关的几个函数

+ Kernel#local_variables输出当前作用域内局部变量
+ binding#local_variable_get(:v1) 获取当前作用域局部变量的值
+ binding#local_variable_set(:v1,1) 设置当前作用域局部变量的值

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

存在相应的规则那肯定也有打破这种规则的方法
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
```

# block也会创建新的作用域,但是可以通过某些方式控制可见性

```
hello = "Hello World"
2.times do |i|
  
end

hello = "Hello World"
def call
	yield
end
call { hello = "456"}
p hello
输出:
"456"


如果想隔离这份可见性,可以加指定的形参
hello ='Hello World'
2.times do |i; hello|
  p i
  hello = '456'
end
p hello  # Hello World
输出:
"Hello World"
```
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
### JavaScript
```
动态作用域
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