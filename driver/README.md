# driver
	关于Linux驱动的一些小程序。
## 1. freg
	虚拟寄存器驱动

> 该驱动主要是用来学习驱动的整体构架。属于字符设备驱动，用到了proc文件系统，sys文件系统，使用了file_operations接口

## 2. globamem
	虚拟内存驱动

> 该驱动可以作为进程间通信的一种蹩脚的方法。主要是用来学习Linux驱动。属于字符设备，用到了file_operations接口。

## 3. mytp
	TP驱动

> 该驱动分为很多块，从base、device tree、input、中断等逐步递进。一步步完成一个完整的TP驱动。目前正在完善中

