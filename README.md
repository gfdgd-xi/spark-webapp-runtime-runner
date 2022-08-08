# spark-webapp-runtime 运行器
## 介绍
一个 spark-webapp-runtime（星火网页应用运行环境）图形化运行器，可以让你更加方便的使用星火网页应用运行环境  
![截图_选择区域_20220808172505.png](https://storage.deepin.org/thread/202208081725151597_截图_选择区域_20220808172505.png)  

## 软件架构
i386、amd64

## 源码编译教程
```bash
git clone https://gitee.com/gfdgd-xi/spark-webapp-runtime-runner
cd spark-webapp-runtime-runner/build
make
```

## 更新内容
### 1.1.0（2022年08月08日）
※1、程序全部重构，语言从 Python 转 C++、GUI 从 Tkinter 转 DTK、布局大改，参考了 sgb76 大佬的 Wine 运行器设计图、zty79的桌面快捷方式编辑器的参考布局  
※2、程序新增打包功能  
![截图_选择区域_20220808172505.png](https://storage.deepin.org/thread/202208081725151597_截图_选择区域_20220808172505.png)  

### 1.0.2（2021年01月31日）
1、设置软件 deb 包中 .desktop 文件的图标  
![](https://images.gitee.com/uploads/images/2021/0131/160754_f781b57d_7896131.png)

### 1.0.1（2021年01月31日）
使用多线程，防止界面假死  

### 1.0.0（2021年01月30日）
没啥好介绍的  
![](https://images.gitee.com/uploads/images/2021/0130/191813_38818882_7896131.png)

## ©2021~Now