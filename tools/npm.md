```bash
npm config list
```

```bash
npm config ls -l
```

```bash
npm config get prefix
```

```bash
npm config set prefix=$HOME/.node_modules_global
```

```bash
npm install npm@latest -g
```

```bash
npm list --global
```

```bash
npm list -g --depth=0
```

```bash
npm uninstall underscore
```

```bash
npm search mkdir
```

```bash
npm cache clean --force
```

- `npm i <package>`: install local package
- `npm i -g <package>`: install global package
- `npm un <package>`: uninstall local package
- `npm up`: npm update packages
- `npm t`: run tests
- `npm ls`: list installed modules
- `npm ll` or `npm la`: print additional package information while listing modules
  

  + 查看某个包所有版本  npm info packageName         npm view <packageName> versions --json

npm config delete registry

npm config delete disturl

或者 
npm config edit 
找到淘宝那两行,删除


查看npmjs服务器上包的版本信息：

使用npm view jquery versions；这种方式可以查看npm服务器上所有的jquery版本信息；

使用npm view jquery version； 这种方式只能查看jquery的最新的版本是哪一个；

使用npm info jquery ；这种方式和第一种类似，也可以查看jquery所有的版本，但是能查出更多的关于jquery的信息；

查看本地已经安装的包的版本信息：

npm ls jquery 即可（查看某个项目安装的jQuery），命令必须在某个项目下执行

npm ls jquery -g    (查看全局安装的jquery)


‘^16.8.0’ 表示安装16.x.x的最新版本，安装时不改变大版本号。
‘~16.8.0’ 表示安装16.8.x的最新版本，安装时不改变大版本号和次要版本号。
‘16.8.0’ 表示安装指定的版本号，也就是安装16.8.0版本。