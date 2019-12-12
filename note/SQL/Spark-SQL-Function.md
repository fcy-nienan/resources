# operator
+ <=>
+ !=,<>
+ NOT IN()
+ NOT LIKE
+ LIKE
+ COALESCE()
+ INTERVAL
+ IS 
+ IS NOT
+ IS NULL
+ IS NOT NULL
+ ISNULL()
+ ISNOTNULL()
+ NOT BETWEEN...AND...
+ = type is same
+ == 1=='1' is true
# string
+ decode('abc','utf-8')
+ encode('abc','utf-8)
+ ascii
+ size
+ length
+ substring
+ space
+ split
+ locate(select lcoate("abc","12345abc") result:6)
+ translate select translate('AaaaBbbbCccc','abc','123') result: A111B222C333
+ trim
+ upper
+ substring_index('www.fcy8.cn','.',2)=www.fcy8
+ lower
+ instr("12345abc","abc")=6
+ isnull
+ initcap select initcap('sPark sQL') Spark Sql  用空格分割，将第一个字符大写
+ left
+ right
+ repeat
+ reverse
+ replace
+ concat
+ concat_ws(split,ex1,ex2..) concat_ws(',','nie','nan') nie,nan
+ strcmp
+ bin
+ big_length
+ char(expr) char(65) 'A'
+ chr(expr) chr(65) 'A'
+ coalesce(expr) coalesce(null,'',1,null,2) ''  返回第一个非null值
+ conv  conv('100',2,10); 将'100'从2进制转为10进制   4
+ format_string
+ hex()
+ format_number('123456.1223',4)=123,456.1223
# function
+ uuid
+ md5
+ sha1
+ sha2
+ reflect('java.util.UUID','randomUUID')
+ java_method
+ base64
+ crc32
+ hash
# type
+ int
+ cast('' as int)
# math
+ abs
+ factorial(5)=120斐波那契数
+ pmod
+ mod
+ pow
+ rand()
+ shiftleft
+ shiftright
+ sqrt
+ max
+ min
+ ln
+ least
+ greatest
+ sign(return -1,0 or 1 as expr is negative ,0 or positive)
+ sin
+ log
+ log10
+ log1p
+ log2
+ negative
+ pi
+ ceil(expr) 返回不小于expr的最小整数
# date
+ current_date()
+ current_timestamp()
+ dayofmonth()
+ from_unixstamp()
+ dayofweek()
+ dayofyear()
+ weekofyear()
+ year
+ month
+ day
+ hour
+ minute
+ second
+ next_day
+ now
+ last_day
+ unix_timestamp
+ to_date
+ to_unix_timestamp('2019-12-12','yyyy-MM-dd')=1583947394
+ date_add
+ date_sub
+ datediff
+ add_months
+ month_between
# struct
+ array
+ sort_array
+ array_contains(array(1,2,3,4,5),6) false
+ struct
+ collect_list(column)返回一个List
+ collect_set(column)返回一个Set
+ if select if(1=1,'a','b') 'a'
+ ifnull select ifnull(null,array('2'))  ["2"]
+ inline select inline(array(struct(1,'a'),struct(2,'b')))
```
1 a
2 b
```



# 聚合函数
+ array_contains(column: Column, value: Any)	Check if a value presents in an array column. Return below values.
+ true - Returns if value presents in an array.
+ false - When valu eno presents.
+ null - when array is null.
+ array_distinct(e: Column)	Return distinct values from the array after removing duplicates.
+ array_except(col1: Column, col2: Column)	Returns all elements from col1 array but not in col2 array.
+ array_intersect(col1: Column, col2: Column)	Returns all elements that are present in col1 and col2 arrays.
+ array_join(column: Column, delimiter: String, nullReplacement: String)
+ array_join(column: Column, delimiter: String)	Concatenates all elments of array column with using provided delimeter. When Null valeus are present, they replaced with 'nullReplacement' string
+ array_max(e: Column)	Return maximum values in an array
+ array_min(e: Column)	Return minimum values in an array
+ array_position(column: Column, value: Any)	Returns a position/index of first occurrence of the 'value' in the given array. Returns position as long type and the position is not zero based instead starts with 1.
+ Returns zero when value is not found.
+ Returns null when any of the arguments are null.
+ array_remove(column: Column, element: Any)	Returns an array after removing all provided 'value' from the given array.
+ array_repeat(e: Column, count: Int)	Creates an array containing the first argument repeated the number of times given by the second argument.
+ array_repeat(left: Column, right: Column)	Creates an array containing the first argument repeated the number of times given by the second argument.
+ array_sort(e: Column)	Returns the sorted array of the given input array. All null values are placed at the end of the array.
+ array_union(col1: Column, col2: Column)	Returns an array of elements that are present in both arrays (all elements from both arrays) with out duplicates.
+ arrays_overlap(a1: Column, a2: Column)	true - if `a1` and `a2` have at least one non-null element in common
+ false - if `a1` and `a2` have completely different elements.
+ null - if both the arrays are non-empty and any of them contains a `null`
+ arrays_zip(e: Column*)	Returns a merged array of structs in which the N-th struct contains all N-th values of input
+ concat(exprs: Column*)	Concatenates all elements from a given columns
+ element_at(column: Column, value: Any)	Returns an element of an array located at the 'value' input position.
+ exists(column: Column, f: Column => Column)	Checks if the column presents in an array column.
+ explode(e: Column)	Create a row for each element in the array column
+ explode_outer ( e : Column )	Create a row for each element in the array column. Unlike explode, if the array is null or empty, it returns null.
+ filter(column: Column, f: Column => Column)
+ filter(column: Column, f: (Column, Column) => Column)	Returns an array of elements for which a predicate holds in a given array
+ flatten(e: Column)	Creates a single array from an array of arrays column.
+ forall(column: Column, f: Column => Column)	Returns whether a predicate holds for every element in the array.
+ posexplode(e: Column)	Creates a row for each element in the array and creaes a two columns "pos' to hold the position of the array element and the 'col' to hold the actual array value.
+ posexplode_outer(e: Column)	Creates a row for each element in the array and creaes a two columns "pos' to hold the position of the array element and the 'col' to hold the actual array value. Unlike posexplode, if the array is null or empty, it returns null,null for pos and col columns.
+ reverse(e: Column)	Returns the array of elements in a reverse order.
+ sequence(start: Column, stop: Column)	Generate the sequence of numbers from start to stop number.
+ sequence ( start : Column , stop : Column , step : Column )	Generate the sequence of numbers from start to stop number by incrementing with given step value.
+ shuffle(e: Column)	Shuffle the given array
+ size(e: Column)	Return the length of an array.
+ slice(x: Column, start: Int, length: Int)	Returns an array of elements from position 'start' and the given length.
+ sort_array(e: Column)	Sorts the array in an ascending order. Null values are placed at the beginning.
+ sort_array(e: Column, asc: Boolean)	Sorts the array in an ascending or descending order based of the boolean parameter. For assending, Null values are placed at the beginning. And for desending they are places at the end.
+ transform(column: Column, f: Column => Column)
+ transform(column: Column, f: (Column, Column) => Column)	Returns an array of elments after applying transformation.
+ zip_with(left: Column, right: Column, f: (Column, Column) => Column)	Merges two input arrays.
+ aggregate(
expr: Column,
zero: Column,
merge: (Column, Column) => Column,
finish: Column => Column)