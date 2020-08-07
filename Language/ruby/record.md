     >rails generate model group
     invoke  active_record
      create    db/migrate/20200803125353_create_groups.rb
      create    app/models/group.rb

    Model, Controller 中 Concerns 目录存放公用方法




## app/

------

`app`目录是rails程序中的主目录，其中主要包括`assets`、`channels`、`controllers（C）`、`helpers`、`jobs`、`mailers`、`models（M）`、`views（V）`这几个文件夹。我们看到，rails程序中的MVC的文件夹都存放在`app`文件夹中，因此我们需要做的绝大多数工作都是在`app`文件夹中进行的。

### app/assets/

通常放置我们自己为了自己的程序所写的js，css，或者是images文件，分别放在`javascripts（js）`、`stylesheets（CSS）`和`images`文件夹下。

### app/channels/

`Action Cable`中的组件，`Action Cable`结合`WebSockets`来实现浏览器端实时的消息通知。一般情况下我们很少使用。

### app/controllers/

rails程序中的控制器文件（controller层）一般都存放在这个文件夹下

### app/helpers/

主要用来存放helper方法。在Rails中，`Helper`指的是可以在`Template`中使用的辅助方法，主要用途是可以将资料转化成输出用的HTML字串。每个控制器都可以有一个对应的Helper模块，它在app/helper目录下，与控制器文件同名。例如`catalog_controller.rb`对应的`helper`文件`catalog_helper.rb`。当我们希望一个`helper`方法是全局共享时，通常将该方法放在`application_helper.rb`中。

### app/jobs/

用来存放任务文件，确保任务文件继承自 ActiveJob::Base即可。

> Active Job 是用来声明任务，并把任务放到多种多样的队列后台中执行的框架。从定期地安排清理，费用账单到发送邮件，任何事情都可以是任务。任何可以切分为小的单元和并行执行的任务都可以用 Active Job 来执行。
>  ** Active Job 的目标**
>  主要是确保所有的 Rails 程序有一致任务框架，即便是以 “立即执行”的形式存在。

### app/mailers/

用来存放实现发送邮件功能的文件。

> Rails 使用 Action Mailer 实现发送邮件功能，邮件由邮件程序和视图控制。邮件程序继承自 ActionMailer::Base，作用和控制器类似，保存在文件夹 app/mailers 中，对应的视图保存在文件夹 app/views 中。

### app/models/

用来存放model文件（M层），例如`user.rb`文件，这个User模型对应一个名为users的table（表），一个模型最多只能对应一张表（可以不对应表）。

### app/views/

用命令生成`controller`时，即



```undefined
rails g controller catalog
```

会在`app/views`文件夹下生成对应的一个文件夹，文件夹名称与控制器名称相同，在此文件夹下即可生成对应控制器的视图文件，例如本例中的`app/views/catalog/catalog_test.html.erb`文件。

## bin/

------

存放运行程序的 rails 脚本，以及其他用来部署或运行程序的脚本。

## config/

------

`config`文件夹下主要包括`environments/`、`initializers/`、`locales/`这三个文件夹和若干文件，主要是存放对rails程序进行配置的文件。
 下面对**部分重要**的文件夹及文件进行介绍。具体的配置内容见[这里](https://link.jianshu.com?t=http://guides.ruby-china.org/configuring.html)。

### config/environments/

rails程序的不同运行环境的配置包括：

- config/environments/development.rb 开发环境配置文件
- config/environments/test.rb 测试环境配置文件
- config/environments/production.rb 生产环境配置文件

### config/initializers/

> 加载完框架以及程序中使用的gem后，Rails会加载初始化脚本。初始化脚本是个Ruby文件，存储在程序的config/initializers文件夹中。初始化脚本可在框架和gem 载完成后做设置。

### config/boot.rb

配置rails程序的Bundler以及加载路径。
 保存并加载可在命令行中执行的任务。任务在 Rails 的各组件中定义。如果想添加自己的任务，不要修改这个文件，把任务保存在 lib/tasks 文件夹中。

### config/application.rb

根据不同的启动环境（Rails.env）加载不同的rails gems, 配置应用程序。

### config/environment.rb

执行所有启动程序(initializers)。

`config/boot.rb`、`config/application.rb`、`config/environment.rb`这三个文件都在启动整个rails环境时加载。

### config/routes.rb

rails程序的路由文件，添加路由时需要在此文件中添加。

### config/database.yml

用来配置rails程序连接数据库的文件，包括连接的数据库类型、数据库连接池限制数量等。

## db/

------

存放当前数据库的模式，以及数据库迁移文件。

### db/migrate/

用来存放数据库的迁移文件。

### db/development.sqlite3

当前程序连接的数据库文件

### db/schema.rb

这个文件用来记录当前迁移的版本编号，同时匹配最新的数据库结构。

### db/seeds.rb

通过这个文件，可以直接把初始化数据存入数据库。

## lib/

------

程序的扩展模块。

### lib/assets/

通常是放置我们使用的插件中用到的assets。

### lib/tasks/

Rake的任务一般存放在`lib/tasks`目录下。

## log/

------

程序的日志文件。不同环境下会生成不同的日志文件，例如`development.log`、`production.log`、`server.log`、`test.log`，我们在开发时的信息都写在`development.log`里，而测试时的log都写在`test.log`里。

## public/

------

唯一对外开放的文件夹，其他人可以直接访问这个目录中的东西。在这里存放于框架不进行交互的资源文件或网页文件。与这个目录相对应，app目录中的内容是对外隐藏的。

## test/

------

用于存放单元测试、功能测试及整合测试文件等测试文件。

## temp/

------

临时文件，例如缓存，PID，会话文件。

## vendor/

------

存放第三方代码。经常用来放第三方 gem。

### vendor/assets/

通常是放置一些我们从别的地方借用的assets，比如说一些jquery插件。

## config.ru

------

基于 Rack 服务器的程序设置，用来启动程序。

## Gemfile

------

用来指定程序所需的gem依赖件，用于Bundler gem。

## Gemfile.lock

------

命令：



```undefined
bundle install
```

执行后生成的文件，用来记录当前使用的gem信息。依赖于`Gemfile`。

## Rakefile

------

> 保存并加载可在命令行中执行的任务。任务在 Rails 的各组件中定义。如果想添加自己的任务，不要修改这个文件，把任务保存在 lib/tasks 文件夹中。

这就是rails程序的目录结构，明确每一个文件夹及文件的功能，对后面rails的学习开发是至关重要的，毕竟rails是“惯例优于设置”的，不同功能的文件放在对应的文件夹下，才更符合rails的开发
