本来是打算看一下ThreadLocal的内存泄露问题的,然后写下了如下的代码
```
public class DemoWeakReferenceMemoryLeak {
    private static ThreadLocal<data> local=new ThreadLocal<>();
    public static void main(String args[]) throws Exception {
        Semaphore semaphore=new Semaphore(1);
        ThreadPoolExecutor executor=new ThreadPoolExecutor(30,40,0, TimeUnit.SECONDS,new ArrayBlockingQueue(10));
        for (int i=0;i<2;i++) {
            executor.submit(() -> {
                System.out.println("start");
                local.set(new data());
                System.out.println("middle");
               
                try {
                    semaphore.acquire(1);
                    Thread.sleep(3000);
                    System.out.println("finished!");
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }finally {
                    semaphore.release(1);
                }
            });
        }
        executor.shutdown();
    }
    static class data{
        private byte[] bytes=new byte[1024*1024*1024*3];
    }
}
```
死活是不会输出middle和finished
怀疑是线程池将异常吞了,然后发现线程池的runWorker方法中是捕获并抛出了异常的
```
                try {
                    beforeExecute(wt, task);
                    Throwable thrown = null;
                    try {
                        task.run();
                    } catch (RuntimeException x) {
                        thrown = x; throw x;
                    } catch (Error x) {
                        thrown = x; throw x;
                    } catch (Throwable x) {
                        thrown = x; throw new Error(x);
                    } finally {
                        afterExecute(task, thrown);
                    }
                } finally {
                    task = null;
                    w.completedTasks++;
                    w.unlock();
                }
```
然后加上了如下代码
```
            System.out.println("start");
            try {
                local.set(new data());
            }catch (Exception e){
                e.printStackTrace();
            }
            System.out.println("middle");
```
最后输出了异常信息
```
java.lang.NegativeArraySizeException
	at Advanced.Reference.DemoWeakReferenceMemoryLeak$data.<init>(DemoWeakReferenceMemoryLeak.java:45)
	at Advanced.Reference.DemoWeakReferenceMemoryLeak$worker.run(DemoWeakReferenceMemoryLeak.java:28)
	at java.util.concurrent.Executors$RunnableAdapter.call(Executors.java:511)
	at java.util.concurrent.FutureTask.run(FutureTask.java:266)
	at java.util.concurrent.ThreadPoolExecutor.runWorker(ThreadPoolExecutor.java:1142)
	at java.util.concurrent.ThreadPoolExecutor$Worker.run(ThreadPoolExecutor.java:617)
	at java.lang.Thread.run(Thread.java:745)
```
终于发现是申请的数组空间太大了,3个G,1024*1024*1024*3,多写了个1024
本来只想申请3M的

之前还怀疑时不时内部类的问题,后来写了个静态内部内和外部类都不会抛出异常,所以思考
方向错了

异常是向上抛出的,但是线程的run方法是被JVM调用的,这个不抛出异常,所以需要我们
手动在run方法中捕获异常

看线程池源码发现生成的线程是被AQS park阻塞在addWorker方法中的getTask中
getTask从某个阻塞队列取任务来执行,阻塞队列一般都用了AQS的一些工具类来控制
同步操作


程序运行了一段然后后面的没运行,直接最简单的代码也没输出,说明执行路径
发生了变化,使得执行路径发生变化的可能有
+ 自己break去了某个地方
+ 线程抛出了异常去了catch的地方

内存泄漏?
每个线程一个ThreadLocalMap,存储数据的是个Entry数组
Entry中有两个成员变量,key和value,value就是我们需要存储的数据
key是一个被WeakReference包裹的ThreadLocal变量
+ 下面的代码出现的异常是所有线程的start都输出了,middle只有四个线程输出了,finished只有四个输出了,
然后就一直卡着,运行时配置的虚拟机参数时-Xmx600m -Xms100m
通过jstat命令查看各个区域内存分配情况
 S0C    S1C    S0U    S1U      EC       EU        OC         OU       MC     MU    CCSC   CCSU   YGC     YGCT    FGC    FGCT     GCT   
1024.0 1024.0  0.0    0.0   102912.0 102716.0  409600.0   309063.6  9984.0 9350.3 1280.0 1075.7    181    1.447  178     2.896    4.343
频繁的YoungGC和Full GC但是内存还是一直保持原样
好奇为啥不抛出OOM而是一直卡着?
```
public class DemoWeakReferenceMemoryLeak {
    public static void main(String args[]) throws Exception {
        ThreadPoolExecutor executor=new ThreadPoolExecutor(30,40,0, TimeUnit.SECONDS,new ArrayBlockingQueue(10));
        for (int i=0;i<12;i++) {
            executor.submit(()->{
                ThreadLocal<data> local=new ThreadLocal<>();
                System.out.println("start");
                try {
                    local.set(new data());
                    local=null;
                    System.gc();
                }catch (Exception e){
                    e.printStackTrace();
                }
                System.out.println("middle");
                try {
                    Thread.sleep(13000);
                } catch (Exception e) {
                    e.printStackTrace();
                }
                System.out.println("finished");
            });
        }
    }
    static class data{
        private byte[] bytes=new byte[1024*1024*100];
    }
}
```