#-*-coding:utf-8-*-

import os
import time
import win32gui
import win32api
import win32con



#os.system('notepad')
wdname1=u"无标题 - 记事本"

w1hd=win32gui.FindWindow(0,wdname1)
print w1hd
w2hd=win32gui.FindWindowEx(w1hd,None,None,None)
print w2hd

def aotohelper_wt(i):
	#获取窗口焦点
	win32gui.SetForegroundWindow(w2hd)
	#快捷键Alt+F
	#win32api.keybd_event(18,0,0,0) #Alt
	win32api.keybd_event(70,0,0,0) #F
	win32api.keybd_event(70,0,win32con.KEYEVENTF_KEYUP,0) #释放按键
	#win32api.keybd_event(18,0,win32con.KEYEVENTF_KEYUP,0)

	time.sleep(1)


aotohelper_wt(1)

print "work done!"