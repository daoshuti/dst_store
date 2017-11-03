#!/usr/bin/python
# -*- coding:utf-8 -*-
 
 
from Tkinter import *
from ttk import *
import sys
import platform
import serial
import time
import threading

 
#ipdb.set_trace()
 
running = False
 
def recevie(obj):
    global running
    print ("start rx:\n")
    while(running == True):
        rx_len = obj.inWaiting()
        if(rx_len):
            s0 = obj.read(rx_len)
            print ("rx",s0)
            txt0.insert(END,s0)
    print ("stop rx:\n")
 
def COMOpen():
    global running
    if not isOpened.isSet():
        try:
            ser.timeout = 1
            ser.xonxoff = 0   
            ser.port = comx.get()
            ser.parity = chck.get()[0]
            ser.baudrate = int(baud.get())
            ser.bytesize = int(dlen.get())
            ser.stopbits = int(slen.get())
            print (ser.port)
            ser.open()
            running = True
            print (running)
            t = threading.Thread(target=recevie, args=(ser,))
            t.start()
        except Exception:
            print ("COM Open Error!",e)
        else:
            isOpened.set()
            Open.set('close')
 
    else:
        running = False
        ser.close()
        isOpened.clear()
        Open.set('open serial')
 
 
def Submit():
    s1 = inpt.get()
    print (s1)
#    txt0.insert(END,s1)
    datain = ser.write(s1)
 
 
def f_Clear():
    print ("delete all")
    txt0.delete(0.0,END)
 
def test():
    dataout = ser.read()
    txt0.insert(0.0,dataout)
     
             
             
if platform.system() == 'Linux':
    sp_list=['ttyUSBS0', 'ttyUSBS1']
elif platform.system() == 'Windows':
    sp_list=['COM80','COM84','COM3','COM4','COM5','COM6']
 
ser = serial.Serial()
 
if __name__ == "__main__":
    isOpened = threading.Event()
     
    root = Tk()
    root.title('RS serial communication')
    txt0 = Text(root,width=80,height=24,border=5)
    txt0.pack(side='top')
    sec0 = Frame(root,border=4)
    sec0.pack(side='top',anchor='w')
    sec1 = Frame(root,border=4)
    sec1.pack(side='top',anchor='w')
    sec2 = Frame(root,border=4)
    sec2.pack(side='top',anchor='w')
     
    comx = StringVar(root,sp_list[0])
    Label(sec0,text='com: ').pack(side='left')
    Combobox(sec0,text=comx,values=sp_list,width='12').pack(side='left')
     
    baud = StringVar(root,"115200")
    Label(sec0,text='  buad: ').pack(side='left')
    Combobox(sec0,textvariable=baud,values=['4800','9600','19200','57600','115200'],width='12').pack(side='left')
     
    dlen = StringVar(root,'8')
    Label(sec1,text='data: ').pack(side='left')
    Combobox(sec1,textvariable=dlen,values=['9','8','7','6','5','4'],width='12').pack(side='left')
     
    slen = StringVar(root,'1')
    Label(sec1,text='  stop: ').pack(side='left')
    lst3 = Combobox(sec1,textvariable=slen,values=['1','2'],width='12').pack(side='left')
     
    chck = StringVar(root,'None')
    Label(sec1,text='  parity: ').pack(side='left')
    lst4 = Combobox(sec1,textvariable=chck,values=['None','Odd','Even'],width='12').pack(side='left')
     
    inpt = StringVar(root,'')
    Label(sec2,text='input: ').pack(side='left')
    Entry(sec2,width=30,textvariable=inpt).pack(side='left')
 
    Send = StringVar(root,'send')
    Button(sec2,textvariable=Send,width=9,command = Submit).pack(side='left')
 
    Clear = StringVar(root,'clear')
    Button(sec2,textvariable=Clear,width=9,command = f_Clear).pack(side='left')
     
    Open = StringVar(root,'open serial')
    Button(sec0,textvariable=Open,width=16,command = COMOpen).pack(side='left')
     
    isOpened = threading.Event()
     
    root.mainloop()
