# comparator接口和comparable

多个对象之间的排序需要一个排序规则  
int,short,long,double等基本数据类型有默认的排序规则  
但自定义的类就没有，这个排序规则需要我们自己去定义  
如Student类有name，age，score三个属性，可以用不同的属性来排序  
comparable接口就是要排序的对象必须实现的接口  
comparator接口就是把排序规则独立出来，然后需要排序的时候在将某个排序规则传递过去  
Student implements comparable  
class orderbyname implements comparator根据姓名排序  
class orderbyage implements comparator根据年龄排序  
使用方法:  
Arrays.sort(allStudents,orderbyname_instance);  
Arrays.sort(allStudents,orderbyage_instance);  

comparator接口的比较方法返回值老是忘记，记录一下:  
>a negative integer, zero, or a positive integer as the
first argument is less than, equal to, or greater than the
second

-1,0,1分别表示  
this<other   
this=other   
1this>other   