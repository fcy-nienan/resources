发送方如果没有把输出流关闭,接收方会一直等待数据到来,所以会阻塞在read方法上  
和读取文件不一样,文件是可以确定是否读到了文件的末尾,而socket是两个主机之间的桥梁,  
一端不关闭另一端是无法知道流中是否还有数据的  
while((size=inputStream.read(bytes))!=-1){  
  
}  
该read方法是一个阻塞方法  
当没有数据时并不会返回-1  
只有当客户端关闭了输出流才会发送一个结束标识符(-1)  
在客户端调用flush方法确实发送数据到了服务器端  
但服务器端读取了也会一直阻塞在read方法中,因为没有读到流的结束标识符  
  
可以在客户端调用socket的shutdownOutput();方法,该方法会发送一个结束标识符  
还可以自定义结束标识符(检查字符串是否是结束标识符)  
或者在开始的几个字节中发送一个长度的数据给服务器端(在tcp上自定义协议)  
或者设置socket读取的超时时间(setSoTimeout)  
  
需要注意的是调用流的close方法会关闭该socket(client.getOutputStream().close())  
  
BufferedReader的readLine方法也类似  
该方法需要接受到一个换行符才会返回,各个操作系统的换行符不同,写入数据的时候可以用writer.newLine()方法  
至于返回null,同样需要接受到结束标识符,结束标识符也是socket关闭或者流关闭(shutdownOutput)才会接收到  