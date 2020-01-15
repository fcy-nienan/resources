## 算子
## transform

## shuffle
* map(fun(e))
* filter(fun(e))
* flatMap(fun(e):Array[Int])
    参数是一个返回数组的函数
    flatMap(e=>e.split(" "))
* mapPartitions(fun(Iterator[Int]):Iterator[Int])
    参数是一个函数,该函数接收一个能遍历一个分区数据的迭代器并且返回一个分区
    def function(iter:Iterator[Int]):Iterator[Int]={
    
    }
* mapPartitionsWithIndex(fun(Int,Iterator[Int]):Iterator[Int])
    作用同mapPartitions,不同点在于传入的参数多了一个当前分区索引值
    def function(index:Int,iter:Iterator[Int]):Iterator[Int]={
    
    }
* sample(withReplacement,fraction,seed)
    数据抽样,去除一部分数据
    sample(false,0.5,1)
    withReplacement表示取样是取出来的数据是否放回
* union
    数据不去重(sql中的union是去重的)
    rdd.union(rdd1)
    Return the union of this RDD and another one. Any identical elements will appear multiple
    times (use `.distinct()` to eliminate them).
* intersection
    两个rdd的交集并去重且无序返回
    this.map(v => (v, null)).cogroup(other.map(v => (v, null)))
            .filter { case (_, (leftGroup, rightGroup)) => leftGroup.nonEmpty && rightGroup.nonEmpty }
            .keys
* distinct(numPartitions)
    map(x => (x, null)).reduceByKey((x, y) => x, numPartitions).map(_._1)
    去重
    scala> val rdd=sc.parallelize(1 to 100,5)
    rdd: org.apache.spark.rdd.RDD[Int] = ParallelCollectionRDD[0] at parallelize at <console>:24
    
    scala> rdd.distinct(10).collect
    res0: Array[Int] = Array(100, 80, 30, 50, 40, 90, 70, 20, 60, 10, 41, 61, 81, 21, 71, 11, 51, 1, 91, 31, 52, 82, 22, 32, 92, 62, 42, 72, 12, 2, 13,
     53, 73, 93, 33, 23, 63, 83, 3, 43, 84, 34, 4, 54, 14, 24, 64, 74, 44, 94, 15, 55, 25, 95, 65, 35, 75, 45, 85, 5, 96, 56, 76, 16, 66, 46, 36, 6, 86
    , 26, 47, 77, 97, 27, 57, 37, 17, 67, 7, 87, 28, 48, 98, 8, 18, 38, 58, 88, 78, 68, 19, 39, 29, 79, 59, 89, 69, 9, 49, 99)
    两个stage
    stage0 distinct task 5  这个是读取数据的任务数
    stage1 collect  task 10 这个是distinct后的任务数
    distinct(10),这个10可以认为生成的分区数,将去重后的数据分成了10个分区
    去重前从1-100中
    第一个任务选择被10整除的数据x%10=0
    然后第二个任务选择除以10余1的数据x%10=1
    以此类推
* groupByKey(numPartitions)
   When called on a dataset of (K, V) pairs, returns a dataset of (K, Iterable<V>) pairs
   res4: Array[(Int, Int)] = Array((1,1), (2,1), (3,1), (4,1), (5,1), (6,1), (7,1), (8,1), (92,1), (3,1), (4,1), (5,1), (6,1), (7,1))
   groupByKey(3).collect 
   res7: Array[(Int, Iterable[Int])] = Array((6,CompactBuffer(1, 1)), (3,CompactBuffer(1, 1)), (4,CompactBuffer(1, 1)), (1,CompactBuffer(1)), (7,Compa
   ctBuffer(1, 1)),(92,CompactBuffer(1)), (8,CompactBuffer(1)), (5,CompactBuffer(1, 1)), (2,CompactBuffer(1)))
   将数据分组,numTasks作用同上
* reduceByKey(fun(e1,e2):e3,numPartitions)
   res4: Array[(Int, Int)] = Array((1,1), (2,1), (3,1), (4,1), (5,1), (6,1), (7,1), (8,1), (92,1), (3,1), (4,1), (5,1), (6,1), (7,1))
   reduceByKey((e1,e2)=>e1+e2,3).collect
   res9: Array[(Int, Int)] = Array((6,2), (3,2), (4,2), (1,1), (7,2), (92,1), (8,1), (5,2), (2,1))
   聚合操作
* aggregateByKey

* glom
    将RDD的每一行合并为一个数组
* sortByKey
    new ShuffledRDD[K, V, V](self, part)
    Sort the RDD by key, so that each partition contains a sorted range of the elements. Calling
    `collect` or `save` on the resulting RDD will return or output an ordered list of records
    (in the `save` case, they will be written to multiple `part-X` files in the filesystem, in
    order of the keys).
* filterByRange(lower: K, upper: K): RDD[P]
* join

* keyBy[K](f: T => K): RDD[(K, T)]
    将一个单独的元素变成一个Map,为一个List的所有左边元素加上一个Key
* leftOuterJoin

* rightOuterJoin

* fullOuterJoin

* cogroup
    (1,2)(2,3)(3,4)
    (2,4)(3,6)(4,8)
    (1,((2),())),(2,((3),(4))),(3,((4),(6))),(4,((),(8)))
* cartesian笛卡尔积

* mapWith
* flatMapWith
* foreachWith
* filterWith
* zip
    两个相同元素的RDD组成一个Map,左边的是key,右边的是value
    元素个数必须相同否则报错
* pipe(command: String): RDD[String]
    就像运行一个Runtime.exec一样
    command是一个脚本的路径
    脚本的输入就是调用这个pipe方法的当前RDD
    对于当前RDD的每一个分区调用一次外部程序
    外部程序的标准输出就是该pipe方法的返回值RDD的一个分区
    rdd每个个分区启动一个外部程序,stdin是外部程序的输入,新的RDD的输入是外部程序的输出
    外部程序怎么引用这个数据源呢?
    while read LINE; do
       echo ${LINE}!
    done
* coalesce(numPartitions:Int,shuffle:Boolean)
    重新分区,比如你现在有100个分区，然后指定numPartitions为10那么新生成的分区会有以前10个分区的数据，这个时候并没有
    发生shuffle,
    如果你进行一个剧烈的coalesce,比如numPartitions=1,那么可能算子都会运行在一个节点上
    你也可以指定shuffle=true,这回增加一个shuffle过程
    比如当前分区是100,指定numPartitions是1000,shuffle=true
    当100个分区中有几个分区的数据特别大的时候这非常有用
    指定1000个分区并且发生shuffle,那么会以哈希分区器将数据分布在不同分区中
* repartition
    def repartition(numPartitions: Int)(implicit ord: Ordering[T] = null): RDD[T] = withScope {
        coalesce(numPartitions, shuffle = true)
    }
* repartitionAndSortWithinPartitions
    根据partitioner进行分区并在每个分区中按照key进行排序
* treeReduce
    使用 treeReduce & treeAggregate 替换 reduce & aggregate。
    数据量较大时，reduce & aggregate 一次性聚合，Shuffle 量太大，
    而 treeReduce & treeAggregate 是分批聚合，更为保险
## Action
* reduce(fun(e1,e2):e3)
* collect
    将数据汇集到driver节点上来,结果是一个数组
* collectPartitions
    将数据汇集到driver节点上来,为每一个分区产生一个数组,结果是要给二维数组
* count():Long
* toArray()
    def toArray(): Array[T] = withScope {
        collect()
    }
* countApprox(timeout)
    在一个timeout内尽可能返回值,即使不完成也无所谓
* countByValue
* treeAggregate
* mapValues(f)
    在key-value中的rdd中对每一个pair中的value执行一个map函数,保持分区
* flatMapValues(f)
    对每一个value做一个flat Map函数
* subtractByKey
    根据key减去其他rdd中的元素
* lookup(key)
* combineByKey
* aggregateByKey
* foldByKey
* sampleByKey
* groupByKey
* partitionByKey(partitioner:Partitioner)
    使用自定义的分区器重新分区一下
* countByKey
* countByValueApprox
* join
    def join[W](other: RDD[(K, W)], partitioner: Partitioner): RDD[(K, (V, W))] = self.withScope {
        this.cogroup(other, partitioner).flatMapValues( pair =>
          for (v <- pair._1.iterator; w <- pair._2.iterator) yield (v, w)
        )
    }
* leftOuterJoin
    this.cogroup(other, partitioner).flatMapValues { pair =>
          if (pair._2.isEmpty) {
            pair._1.iterator.map(v => (v, None))
          } else {
            for (v <- pair._1.iterator; w <- pair._2.iterator) yield (v, Some(w))
          }
    }
* rightOuterJoin
    this.cogroup(other, partitioner).flatMapValues { pair =>
          if (pair._1.isEmpty) {
            pair._2.iterator.map(w => (None, w))
          } else {
            for (v <- pair._1.iterator; w <- pair._2.iterator) yield (Some(v), w)
          }
    }
* fullOuterJoin
    this.cogroup(other, partitioner).flatMapValues {
          case (vs, Seq()) => vs.iterator.map(v => (Some(v), None))
          case (Seq(), ws) => ws.iterator.map(w => (None, Some(w)))
          case (vs, ws) => for (v <- vs.iterator; w <- ws.iterator) yield (Some(v), Some(w))
    }
* collectAsMap():Map[K,V]
* top
* max
* min
* collect(fun)
    收集符合函数的结果
* subtract
    rdd1.subtract(rdd)
    rdd1中的元素减去rdd中的元素
* fold
* first()
* taskSample(withReplacement,num,seed)
    该方法需要将所有的数据都拉到driver端
* take(n)
* takeOrdered(n,[ordering])
    返回前几行数据并且排序
* saveAsTextFile(path)
    val rdd=sc.parallelize(1 to 100,5)
    rdd.saveAsTextFile("D:/data/3")
    生成的文件
    2020/01/11  23:13                12 .part-00000.crc
    2020/01/11  23:13                12 .part-00001.crc
    2020/01/11  23:13                12 .part-00002.crc
    2020/01/11  23:13                12 .part-00003.crc
    2020/01/11  23:13                12 .part-00004.crc
    2020/01/11  23:13                 8 ._SUCCESS.crc
    2020/01/11  23:13                51 part-00000
    2020/01/11  23:13                60 part-00001
    2020/01/11  23:13                60 part-00002
    2020/01/11  23:13                60 part-00003
    2020/01/11  23:13                61 part-00004
* saveAsSequenceFile(path)
* saveAsObjectFile(path)
* countByKey()
* foreach(fun(e))
* foreachPartition(fun(e))
    





* reduce归约操作
* reduceByKey对所有相同的key做归约操作
* groupByKey  
    去重的并集
    select * from a union select * from b;
    没去重的并集
    select * from a union all select * from b;
    差集
    select * from a except select * from b;
* distinct	
    去重	(k,v),去重时相同的key不同的value是不同的数据,只有key和value都相同才去掉
    def distinct(numPartitions: Int)(implicit ord: Ordering[T] = null): RDD[T] = withScope {
        map(x => (x, null)).reduceByKey((x, y) => x, numPartitions).map(_._1)
    }
filter		过滤		rdd1.filter(_._2>2)  		rdd.filter(x => x._2==2)
groupBy(Function)
按照给定的函数进行分组
groupBy(_%2)按照模2的值进行分组,所以只有两组,一组的值为0,另一个为1
groupByKey
	for(s:data){
		if(map[s.key]!=null){
			map[s.key]=(map[s.key],s.value)
		}else{
			map[s.key]=(map[s.key])
		}
	}
cogroup		两个数据共同的分组
		先把两个数据集的所有key去重得到不同的值
		在每一个不同的值后面加上帝一个数据集中和他相同的值
		在第二个数据及中加上和他讲通的值
		rdd1(List((tom,1),(jerry,2),(jerry,3),(shuke,4)
		rdd2(List((tom,1),(jerry,4),(kitty,5))
		rdd1.cogroup(rdd2)
		
		tom,jerry,shuke,kitty
		
		tom,(1),(1)
		jerry,(2,3),(4)
		shuke,(4),()
		kitty,(),(5)
mapValues		对value进行map操作不对key操作
reduce		reduce将RDD中元素前两个传给输入函数，产生一个新的return值，新产生的return值与RDD中下一个元素（第三个元素）组成两个元素，再被传给输入函数，直到最后只有一个值为止。
Cartesian笛卡尔积
1、Except返回两个结果集的差（即从左查询中返回右查询没有找到的所有非重复值）。
Returns a new Dataset containing rows in this Dataset but not in another Dataset.
* def textFile(
        path: String,
        minPartitions: Int = defaultMinPartitions): RDD[String] = withScope {
    def defaultMinPartitions: Int = math.min(defaultParallelism, 2)
    没指定的话分区为默认并行度和2的最小值,通常是2
    但第一个参数path也可以用目录,那么如果目录下又多个文件分区数如何算?
    不指定分区参数的情况下
    1. 一个605M两个7M的文件最后有了21个Task
    605/32~=18.9=19
    两个文件各一个Task
    2. 单独两个7M的文件最后有了2个Task
    也就是一个文件只要不达到spark的读取一个分区的最大数据那么就一个分区
    如果达到了就将该文件划分为多个分区
    如果指定了分区数为3
    表现行为暂时未得出规律------源码在computeSize相关方法和HDFS计算splitSize中,InputFormat的getSplits
