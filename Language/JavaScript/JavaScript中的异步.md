# async关键字和await关键字

```
function getUserData(){
	return new Promise((resolve,reject) => {
		setTimeout(resolve,
	3000);
	})
}
async function blockMethod(){
	console.log("start");
	await getUserData();
	console.log("has alreadly");
}
console.log("xxxxxxx");
blockMethod();
console.log("yyyyyyy");
输出结果:
xxxxxxx
start
yyyyyyy
undefined
has alreadly
```

+ async函数内是同步的,也就是先输出"start"后输出"has alreadly"
+ async内的同步不影响,阻塞其他代码的执行
+  await 只在异步函数里面才起作用。
+ 它可以放在任何异步的，基于 promise 的函数之前。
+ 它会暂停代码在该行上，直到 promise 完成，然后返回结果值。
+ 在暂停的同时，其他正在等待执行的代码就有机会执行了。

# promise

## 为什么需要使用promise

promise使我们能够写干净的回调代码,并且减少回调地狱

>  The Promise object is used for asynchronous computations. A Promise represents a single asynchronous operation that hasn't completed yet, but is expected in the future.

异步计算,代表着一个还未完成的异步操作,但是会在未来完成
promise 代表着一个承诺

## 三种状态

+ pending

  ```
  y=new Promise((r,j)=>{
      setTimeout(r,1000)
  })
  // Promise {<pending>}
  // 一秒后调用
  y
  // Promise {<fulfilled>: undefined}
  ```

+ fullfilled

  ```
  y=new Promise((r,j)=>r(1))
  // Promise {<fulfilled>: 1}
  ```

+ rejected

  ```
  y=new Promise((r,j)=>{
      setTimeout(j,1000)
  })
  // Promise {<pending>}  //刚开始是pending状态
  //Uncaught (in promise) undefined // 调用reject方法会抛出一个异常
  //setTimeout (async)
  //(anonymous) @ VM168:2
  //(anonymous) @ VM168:1
  // 一秒后调用
  y 
  // Promise {<rejected>: undefined} //一秒后变成rejected状态
  ```

## promise的状态转移

这个非常简单

最开始是pending状态

调用resolve方法变成fullfilled状态

调用reject方法变成rejected状态

+ **从pending转换为fullfilled或rejected之后， 这个promise对象的状态就不会再发生任何变化**

  

**可以参照观察者模式进行理解promise,在then和catch中注册了相应的处理方法,而在被观察者new Promise中处理逻辑,然后调用resolve或者reject来通知来主动触发状态转变通知观察者**