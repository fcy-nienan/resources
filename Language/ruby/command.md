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
			