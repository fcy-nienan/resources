# 管理spring中注册的bean

	通过context中的方法获取
		ApplicationContext context=new ClassPathXmlApplicationContext("application-context.xml");
	    String[] beanDefinitionNames = context.getBeanDefinitionNames();
	    int beanDefinitionCount = context.getBeanDefinitionCount();
	通过SpringBootActuator管理
# spring的生命周期

	BeanNameAware、BeanFactoryAware、ApplicationContextAware、InitalizingBean、DisposableBean
	相关接口
	其实也就是它内部的初始化流程中提供了一些接口供我们来实现,使得我们可以在spring处理bean的时候注入一些我们自己的代码
# 最基础的spring

+ 注入对象,获取对象

  读取xml配置文件,根据定义生成对象,然后直接通过他提供的方法获取它的引用

  ```
  通过context中的方法获取
  	ApplicationContext context=new ClassPathXmlApplicationContext("application-context.xml");
      String[] beanDefinitionNames = context.getBeanDefinitionNames();
      int beanDefinitionCount = context.getBeanDefinitionCount();
  ```

  

+ 通过注解注入,通过注解获取

​	@Component,@Autowired

# 和web框架整合

JEE中的Listener ,在web.xml中配置

```
<listener>  
        <listener-class>org.springframework.web.context.ContextLoaderListener</listener-class>  
    </listener>  
```

