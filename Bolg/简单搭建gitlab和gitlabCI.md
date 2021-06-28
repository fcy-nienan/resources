# 安装docker

```
sudo yum install docker-ce docker-ce-cli containerd.io
sudo systemctl start docker
```



# 搭建gitlab

```
docker pull gitlab/gitlab-ce


docker run --detach \
  --hostname 192.168.204.130 \
  --publish 443:443 --publish 80:80 --publish 8222:22 \
  --name gitlab \
  --restart always \
  --volume /workspace/gitlab/config:/etc/gitlab \
  --volume /workspace/gitlab/logs:/var/log/gitlab \
  --volume /workspace/gitlab/data:/var/opt/gitlab \
  --privileged=true \
  gitlab/gitlab-ce:latest

```

# 搭建gitlab-runner

```
docker pull gitlab/gitlab-runner

docker run -d --name gitlab-runner --restart always \
  -v /data/gitlab-runner/config:/etc/gitlab-runner \
  -v /var/run/docker.sock:/var/run/docker.sock \
  -v /workspace/docker/railsDemo:/workspace/docker/railsDemo \
  gitlab/gitlab-runner:latest
```



# 配置

```
  
  注册runner
  
    docker exec gitlab-runner gitlab-runner register -n \
       --url http://192.168.204.130/ \
       --registration-token MsAAHiGM1xU2sF8qPBEq \
       --tag-list build,deploy \
       --executor docker \
       --docker-image docker \
       --docker-volumes /root/.m2:/root/.m2 \
       --docker-volumes /root/.npm:/root/.npm \
       --docker-volumes /var/run/docker.sock:/var/run/docker.sock \
       --description "runInDk"
       

项目根目录新建.gitlab-ci.yml文件

```

