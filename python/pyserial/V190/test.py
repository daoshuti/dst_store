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

set_gyro_para_cmd="Set Gyro Param"
get_gyro_para_cmd="Get Gyro Param"
set_acc_para_cmd="Set Acc Param"
get_acc_para_cmd="Get Acc Param"
set_mag_para_cmd="Set Mag Param"
get_mag_para_cmd="Get Mag Param"
get_sn_cmd="Get SN Param"
led_on_cmd="LED On"
led_off_cmd="LED Off"

# Settings
MAX_COUNT = 10000
comport = 'COM117'
BIN_FILE = 'LLALM03_Controller_T07C0918_periph_factory_test.bin'
LOG_FILE = "func_log_20170927_3.txt"

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
        f.write("[Error] Download Failed!\n")
        error_count = error_count + 1
        continue

    # Testing ...

    # open serial
    ser.port = comport
    ser.baudrate = 115200
    ser.rts = False
    ser.timeout = 5
    ser.open()

    if ser.isOpen():
        print "Open "+comport+" succeeded."
        ser.write(get_sn_cmd)
        sleep(0.05) 
        sn_at_begin = ser.read(16)[:2]
    
        #write gyro data  
        gyro_data ="0D00"+random_str(96)
        gyro_data =gyro_data.decode("hex")
        ser.write(set_gyro_para_cmd)
        sleep(0.05) 
        ser.write(gyro_data)
        wr_rlt = ser.read(4)
        sleep(0.05)    
        ser.write(get_gyro_para_cmd)    
        gyro_para_readback = ser.read(50)
        if gyro_para_readback[2:]==gyro_data[2:]:
            print "write gyro ACK : "+wr_rlt
            f.write(time.strftime("%H:%M:%S")+" write gyro OK\n")
            f.write("ACK : "+wr_rlt)
        else:
            print "Error: write gyro data failed!"
            f.write(time.strftime("%H:%M:%S")+" Failed!gyro_data is "+":".join("{:02x}".format(ord(c)) for c in gyro_data)+"\n")
            f.write("ACK : "+wr_rlt)
            f.write("       gyro_para_readback is "+":".join("{:02x}".format(ord(c)) for c in gyro_para_readback)+"\n") 
            f.write("SN : "+sn_at_begin+"\n") 
            ser.close()
            print "Close "+comport
            error_count = error_count + 1
            continue

        #write acc data  
        acc_data ="0E00"+random_str(96)
        acc_data =acc_data.decode("hex")
        ser.write(set_acc_para_cmd)
        sleep(0.05) 
        ser.write(acc_data)
        wr_rlt = ser.read(4)
        sleep(0.05)    
        ser.write(get_acc_para_cmd)    
        acc_para_readback = ser.read(50)
        if acc_para_readback[2:]==acc_data[2:]:
            print "write acc ACK : "+wr_rlt
            f.write(time.strftime("%H:%M:%S")+" write acc OK\n")
            f.write("ACK : "+wr_rlt)
        else:
            print "Error: write acc data failed!"
            f.write(time.strftime("%H:%M:%S")+" Failed!acc_data is "+":".join("{:02x}".format(ord(c)) for c in acc_data)+"\n")
            f.write("ACK : "+wr_rlt)
            f.write("       acc_para_readback is "+":".join("{:02x}".format(ord(c)) for c in acc_para_readback)+"\n")
            f.write("SN : "+sn_at_begin+"\n")  
            ser.close()
            print "Close "+comport
            error_count = error_count + 1
            continue
        
        #write mag data  
        mag_data ="0F00"+random_str(96)
        mag_data =mag_data.decode("hex")
        ser.write(set_mag_para_cmd)
        sleep(0.05) 
        ser.write(mag_data)
        wr_rlt = ser.read(4)
        sleep(0.05)    
        ser.write(get_mag_para_cmd)    
        mag_para_readback = ser.read(50)
        if mag_para_readback[2:]==mag_data[2:]:
            print "write mag ACK : "+wr_rlt
            f.write(time.strftime("%H:%M:%S")+" write mag OK\n")
            f.write("ACK : "+wr_rlt)
        else:
            print "Error: write mag data failed!"
            f.write(time.strftime("%H:%M:%S")+" Failed!mag_data is "+":".join("{:02x}".format(ord(c)) for c in mag_data)+"\n")
            f.write("ACK : "+wr_rlt)
            f.write("       mag_para_readback is "+":".join("{:02x}".format(ord(c)) for c in mag_para_readback)+"\n") 
            f.write("SN : "+sn_at_begin+"\n") 
            ser.close()
            print "Close "+comport
            error_count = error_count + 1
            continue

		#led on
        ser.write(led_on_cmd)
        sleep(0.05) 

        #verify sn
        ser.write(get_sn_cmd)
        sleep(0.05) 
        sn_now = ser.read(16)[:2]
        if sn_at_begin!=sn_now:
            print "Failed, SN does not exist!"
            print "sn_at_begin:" + sn_at_begin
            print "sn_now:" + sn_now
            f.write("sn_now:" + sn_now
                    +"\nFailed, SN does not exist!"
                    +"\nsn_at_begin:" + sn_at_begin
                    +"\nsn_now:" + sn_now+"\n")
            ser.close()
            print "Close "+comport
            error_count = error_count + 1
            continue

        #led off
        ser.write(led_off_cmd)
        sleep(0.05) 

        # Test end
        ser.close()
        f.flush()
        print "Close "+comport
    else:
        print "Error: open "+comport+" failed!"

print "--------------------"
f.write("-------------------------------------------\n")
print "All : " + str(count) + " time"
f.write("All : " + str(count) + " time\n")
print "Error : " + str(error_count) + " time"
f.write("Error : " + str(error_count) + " time\n")
f.flush()
sleep(0.01)
f.close()
print "Close " + LOG_FILE
print "--------------------Test End--------------------"
