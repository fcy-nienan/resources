--aot参数

--prod.   最小化打包，将一些不必要的文件去除

--max_old_space_size=5048    调整内存的，怕编译时内存溢出



angular.json文件



https://github.com/angular/angular-cli/issues/16572

npm i.    npm install的简写

npm config set registry "https://registry.npm.taobao.org"

node -e "try{require('./postinstall')}catch(e){}"

node install.js

npm i electron-packager@15.0.0

NODE_ENV=${CHUNK} node desktop-builder.js

# dependencies和devDependencies的区别

#  skills

 ```html
<p>对象为空:{{student&&student.name}}</p>
 ```
   ```html
<p *ngIf="content">this is {{content}}</p>
   ```

```html
<p>对象为空2:{{student?.name}}</p>
```

# angular中的父子通信

```
@Component({
    selector : 'child',
    template : `
        <button (click)="sendNotification()">Notify my parent!</button>
    `
})
class Child {
    @Output() notifyParent: EventEmitter = new EventEmitter();
    sendNotification() {
        this.notifyParent.emit('Some value to send to the parent');
    }
}

@Component({
    selector : 'parent',
    template : `
        <child (notifyParent)="getNotification($event)"></child>
    `
})
class Parent {
    getNotification(evt) {
        // Do something with the notification (evt) sent by the child!
    }
}
```

# 父子组件信息交互

##### 方法一 在父组件上设置子组件的属性

父组件绑定信息

```
<app-child childTitle="可设置子组件标题"></app-child>
```

子组件接收消息

```
import { Component, OnInit, Input } from '@angular/core';
@Input childTitle: string;
```

##### 方法二 父组件调用子组件的方法

父组件触发消息

```
<app-child #child></app-child> <button (click)="child.childPrint()"></button>
```

子组件接收消息

```
childPrint() {
  alert("来自子组件的打印");
}
```
# angular数据绑定的三种写法
<app-custom-input ngModel="inputOne"></app-custom-input>
这里inputOne是字符串，传入的是inputOne这个字符串
<app-custom-input [ngModel]="inputOne"></app-custom-input>
这里inputOne是变量，单项绑定，传入的是inputOne的值，控件里面值得变更不会影响外面的inputOne变量
<app-custom-input [(ngModel)]="inputOne"></app-custom-input>、
这里inputOne是变量，双向绑定，传入逇是inputOne的值，控件里面值得变更会同步到外面inputOne变量
