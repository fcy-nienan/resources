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