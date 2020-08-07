# brew和gem

都是包管理器,但brew 和 gem 不同，`brew`用于操作系统层面上软件包的安装，而`gem`只是管理`ruby`软件。

# yarn

前端的包管理器

# webpacker
打包工具
# rvm
rvm 是一个命令行工具，可以提供一个便捷的多版本 Ruby 环境的管理和切换

# gem命令

> https://guides.rubygems.org/command-reference/

查看现有的gem源	gem sources -l

增加gem源				gem sources -a https://gems.ruby-china.com/



# 杂

查看默认的数据库		rails db

The method **self.up** is used when migrating to a new version, **self.down** is used to roll back any changes if needed
# ruby中的@是实例变量

# ruby中的@@是类变量

# ruby中的 :name  是Symbol类型(具体意思可以同常量表,符号表,枚举值等)

# def render(*args) 这是什么参数?
	*号的作用
	
	"name"*2
	namename
	
	[1,2,3]*2
	[1,2,3,1,2,3]
	
	*a=1,2,3,"as"相当于
	a=[1,2,3,"as"]
	
	相当于变长参数
	def f(*a)
		puts a
	end
	
	x=Hash[:a,1,:b,2]
	array=[:a,1,:b,2]
	Hash[*array]
	
	传递数组参数
		def h name1,name2,name3
			puts "#{name1},#{name2},#{name3}
		end
		
		a=["nie","nan","fcy"]
		h *a     #中间需要有个空格
# ruby中的实例变量
	所有变量都是私有的,必须通过方法访问
	可以偷懒  写
	attr_reader – define instance-level getters 
	attr_writer – define instance-level setters 
	attr_accessor – define both
	class Fcy
		attr_accessor :name
	end
	相当于有了set和get方法了

# ruby中的双冒号
	双冒号可以用来定义name space
	ActiveRecord::Base
	继承ActiveRecord模块中的Base类
# rails中的数据库迁移
	数据库迁移就是使用数据库迁移文件将数据库从一个状态转换到另一个状态的动作。
	记录状态便于回滚
# rails 命令
  Rails generate controller fcy index show profile
  Rails  destroy controller fcy
  命令行创建的Controller大小会变成小写
  routes.rb中大小写敏感

  Ruby的类名必须大写

# 异常处理
	begin
		rescue
	
		retry
	end
	raise
# 条件语句

# 方法
	方法定义
	方法参数默认值
	变长参数
	参数个数可以少写
	返回方式
	实例方法
	类方法
# 模块
	基本和类一样，提升一层命名空间
	不同点在于
		模块不可以实例化
		模块没有子类
		模块只能被另一个模块定义
引入其他模块 require

# ruby单继承
# rails中的Active Record
	如果创建了一个Article模型，rails会自动找到Article的复数形式，并作为表名
	如果模型名复杂也有相应的规则去得到表名

# 步骤
	文件名
	类名
	模块
	require,load,include,extend等的区别
	load 和 require 是 Kernel 提供的类加载接口，extend 和 include 是互相引用的接口，有本质区别
## extend
	extend - adds the specified module's methods and constants to the target's metaclass (i.e. the singleton class) e.g.

if you call Klazz.extend(Mod), now Klazz has Mod's methods (as class methods)
if you call obj.extend(Mod), now obj has Mod's methods (as instance methods), but no other instance of of obj.class has those methods added.
extend is a public method
## include
	include - By default, it mixes in the specified module's methods as instance methods in the target module/class. e.g.

if you call class Klazz; include Mod; end;, now all instances of Klazz have access to Mod's methods (as instance methods)
include is a private method, because it's intended to be called from within the container class/module.

>https://stackoverflow.com/questions/156362/what-is-the-difference-between-include-and-extend-in-ruby
# Ruby中的Mixin
	通过Module来解决多重继承
	在Module中定义一些共用的方法
	在类中通过include来继承或者说使用这些方法
	如果两个Module又相同的方法那么谁先被include就调用谁的
	Ruby中的Mixin是基于include时的顺序来决定方法调用的顺序

# 可以将一个模块中的其他类的方法变为本类的类方法或者实例方法
	module Mood
		def h
			puts "hello"
		end
	end
	class Per
		extend Mood
	end
	Per.h  #可以直接调用这个方法
	x=Per.new
	x.h    # 调用失败
	
	module Mood
	 def say
	      p "hello, everyone!"
	  end
end
class Person
end
person = Person.new 
person.extend(Mood)    
person.say
# 反射
	获取对象的所有方法
	class T
	end
	T.new.methods# 获取当前类所有实例方法
	T.singleton_methods# 获取当前类所有类方法（包括父类）
	T.singleton_methods(false)#获取当前类所有类方法（不包括父类）
# ruby中的delegate
```
  class Greeter < ActiveRecord::Base  
    def hello()   "hello" end
    def goodbye() "goodbye" end
  end

  class Foo < ActiveRecord::Base  
    delegate :hello, :goodbye, :to => :greeter
  end

  Foo.new.hello   # => "hello"  
  Foo.new.goodbye # => "goodbye"
```
## 增加:prefix => true：
```
class Foo < ActiveRecord::Base  
  delegate :hello, :goodbye, :to => :greeter, :prefix => true
end
   
Foo.new.greeter_hello   # => "hello"  
Foo.new.greeter_goodbye # => "goodbye"  
```
## 自定义前缀名：
```
class Foo < ActiveRecord::Base  
  delegate :hello, :goodbye, :to => :greeter, :prefix => :foo
end
  
Foo.new.foo_hello   # => "hello"  
Foo.new.foo_goodbye # => "goodbye" 
```
# rails中的Active Record 
ORM中的Active Record和Data Mapper

# Ruby和Laravel的ORM都采取了Active Record的模式，因此它们ORM可能像下面这样：
 $user = new User;
$user->username = 'philipbrown';
$user->save();
# 再来看使用Data Mapper的ORM是怎样的：
$user = new User;
$user->username = 'philipbrown';
EntityManager::persist($user);

# 现在我们察看到了它们最基本的区别：在Active Record中，领域对象有一个save()方法，领域对象通常会继承一个ActiveRecord的基类来实现。而在Data Mapper模式中，领域对象不存在save()方法，持久化操作由一个中间类来实现。

# 为什么使用Docker Compose File？

按照docker官方的建议，每一个容器只启动一个进程，这样便于管理和解耦。而在生产部署的时候，我们的一个应用不太可能只有一个进程，除了代码应用的主进程外，你可能还需要开启reids、mysql、nginx等。也就是说不会只靠一个镜像便能部署完成，所以我们每次部署应用需要同时用多个镜像启动多个容器，操作端口映射、数据卷，完成容器间的通信。如果涉及到分布式和多台服务器，那岂不是每个服务器都得这样操作一次？因此，docker提供了Docker Compose File，可以使用docker-compose.yaml文件，按照特定的语法语句编写指令，管理多个镜像的部署和端口等操作，实现真证的快速部署。在不同服务器上部署时，只需要一个docker-compose.yaml文件，便能完成应用的部署操作。

# postgresql

brew install postgresql -v

启动：
pg_ctl -D /usr/local/var/postgres -l /usr/local/var/postgres/server.log start

关闭：
pg_ctl -D /usr/local/var/postgres stop -s -m fast

新建一个数据库用户

createuser username -P
为这个用户新建一个数据库

createdb databaseName -O username -E UTF8 -e
用这个用户访问数据库

psql -U username -d databaseName -h 127.0.0.1

查看所有连接的用户：

```
select * from pg_stat_activity;
```

查看连接总数：

```
select count(*) from pg_stat_activity;
```

#在查询表结构
```text	
 \d tablename  
```
## 导出数据

```text
pg_dump --host xxxxx.com --port 5432 --username fcy  > fcy.sql fcydb
```
xxxxx.com服务器上5432端口

通过用户名fcy将fcydb数据库中的所有数据导入到本地的fcy.sql文件中

## 导入数据

```text
psql -d fcy  -f fcy.sql fcydb
```

将fcy.sql导入到本地的fcy用户下的fcydb数据库中

### 导入数据时遇到问题。psql:mozhou.sql:102553: error: invalid command \N

​	执行   psql -v ON_ERROR_STOP=1 fcy < fcy.sql     正常导入

# # brew

​	brew info redis查看redis信息