# p6spy
    劫持相关框架的sql,然后自己处理
# aop的execution表达式
    拦截的是方法,所以我们需要用正则表达式来表达一个或者多个方法
    
    execution(* com.sample.service.impl..*.*(..))
    返回值任意类型
    com.sample.service.impl  ..表示当前包和子包   *表示任意类
    .* 代表任意方法
    (..)代表任意参数
# maven
    通过profiles属性定义不同环境下的属性
    通过resources标签定义哪些目录哪些文件会被打包