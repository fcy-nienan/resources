# 多线程

	主线程执行完成后，程序就退出了，子线程就再也没有执行的机会，即主线程结束，子线程也会被迫结束
	(和Java不同,Java是如果开启了子线程,那么主线程运行到了最后整个程序还在运行)
# CLion解决多个main函数问题
```
file (GLOB_RECURSE files *.cpp)
foreach (file ${files})
    string(REGEX REPLACE ".+/(.+)\\..*" "\\1" exe ${file})
    add_executable (${exe} ${file})
    message (\ \ \ \ --\ src/${exe}.cpp\ will\ be\ compiled\ to\ bin/${exe})
endforeach ()
```
# xshell在vim中粘贴错行
	先在vim中输入
	:set paste
	然后再粘贴
# Linux进程和线程的区别