java程序启动后，默认（请注意是默认）会在/tmp/hsperfdata_userName目录下以该进程的id为文件名新建文件，并在该文件中存储jvm运行的相关信息，其中的userName为当前的用户名，/tmp/hsperfdata_userName目录会存放该用户所有已经启动的java进程信息。对于windows机器/tmp用Windows存放临时文件目录代替
https://docs.oracle.com/javase/1.5.0/docs/tooldocs/share/jstat.html#class_option
javap查看字节码
jcmd
jstat查看gc状态，显示的时间时毫秒，大小时KB
jinfo打印Java运行时的相关环境信息Generates configuration information
javah和jni有关,生成想要的jni头文件
jmapPrints shared object memory maps or heap memory details for a process, core file, or remote debug server
jdb通过控制台调试程序
jhat从一个dump文件获取信息并分析并可以通过web访问http://localhost:7000/oqlhelp/
jstack查看线程状态
jps查看运行的进程信息
生成JitWatch分析日志
-XX:+UnlockDiagnosticVMOptions -XX:+PrintAssembly -XX:+LogCompilation -XX:LogFile=jit.log

测试工具
JMH(Java Microbenchmark Harness)

jvm的相关参数
jinfo中看到的参数时不能更改的file.encoding和sun.jnu.encoding这中可以通过System.getProperty获取的
file.encoding affects the content of file;
sun.jnu.encoding affects the name of file;


jcmd pid VM.flags
查看汇编
	将hsdis.dll放到：jre安装目录\bin\server
	java -XX:+UnlockDiagnosticVMOptions -XX:+PrintAssembly -XX:CompileCommand=compileonly,*ThreadAssembly.tttt 
	-XX:CompileCommand=print,*MyClass.myMethod prints assembly for just one method
	-XX:CompileCommand=option,*MyClass.myMethod,PrintOptoAssembly (debug build only) produces the old print command output
	-XX:CompileCommand=option,*MyClass.myMethod,PrintNMethods produces method dumps
	java -XX:+UnlockDiagnosticVMOptions -XX:+PrintAssembly -XX:CompileCommand=compileonly,*TestVolatile1.getInstance TestVolatile1
	java -XX:+UnlockDiagnosticVMOptions -XX:+PrintAssembly -XX:CompileCommand=print,*TestVolatile1.getInstance  TestVolatile1
java分析工具
jinfo -flag MaxHeapSize pid

jinfo -flags pid
# 带包编译
	javac -Djava.ext.dirs=H:\lib springtest.java   编译时添加指定jar包
# 带包运行
	java -classpath hello.jar myapp
# 查看运行时数据hsdb
	java -cp %JAVA_HOME%/lib/sa-jdi.jar sun.jvm.hotspot.HSDB
	查询对象语言	select a from java.lang.String a
# 调试类
	jdb -XX:+UseSerialGC -Xmx10m
	stop in son.show
	run ArrayTest
# 反编译
	jad 将一个class文件反编译为Java文件
	-s 扩展名
	-d 生成文件目录
	-8 utf-8编码
	-o 忽略确认(omit confirmation)
# 打包
	jar 将一个或多个class文件组织成.jar文件格式
	jar cvf hello.jar *.class
	jar cvfm hello.jar MANIFEST.MF *.class(自带MANIFEST.MF文件打包)
	Main-Class: makepojo带包运行(在MANIFEST.MF文件中添加)
	java -jar hello.jar(运行jar)
	显示jar文件的所有文件和目录清单:jar tvf hello.jar
	解压jar文件:jar xvf hello.jar
	
	c是创建jar,t是显示清单,x是解压
	f指定jar报名,v显示详细信息
	
打开任意文件夹后，在空白处按住shift再按右键就可以选择  在此处打开命令窗口
Class-Path: FirstApplet.jar
Class-path: SecondApplet.jar
Java调用类的顺序：java\lib\ext中的类--->Manifest.mf中指定的类-->当前目录中的类-->set CLASSPATH中指定的类
# MANIFEST文件编写规则
	第一行不能有空行,行与行间不能有空行,行尾不能有空格
	最后一行一定是空行
	key: value分号后面有一个空格
GC日志中的PSYoungGen（PS是指Parallel Scavenge）为Eden+FromSpace，
而整个YoungGeneration为Eden+FromSpace+ToSpace。
我们设置的新生代大小为10240K，这包括9216K大小的PSYoungGen和1024K大小的ToSpace。
其中，PSYoungGen中的Eden:FromSpace为8:1，
这包括8192K的Eden和1024K的FromSpace。	













