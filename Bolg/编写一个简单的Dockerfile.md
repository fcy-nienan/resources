```
From ubuntu
MAINTAINER fcy
RUN mkdir /fcy
RUN echo "start to construct a demo image"
RUN echo "复制文件到当前目录(这个目录的位置有坑)" 
ADD ./electron-builder.pptx /fcy
RUN echo "只允许使用一次的CMD指令,重复会覆盖"
CMD touch CMD1.txt
CMD touch CMD2.txt
CMD touch CMD3.txt
CMD top
RUN echo "暴露一个端口"
EXPOSE 8079
RUN echo "指定当前工作目录"
WORKDIR /fcy
RUN pwd
RUN echo "设置环境变量"
ENV env "uat"
RUN echo "访问主机目录"
VOLUME ["/workspace"]
```

执行命令

```
docker build -t fcydemo:v1 .
```

RESULT OUTPUT

```
Sending build context to Docker daemon  567.8kB
Step 1/20 : From ubuntu
 ---> 1d622ef86b13
Step 2/20 : MAINTAINER fcy
 ---> Using cache
 ---> 288e75a8a164
Step 3/20 : RUN mkdir /fcy
 ---> Running in d0df8339db15
Removing intermediate container d0df8339db15
 ---> 761b2c8d6245
Step 4/20 : RUN echo "start to construct a demo image"
 ---> Running in 9510c10b4c43
start to construct a demo image
Removing intermediate container 9510c10b4c43
 ---> 726578fa4154
Step 5/20 : RUN echo "复制文件到当前目录(这个目录的位置有坑)"
 ---> Running in c9d1011aea14
复制文件到当前目录(这个目录的位置有坑)
Removing intermediate container c9d1011aea14
 ---> 3ac57d498efa
Step 6/20 : ADD ./electron-builder.pptx /fcy
 ---> 404a3f27610c
Step 7/20 : RUN echo "只允许使用一次的CMD指令,重复会覆盖"
 ---> Running in 73442f53018a
只允许使用一次的CMD指令,重复会覆盖
Removing intermediate container 73442f53018a
 ---> 84d53cd69f05
Step 8/20 : CMD touch CMD1.txt
 ---> Running in d100752539d9
Removing intermediate container d100752539d9
 ---> a4f40eef24ca
Step 9/20 : CMD touch CMD2.txt
 ---> Running in 7bb12960d565
Removing intermediate container 7bb12960d565
 ---> d2cbd34f93d4
Step 10/20 : CMD touch CMD3.txt
 ---> Running in 04dc0e54d2d0
Removing intermediate container 04dc0e54d2d0
 ---> d5a6eb34d127
Step 11/20 : CMD top
 ---> Running in 8094ef41912e
Removing intermediate container 8094ef41912e
 ---> 37ef72d395cd
Step 12/20 : RUN echo "暴露一个端口"
 ---> Running in b10edd6921f6
暴露一个端口
Removing intermediate container b10edd6921f6
 ---> a13f5639513d
Step 13/20 : EXPOSE 8079
 ---> Running in 4983e4ffbc8e
Removing intermediate container 4983e4ffbc8e
 ---> da29ddee9f05
Step 14/20 : RUN echo "指定当前工作目录"
 ---> Running in 5748ac73f060
指定当前工作目录
Removing intermediate container 5748ac73f060
 ---> 797156730456
Step 15/20 : WORKDIR /fcy
 ---> Running in 48fcb7b3f04e
Removing intermediate container 48fcb7b3f04e
 ---> 76509a430b94
Step 16/20 : RUN pwd
 ---> Running in a196e6625700
/fcy
Removing intermediate container a196e6625700
 ---> 05f32cc56e8a
Step 17/20 : RUN echo "设置环境变量"
 ---> Running in 3512ae96af32
设置环境变量
Removing intermediate container 3512ae96af32
 ---> f30b6c6910b6
Step 18/20 : ENV env "uat"
 ---> Running in 8c442deaf15f
Removing intermediate container 8c442deaf15f
 ---> 673287fb5a72
Step 19/20 : RUN echo "访问主机目录"
 ---> Running in 67aa6a13a589
访问主机目录
Removing intermediate container 67aa6a13a589
 ---> 1d5b2c2cfa66
Step 20/20 : VOLUME ["/workspace"]
 ---> Running in 65510cfaa8a8
Removing intermediate container 65510cfaa8a8
 ---> 291145e2484c
Successfully built 291145e2484c
Successfully tagged fcydemo:v1
```

# run

```
docker run -itd fcydemo:v1
```

# output

```
2e145e0477d481b15fe8e07d1985952d6e32e8568a700eb01a6f061860d902eb
```

# docker ps

```
[root@fcy docker]# docker ps
CONTAINER ID        IMAGE               COMMAND                  CREATED             STATUS              PORTS                    NAMES
2e145e0477d4        fcydemo:v1          "/bin/sh -c top"         9 seconds ago       Up 8 seconds        8079/tcp                 frosty_wu
```

# enter it

```
 docker exec -it 2e /bin/bash
```

# output

```
[root@fcy docker]# docker exec -it 2e /bin/bash
root@2e145e0477d4:/fcy# ls
electron-builder.pptx
root@2e145e0477d4:/fcy# ll
total 560
drwxr-xr-x 1 root root   4096 Oct 15 19:51 ./
drwxr-xr-x 1 root root   4096 Oct 15 19:52 ../
-rw-r--r-- 1 root root 565192 Oct 15 19:34 electron-builder.pptx
root@2e145e0477d4:/fcy#
```

# 碰到的问题

## add指令不起作用

这不起作用，因为`test_input.txt`不在[docker build context](https://docs.docker.com/engine/reference/builder/#usage)中。
执行命令时，最后一个“.”表示生成上下文。Docker所做的是将上下文上传到Docker Deamon以构建图像。在您的情况下，上下文不包含`sudo docker build -t myimage .`，因此未上载，Docker找不到文件/
有两种方法可以解决这个问题：
在测试目录中运行命令`test_input.txt`。在这种情况下，上下文包括所有测试目录。然后修改dockerfile以解释此更改：

```
FROM python:3
...    
ADD code/test.py /test/code/
ADD code/test_output.txt /test/code/
ADD config/test_input.txt /test/configs/
ADD logs/logfile.log /test/logs/
```


第二个选项是简单地将dockerfile移动到测试文件夹中，然后如上所述对其进行修改。在这种情况下，命令`sudo docker build -t myimage -f code/Dockerfile .`应该可以工作。