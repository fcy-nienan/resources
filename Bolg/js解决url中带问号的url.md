# 问题

我要从当前页面打开一个新的页面并且传入url参数

通过window.open打开

地址是 http://www.xxx.cn/page1?url=http://www.xxx.cn/page2?params1=x&params2=y
在http://www.xxx.cn/page1通过路由接受到的参数是

```
url = http://www.xxx.cn/page2
```
丢失了后面携带的参数

params1和params2

# 解决办法

通过base64对其进行编码

```
window.open("page1?url=" + btoa('http://www.xxx.cn/page2?params1=x&params2=y'));
```

在另一个页面获取url参数并通过atob对其进行解码
```
decodedUrl =  atob(url);
```

# 注意

这里之前用encodeURIComponent，decodeURIComponent和encodeURI，decodeURI这两对函数进行编码解码，均出现了错误，后来发现是参数中有一些特殊字符
后来转用base64成功解决