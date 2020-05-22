boolean           Z  
byte                B  
short               S  
int                 I  
long                J  
float               F  
double              D  
void                V  
引用                 String-->Ljava/lang/String;  
数组                 int[]--->[I
可以看到除了long和boolean不同外,其他都是相应类型的第一个字母  
long是J,boolean是Z,引用是L开头然后跟上类的全路径名加一个';'号

一个方法的表示形式是:(参数...)返回值  
如下左边的是class文件中的定义,右边是代码中的定义  
()I                        int getSize()  
()Ljava/lang/String;	   String toString()  
([Ljava/lang/String;)V	   void main(String[] args)  
()V	                       void wait()  
(JI)V	                   void wait(long timeout, int nanos)  
(ZILjava/lang/String;II)Z  boolean regionMatches(boolean ignoreCase, int toOffset, String other, int ooffset, int len)  
([BII)I	                   int read(byte[] b, int off, int len )  
()[[Ljava/lang/Object;	   Object[][] getObjectArray()  

