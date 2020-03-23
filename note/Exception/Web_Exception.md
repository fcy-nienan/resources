Upload-master

上传文件（测试Jetty占用文件无法修改删除的解决方法）

经测试有效

文件被锁定是由于在使用windows系统时，jetty默认在内存中映射了这些文件，而windows会锁定内存映射的文件。解决的办法就是修改jetty的配置，让其在启动server时将useFileMappedBuffer标志位设置为false。
修改项目中的WEB-INF/web.xml文件，在其中加入这个节点。
<servlet>
    <!-- Override init parameter to avoid nasty -->
    <!-- file locking issue on windows.         -->
    <servlet-name>default</servlet-name>
        <init-param>
            <param-name>useFileMappedBuffer</param-name>
            <param-value>false</param-value>
        </init-param>
</servlet>

# windows无法上网
    右下角显示有网络
    浏览器访问网址无效
    通过Windows诊断发现DNS服务器未响应
    在网络连接配置了一下IPV4中的属性,手动填写DNS地址114.114.114.114
    填写后正常访问网络