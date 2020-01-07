配置yum源

找到/etc/yum.repos.d目录下的Centos-Base.repo
修改其中的baseurl为http://mirrors.aliyun.com/repo/Centos-6.repo

集线器 广播
交换机 MAC
路由器 IP

、桥接：就是把虚拟机通过VMnet0桥接到主机的本地连接。

       现在虚拟机是通过VMnet0与外界联系，现在的虚拟机就相当于和主机一样是物理网络中的一台电脑，
       说的通俗的就是现在虚拟机就相当于和你主机同在一个网络的另一台真实的电脑。
       所以要想使用桥接使虚拟机上网，前提必须你的主机处在局域网中，
       也就是你的主机上网得有路由器，这时才能用桥接使虚拟机上网。
       至于虚拟机的IP设置方式和你主机一样，用不用设置IP要看你的路由器是否开启了DHCP和DNS，
       主机不用虚拟机也不用，主机要设置那么虚拟机也要设置。对于那些使用拨号上网方式并且没用路由器的就不要用桥接。

     2、NAT：就是网络地址转换，通过VMnet8连接作为网关使虚拟机经过主机上网。

      现在虚拟机是通过VMnet8与外界联系，说的通俗的就是在你的主机和虚拟机之间加了一个路由器，虚拟机通过这个路由器上网。NAT方式就不用考虑那么多，只要你主机能上网虚拟机就能上网，所以一般没有特殊要求推荐用NAT方式。

     3、host-only：就是虚拟机和主机在一个私有网络中。

       这时虚拟机只能和主机通讯，默认它是不能上网的。（当然不是绝对的，要想上网不过要进行另外的设置）
	   
	   
	   
	   
	   
	   
	   什么是桥接模式？桥接模式就是将主机网卡与虚拟机虚拟的网卡利用虚拟网桥进行通信。在桥接的作用下，
	   类似于把物理主机虚拟为一个交换机，所有桥接设置的虚拟机连接到这个交换机的一个接口上，
	   物理主机也同样插在这个交换机当中，所以所有桥接下的网卡与网卡都是交换模式的，
	   相互可以访问而不干扰。在桥接模式下，虚拟机ip地址需要与主机在同一个网段，
	   如果需要联网，则网关与DNS需要与主机网卡一致。其网络结构如下图所示：
	   
	   
	   
	   
	   
	   
	   
	   
	   EL是Red Hat Enterprise Linux的简写 
- EL6软件包用于在Red Hat 6.x, CentOS 6.x, and CloudLinux 6.x进行安装 
- EL5软件包用于在Red Hat 5.x, CentOS 5.x, CloudLinux 5.x的安装 
- EL7 软件包用于在Red Hat 7.x, CentOS 7.x, and CloudLinux 7.x的安装

数据库中的host
则:;1表示为ipv6，即ipv4的127.0.0.1

vim搜索高亮 set hlsearch

::1            localhost

出站规则和入站规则
出站规则是服务器访问外网
入站规则是外网访问服务器

多播和广播？
0.0.0.0和255.255.255.255
The IP address 0.0.0.0 is used as a wildcard to bind to all addresses. The IP address 255.255.255.255 is used to indicate a local broadcast.

    0.0.0.0代表本机的所有IPV4地址
    255.255.255.255代表所有的主机,这个所有是指互联网的所有主机吗(兴奋)
    不是的，有广播边界(一般是网关)
    受限广播地址
    
    255.255.255.255 to indicate all other nodes on the local network (LAN) should pick up that message. This broadcast is 'limited' in that it does not reach every node on the Internet, only nodes on the LAN
    
IP地址  120.79.158.25
网络地址 120
网络掩码 255.0.0.0
主机地址  79.158.25

那120.0.0.0和120.255.255.255这两个地址是干啥的?
一个是代表一个网段,一个是广播段
192.168.0.0           网段
192.168.0.255           广播段
192.168.0.1 - 192.168.0.254   IP地址