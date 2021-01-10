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

# Windows下定时任务

    cmd taskschd.msc
    
    set timestamp=%date:~0,4%%date:~5,2%%date:~8,2%%time:~0,2%%time:~3,2%%time:~6,2%
    echo %timestamp%
    echo %timestamp% > D:\%timestamp%

# bat不显示窗口

	CreateObject("WScript.Shell").Run "cmd /c D:\ScheduledTask\shieldWIndows.bat",0

# bat

    参数  %1%   %2%
    
    call other.bat
    start other.bat
    call是同步调用,在一个cmd总执行
    start是开多个cmd执行

# wireshark抓取本机回环数据

    net start npf
    route add 192.168.43.176 mask 255.255.255.255 192.168.43.1  metric 1
    打开wireshark选择本地回环网卡

# 环境变量

    在cmd窗口中set设置的环境变量为临时变量，如：


    set PATH=%PATH%;D:\Program Files\
    
    使用setx设置为永久环境变量,适用于bat中：
    
    setx PATH "%PATH%;D:\Program Files\"
    setx 后面的字符串最长1024
    
    setx ENV_NAME env_value /m
    setx ENV_NAME env_value


​    

# window下查找文件

	for /r testdir %i in (*) do @echo %i 列举testdir目录及所有子目录的所有文件
	for /r testdir %i in (*.txt,*.jpg,*.java) do @echo %i 寻找txt,jpg,java文件

# window下查找字符串

	netstat -ano | find "8080"

# windows下路由表的在链路上是啥意思

    IPv4 路由表
    ===========================================================================
    活动路由:
    网络目标            网络掩码            网关                  接口           跃点数
              0.0.0.0          0.0.0.0     172.16.0.254     172.16.0.220     35
              0.0.0.0          0.0.0.0   130.233.90.254    130.233.17.91     55
             10.0.0.0        255.0.0.0     172.16.0.254     172.16.0.220     36
            127.0.0.0        255.0.0.0            在链路上         127.0.0.1    331
            127.0.0.1  255.255.255.255            在链路上         127.0.0.1    331
      127.255.255.255  255.255.255.255            在链路上         127.0.0.1    331
          130.233.0.0      255.255.0.0            在链路上     130.233.17.91    311
        130.233.17.91  255.255.255.255            在链路上     130.233.17.91    311
      130.233.255.255  255.255.255.255            在链路上     130.233.17.91    311
           172.16.0.0    255.255.255.0            在链路上      172.16.0.220    291
         172.16.0.220  255.255.255.255            在链路上      172.16.0.220    291
         172.16.0.255  255.255.255.255            在链路上      172.16.0.220    291
            224.0.0.0        240.0.0.0            在链路上         127.0.0.1    331
            224.0.0.0        240.0.0.0            在链路上      172.16.0.220    291
            224.0.0.0        240.0.0.0            在链路上     130.233.17.91    311
      255.255.255.255  255.255.255.255            在链路上         127.0.0.1    331
      255.255.255.255  255.255.255.255            在链路上      172.16.0.220    291
      255.255.255.255  255.255.255.255            在链路上     130.233.17.91    311
    ===========================================================================
    永久路由:
      无
    上述的网关下的值“显示在链路上”代表的是网关地址和接口地址一样

# 路由表解释

    如第一条
            0.0.0.0          0.0.0.0     172.16.0.254     172.16.0.220     35
    这个是默认路由，如果网络地址没匹配路由表中的任何一项,则通过172.16.0.220接口地址发送到172.16.0.254这个网关
    如第二条
    10.0.0.0        255.0.0.0     172.16.0.254     172.16.0.220     36
    10网段的掩码是255.0.0.0,访问10网段地址的请求将通过172.16.0.220这个接口地址发送到172.16.0.254网关
    
    上述的172.16.0.22这个一般也能通过ipconfig这个命令查询到，这个就是本地电脑的某一个网络地址

# windows下网络命令

    输入netsh可一层一层显示
    
    输入
    netsh interface ip 
    可显示命令信息
    netsh interface tcp同理

# Windows下删除目录

    rd命令

# Windows下显示所有环境变量

	set命令可以显示所有环境变量

# Windows下小工具命令行

	snippingtool   截图
	Win+Shift+S    框选截屏
	mspaint 		画图板
	notepad			记事板
	calc			计算器
	services.msc	服务
	diskmgmt.msc	磁盘管理
	compmgmt.msc	计算机管理
	perfmon.msc		性能监视器
	devmgmt.msc		设备管理器

# windows家庭版执行gpedit.msc

bat执行下面的代码

```
@echo off
  pushd "%~dp0"
  dir /b %systemroot%\Windows\servicing\Packages\Microsoft-Windows-GroupPolicy-ClientExtensions-Package~3*.mum >gp.txt
  dir /b  %systemroot%\servicing\Packages\Microsoft-Windows-GroupPolicy-ClientTools-Package~3*.mum >>gp.txt
  for /f %%i in ('findstr /i . gp.txt 2^>nul') do dism /online /norestart /add-package:"%systemroot%\servicing\Packages\%%i"
  pause

```



# win10 家庭版 关闭Antimalware Service Executable

以管理员身份运行

```
reg add "HKEY_LOCAL_MACHINE\SOFTWARE\Policies\Microsoft\Windows Defender" /v "DisableAntiSpyware" /d 1 /t REG_DWORD /f
```

