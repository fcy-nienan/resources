# Partial (片段)

有时候，如果某个erb文件， 过于复杂了。 例如： 20行。

或者， 某些代码可以重用。

我们就用 Partial 来简化我们的代码,提取出公共的部分.

app/views/fruits/_footer.html.erb

```
<!-- 下面这段是版权声明，多个页面都需要重用  -->
<footer>
  copyright@2016 xx.co.ltd
</footer>
```

```
<%= render :partial => 'footer' %>
```

# 新增字段

rails generate migration add_x_and_y_to_articles x:string y:string

rails generate migration add_test_to_post test:string

rails generate migration add_course_student_remind_and_course_student_remind_interval_and_course_teacher_remind_and_course_teacher_remind_interval_to_course_plan course_student_remind:boolean course_student_remind_interval:string course_teacher_remind:boolean course_teacher_remind_interval:string

## 带参数的partial

如果，某个partial ,是需要参数的，（例如： 年份是个变量）

```
<!-- 下面这段是版权声明，多个页面都需要重用  -->
<footer>
  copyright@ <%= year %>xx.co.ltd
</footer>
```

那么，在调用时，就：

```
<%= render :partial => 'footer', :locals => {:year => 2016} %>
```

可以看到, 使用了 locals 来传递参数.





# tools

打印params

​	

```
puts params
puts "sdfsdf #{params}"
puts params.inspect
```

# gem和bundler的区别

> > The main difference is that **Rubygems** (invoked with the command `gem`) manages all the gems (gemsets if you are using RVM) for a single machine, whereas **Bundler** (`bundle`) manages a gem set for a single application (its purpose being to deploy on multiple machines)

> > The `Gemfile` is where you specify which gems you want to use, and lets you specify which versions.

> > The `Gemfile.lock` file is where Bundler records the exact versions that were installed. This way, when the same library/project is loaded on another machine, running `bundle install` will look at the `Gemfile.lock` and install the exact same versions, rather than just using the `Gemfile` and installing the most recent versions. (Running different versions on different machines could lead to broken tests, etc.) You shouldn't ever have to directly edit the lock file.

> > Almost seems like running 'gem install' adds it to the global available gems (and hence terminal can run the package's commands), whereas adding it to the gemfile and running bundle install only adds it to the application. Similar to npm install --global

# save and save!

> > `save!` will raise an error if not successful.

> > `save` will return boolean value like true or false.

# 访问路径

[http://127.0.0.1:4200/api/homework_papers.json?search%5Border%5D%5B%5D=homework_papers.updated_at%20DESC&page=1&per=10&access_token=RM-5VsnC51YjI7vpFT-v0tzA9mIfTrd8CoiYyPMYdg0&user_session_key=JRdhhjBX66DrM8JWglUcpBOyh2zm1IqcGGQl4F343gAFIH3ZUmOnHmqbtHlWt0QOFHGPD%2Fj%2F6ja4IRojh%2F0cw%3D%3D](http://127.0.0.1:4200/api/homework_papers.json?search[order][]=homework_papers.updated_at DESC&page=1&per=10&access_token=RM-5VsnC51YjI7vpFT-v0tzA9mIfTrd8CoiYyPMYdg0&user_session_key=JRdhhjBX66DrM8JWglUcpBOyh2zm1IqcGGQl4F343gAFIH3ZUmOnHmqbtHlWt0QOFHGPD%2Fj%2F6ja4IRojh%2F0cw%3D%3D)
```
GET /api/homework_papers(.:format)  api/homework_papers#index
```

# Sidekiq

提供执行定时/异步任务的后台任务处理系统

# PaperTrail

Track changes to your models, for auditing or versioning. See how a model looked at any stage in its lifecycle, revert it to any version, or restore it after it has been destroyed

# ActsAsParanoid

A Rails plugin to add soft delete.

This gem can be used to hide records instead of deleting them, making them recoverable later.

# 回退版本

bin/rails db:rollback     回退到上一个版本

# params

params.require（：person）.permit（：name，：age）
>https://stackoverflow.com/questions/18424671/what-is-params-requireperson-permitname-age-doing-in-rails-4
params控制器看起来像一个哈希，但实际上它的一个实例ActionController::Parameters，它提供了多种方法，如require和permit。

require方法确保存在特定的参数，如果未提供，require方法将引发错误。它返回ActionController::Parameters传入的密钥的一个实例require。

permit方法返回参数对象的副本，只返回允许的键和值。当创建一个新的ActiveRecord模型时，只有允许的属性被传递到模型中。
# 写法
period_id, course_id = params[:period_id], params[:course_id]

 CommentTemplate.eager_load(:comment_category).where(comment_categories: {comment_type: ['standard', 'creation']}).update_all(comment_label: "normal")

# save和save！

save失败返回ni l

Save!失败抛出异常

# pluck(:id)

纵向取值

# where用法

```rb
Movie.where('release > ?', DateTime.now)
where("LENGTH(title) > 20")
Book.where("LENGTH(title) > ?", params[:min_length])
Book.where("LENGTH(title) > :min", min: params[:min_length])
Book.where.not(category: "Java")
Book.where.not(title: nil)
Book.where(category: "Programming").or(Book.where(category: "Ruby"))
Book.where(id: [1,2,3])
	SELECT "books".* FROM "books" WHERE "books"."id" IN (1, 2, 3)
User.where.not(id:[1,2,3])
```

# Order用法

```
User.order(:name)
# SELECT "users".* FROM "users" ORDER BY "users"."name" ASC

User.order(email: :desc)
# SELECT "users".* FROM "users" ORDER BY "users"."email" DESC

User.order(:name, email: :desc)
# SELECT "users".* FROM "users" ORDER BY "users"."name" ASC, "users"."email" DESC

User.order('name')
# SELECT "users".* FROM "users" ORDER BY name

User.order('name DESC')
# SELECT "users".* FROM "users" ORDER BY name DESC

User.order('name DESC, email')
# SELECT "users".* FROM "users" ORDER BY name DESC, email
```

# 连表查询

eager_load	左连接?

includes	

joins	内连接?

joins	内连接?
=======
# rails回调

\> before_validation
\> before_validation_on_create
\> after_validation
\> after_validation_on_create
\> before_save
\> before_create
\> DATABASE INSERT
\> after_create
\> after_save

# distinct and uniq

**Rails查询就像数组一样**，因此`.uniq`会产生与`.distinct`相同的结果，但是

- `.distinct`是SQL查询方法
- `.uniq`是数组方法

**注意**：在Rails 5+中`Relation#uniq`已弃用，建议改为使用`Relation#distinct`。 见http://edgeguides.rubyonrails.org/5_0_release_notes.html#active-record-deprecations

<强>提示：

在致电`.includes`之前使用`.uniq/.distinct`可以*慢*或*加速*您的应用，因为

- `uniq`不会产生额外的SQL查询
- `distinct`会做

但两个结果都是一样的

示例：

```
users = User.includes(:posts)
puts users
# First sql query for includes

users.uniq
# No sql query! (here you speed up you app)
users.distinct
# Second distinct sql query! (here you slow down your app)
```

这对于制作高性能应用程序非常有用

<强>提示：

同样适用于

- `.size` vs `.count`;
- `present?` vs `.exists?`
- `pluck` vs `map`

# ruby的数组

```
2.6.1 :109 > t="12"
"12"
2.6.1 :110 > puts "#{t[0]},#{t[1]},#{t[2]}-----#{t[-1]},#{t[-2]},#{t[-3]}"
1,2,-----2,1,
nil
2.6.1 :111 > 
```

+ 没有常量池的概念
```
2.6.1 :111 > t="123"
"123"
2.6.1 :112 > y="123"
"123"
2.6.1 :113 > t.object_id
70151270741780
2.6.1 :114 > y.object_id
70151533108760
```
+ Symbols类似常量池
```
2.6.1 :123 > x=:yes
:yes
2.6.1 :124 > y=:yes
:yes
2.6.1 :125 > x.object_id
17561948
2.6.1 :126 > y.object_id
17561948
```

```
2.6.1 :127 > x="123"
"123"
2.6.1 :128 > y="123"
"123"
2.6.1 :129 > x.object_id
70151533269900
2.6.1 :130 > y.object_id
70151533302500
2.6.1 :131 > xs=x.to_sym
:"123"
2.6.1 :132 > ys=y.to_sym
:"123"
2.6.1 :133 > xs.object_id
70151533402300
2.6.1 :134 > ys.object_id
70151533402300
```

# 反射

+ obj.respond_to?(:hello)  当前对象是否有hello方法,也可以使用字符串"hello"
+ obj.send(:methodName,params...)    动态调用当前对象的某个方法，也可以使用字符串
+ define_method动态定义方法，需要传递方法名和代码块
	```
	class Fcy
  define_method :hello do |my_arg|
    my_arg
  end
end
obj = Rubyist.new
puts(obj.hello('fcy hello world')) # => Matz

	```

+ method_missing    当搜索不到方法时会调用method_missing方法

# 关联

```
SettleRecord.eager_load(:payment_record, [last_record: [settle_record_orders: [settle_record_details: :partner]]])

LEFT OUTER JOIN "payment_records" 
ON "payment_records"."id" = "settle_records"."payment_record_id"
LEFT OUTER JOIN "settle_records" 
"last_records_settle_records" ON "last_records_settle_records"."last_record_id" = "settle_records"."id"
LEFT OUTER JOIN "settle_record_orders" ON                                             "settle_record_orders"."settle_record_id" =                             "last_records_settle_records"."id"
LEFT OUTER JOIN "settle_record_details" ON                                           "settle_record_details"."settle_record_order_id" =                                          "settle_record_orders"."id"
LEFT OUTER JOIN "partners""partners"."id" = "settle_record_details"."partner_id"
```



```
Category.joins(articles: [{ comments: :guest }, :tags])

INNER JOIN articles ON articles.category_id = categories.id
INNER JOIN comments ON comments.article_id = articles.id
INNER JOIN guests ON guests.comment_id = comments.id
INNER JOIN tags ON tags.article_id = articles.id
```

# sidekiq

```
bundle exec sidekiq  -C config/sidekiq.yml 调试启动方式
bundle exec sidekiq  -C config/sidekiq.yml -d 后台启动方式
bundle exec sidekiq  -C config/sidekiq.yml -d -e production 指定环境启动
```

# skill

gem unpack rails   把gem源赋值到当前目录

require 'active_record'

```rb
ActiveRecord::Base.establish_connection(
  adapter:  'postgresql', # or 'postgresql' or 'sqlite3'
  database: 'mozhou_uat',
  username: 'mozhou',
  password: 'N5z4PtAbyTaVPv5g',
  host:     's2-mozhou-tech.moshuokejiao.com'
)
class Order < ActiveRecord::Base
end

def source_for(object, method)
  location = object.method(method).source_location
  `sed -n '9p' test.txt`
  `# sed -n '9p;15p' passwd `
  `sed -n '9
  ,15p' passwd `
  `code #{location[0]}:#{location[1]}` if location && location[0] != '(eval)'
  location
end

def source_for(object, method)
  location = object.method(method).source_location
  `code --goto #{location[0]}:#{location[1]}` if location && location[0] != '(eval)'
  location
end

source_for(User.first,:update_attribute)


$ 是 pry 为我们提供的用于查看方法源代码的工具
```



## code启动vscode

Ctrl+Shift+P

Shell command in path

## ruby执行Linux命令

`ls`

# rails

```
ActionController::Parameters.permit_all_parameters = true
cd /www/k8s/apps/logs/mozhou-api-uat
```

# eager_load,includes,joins

```
Rails has 2 ways of avoiding the n+1 problem. One involves creating a big join based query to pull in your associations, the other involves making a separate query per association.

When you do includes rails decides which strategy to use for you. It defaults to the separate query approach (preloading) unless it thinks you are using the columns from the associations in you conditions or order. Since that only works with the joins approach it uses that instead.

Rails' heuristics sometimes get it wrong or you may have a specific reason for preferring one approach over the other. preload ( and its companion method eager_load) allow you to specify which strategy you want rails to use.
```

# around_create and before_create
Had this question, too, and have now found the answer: around_create allows you to basically do both a before_create and an after_create in one method. You have to use yield to execute the save in between.
```
class MyModel < ActiveRecord::Base
  around_create :my_callback_method

  private
    def my_call_back_method
      # do some "before_create" stuff here

      yield  # this makes the save happen

      # do some "after_create" stuff here
    end
end
```

# 回调顺序
3.1 创建对象
before_validation
after_validation
before_save
around_save
before_create
around_create
after_create
after_save
after_commit/after_rollback

3.2 更新对象
before_validation
after_validation
before_save
around_save
before_update
around_update
after_update
after_save
after_commit/after_rollback

3.3 删除对象
before_destroy
around_destroy
after_destroy
after_commit/after_rollback


# 查看修改之前的值
user.real_name # ttt
user.real_name = 'fcy'
user.real_name_was # ttt

# rails c获取上一条命令的输出
"_"保存着上一条命令返回的结果

