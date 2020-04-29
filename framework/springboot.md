# springboot相关文档
+ https://docs.spring.io/spring-boot/docs/current/reference/html/appendix-application-properties.html  
+ https://docs.spring.io/spring-boot/docs/current/reference/html/spring-boot-features.html#boot-features-developing-web-applications  
# spring security
# 参考文档
+ https://docs.spring.io/spring-security/site/docs/5.2.2.RELEASE/reference/htmlsingle/
SecurityContextHolder  存储当前认证通过的主体信息
    存储策略有三种
        全局
        父子线程
        线程本地
        (从线程角度看待,所有线程公用,仅仅当前线程使用,父子线程共用)
SecurityContextHolder, to provide access to the SecurityContext.
SecurityContext, to hold the Authentication and possibly request-specific security information.
Authentication, to represent the principal in a Spring Security-specific manner.
GrantedAuthority, to reflect the application-wide permissions granted to a principal.
UserDetails, to provide the necessary information to build an Authentication object from your application’s DAOs or other source of security data.
UserDetailsService, to create a UserDetails when passed in a String-based username (or certificate ID or the like).

# 基本认证流程

1. 用户提供用户名和密码
2. 系统成功验证用户名和密码
3. 加载该用户的上下文信息(角色权限等)
4. 为该用户建立一个安全上下文
5. 用户操作其他页面

在spring-security中对于的概念
1. 通过用户名和密码实例化一个UsernamePasswordAuthenticationToken
2. 传递一个token给AuthenticationManager去验证
3. 返回一个填充好的Authentication实例
4. 通过调用SecurityContextHolder.getContext().setAuthentication(…)建立安全上下文

# web认证流程
1. 你访问一个页面或者点击一个链接
2. 发送一个请求给服务器,服务器判断出你正在访问受保护的资源
3. 此时你还没有认证,服务器的响应暗示你必须认证,响应可以是一个页面或者一个code值
4. 由于认证机制,你的浏览器会被重定向到一个认证页面,此时你可以在表单中输入你的认证信息
5. 浏览器返回响应给服务器,响应内容可能是包含在HTTP请求中的form表单数据或者HTTP头部数据
6. 然后服务器判断凭证是否有效,如果有效就下一步,如果无效进行第二步和第三步
7. 导致你认证的原始请求将会被处理,如果你有足够的权限访问这个受保护的资源那么请求成功,否则HTTP403,禁止访问
# ExceptionTranslationFilter
负责处理spring-security抛出的各种认证异常
# AuthenticationEntryPoint
认证进入点,每个系统都有自己的认证策略,这个代表上面的第三步
# 认证机制
通过用户提供的认证信息构造一个 "Authentication" 请求传递给 AuthenticationManager
认证管理器认证通过后将改用户的认证信息 Authentication 存储在SecurityContextHolder
# 在两次请求间存储安全上下文
在两次请求之间都要认证

