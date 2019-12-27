gcc命令处理过程
预处理--》汇编--》二进制--》链接--》可执行程序或者库文件

预处理
    gcc -E test.c -o test.i
生成汇编代码
    gcc -S test.i -o test.s
生成二进制文件
    gcc -c test.s -o test.o
链接
    gcc test.o -o test
然后执行./test


编译静态库
    前提条件  有一个二进制文件test.o
    ar rcs -o static-library.a test.o
编译动态库
    生成目标文件  gcc -c -o test.o -fPIC test.c
    使用shared参数生成动态库 gcc -shared -o dynamic-library.so test.o