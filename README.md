# dst_store
	这个仓库主要是用来存放一些个人的代码，目前没有什么特别的用途。

## 1.c
	关于c语言语法的一些小程序，放在c_test目录下。

## 2.c++
	关于c++语法的一些小程序，放在cpp_test目录下。

## 3.java
	关于java语法的一些小程序，放在java目录下。

## 4.python
	关于python语法的一些小程序，放在python目录下。

## 5.shell
	关于shell语法的一些小程序，放在shell目录下。

## 6.driver
	关于Linux驱动的一些小程序。
### 6.1 freg
	虚拟寄存器驱动
```
	该驱动主要是用来学习驱动的整体构架。
	属于字符设备驱动，用到了proc文件系统，sys文件系统，使用了file_operations接口
```
### 6.2 globamem
	虚拟内存驱动
```
	该驱动可以作为进程间通信的一种蹩脚的方法。主要是用来学习Linux驱动。
	属于字符设备，用到了file_operations接口。
```
### 6.3 mytp
	TP驱动
```
	该驱动分为很多块，从base、device tree、input、中断等逐步递进。
	一步步完成一个完整的TP驱动。目前正在完善中
```

## 7.vimconfig
	该目录下，存放了我常用的三种vim配置。

	vimrc_base是无插件的版本，用于临时场合下使用vim。
	
	vimconfig是结合网上的配置，自己修改后的一个版本。含有常用的插件。
	
	myconfig是自己配置的vim版本，目前主要使用这个版本vim配置。含有常用的插件。

## 8.shellconfig
	bash目录下是关于.bashrc配置的一些配置文件
	
	将来会增加zsh目录。

