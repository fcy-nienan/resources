# spring中bean的存在形式

对于的接口是BeanDefinition
```
public interface BeanDefinition extends AttributeAccessor, BeanMetadataElement
```

最本质只是一个Object对象,但是由于我们要托管给Spring去管理去实现依赖注入等功能,自然就多了一些其他的东西

+ spring需要知道如何去创建这个对象

+ 该对象详细的生命周期

+ spring需要知道这个对象需要哪些依赖

# Bean和BeanDefinition
	BeanDefinition是对象的定义,spring管理对象需要我们定义对象的属性(如何创建,依赖等)
	Bean是Spring根据BeanDefinition通过某种代理创建出来的对象
# BeanFactory和ApplicationContext
	BeanFactory是最底层的Bean容器,实例化和
	ApplicationContext


# IOC容器启动的主要过程
```
public void refresh() throws BeansException, IllegalStateException {
		synchronized (this.startupShutdownMonitor) {
			// Prepare this context for refreshing.
			prepareRefresh();

			// Tell the subclass to refresh the internal bean factory.
			ConfigurableListableBeanFactory beanFactory = obtainFreshBeanFactory();

			// Prepare the bean factory for use in this context.
			prepareBeanFactory(beanFactory);

			try {
				// Allows post-processing of the bean factory in context subclasses.
				postProcessBeanFactory(beanFactory);

				// Invoke factory processors registered as beans in the context.
				invokeBeanFactoryPostProcessors(beanFactory);

				// Register bean processors that intercept bean creation.
				registerBeanPostProcessors(beanFactory);

				// Initialize message source for this context.
				initMessageSource();

				// Initialize event multicaster for this context.
				initApplicationEventMulticaster();

				// Initialize other special beans in specific context subclasses.
				onRefresh();

				// Check for listener beans and register them.
				registerListeners();

				// Instantiate all remaining (non-lazy-init) singletons.
				finishBeanFactoryInitialization(beanFactory);

				// Last step: publish corresponding event.
				finishRefresh();
			}

			catch (BeansException ex) {
				logger.warn("Exception encountered during context initialization - cancelling refresh attempt", ex);

				// Destroy already created singletons to avoid dangling resources.
				destroyBeans();

				// Reset 'active' flag.
				cancelRefresh(ex);

				// Propagate exception to caller.
				throw ex;
			}
		}
	}
```

