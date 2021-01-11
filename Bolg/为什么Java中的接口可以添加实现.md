> https://levelup.gitconnected.com/java-good-reasons-to-add-method-implementation-to-interface-744eb4717d7



> Typically, as a service provider, when you provide interface that needs to be conformed to in order to access some specific services, you also need to provide some methods to provide some utility functions related to the service you provide

一般而言，作为一个服务提供者，当你提供访问某些特定服务需要遵循的接口时

你也需要提供一些与这个服务与之关联的实用方法



以前是把这些方法分离开了，提供一个接口，同时提供与之关联的工具类

比如Path和Paths,现在可以直接在这里面写相应的static方法，不用再创建多余的对象了



还有一种好处是如果你要在这个接口中添加一些新的行为，那么所有实现了这些接口的类都将会因为找不到某个方法的实现而编译报错，但是如果有了默认行为的话，那么将能正常编译



那缺点呢：

类和接口的界限开始变得有点模糊了

