# 全局作用域

## 全局变量

### 显示声明

在全局作用域中带有var的声明

### 隐式声明

在其他作用域中的不带有声明关键字的变量,会被挂在在window对象上

# 函数作用域

函数作用域对外封闭,从外层无法访问函数内的作用域

### 通过return访问函数内部变量

### 通过闭包访问函数内部变量

# 块级作用域

其他语言中如果输出i是会报错的,说明仍在全局作用域里面,没有封闭效果

```
for(var i=0;i<2;i++){
}
console.log(i)//2
console.log(window.i)//2
```

要达到封闭效果需要使用let

```
for(let i=0;i<2;i++){
}
console.log(i) //ReferenceError: i is not defined
```

能形成块级作用域的还有const

```
if(true){
	const x = "inner";
}
console.log(x)  //ReferenceError: x is not defined
```

## 面试题

```
for(var i = 0; i < 5; i++) {
  setTimeout(function() {
     console.log(i);			// 5 5 5 5 5
  }, 200);
};
```

在函数执行的时候i确实是5了,挂在在window上

### 调用函数,创建函数作用域

```
for(var i = 0; i < 5; i++) {
  abc(i);
};

function abc(i) {
  setTimeout(function() {
     console.log(i);			// 0 1 2 3 4 
  }, 200); 
}
```

创建了5个函数作用域来保存

### 采用立即执行函数

```
for(var i = 0; i < 5; i++) {
  (function(j) {
    setTimeout(function() {
      console.log(j);
    }, 200);
  })(i);
};
```

### let创建块级作用域

```
for(let i = 0; i < 5; i++) {
    setTimeout(function() {
      console.log(i);
    }, 200);
};
```

# 词法作用域 VS 动态作用域

## 动态作用域

调用foo函数的时候testValue没有值,然后向上查找,foo实在bar函数内被调用的,bar函数中有一个testValue的值,所以使用的就是bar函数作用域中的这个变量

```
var testValue = 'outer';

function foo() {
  console.log(testValue);		// "inner"
}

function bar() {
  var testValue = 'inner';
  
  foo();
}

bar();
```

## 词法作用域

调用foo函数的时候testValue没有值,然后向上查找,由于定义的时候foo是在Global作用域中定义的,所以查找的也是Global作用域中的testValue

```
var testValue = 'outer';

function foo() {
  console.log(testValue);		// "outer"
}

function bar() {
  var testValue = 'inner';
  
  foo();
}

bar();
```

## 总结

> > When a variable is **lexically scoped**, the system looks to where the function is **defined** to find the value for a free variable. When a variable is **dynamically scoped**, the system looks to where the function is **called** to find the value for the free variable.

词法作用域:去定义的地方查找这个变量

动态作用域:去调用的地方查找这个变量

# 动态绑定和词法绑定
词法作用域和动态作用域指的是如何根据变量名查找变量
## Binding: 命名和值的映射
let a=1
动态绑定: 所有的变量和值在一个全局环境中
静态绑定: 每个作用域绑定创建一个名称和值的环境,并且有等级的组织起来

动态绑定是非常利于修改子系统的行为
静态绑定对程序员更友好,也非常利于编译器优化

>>https://www.emacswiki.org/emacs/DynamicBindingVsLexicalBinding

# 声明提升

## 函数声明和变量声明总是会被移动到他们所在的作用域的顶部(这对你来说是透明的),另外函数声明在最顶层,变量声明在函数声明之下

如下代码不会报错,但输出是undefined

```
console.log(a);
var a=1;
```
最开始我以为他会这样处理,如果这样的话输出就是1了
```
var a=1;
console.log(a)
```
后来想一下,他应该是这样处理
```
var a;
console.log(a);
a=1;
```
考虑如下代码
```
function testOrder(arg) {
    console.log(arg); // arg是形参，不会被重新定义
    console.log(a); // 因为函数声明比变量声明优先级高，所以这里a是函数
    var arg = 'hello'; // var arg;变量声明被忽略， arg = 'hello'被执行
    var a = 10; // var a;被忽视; a = 10被执行，a变成number
    function a() {
        console.log('fun');
    } // 被提升到作用域顶部
    console.log(a); // 输出10
    console.log(arg); // 输出hello
}; 
testOrder('hi');
```
输出如下
```
hi
f a() {
	console.log('fun');
}
10
hello
```
可以认为最后生成了如下代码
```
function testOrder(arg) {
    var a = function(){
    	console.log('fun');
    }
    var arg;
    console.log(arg);
    console.log(a);
    arg = 'hello';
    a = 10;
    console.log(a);
    console.log(arg);
}; 
testOrder('hi');
```
# the difference between var and let
>>The reason why let keyword was introduced to the language was function scope is confusing and was one of the main sources of bugs in JavaScript

var定义的的变量有Hoisting效果,let的没有,let的会引发ReferenceError
```
function run() {
  console.log(foo); // undefined
  var foo = "Foo";
  console.log(foo); // Foo
}

run();
```
```
function checkHoisting() {
  console.log(foo); // ReferenceError
  let foo = "Foo";
  console.log(foo); // Foo
}

checkHoisting();
```