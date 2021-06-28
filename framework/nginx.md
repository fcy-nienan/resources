# rtmp服务器配置

## 下载nginx

```bash
wget http://nginx.org/download/nginx-1.8.1.tar.gz
```

## 下载nginx-rtmp-module

```php
git clone https://github.com/arut/nginx-rtmp-module.git
```

## 解压并编译安装
```
tar -zxvf nginx-1.8.1.tar.gz
./configure --add-module=../nginx-rtmp-module
make 
make install
```
## 运行
nginx 

## 配置rtmp服务器
```
user  root; # worker进程用户身份,和权限有关
worker_processes  1;

#error_log  logs/error.log;
#error_log  logs/error.log  notice;
#error_log  logs/error.log  info;

#pid        logs/nginx.pid;


events {
    worker_connections  1024;
}

rtmp {
    server {
        listen 1935;# 端口
        chunk_size 496;

        application vod { # vod应用名 rtmp路径里面有这个
            play /root/videos;
        }
    }
}

http {
    include       mime.types;
    default_type  application/octet-stream;

    #log_format  main  '$remote_addr - $remote_user [$time_local] "$request" '
    #                  '$status $body_bytes_sent "$http_referer" '
    #                  '"$http_user_agent" "$http_x_forwarded_for"';

    #access_log  logs/access.log  main;

    sendfile        on;
    #tcp_nopush     on;

    #keepalive_timeout  0;
    keepalive_timeout  65;

    #gzip  on;

    server {
        listen       81;
        server_name  localhost;

        #charset koi8-r;

        #access_log  logs/host.access.log  main;

        location / {
            root   html;
            index  index.html index.htm;
        }

        #error_page  404              /404.html;

        # redirect server error pages to the static page /50x.html
        #
        error_page   500 502 503 504  /50x.html;
        location = /50x.html {
            root   html;
        }
    }
}


```
# 配置好后通过vlc访问rtmp://host/vod/xxx.mp4就可以播放视频了







# 配置直播

```
user root;
worker_processes  1;

events {
    worker_connections  1024;
}

rtmp {                #RTMP service
    server {
        listen 1935;  #port
        chunk_size 4096;   #data size

        application vod {
            play /root/videos; #video path
        }

        application live{ #first live field
            live on;
        }
    }
}

http {
    include       mime.types;
    default_type  application/octet-stream;

    sendfile        on;
    keepalive_timeout  65;

    server {
        listen       80;
        server_name  localhost;

        location /stat {     #first location field
            rtmp_stat all;
            rtmp_stat_stylesheet stat.xsl;
        }

        location /stat.xsl { #second location field
            root /root/nginx-rtmp-module-master/;
        }

        location / {
            root   html;
            index  index.html index.htm;
        }
        
        error_page   500 502 503 504  /50x.html;
        location = /50x.html {
            root   html;
        }
        
    }

}
```

主播端推流到   rtmp://120.79.158.25/live    串流密钥(obs里面的)填test

观众拉流   rtmp://120.79.158.25/live/test