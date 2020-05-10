# aspect的三个概念

+ join point:  is a well-defined point in the program flow
+ pointcut :  picks out certain join points and values at those points
+ advice:  is code that is executed when a join point is reached

## advice(增强)
	是我们实际需要执行的代码
## join point(连接点)
	可以理解为方法前,方法后
## pointcut(切点)
	可以理解为在哪些指定的方法中
	通过一组正则匹配规则