https://docs.docker.com/engine/reference/commandline/inspect/

docker rm 	移除容器
docker rm -f containe_id   强制移除
docker rmi     移除镜像
docker images	查看所有镜像
docker ps -as    查看所有容器
docker rm $(docker ps -qa) docker移除所有运行得容器
docker run -it containerId /bin/bash    进入docker
docker cp 89s894d832kl:/www/web.xml ./	复制容器内的文件到本地
docker inspect image_id | grep IPAddress	查看网络信息    
docker inspect image_id -f '{{json .State}}' 	docker查看容器被杀的原因 
docker logs -f containerID	查看启动日志
docker status id   实时监控dockers内存CPU等情况

# docker网络
    docker network --help
## Bridge模式和Host模式
* No “Port Mapping” is required when the docker “host” network driver will be used.
* “Port Mapping” is required when the docker “bridge” network driver will be used
* Bridge模式使用的是另一个网络协议栈
* Host模式是和主机使用同一个网络协议栈
* Bridge connections are just that, essentially a virtual switch is connected between the VM and your physical network connection.  
* NAT'd connections are also just that, instead of a switch a NAT router is between the VM and your physical network connection.
* 所有计算机都需要连接到交换机上,交换机通过一个MAC地址矩阵将报文发送到目的地址
* 集线器比较笨,通过广播的方式发送给所有的报文
* NAT就是在主机和虚拟容器之间提供了一个路由器
* Bridge就是主机和虚拟容器之间提供了一个交换器
* NAT和Bridge有什么区别?感觉都提供了IP地址啊,然后都可以端口映射
# docker命令参数
## 暂时用得到的
-d: 后台运行容器

-i: 以交互模式运行容器，通常与 -t 同时使用；

-P: 随机端口映射，容器内部端口随机映射到主机的高端口

-p: 指定端口映射，格式为：主机(宿主)端口:容器端口

-t: 为容器重新分配一个伪输入终端，通常与 -i 同时使用；

--name="nginx-lb":  给容器命名

-v  挂载目录    主机目录:容器目录    /opt/docker_v/mysql/conf:/etc/mysql/conf.d：**将主机/opt/docker_v/mysql/conf目录挂载到容器的/etc/mysql/conf.d

## 没接触过的

-a stdin: 指定标准输入输出内容类型，可选 STDIN/STDOUT/STDERR 三项；

--dns 8.8.8.8: 指定容器使用的DNS服务器，默认和宿主一致；

--dns-search example.com: 指定容器DNS搜索域名，默认和宿主一致；

-h "mars": 指定容器的hostname；

-e username="ritchie": 设置环境变量；

--env-file=[]: 从指定文件读入环境变量；

--cpuset="0-2" or --cpuset="0,1,2": 绑定容器到指定CPU运行；

-m :设置容器使用内存最大值；

--net="bridge": 指定容器的网络连接类型，支持 bridge/host/none/container: 四种类型；

--link=[]: 添加链接到另一个容器；

--expose=[]: 开放一个端口或一组端口；

--volume , -v: 绑定一个卷
