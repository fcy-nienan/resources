docker attach container_id
docker rm
docker rmi
docker ps
docker images
docker ps -as
docker rm $(docker ps -qa)
docker run -it containerId /bin/bash    进入docker

docker查看网络信息    docker inspect image_id | grep IPAddress

docker查看容器被杀的原因 docker inspect image_id -f '{{json .State}}'

查看启动日志
docker logs -f containerID

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
