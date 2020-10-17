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