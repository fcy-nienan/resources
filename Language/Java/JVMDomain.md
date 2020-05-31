javac将java代码翻译成虚拟机能识别得字节码
字节码运行有两种形式
    编译和解释
    编译是在运行前将该字节码翻译成与平台相关的机器码
    解释是在运行中每次要运行一条字节码得时候将其翻译成与平台相关得机器码

编译和解释共存
	最开始通过解释执行,当某个方法执行次数过多或者某个循环体执行次数过多的时候
	将其编译成本地机器码并缓存起来,下次执行的时候就可以直接机器码运行了
JIT属于动态编译器的一种
>JIT并不是JVM的必须部分，JVM规范并没有规定JIT必须存在，更没有限定和指导JIT。但是，JIT性能的好坏、代码优化程度的高低却是衡量一款JVM是否优秀的最关键指标之一，也是虚拟机中最核心且最能体现虚拟机技术水平的部分。

# 什么是热点代码
多次执行的方法
多次执行的循环体

# 如何判定热点代码
## 采样    周期性的检测各个方法的栈顶,发现某个方法经常出现在栈顶就认为是热点代码.简单粗暴,但是不精确
## 计数器  某个方法的调用次数超过阈值就认为是热点代码

# 栈上替换
但是如果方法里有一个很长的循环或者是一个永远都不会退出并提供了所有逻辑的程序会怎么样呢？这种情况下，JVM 需要编译循环而并不等待方法被调用。所以每执行完一次循环，分支计数器都会自增和自检。如果分支计数器计数超出其自身阈值，那么这个循环（并不是整个方法）将具有被编译资格。

这种编译叫做栈上替换（OSR），因为即使循环被编译了，这也是不够的：JVM 必须有能力当循环正在运行时，开始执行此循环已被编译的版本。换句话说，如果一个循环被栈上替换方式所编译，那么下一次循环迭代则会执行新编译的代码。

阈值参数
-XX:CompileThreshold=Nflag

Dalvik，ART是Android的两种运行环境，也可以叫做Android虚拟机 JIT，AOT是Android虚拟机采用的两种不同的编译策略
jit即时编译技术
    在运行时将字节码翻译成机器码,并将缓存热点代码

三种运行模式
    -mixed mode         混杂模式
    -compile mode       编译模式    启动费时，运行流畅
    -interpreted mode   解释模式    启动快速，运行费时
混杂模式中使用了C1和C2两种即时编译器
    C1使用保守得优化模式
    C2使用激进得优化模式
-client使用C1
-server使用C2

-Xint   解释模式
-Xcomp  编译模式

有两个不同得即时编译器
    -client 和 -server
+:UseCompressedClassPointers
+:UseCompressedObjectOops

jdk8去掉了永久代，变成了元空间
两方面的改变
    1、名称改变了
    2、存储的地方改变了，永久代是在jvm中的内存，而元空间则是使用本地的内存，主要是方法区中的对象回收条件太苛刻,方法去也容易溢出


    如果收集器为ParNew收集器，新生代为ParNew，Parallel New Generation
    如果收集器是Serial收集器，新生代为DefNew，Default New Generation

栈上分配是基于逃逸分析的，为什么这么说呢？没有逃逸的对象会在栈上分配内存，逃逸的对象会在堆中分配内存。
逃逸分析：就是关注对象的作用域，什么情况表示没逃逸呢，就是当前对象的作用域仅在当前方法内有效。


Java对象头
MarkWord+类指针
MarkWork
32位系统   64位系统
4           8
类指针
            32位系统       64位系统
开启压缩指针   不支持             4
不开启        4             8

//  32 bits:
//  --------
//             hash:25 ------------>| age:4    biased_lock:1 lock:2 (normal object)
//             JavaThread*:23 epoch:2 age:4    biased_lock:1 lock:2 (biased object)
//             size:32 ------------------------------------------>| (CMS free block)
//             PromotedObject*:29 ---------->| promo_bits:3 ----->| (CMS promoted object)
//
//  64 bits:
//  --------
//  unused:25 hash:31 -->| unused:1   age:4    biased_lock:1 lock:2 (normal object)
//  JavaThread*:54 epoch:2 unused:1   age:4    biased_lock:1 lock:2 (biased object)
//  PromotedObject*:61 --------------------->| promo_bits:3 ----->| (CMS promoted object)
//  size:64 ----------------------------------------------------->| (CMS free block)
//
//  unused:25 hash:31 -->| cms_free:1 age:4    biased_lock:1 lock:2 (COOPs && normal object)
//  JavaThread*:54 epoch:2 cms_free:1 age:4    biased_lock:1 lock:2 (COOPs && biased object)
//  narrowOop:32 unused:24 cms_free:1 unused:4 promo_bits:3 ----->| (COOPs && CMS promoted object)
//  unused:21 size:35 -->| cms_free:1 unused:7 ------------------>| (COOPs && CMS free block)

APT编译时注解
javaagent原理
javassist运行时修改字节码
javaattach



jvm的相关参数
jinfo中看到的参数时不能更改的file.encoding和sun.jnu.encoding这中可以通过System.getProperty获取的
file.encoding affects the content of file;
sun.jnu.encoding affects the name of file;

# HashMap的三个方法
```
	// Callbacks to allow LinkedHashMap post-actions
    void afterNodeAccess(Node<K,V> p) { }
    void afterNodeInsertion(boolean evict) { }
    void afterNodeRemoval(Node<K,V> p) { }
```
	之前一直以为这三个方法可以被重写，今天突然发现不对，default修饰符,包内访问,子类访问不了，另外注释也写明白了，这是被LinkedHashMap调用的