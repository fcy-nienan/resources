# p6spy
    劫持相关框架的sql,然后自己处理
# aop的execution表达式
    拦截的是方法,所以我们需要用正则表达式来表达一个或者多个方法
    
    execution(* com.sample.service.impl..*.*(..))
    返回值任意类型
    com.sample.service.impl  ..表示当前包和子包   *表示任意类
    .* 代表任意方法
    (..)代表任意参数
# web.xml详解
## servlet传参数
    <servlet>
        <servlet-name>controlServlet</servlet-name>
        <servlet-class>com.jenkov.butterfly.ControlServlet</servlet-class>
        
            <init-param>
            <param-name>myParam</param-name>
            <param-value>paramValue</param-value>
            </init-param>
    </servlet>
    
    public class SimpleServlet extends GenericServlet {
    
      protected String myParam = null;
    
      public void init(ServletConfig servletConfig) throws ServletException{
        this.myParam = servletConfig.getInitParameter("myParam");
      }
    
      public void service(ServletRequest request, ServletResponse response)
            throws ServletException, IOException {
    
        response.getWriter().write("<html><body>myParam = " +
                this.myParam + "</body></html>");
      }
    }
# load-on-startup
    <servlet>
        <servlet-name>controlServlet</servlet-name>
        <servlet-class>com.jenkov.webui.ControlServlet</servlet-class>
        <init-param><param-name>container.script.static</param-name>
                    <param-value>/WEB-INF/container.script</param-value>
        </init-param>
        <load-on-startup>1</load-on-startup>
    </servlet>
    
    The number inside the <load-on-startup>1</load-on-startup> element 
    tells the servlet container in what sequence the servlets should be loaded. 
    The lower numbers are loaded first. If the value is negative, or unspecified, 
    the servlet container can load the servlet at any time
# context-param
    <context-param>
        <param-name>myParam</param-name>
        <param-value>the value</param-value>
    </context-param>
    
    Here is how you access the parameter from inside an HttpServlet subclass:
    String myContextParam =
            request.getSession()
                   .getServletContext()
                   .getInitParameter("myParam");
# 在web.xml配置spring
    <!-- Spring配置文件开始  -->
    <context-param>
        <param-name>contextConfigLocation</param-name>
        <param-value>
            classpath:spring-config.xml
        </param-value>
    </context-param>
    <listener>
        <listener-class>org.springframework.web.context.ContextLoaderListener</listener-class>
    </listener>
    <!-- Spring配置文件结束 -->
# HandlerInterceptor 
    拦截器的三个方法  
    preHandler
    postHandler
    afterCompletion 
    
    单个拦截器的执行流程
    request
    preHandler
    Controller执行返回ModalAndView
    postHandler
    根据ModalAndView渲染试图
    afterCompletion   
    
    多个拦截器执行流程
    preHandler1
    preHandler2
    preHandler3
    postHandler3
    postHandler2
    postHandler1
    afterCompletion3 
    afterCompletion2
    afterCompletion1 
# 拦截器和过滤器
    filterPre-->servlet.service-->dispatcher-->preHandler-->Controller-->postHandler-->afterCompletion-->afterFilter
# 事务传播
    PROPAGATION_REQUIRED	如果当前没有事务，就新建一个事务，如果已经存在一个事务中，加入到这个事务中。这是最常见的选择。
    PROPAGATION_SUPPORTS	支持当前事务，如果当前没有事务，就以非事务方式执行。
    PROPAGATION_MANDATORY	使用当前的事务，如果当前没有事务，就抛出异常。
    PROPAGATION_REQUIRES_NEW	新建事务，如果当前存在事务，把当前事务挂起。
    PROPAGATION_NOT_SUPPORTED	以非事务方式执行操作，如果当前存在事务，就把当前事务挂起。
    PROPAGATION_NEVER	以非事务方式执行，如果当前存在事务，则抛出异常。
    PROPAGATION_NESTED	如果当前存在事务，则在嵌套事务内执行。如果当前没有事务，则执行与PROPAGATION_REQUIRED类似的操作。
    