# 编译时注解

-d 指定放置生成的类文件的位置
-s 指定放置生成的源文件的位置
-cp 指定查找用户类文件和注释处理程序的位置
-classpath 指定查找用户类文件和注释处理程序的位置
-processor 要运行的注释处理程序的名称

javac -d target/classes/ src/main/java/com/fcy/lombok/*.java src/main/java/com/fcy/processor/*.java src/main/
java/com/fcy/Bean/*.java


javac -cp target/classes/ -d src/ -processor com.fcy.processor.FcyLomBok -s src src/main/java/com/fcy/Bean/St
udent.java
Student

javac -cp -cp target/classes -d src/ -processor org.example.FcyLomBak -s D:\\ 


