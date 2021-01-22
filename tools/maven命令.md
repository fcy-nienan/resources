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
site生命周期   生成项目的站点文档
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
	定义不同的环境(开发，测试，生产)

# maven打包跳过测试
    mvn package -Dmaven.test.skip=true 
    mvn install -Dmaven.test.skip=true
# maven
    通过profiles属性定义不同环境下的属性
    通过resources标签定义哪些目录哪些文件会被打包
# maven多个源的优先级
    本地仓库
    setting.xml
    pom.xml
    中央仓库
# maven的多个setting.xml
    用mvn help:effective-settings可以查看当前生效的settings.xml：
    
    mvn -X命令可以查看settings.xml文件的读取顺序：
# scope属性解析

	scope元素的作用：控制 dependency 元素的使用范围
	compile（默认）
含义：compile 是默认值，如果没有指定 scope 值，该元素的默认值为 compile。被依赖项目需要参与到当前项目的编译，测试，打包，运行等阶段。打包的时候通常会包含被依赖项目。

provided
含义：被依赖项目理论上可以参与编译、测试、运行等阶段，相当于compile，但是再打包阶段做了exclude的动作。
适用场景：例如， 如果我们在开发一个web 应用，在编译时我们需要依赖 servlet-api.jar，但是在运行时我们不需要该 jar 包，因为这个 jar 包已由应用服务器提供，此时我们需要使用 provided 进行范围修饰。

runtime
含义：表示被依赖项目无需参与项目的编译，但是会参与到项目的测试和运行。与compile相比，被依赖项目无需参与项目的编译。
适用场景：例如，在编译的时候我们不需要 JDBC API 的 jar 包，而在运行的时候我们才需要 JDBC 驱动包。

test
含义： 表示被依赖项目仅仅参与测试相关的工作，包括测试代码的编译，执行。
适用场景：例如，Junit 测试

# 快照和版本
    版本（Version）的情况下，如果Maven以前下载过指定的版本文件，比如说data-service:1.0，Maven将不会再从仓库下载新的可用的1.0文件。若要下载更新的代码，data-service的版本需要升到1.1。

快照（Snapshot）的情况下，每次app-ui团队构建他们的项目时，Maven将自动获取最新的快照(data-service:1.0-SNAPSHOT)。

Maven会根据模块的版本号（pom.xml文件中的version）中是否带有-SNAPSHOT来判断是快照版本还是正式版本。如果是快照版本，那么在mvn deploy时会自动发布到快照版本库中，而使用快照版本的模块，在不更改版本号的情况下，直接编译打包时，Maven会自动从镜像服务器上下载最新的快照版本。如果是正式发布版本，那么在mvn deploy时会自动发布到正式版本库中，而使用正式版本的模块，在不更改版本号的情况下，编译打包时如果本地已经存在该版本的模块则不会主动去镜像服务器上下载

Maven中的仓库分为两种，Snapshot快照仓库和Release发布仓库。Snapshot快照仓库用于保存开发过程中的不稳定版本，Release正式仓库则是用来保存稳定的发行版本。定义一个组件/模块为快照版本，只需要在pom.xml文件中在该模块的版本号后加上-SNAPSHOT即可（注意这里必须是大写），如下所示：

<groupId>fcy</groupId>
<artifactId>Util</artifactId>
<version>1.0-SNAPSHOT</version>
<packaging>jar</packaging>

# 使用maven打可执行包

## 依赖包放置到外部目录

```
            <plugin>
                <groupId>org.apache.maven.plugins</groupId>
                <artifactId>maven-jar-plugin</artifactId>
                <configuration>
                    <archive>
                        <manifest>
                            <mainClass>org.b3log.solo.Server</mainClass>
                            <addClasspath>true</addClasspath>
                            <classpathPrefix>lib/</classpathPrefix>
                        </manifest>
                    </archive>
                </configuration>
            </plugin>
            <plugin>
                <groupId>org.apache.maven.plugins</groupId>
                <artifactId>maven-dependency-plugin</artifactId>
                <executions>
                    <execution>
                        <id>copy-dependencies</id>
                        <phase>package</phase>
                        <goals>
                            <goal>copy-dependencies</goal>
                        </goals>
                        <configuration>
                            <outputDirectory>target/lib</outputDirectory>
                        </configuration>
                    </execution>
                </executions>
            </plugin>
```
## 将依赖也打入包

这两个配置可以不用加入,具体作用观察一下jar中META-INF/MANIFEST.MF文件内容就知道了
		<addClasspath>true</addClasspath>

>Whether to create a Class-Path manifest entry. The default value is false.

<classpathPrefix>lib/</classpathPrefix>
>A text that will be prefixed to all your Class-Path entries. The default value is ""

```
            <plugin>
                <artifactId>maven-assembly-plugin</artifactId>
                <configuration>
                    <appendAssemblyId>false</appendAssemblyId>
                    <descriptorRefs>
                        <descriptorRef>jar-with-dependencies</descriptorRef>
                    </descriptorRefs>
                    <archive>
                        <manifest>
                            <mainClass>org.b3log.solo.Server</mainClass>
                        </manifest>
                    </archive>
                </configuration>
                <executions>
                    <execution>
                        <id>make-assembly</id>
                        <phase>package</phase>
                        <goals>
                            <goal>assembly</goal>
                        </goals>
                    </execution>
                </executions>
            </plugin>
```

# 构建java项目

```
mvn archetype:generate "-DgroupId=com.fcy" "-DartifactId=image" "-DarchetypeArtifactId=maven-archetype-quickstart" "-DinteractiveMode=false"

```






















