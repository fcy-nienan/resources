maven的生命周期
三套独立的生命周期
clean,default,site
clean生命周期
    pre-clean   清理前的工作
    clean       清理相关目录
    post-clean  清理后的工作
default生命周期
    validate    valid the project is correct and the necessary information is avaiable
    compile     compile the source code
    test        run the all test
    package     package it
    integration-test    集成测试
    verify      ensure the quality of the result of the integration-test of the project are met
    install     install the package into the repository
    deploy      copy the package to the remote repository for sharing with other developers or projects
site生命周期
    pre-site
    site
    post-site

mvn dependency:tree 查看当前项目依赖

任何一个POM文件都隐式地继承一个SuperPOM,超级POM文件中定义了项目中的一系列参数
比如源码目录,资源目录,测试目录,输出目录等等,也就是默认的src/man/java等目录

每个生命周期有多个phase(阶段)
阶段需要和goal(插件目标)绑定
如果没指定插件目标则使用maven默认的绑定
如下配置
每个execution都是一个执行任务
下面run目标与pre-clean阶段绑定,那么当执行到clean生命周期的pre-clean中时就会执行此插件中的run这个目标
(应该就是该插件实现了maven提供的相关接口,然后这个run目标名由插件开发者自定义,也可以类比为命令行参数)
一个goal就是一个实现了maven相关接口的类,然后通过类似与Controller注解指定该goal的名称,然后再注入一系列参数
然后重写execute方法进行相关的工作
<plugin>
   <groupId>org.apache.maven.plugins</groupId>
   <artifactId>maven-antrun-plugin</artifactId>
   <version>1.1</version>
   <executions>
      <execution>
         <id>id.pre-clean</id>
         <phase>pre-clean</phase>
         <goals>
            <goal>run</goal>
         </goals>
         <configuration>
            <tasks>
               <echo>pre-clean phase</echo>
            </tasks>
         </configuration>
      </execution>
      <execution>
         <id>id.clean</id>
         <phase>clean</phase>
         <goals>
          <goal>run</goal>
         </goals>
         <configuration>
            <tasks>
               <echo>clean phase</echo>
            </tasks>
         </configuration>
      </execution>
      <execution>
         <id>id.post-clean</id>
         <phase>post-clean</phase>
         <goals>
            <goal>run</goal>
         </goals>
         <configuration>
            <tasks>
               <echo>post-clean phase</echo>
            </tasks>
         </configuration>
      </execution>
   </executions>
   </plugin>
   
# maven的profile

# maven打包跳过测试
    mvn package -Dmaven.test.skip=true 
    mvn install -Dmaven.test.skip=true
# maven
    通过profiles属性定义不同环境下的属性
    通过resources标签定义哪些目录哪些文件会被打包
