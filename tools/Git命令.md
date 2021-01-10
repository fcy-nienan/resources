# 远程仓库

     git中的origin的意思      远程仓库在本地的别名  
     git remote				查看当前远程仓库  
     git remote add test git://github.com/wingrai/test.git	添加远程仓库 
     git remote rm label     删除远程仓库  
     git remote show label  显示远程仓库信息
        * remote remoteName  
          Fetch URL: https://github.com/windrai/pratice.git  
          Push  URL: https://github.com/windrai/pratice.git  
          HEAD branch: master  
          Remote branch:  
            master tracked  
          Local branch configured for 'git pull':使用git pull 缺省pull  
            fcy merges with remote master  
          Local ref configured for 'git push':使用git push 缺省提交  
            master pushes to master (fast-forwardable)  
# 刚下载时需要配置这些user.name和user.email  
    git config --list查看配置信息  
    git config --global user.name "name"配置用户名  
    git config --global user.email 807715333@qq.com配置邮箱  
    git config --global -l                  显示全局配置信息  
    git config --system -l                  显示系统配置信息  
    git config --local -l                   显示本地配置信息  
# 克隆指定分支
    git clone -b name url       
# 分支操作            
    git add .                               将本地所有代码加入到暂存区  
    git checkout .                          取消所有本地变更  
    git commit -m 'msg'                     提交到本地  
    git push origin localName:remoteName	提交本地分支到原创分支  
    git fetch origin master:br3				将远程的master分支拉下来并在本地创建br3分支  
## 分支比较
    git diff br3    						查看当前分支与br3分支有何不同  
    git diff branchName branchName            比较两个分支有何不同  
    git diff branchName branchName filePath   比较两个分支某一具体文件差异
## 分支CRUD
	git checkout branchName                 切换分支  
	git add remote label address            添加远程仓库路径并命名为label  
	git push origin --delete branchName     删除远程分支  
	git push origin localName:newName       创建远程分支  
	git branch -m old new                   本地分支重命名  
	git branch branchName                   创建本地分支  
	git branch -a                           列出所有分支  
	git branch -d br3						删除本地br3分支  
	git branch -D br3                       强制删除b 
	git remote rename oldName newName       远程仓库重命名 
# git合并
	git merge tmp -s resolve				合并tmp分支并指定合并策略位resolve
	合并策略  resolve,recursive,octopus,ours,subtree
	git merge br3							将br3分支与本地分支合并(最新的是br3分支)  
	git merge br3 -s theirs 
	git reset --hard						git放弃merge 
# upstream

        git remote show fcy  
        cat .git/config  
    例如要把push和pull的默认分支设置为dev，那么：git branch --set-upstream-to=origin/dev dev  
    git config --global push.default "current"   还可以设置为upstream  
    git branch -vv                            查看当前分支的upstream  
    git branch -u fcy/master                将当前分支的upstream指定为远程的master分支  
    git push --set-upstream originName localName:remoteNamegit  
    关联本地分支和远程分支,使得可以直接通过git push提交,其实最终修改的也是gitconfig文件,命令行可以通过git config --list看到
    git push                                如果没指定originName则会在远程仓库创建一个和本地分支同名的分支  
    git push -f fcy wind:develop            强行推送  
    HEAD本地指针
    回退的时候可以用到
    git reset -hard HEAD^^^^^
    一个^代表往前一个版本
# HEAD远程指针?  
    git remote set-head origin master        将HEAD指针指向master分支  
    git remote set-head origin -d            删除这个指针  
# git回退  
	git有三个区域  
	工作区  
	暂存区  
	历史版本
	撤销暂存区内容  
	撤销修改了的文件  
	回退到之前提交的某个版本  
	本地分支是最新的  
	git commit后执行了git reset --hard HEAD~1回退到了上一个版本  
	此时本地最新的代码丢失了  
	可以通过git reflog查看历史操作系统  
	然后通过git reset --hard versionID回退到最新的代码那次提交  
	我们是修改工作区的文件  
	然后执行git add .后将其变更的文件加入到了暂存区  
	然后执行git commit后将所有变更的文件加入到了实力版本  此时就是一个版本的快照  
	执行git reset --hard versionId后重置HEAD指针并清空暂存区和工作区  
	执行git reset --soft versionID后重置HEAD指针并保留暂存区和工作区  
	执行git reset --mixed versionID后重置HEAD指针并清空暂存区保留工作区(默认选项)  
	git reset --hard commitID
	回退到commitID后的时间段,清除暂存区和工作区
	git reset和git revert  
	git reset是通过移动HEAD指针并删除落后的分支 向前移动  
	git revert是通过新建要给新的分支           向后移动  
	
	git reset HEAD  取消add
# 比较
    git diff 命令  
    暂存区     工作区     历史版本    某个历史版本      某两次提交   远程某个版本
    可比较上面某两个的差别  
    比较两个分支的差异列表
    git diff teacher-uat production --stat

# .gitignore
    git中忽略指定文件夹或者文件  
    在.gitignore文件中添加或者修改配置  
    另外git只能对未追踪的文件进行忽略  
    如果需要忽略已经追踪的文件则需要先删除再push将变更提交到远程仓库  
# git配置免密提交
+ 使用openssh生成一个公钥和一个私钥  
    Linux:~/.ssh/  
    Windows:C:/User/username/.ssh
+ github中配置  
    Setting-->SSH and GPG Keys-->New SSH key
    将id_rsa.pub中的内容复制进去
+ 如果上面没配置的话提交的时候会报异常
    git@github.com: Permission denied (publickey).
    fatal: Could not read from remote repository.
+ 进入用户的home目录
+ 编辑 .git-credentials文件
+ 按照以下格式输入内容：   
　　```https://{username}：{password}@github.com  ``` 
　　其中username，password，github.com 都换成你自己的内容 
+  保存退出后执行下面命令 
　　git config --global credential.helper store
　　执行完后/home/用户名/.gitconfig 会新增一项
　　helper = store
　　这时再执行git push/pull的时候就不会在要求你输入密码了。    
# git删除untracked文件

    git clean -fd
# git fetch的时候报错non-fast-forward

	本地有两个分支 tmp1 tmp2
	执行 git fetch origin dev:tmp1的时候报错non-fast-forward
	执行 git fetch origin dev:tmp3正常
# git

	|-- HEAD # 记录当前处在哪个分支里
	|-- config # 项目的配置信息，git config命令会改动它
	|-- description # 项目的描述信息
	|-- hooks/ # 系统默认钩子脚本目录
	|-- index # 索引文件
	|-- logs/ # 各个refs的历史信息
	|-- objects/ # Git本地仓库的所有对象 (commits, trees, blobs, tags)
	|-- refs/ # 标识每个分支指向了哪个提交(commit)

# git撤销某次更改

git revert commitId

# git 提交单个文件

git commit filename -m "message" 

git push

# git保存当前操作

git stash save

git stash save -u "message"  # 不加-u新增的文件不会暂存，加了会，另外别用-a参数

git stash list

git stash apply stash@{0}

git stash pop