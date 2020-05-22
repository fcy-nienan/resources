# 三个端口

zkClient连接zkServer的端口
Leader和followers数据交流的端口
followers选举的端口

server.A=B.:C:D

A:表示一个数字，这个数字表示第几个服务器，配置在myid的文件

B:服务器地址，也就是ip地址

C:本台服务器与集群中的lender服务器交换信息端口

D:万一leader挂了就需要这个端口重新选举


Finally, note the two port numbers after each server name: " 2888" and "3888". 
Peers use the former port to connect to other peers. 
Such a connection is necessary so that peers can communicate, 
for example, to agree upon the order of updates. More specifically, 
a ZooKeeper server uses this port to connect followers to the leader. 
When a new leader arises, a follower opens a TCP connection to the leader using this port. 
Because the default leader election also uses TCP, 
we currently require another port for leader election. 
This is the second port in the server entry.

客户端连接Zookeeper服务器
zkCli.sh -server ip:port
zookeeper的选举
    zookeeper中有一个leader,如果leader挂了的话会自动选举一个leader出来

    两种模式，恢复和广播模式
        当leader节点崩溃或者leader丢失太多follower时进入恢复模式，需要选举出一个新的leader
        选举算法有两种basic paxos和fast paxos,默认时fast paxos
    
    事务的一致性，递增的事务id，leaderId+递增计数
    服务器的状态
        leader
        follower
        looking
    选举过程

zookeeper节点类型
    临时节点 -e参数
    顺序节点 -s参数
    不指定默认为持久节点

    事务id和数据的版本号
        每当对zookeeper的文件系统的节点进行crud时都会使用一个新的事务id
        事务id的前32位代表不同的leader时期，后32位是递增的id
    节点内容
        创建时的事务id
        最后修改的事务id
        子节点最后修改的事务id
        数据版本号
        子节点的最新版本号
        ACL版本号
        数据长度

zookeeper提供了哪些功能?
    创建节点
    删除节点
    ls /
    get /path
    set /path 'data'
    delete /path
zookeeper的版本？
    一个路径可以存在多份数据？那最大限制呢，是单独还是共享
    另外中间路径是否可以存数据？可以 /fcy可以存放数据,/fcy/nn同样可以存放数据
zookeeper的watcher
    允许在znode节点上注册观察者，当znode节点发生变更的时候会通知观察者
