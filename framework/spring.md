# 管理spring中注册的bean

	通过context中的方法获取
		ApplicationContext context=new ClassPathXmlApplicationContext("application-context.xml");
	    String[] beanDefinitionNames = context.getBeanDefinitionNames();
	    int beanDefinitionCount = context.getBeanDefinitionCount();
	通过SpringBoot