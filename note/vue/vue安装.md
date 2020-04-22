# 安装nodejs
# 安装cnpm
    显示npm配置  npm config ls
    npm install cnpm -g --registry=https://registry.npm.taobao.org
# 安装vue-cli
    cnpm install --global vue-cli
    
    执行vue -V 显示版本信息查看是否安装成功
    
# 初始化项目
    vue init webpack vueui
    命令执行后会以交互式的命令行提示你配置一下项目信息(和在IDEA中新建vue项目需要填的东西差不多)
    将会在当前目录下生成一个vueui目录
    然后会在vueui目录下生成一系列文件
# 安装依赖
    cnpm install
    会生成一个nodeModules目录,里面是一些js依赖
# 运行项目
    npm run dev
    