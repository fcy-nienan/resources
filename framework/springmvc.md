# springmvc配置文件

```
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans" 
	xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
	xmlns:context="http://www.springframework.org/schema/context" 
	xmlns:jdbc="http://www.springframework.org/schema/jdbc"  
	xmlns:jee="http://www.springframework.org/schema/jee" 
	xmlns:tx="http://www.springframework.org/schema/tx"
	xmlns:aop="http://www.springframework.org/schema/aop" 
	xmlns:mvc="http://www.springframework.org/schema/mvc"
	xmlns:util="http://www.springframework.org/schema/util"
	xmlns:jpa="http://www.springframework.org/schema/data/jpa"
	xsi:schemaLocation="
		http://www.springframework.org/schema/beans http://www.springframework.org/schema/beans/spring-beans-3.2.xsd
		http://www.springframework.org/schema/context http://www.springframework.org/schema/context/spring-context-3.2.xsd
		http://www.springframework.org/schema/jdbc http://www.springframework.org/schema/jdbc/spring-jdbc-3.2.xsd
		http://www.springframework.org/schema/jee http://www.springframework.org/schema/jee/spring-jee-3.2.xsd
		http://www.springframework.org/schema/tx http://www.springframework.org/schema/tx/spring-tx-3.2.xsd
		http://www.springframework.org/schema/data/jpa http://www.springframework.org/schema/data/jpa/spring-jpa-1.3.xsd
		http://www.springframework.org/schema/aop http://www.springframework.org/schema/aop/spring-aop-3.2.xsd
		http://www.springframework.org/schema/mvc http://www.springframework.org/schema/mvc/spring-mvc-3.2.xsd
		http://www.springframework.org/schema/util http://www.springframework.org/schema/util/spring-util-3.2.xsd">
	<!-- 配置组件扫描 -->
	<context:component-scan base-package="controller" />
	<!-- 配置MVC注解扫描 -->
	<mvc:annotation-driven />
	<!-- 配置视图解析器， -->
	<bean class="org.springframework.web.servlet.view.InternalResourceViewResolver">
		<property name="prefix" value="/WEB-INF/" /><!-- 前缀 -->
		<property name="suffix" value=".jsp" /><!-- 后缀 -->
	</bean>
	
	<!-- 配置拦截器 -->
	<mvc:interceptors>
		<mvc:interceptor>
			<mvc:mapping path="/*"/>
			<bean class="interceptors.SomeInterceptor"/>
		</mvc:interceptor>
	</mvc:interceptors>
</beans>
```
# HandlerMapping和HandlerAdapter

HandlerMapping 和 HandlerAdapter 都是 interface ，DefaultAnnotationHandlerMapping 和 RequestMappingHandlerMapping 为 HandlerMapping 的实现类，AnnotationMethodHandlerAdapter 和 RequestMappingHandlerAdapter 为 HandlerAdapter 的实现类

1、Controller：处理器/页面控制器，做的是MVC中的C的事情，但控制逻辑转移到前端控制器了，用于对请求进行处理；

2、HandlerMapping：请求到处理器的映射，如果映射成功返回一个HandlerExecutionChain对象（包含一个Handler处理器（页面控制器）对象、多个HandlerInterceptor拦截器）对象；如BeanNameUrlHandlerMapping将URL与Bean名字映射，映射成功的Bean就是此处的处理器；

3、HandlerAdapter：HandlerAdapter将会把处理器包装为适配器，从而支持多种类型的处理器，即适配器设计模式的应用，从而很容易支持很多类型的处理器；如SimpleControllerHandlerAdapter将对实现了Controller接口的Bean进行适配，并且掉处理器的handleRequest方法进行功能处理；

4、ViewResolver：ViewResolver将把逻辑视图名解析为具体的View，通过这种策略模式，很容易更换其他视图技术；如InternalResourceViewResolver将逻辑视图名映射为jsp视图；

5、LocalResover：本地化解析，因为Spring支持国际化，因此LocalResover解析客户端的Locale信息从而方便进行国际化；

6、ThemeResovler：主题解析，通过它来实现一个页面多套风格，即常见的类似于软件皮肤效果；

7、MultipartResolver：文件上传解析，用于支持文件上传；

8、HandlerExceptionResolver：处理器异常解析，可以将异常映射到相应的统一错误界面，从而显示用户友好的界面（而不是给用户看到具体的错误信息）；

9、RequestToViewNameTranslator：当处理器没有返回逻辑视图名等相关信息时，自动将请求URL映射为逻辑视图名；

10、FlashMapManager：用于管理FlashMap的策略接口，FlashMap用于存储一个请求的输出，当进入另一个请求时作为该请求的输入，通常用于重定向场景



Servlet上下文关系

DispatcherServlet的上下文是通过配置servlet的contextConfigLocation来加载的，默认实现是XmlWebApplicationContext。

值得注意的是DispatcherServlet的上下文仅仅是Spring MVC的上下文，而Spring加载的上下文是通过ContextLoaderListener来加载的。一般spring web项目中同时会使用这两种上下文，前者仅负责MVC相关bean的配置管理（如ViewResolver、Controller、MultipartResolver等），后者则负责整个spring相关bean的配置管理（如相关Service、DAO等）。

因此在/WEB-INF/[server-name]-servlet.xml中配置的Bean一般只针对Spring MVC有效，而在ContextLoaderListener配置文件下配置的bean则对整个spring有效。