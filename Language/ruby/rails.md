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