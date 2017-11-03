#!/usr/bin/env python  
#coding=gbk  
 
#此模块主要提供抓图功能，支持以下三种抓图方式：  
#1、抓取全屏,快捷键CTRL+F1  
#2、抓取当前窗口，快捷键CTRL+F2  
#3、抓取所选区域，快捷键CTRL+F3  
#抓到之后，会自动弹出保存对话框，选择路径保存即可  
#*******************************************  
#更新记录  
#0.1 2012-03-10 create by dyx1024  
#********************************************  

import pyhk
import wx
import os
import sys
from PIL import ImageGrab
import ctypes
import win32gui
import ctypes.wintypes


def capture_fullscreen(): 
    '''
    Function:全屏抓图
    Input：NONE
    Output: NONE
    author: socrates
    blog:http://blog.csdn.net/dyx1024
    date:2012-03-10
    '''
    #抓图
    pic = ImageGrab.grab()

    #保存图片
    save_pic(pic)
     
def capture_current_windows(): 
    '''''
    Function:抓取当前窗口
    Input：NONE
    Output: NONE
    author: socrates
    blog:http://blog.csdn.net/dyx1024
    date:2012-03-10
    '''  
    #窗口结构         
    class RECT(ctypes.Structure): 
        _fields_ = [('left', ctypes.c_long), 
                ('top', ctypes.c_long), 
                ('right', ctypes.c_long), 
                ('bottom', ctypes.c_long)] 
        def __str__(self): 
            return str((self.left, self.top, self.right, self.bottom)) 
     
    rect = RECT() 
     
    #获取当前窗口句柄  
    HWND = win32gui.GetForegroundWindow() 
     
    #取当前窗口坐标  
    ctypes.windll.user32.GetWindowRect(HWND,ctypes.byref(rect)) 
 
    #调整坐标  
    rangle = (rect.left+2,rect.top+2,rect.right-2,rect.bottom-2) 
     
    #抓图  
    pic = ImageGrab.grab(rangle) 
     
    #保存  
    save_pic(pic) 
     
def capture_choose_windows(): 
    '''''
    Function:抓取选择的区域，没有自己写这个，借用QQ抓图功能
    Input：NONE
    Output: NONE
    author: socrates
    blog:http://blog.csdn.net/dyx1024
    date:2012-03-10
    '''      
    try: 
         #加载QQ抓图使用的dll  
         dll_handle = ctypes.cdll.LoadLibrary('CameraDll.dll')  
    except Exception: 
             try: 
                 #如果dll加载失败，则换种方法使用，直接运行，如果还失败，退出  
                 os.system("Rundll32.exe CameraDll.dll, CameraSubArea") 
             except Exception: 
                 return     
    else: 
         try: 
             #加载dll成功，则调用抓图函数，注:没有分析清楚这个函数带的参数个数  
             #及类型，所以此语句执行后会报参数缺少4个字节，但不影响抓图功能，所  
             #以直接忽略了些异常  
             dll_handle.CameraSubArea(0) 
         except Exception: 
             return            
 
def save_pic(pic, filename = '未命令图片.png'): 
    '''''
    Function:使用文件对框，保存图片
    Input：NONE
    Output: NONE
    author: socrates
    blog:http://blog.csdn.net/dyx1024
    date:2012-03-10
    '''      
    app = wx.PySimpleApp() 
     
    wildcard = "PNG(*.png)|*.png" 
    dialog = wx.FileDialog(None, "Select a place", os.getcwd(), 
                           filename, wildcard, wx.SAVE) 
    if dialog.ShowModal() == wx.ID_OK: 
        pic.save(dialog.GetPath().encode('gb2312')) 
    else: 
        pass 
     
    dialog.Destroy()     
     
 
def main(): 
    '''''
    Function:主函数，注册快捷键
    Input：NONE
    Output: NONE
    author: socrates
    blog:http://blog.csdn.net/dyx1024
    date:2012-03-10
    '''          
     
    #创建hotkey句柄   
    hot_handle = pyhk.pyhk() 
  
    #注册抓取全屏快捷键CTRL+F1  
    hot_handle.addHotkey(['Ctrl', 'F1'], capture_fullscreen) 
     
    #注册抓取当前窗口快捷键CTRL+F2  
    hot_handle.addHotkey(['Ctrl', 'F2'], capture_current_windows) 
     
    #注册抓取所选区域快捷键CTRL+F3  
    hot_handle.addHotkey(['Ctrl', 'F3'], capture_choose_windows) 
  
    #开始运行  
    hot_handle.start() 
     
if __name__ == "__main__": 
    main()  
