#-*-coding:utf-8-*-

from ctypes import *
from time import sleep

class POINT(Structure):
    _fields_ = [("x", c_ulong),("y", c_ulong)]

def get_mouse_point():
    po = POINT()
    windll.user32.GetCursorPos(byref(po))
    return int(po.x), int(po.y)

if __name__ == "__main__":
	count = 0
	while count < 100:
	    x, y = get_mouse_point()
	    print str(x)+','+str(y)
	    sleep(0.1)
	    count=count+1