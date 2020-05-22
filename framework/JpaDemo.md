# Jpa标签
```
<Jpa:repositories base-package="com.fcy.JpaDemo.Dao"
                      entity-manager-factory-ref="entityManagerFactory"
                      transaction-manager-ref="transactionManager"/>
```
配置了 <jpa:repositories> 后，Spring 初始化容器时将会扫描 base-package 指定的包目录及其子目录，
为继承 Repository 或其子接口的接口创建代理对象，并将代理对象注册为 Spring Bean，
业务层便可以通过 Spring 自动封装的特性来直接使用该对象

# 继承Repository接口

```
public interface UserInterface extends Repository<User,Integer> {
    @Query(nativeQuery=true,value="select * from User a order by convert(username using gbk) desc")
    List<User> getAllUser();
}
```
该接口可以不被Repository注解

# 查看一下Spring为这个接口生成的代理对象

```
    public static void main(String[] args) {
        ApplicationContext context = new ClassPathXmlApplicationContext("JpaDemo/application-context.xml");
        int beanDefinitionCount = context.getBeanDefinitionCount();
        String[] beanDefinitionNames = context.getBeanDefinitionNames();
        for (int i=0;i<beanDefinitionCount;i++){
            Object bean = context.getBean(beanDefinitionNames[i]);
            System.out.println(bean.getClass().getName());
            if (bean.getClass().getName().equals("com.fcy.JpaDemo.Dao.Impl.UserDaoImpl")){
                UserDaoImpl impl= (UserDaoImpl) bean;
                System.out.println("------------------------");
                System.out.println("继承Repository接口的接口的代理对象:"+impl.userinterface.getClass().getName());
                System.out.println("---------------实现的接口--------------");
                for (Class<?> anInterface : impl.userinterface.getClass().getInterfaces()) {
                    System.out.println(anInterface.getName());
                }
                System.out.println("-----------------父类------------------");
                System.out.println(impl.userinterface.getClass().getSuperclass().getName());
                System.out.println("------------------------");
            }
        }

    }
```

# 输出结果

com.sun.proxy.$Proxy24这种格式的
```
com.alibaba.druid.pool.DruidDataSource
org.springframework.data.jpa.repository.config.JpaRepositoryConfigExtension
org.springframework.data.repository.core.support.RepositoryInterfaceAwareBeanPostProcessor
org.springframework.data.jpa.repository.support.EntityManagerBeanDefinitionRegistrarPostProcessor
org.springframework.data.jpa.mapping.JpaMetamodelMappingContext
org.springframework.orm.jpa.support.PersistenceAnnotationBeanPostProcessor
org.springframework.data.jpa.repository.support.DefaultJpaContext
com.sun.proxy.$Proxy24
com.sun.proxy.$Proxy25
com.fcy.JpaDemo.Dao.Impl.UserDaoImpl
------------------------
继承Repository接口的接口的代理对象:com.sun.proxy.$Proxy24
---------------实现的接口--------------
com.fcy.JpaDemo.Dao.UserInterface
org.springframework.data.repository.Repository
org.springframework.aop.SpringProxy
org.springframework.aop.framework.Advised
-----------------父类------------------
java.lang.reflect.Proxy
------------------------
com.fcy.JpaDemo.Service.UserService$$EnhancerBySpringCGLIB$$76bd8383
org.springframework.context.annotation.ConfigurationClassPostProcessor
org.springframework.beans.factory.annotation.AutowiredAnnotationBeanPostProcessor
org.springframework.beans.factory.annotation.RequiredAnnotationBeanPostProcessor
org.springframework.context.annotation.CommonAnnotationBeanPostProcessor
com.fcy.JpaDemo.core.SystemPropertyPlaceholderConfigurer
org.hibernate.ejb.HibernatePersistence
com.sun.proxy.$Proxy16
org.springframework.orm.jpa.JpaTransactionManager
org.springframework.transaction.interceptor.TransactionInterceptor
org.springframework.aop.aspectj.autoproxy.AspectJAwareAdvisorAutoProxyCreator
org.springframework.aop.aspectj.AspectJExpressionPointcut
org.springframework.aop.support.DefaultBeanFactoryPointcutAdvisor
com.fcy.JpaDemo.Aop.TestAop
org.springframework.aop.aspectj.AspectJExpressionPointcut
org.springframework.aop.aspectj.AspectJPointcutAdvisor
org.springframework.aop.aspectj.AspectJPointcutAdvisor
org.springframework.aop.aspectj.AspectJPointcutAdvisor
org.springframework.aop.aspectj.AspectJPointcutAdvisor
org.springframework.aop.aspectj.AspectJPointcutAdvisor
org.springframework.context.annotation.ConfigurationClassPostProcessor$ImportAwareBeanPostProcessor
org.springframework.context.annotation.ConfigurationClassPostProcessor$EnhancedConfigurationBeanPostProcessor
com.sun.proxy.$Proxy19

Process finished with exit code 0


Process finished with exit code 0
```