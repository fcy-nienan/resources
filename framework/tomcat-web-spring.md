# 九大对象

	request	       HttpServletRequest
	response       HttpServletResponse
	config         ServletConfig
	application    ServletContext
	session        HttpSession
	exception      Throwable
	page           Object(this)
	out            JspWriter
	pageContext    PageContext 
# 四个作用域
	page域:    只能在当前jsp页面使用                
	request域: 只能在同一个请求中使用               
	session域: 只能在同一个会话(session对象)中使用  
	context域: 只能在同一个web应用中使用            
# ContextLoaderListener
	实现ServletContextListener接口
```
	@Override
	public void contextInitialized(ServletContextEvent event) {
		initWebApplicationContext(event.getServletContext());
	}
```
initWebApplicationContext中有如下代码
```
	//将WebApplicationContext设置为servletContext的属性        servletContext.setAttribute(WebApplicationContext.ROOT_WEB_APPLICATION_CONTEXT_ATTRIBUTE, this.context);

```
# DispatchServlet的WebApplicationContext
得到rootContext(也就是上面Listener注册的)
```
WebApplicationContext rootContext =WebApplicationContextUtils.getWebApplicationContext(getServletContext());
```
设置父子关系
```
wac.setEnvironment(getEnvironment());
wac.setParent(parent);
wac.setConfigLocation(getContextConfigLocation());
```
同时将该webcontext也保存到servletContext中
```
// Publish the context as a servlet context attribute.
String attrName = getServletContextAttributeName();
getServletContext().setAttribute(attrName, wac);
```

webcontext之间有父子关系
但上面两个webcontext都保存在servletContext中
同时和servletContext相互引用


