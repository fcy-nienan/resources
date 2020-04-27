# winsows10的快捷键Ctrl+Alt+S和IDEA的快捷键冲突
Ctrl+Alt+S出现一个框选录屏区域  
没找到Windows的这个快捷键在哪设置  
只能更改IDEA的快捷键了
后来好像是关闭了xbox后正常了
# Windows下通过bat设置环境变量  
```
echo.................
echo 开始注册环境变量
echo.................
rem start /WAIT jre-8u144-windows-i586.exe /s INSTALLDIR=C:\Java\jre
rem set只对当前session有效,setx全局有效
setx JAVA_HOME "D:\Code\Language\java"
setx GRADLE_HOME "D:\Code\Build\gradle-5.6"
setx M2_HOME "D:\Code\Build\apache-maven-3.6.1"
setx MAEVN_HOME "D:\Code\Build\apache-maven-3.6.1"
setx NODEJS_HOME "D:\Code\Language\nodejs"
setx PYTHON_HOME "D:\Code\Language\python"
setx SBT_HOME "D:\Code\Build\sbt-1.3.5"
setx SCALA_HOME "D:\Code\Language\scala-2.13.0"
SETX GIT_HOME "D:\Code\CodeTool\VCS\Git"
setx TEMP "D:\Dir\tmp"
setx TMP "D:\Dir\tmp"
setx SPARK_HOME "D:\Code\BigData\spark-2.4.3-bin-hadoop2.7"
setx HADOOP_HOME "D:\Code\BigData\hadoop-3.1.2"
setx CLASSPATH ".;%JAVA_HOME%\lib\dt.jar;%JAVA_HOME%\lib\tools.jar;"

rem 将path变量的值写在一起，要不然会出现一些奇怪的现象，另外path的值最大1024
setx PATH "%PATH%;%SYSTEMROOT%\System32\OpenSSH\;%SYSTEMROOT%\System32\WindowsPowerShell\v1.0\;%GIT_HOME%\cmd;%JAVA_HOME%\bin;%GRADLE_HOME%\bin;%MAEVN_HOME%\bin;%NODEJS_HOME%\bin;%PYTHON_HOME%\bin;%SBT_HOME%\bin;%SCALA_HOME%\bin;%SPARK_HOME%\bin;"

mshta vbscript:msgbox("环境变量已成功注册！",64,"成功")(window.close)

pause
```