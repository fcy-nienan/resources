# ssh免登录原理
    .ssh目录下有三个文件:id_rsa,id_rsa.pub,known_hosts,authorized_keys
    分别用来存放私钥,公钥,已经访问过的主机公钥信息,登陆其他系统需要的公钥信息
    登陆其他系统的时候使用公钥登陆,authorized_keys文件可以存放多个主机的公钥信息
# 证书
## 证书的结构

## 生成证书
    keytool -genkey -v -alias tomcatKey -keyalg RSA -validity 36500 -keystore F:\\tomcatStore
    有效期36500天
    存储位置F:\\tomcatStore
    RSA算法
    别名tomcatKey
# tomcat配置https并且http自动跳转到https
1. 生成证书
2. 配置server.xml
        <Connector port="8443" protocol="org.apache.coyote.http11.Http11Protocol"
                   maxThreads="150" SSLEnabled="true" scheme="https" secure="true"
                   clientAuth="false" sslProtocol="TLS" keystoreFile="F:\\tomcatStore" keystorePass="521314"/>
3. 配置web.xml
        <security-constraint>
        <display-name>Auth</display-name>
        <web-resource-collection>
            <web-resource-name>Protected Area</web-resource-name>
            <url-pattern>/*</url-pattern>
        </web-resource-collection>
        <user-data-constraint>
            <description>SSL required</description>
            <transport-guarantee>CONFIDENTIAL</transport-guarantee>
        </user-data-constraint>
        </security-constraint>
4. 原理
    <Connector port="8080" protocol="HTTP/1.1"
                   connectionTimeout="20000"
                   redirectPort="8443" />
    redirectPort的作用
        If this Connector is supporting non-SSL requests, 
        and a request is received for which a matching <security-constraint> requires SSL transport, 
        Catalina will automatically redirect the request to the port number specified here.
    如果此connector支持非SSL请求,并且收到一个匹配security-constraint需要SSL传输的请求
    Catalina会自动将该请求重定向到redirectPort指定的端口
    通过security-constraint我们也可以指定特定的一些资源将请求重定向到https