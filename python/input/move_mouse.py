#-*-coding:utf-8-*-

from ctypes import *
from time import sleep

if __name__ == "__main__":
	windll.user32.SetCursorPos(100, 100)
	sleep(0.5)
	windll.user32.SetCursorPos(200, 200)
	sleep(0.5)
	windll.user32.SetCursorPos(300, 300)
	sleep(0.5)
	windll.user32.SetCursorPos(400, 400)
	sleep(0.5)
	windll.user32.SetCursorPos(500, 500)
	sleep(0.5)
	windll.user32.SetCursorPos(600, 600)
	sleep(0.5)
