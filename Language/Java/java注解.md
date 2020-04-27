SOURCE. 注解保留在源代码中，但是编译的时候会被编译器所丢弃。比如@Override, @SuppressWarnings
CLASS. 这是默认的policy。注解会被保留在class文件中，但是在运行时期间就不会识别这个注解。
RUNTIME. 注解会被保留在class文件中，同时运行时期间也会被识别。所以可以使用反射机制获取注解信息。比如@Deprecated