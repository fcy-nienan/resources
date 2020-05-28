```
FileOutputStream fileOutputStream=new FileOutputStream(file);
DataOutputStream outputStream=new DataOutputStream(fileOutputStream);
outputStream.write(48);
outputStream.writeChar(',');
```
写入的内容实际是二进制的值

写入48   用记事本查看就是1

写入0    用记事本查看就是nul