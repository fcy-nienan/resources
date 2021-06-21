# xxx.component.spec.ts文件

单元测试文件,每个组件一个,当你使用'ng test'命令时，它们通过Karma任务运行器使用Jasmine javascript测试框架运行。

```
ng g c pages/testC --module app
```

ng g m pages/demo --routing

ng g c pages/demo/welcome --module demo

ng g m pages/other --routing

ng g c pages/other/test --module other

创建自定义指令

ng g m directive

ng g directive directive/hello --module directive

# angular的指令

## 属性型指令

## 结构型指令

### 组件





```
ng g module --routing

```

# [Difference between [(ngModel)\] and [ngModel] for binding state to property?](https://stackoverflow.com/questions/42504918/difference-between-ngmodel-and-ngmodel-for-binding-state-to-property)

```
[(ngModel)]="overRideRate" is the short form of [ngModel]="overRideRate"
 (ngModelChange)="overRideRate = $event"

[ngModel]="overRideRate" is to bind overRideRate to the input.value
(ngModelChange)="overRideRate = $event" is to update overRideRate with the value of input.value when the change event was emitted.
```

