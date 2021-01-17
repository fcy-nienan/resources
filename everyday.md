# css伪元素设置图片

# css绝对定位和相对定位

‘里面可以包含xml="1.1"这种字符串

“里面会语法错误

# outline不生效

button:active样式

button:focus

box-shadow:none;

# The difference between controller and component

Angular1 是controller

angular2是component

# JavaScript减去七天

```javascript
var sdtime1 = new Date('2018-03-22 16:14:55')

var sdtime2 = sdtime1.setHours(sdtime1.getHours() -1)//小时

var sdtime3=new Date().setDate((new Date().getDate()-7))//7天
var sdtime4=new Date().setMonth((new Date().getMonth()-1))//一个月
var sdtime5=new Date().setFullYear((new Date().getFullYear()-1))//一年	
```

# javascript日期格式化

```
var d = new Date();

var datestring = d.getDate()  + "-" + (d.getMonth()+1) + "-" + d.getFullYear() + " " +
d.getHours() + ":" + d.getMinutes();
```

# content-Type常见类型(以前容易搞混的)

```
application/xhtml+xml：XHTML格式。

application/xml： XML数据格式。

application/atom+xml：Atom XML聚合格式 。

application/json： JSON数据格式。

application/pdf：pdf格式 。

application/msword： Word文档格式。

application/octet-stream： 二进制流数据（如常见的文件下载）。

application/x-www-form-urlencoded： <form encType=””>中默认的encType，form表单数据被编码为key/value格式发送到服务器（表单默认的提交数据的格式）。
multipart/form-data ： 需要在表单中进行文件上传时，就需要使用该格式。
```

