# 相关收集算法
## 通过GCRoot寻找存活的对象
+ 标记清除  先标记存活的对象,然后再清理其他内存区域,容易造成内存碎片
+ 复制算法  内存区域分为两份,将存活的对象移动到右侧,清理左侧,逻辑上左右侧身份互换,然後清理因为分成了两份可用内存大大减少
+ 标记整理  先标记存活对象,然后将存活对象移动到低地址的空间,内存空间不浪费,并且不产生内存碎片,但是效率相对来说要低,因为他不仅需要标记还需要移动对象
+ 标记整理算法和复制算法的疑惑?
    + 我的理解是通过GCRoot找到存活对象然后直接移动到低地址的一端,然后再清除其他内存区域
    + 复制算法和标记整理算法堆不需要扫描全堆
    + 标记整理算法需要标记吗?直接GCROOT扫描到直接移动,是这样吗?
    + 既然这样那为什么标记整理算法会比复制算法慢呢?
- 复制算法的缺点:如果内存对象存活率非常低那么移动对象非常耗时,所以常用于内存对象存活率不高的场景下
- 标记整理算法的缺点:效率相对复制算法来说更低
#相关垃圾收集器
![](../resources/photo/gc-collector.gif)
* Serial收集器
    * 串行收集,进行收集时会造成STW,采用标记整理算法
    ![](../resources/photo/serial.gif)
* ParNew收集器
    * Serial收集器的多线程版本
* ParallelScavenge收集器
    * Serial收集器的多线程版本,和ParNew不同的是该收集器能和CMS一起使用
* Parallel Old收集器
    * 老年代的并行多线程串行收集器
* SerialOld收集器,老年代的串行单线程收集器
* CMS收集器
# 直接可选的垃圾收集器方案
**通过以上垃圾收集器常用的不同的排列组合**
* -XX:+UseSerialGC
相当于”Serial” + “SerialOld”
* -XX:+UseParallelGC
相当于” Parallel Scavenge” + “SerialOld”
* -XX:+UseParallelOldGC
相当于” Parallel Scavenge” + “ParallelOld”，都是多线程并行处理；
* -XX:+UseConcMarkSweepGC,相当于"ParNew" + "CMS" + "Serial Old"

