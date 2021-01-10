# 为什么需要VNode

    传统的操作dom的方式
    var arr = [1,2,3,4]
    function render(data){
       function createElement(tag){
          var dom = document.createElement(tag)
       }
      var ul= createElement('ui')
      data.forEach((elem)=>{
          var liDom = createElement('li')
          liDom.innerHTML = elem
          ul.append(liDom)
      })
      return ul
    }
    render(arr)
    
    vue的方式
    生成一个VNode对象，该对象代表了真实的DOM
    {
        tag: 'div'
        data: {
            class: 'test'
        },
        children: [
            {
                tag: 'span',
                data: {
                    class: 'demo'
                }
                text: 'hello,VNode'
            }
        ]
    }
    ```
    
    渲染之后的结果就是这样的
    
    ```html
    <div class="test">
        <span class="demo">hello,VNode</span>
    </div>
    
    那如何渲染呢，啥时候渲染呢，怎么发现变动然后渲染了？
    通过传统的创建DOM节点
    发现变动并渲染是通过相应的算法递归比对，然后更新值，又因为值被双向绑定了，所以其他值也就变了
# 双向绑定原理
    Object.defineProperty方法
    var Book={}
    undefined
    var name='';
    undefined
    Object.defineProperty(Book,'name',{
        set:function(value){
            name=value;
            console.log("设置了name的值")
        },
        get:function(){
            console.log("获取了name的值");
        	return name+"fcy";
        }
    })
    Book.name='nienan'//我们赋值他底层会调用set方法
    VM549:4 设置了name的值
    console.log(Book.name)//我们取值他底层会调用get方法
    VM549:7 获取了name的值
    VM671:1 nienanfcy
    
    类似于JavaScript已经提供了对变量值改变的监听方法

