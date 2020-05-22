# Promise
```
	new Promise(function (resolve,reject){
		if(1>2){
			resolve("1>2")
		}else{
			reject("1<2")
		}
	}).then(function(success){
		console.log(success);
	},function(error){
		console.log(error);
	})
```
# async和await

	这个是基于Promise的,语义层面的,包装了一层

# 微任务和宏任务
	引擎先执行微任务然后执行宏任务
	执行过程中碰到微任务将其放入一个队列,碰到宏任务将其放入一个队列
# JavaScript单线程
	JavaScript是单线程的,基于事件驱动
	浏览器是多线程的
	Ajax请求所在的线程是浏览器托管的
	Ajax请求完成后将完成事件放入到发出线程的时间队列中
	
	SetTimeout也是如此,浏览器另开一个线程计时,计时完成后将完成事件放入到事件队列中
	
	JavaScript单线程需要执行脚本(变量赋值,计算等)
	对点击Dom元素的事件做出相应
	对SetTimeout做出响应
	对Ajax完成的IO做出响应
	对Promise.then做出响应