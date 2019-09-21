java.lang.IllegalStateException: The procedure WAL relies on the ability to hsync for proper operation during component failures, but the underlying filesystem does not support doing so. Please check the config value of 'hbase.procedure.store.wal.use.hsync' to set the desired level of robustness and ensure the config value of 'hbase.wal.dir' points to a FileSystem mount that can provide it.

hbase-site.xml增加配置 

<property>
<name>hbase.unsafe.stream.capability.enforce</name>
<value>false</value>
</property>


在spark上运行程序出现如下异常（serialVersionUID不一致）
Caused by: org.apache.spark.SparkException: Job aborted due to stage failure: Task 1 in stage 193.0 failed 4 times, most recent failure: Lost task 1.3 in stage 193.0 (TID 392, ...): java.io.InvalidClassException: ** local class incompatible: stream classdesc serialVersionUID = -9117779196120965598, local class serialVersionUID = 2841008943488659566

这个异常是说编译的class的uid和集群上的class不一致，导致这个的原因有以下几个：
1、spark运行的jar包的类和集群上的jars包不一致
在运行spark程序的时候，需要把运行的jar包上传到集群上，即通过sparkconf.setJars（）将jar包里的类上传到集群，并分散到各个Worker节点，才能实现并行处理。
所以要保证命令行运行的jar（java -jar …或者spark-submit…）和集群上设置的sparkconf.setJars（）要是同一个jar包。
2、编译运行的类的jdk版本和spark集群上的jdk版本不一致导致的。

这个异常跟类没有序列化不一样，这个是编译的类跟集群上不同节点的相应的类不一致的问题。