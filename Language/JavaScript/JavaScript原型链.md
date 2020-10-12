# 属性和prototype属性和\__proto__属性

​	\__proto__属性是用来查找方法的

​	prototype属性是当你new一个对象时来寻找原型的

```
	function Person(){
		this.name="nienan";
	}
	x=new Person();
	y=new Person();
	x.__proto__ == Person.prototype   //true
	y.__proto__ == Person.prototype   //true
	x.__proto__.__proto__ == Object.prototype //true
	typeof Person //function
	typeof Person.prototype //object
	typeof Function //function
	typeof Function.prototype // function
	typeof Object // function
	typeof Object.prototype //object
	
	Person.constructor == Function // true
	Person.__proto__ == Function.prototype // true
	Person.prototype.constructor == Person // true
	Person.prototype.__proto__ == Object.prototype

	
	Object.constructor == Function // true
	Object.__proto__ == Function.prototype // true
	Object.prototype.constructor == Object // true
	Object.prototype.__proto__ == null
	
	Function.constructor == Function
	Function.__proto__ == Function.prototype
	Function.prototype.constructor == Function
	Function.prototype.__proto__ == Object.prototype
	

```

# 删除一个属性

delete o.x

# 查询对象是否拥有某个属性

hasOwnProperty()

hasOwnProperty有可能被用户重新定义,所以可以使用({}).hasOwnProperty.call(foo,'bar')来判断

该函数不会向上查询(查询原型链的)