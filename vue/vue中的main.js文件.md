import Vue from 'vue';
等于
import Vue from "../node_modules/vue/dist/vue.js";

import App from './App';
等于
import App from './App.vue';

import router from './route';
等于
import router from './route.js';

import axios from 'axios';
等于
import axios from '..\node_modules\axios\dist\axios.js';

import './less/index';
等于
import './less/index.less';

@方式
以根目录的方式定义相对路径

访问的页面是从index.html入口

App.vue是项目的主组件，页面入口文件 ，所有页面都在App.vue下进行切换，app.vue负责构建定义及页面组件归集
在index.html中也有一个
    <div id="app"></div>
    
    
Vue使用import ... from ...来导入组件，库，变量等。
而from后的来源可以是js，vue，json。这个是在webpack.base.conf.js中设置的：
module.exports = {
  resolve: {
    extensions: ['.js', '.vue', '.json'],
    alias: {
      'vue$': 'vue/dist/vue.esm.js',
      '@': resolve('src'),
    }
  },