import serial
import array
import os
import signal
from time import sleep
import time

COM_PORT = 'COM75'
DOWNLOAD_TIMEOUT = 60


if __name__ == '__main__':
    
    ser = serial.Serial()
    ser.port = COM_PORT
    ser.baudrate = 57600
    ser.rts = False
    ser.timeout = DOWNLOAD_TIMEOUT
    ser.open()

    if ser.isOpen():
        print "Open "+COM_PORT+" succeeded."

        cont = 0
        while cont < 10 :
            ser.rts = True
            print ser.rts
            sleep(3)
            ser.rts = False
            print ser.rts
            sleep(3)
            cont += 1

        ser.close()
        print "Close "+COM_PORT
    else:
        print "Error: open "+COM_PORT+" failed!"
        exit()