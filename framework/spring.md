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