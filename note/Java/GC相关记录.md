#相关收集算法
+ 标记清除  先标记,然后再清理
+ 复制算法  内存区域分为两份
+ 标记整理
#相关垃圾收集器
![](../resources/photo/gc-collector.gif)
* Serial收集器
    * 串行收集,进行收集时会造成STW
    ![](../resources/photo/serial.gif)
* ParNew收集器
    * Serial收集器的多线程版本
* ParallelScavenge收集器
    * Serial收集器的多线程版本,和ParNew不同的是该收集器能和CMS一起使用
* Parallel Old收集器
    * 老年代的并行多线程串行收集器
* SerialOld收集器
* CMS收集器
    