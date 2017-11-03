import serial
import array
import os
import signal
from time import sleep
import time
from random import Random
import download

def random_str(randomlength=8):
    str = ''
    chars = 'ABCDEF0123456789'
    length = len(chars) - 1
    random = Random()
    for i in range(randomlength):
        str+=chars[random.randint(0, length)]
    return str

def onsignal_int(a,b):
    print "sigint!"
    global ser
    if ser.isOpen():
        ser.close()

signal.signal(signal.SIGINT, onsignal_int)
signal.signal(signal.SIGTERM, onsignal_int)

# commands
read_sn_cmd="01d0400100".decode("hex")

# Settings
MAX_COUNT = 1
comport = 'COM75'
BIN_FILE = 'prod_test_580.bin'
LOG_FILE = 'prodtest_log.txt'

# Create download object
burn = download.Download(comport, BIN_FILE)

# init log
f = open(LOG_FILE, "w")
f.write("-------------------------------------------------------\n")
f.write("start time:"+time.strftime("%H:%M:%S")+"\n")

# init serial
ser = serial.Serial()

print "--------------------Test Start--------------------"

count = 0
error_count = 0
while count < MAX_COUNT:
    count = count+1

    print "--------------------"
    print "["+time.strftime("%H:%M:%S")+"]Run "+str(count)+" time."
    print "--------------------"
    f.write("-------------------------------------------------------\n")
    f.write("["+time.strftime("%H:%M:%S")+"]Run "+str(count)+" time.\n")

    # Download file
    if not burn.download() :
        print "Download Failed!"
        f.write("Download Failed!\n")
        error_count = error_count + 1
        continue;

    # Testing ...

    # open serial
    ser.port = comport
    ser.baudrate = 115200
    ser.rts = False
    ser.timeout = 5
    ser.open()

    if ser.isOpen():
        print "Open "+comport+" succeeded."

        #read SN number
        ser.write(read_sn_cmd)
        sn_number = ser.read(23)[7:]
        print "SN : " + sn_number

        # Test end
        ser.close()
        print "Close "+comport
    else:
        print "Error: open "+comport+" failed!"

f.flush()
sleep(0.01)
f.close()
print "Close " + LOG_FILE
print "All : " + str(count) + " time"
print "Error : " + str(error_count) + " time"
print "--------------------Test End--------------------"
