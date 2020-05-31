# 下载nexus

官网下载: https://sonatype-download.global.ssl.fastly.net/repository/downloads-prod-group/3/nexus-3.23.0-03-win64.zip
修改配置文件
	nexus-3.23.0-03-win64\nexus-3.23.0-03-win64\etc\nexus-default.properties
	下面配置为通过 http://localhost:8081/nexus访问

```
## DO NOT EDIT - CUSTOMIZATIONS BELONG IN $data-dir/etc/nexus.properties
##
# Jetty section
application-port=8081
application-host=127.0.0.1
nexus-args=${jetty.etc}/jetty.xml,${jetty.etc}/jetty-http.xml,${jetty.etc}/jetty-requestlog.xml
nexus-context-path=/nexus     

# Nexus section
nexus-edition=nexus-pro-edition
nexus-features=\
 nexus-pro-feature

nexus.hazelcast.discovery.isEnabled=true
```
nexus-3.23.0-03-win64\nexus-3.23.0-03-win64\bin\nexus.vmoptions

# 启动nexus

1. 直接在bin目录下执行   .\nexus.exe  /run 

2. 安装为服务   
	2.  .\nexus.exe /install     安装
	3.  .\nexus.exe /uninstall   卸载
	4. 执行net start nexus
3. 访问http://127.0.0.1:8081/nexus页面



# 发布jar包到远程仓库
settings.xml的servers节点下配置
```
	<server>
		<id>releases</id>
		<username>fcy</username>
		<password>666</password>
	</server>
	<server>
		<id>snapshots</id>
		<username>fcy</username>
		<password>666</password>
	</server>
```
pom.xml中配置
```
    <distributionManagement>
        <repository>
            <!--id的名字可以任意取，但是在setting文件中的属性<server>的ID与这里一致-->
            <id>releases</id>
            <!--指向仓库类型为host(宿主仓库）的储存类型为Release的仓库-->
            <url>http://localhost:8081/nexus/repository/fcy-release/</url>
        </repository>
        <snapshotRepository>
            <id>snapshots</id>
            <!--指向仓库类型为host(宿主仓库）的储存类型为Snapshot的仓库-->
            <url>http://localhost:8081/nexus/repository/fcy-snapshot/</url>
        </snapshotRepository>
    </distributionManagement>
```

# 从远程仓库拉取jar包
settings.xml的servers节点下配置
```
	<server>
		<id>releases</id>
		<username>fcy</username>
		<password>666</password>
	</server>
	<server>
		<id>snapshots</id>
		<username>fcy</username>
		<password>666</password>
	</server>
```
pom.xml中配置
```
    <repositories>
        <repository>
            <id>snapshots</id>
            <url>http://localhost:8081/nexus/repository/fcy-snapshot/</url>
            <snapshots>
                <enabled>true</enabled>
                <updatePolicy>always</updatePolicy>
                <checksumPolicy>fail</checksumPolicy>
            </snapshots>
        </repository>
    </repositories>
```
注意:pom.xml中的id需要是settings.xml文件中的id

# Nexus 的仓库分为这么几类：

- hosted 宿主仓库：存放一些个性化的jar包
- proxy 代理仓库：去远程拉取jar包
- virtual 虚拟仓库：用于适配 Maven 1；
- group 仓库组：Nexus 通过仓库组的概念统一管理多个仓库，这样我们在项目中直接请求仓库组即可请求到仓库组管理的多个仓库。


# 参考文章
https://www.cnblogs.com/EasonJim/p/6852840.html
https://www.cnblogs.com/shoufeng/p/11174546.html
