import serial
import array
import os
import signal
import time
import struct

def hex_to_short_int(hex_h, hex_l, status):
    if status :
        tmp = ((int(ord(hex_h)) << 8) & 0x0f00) | (int(ord(hex_l)) & 0xff)
        if tmp > 0x07ff :
            tmp = tmp - 0x1000
    else:
        tmp = ((int(ord(hex_h)) << 8) & 0xff00) | (int(ord(hex_l)) & 0xff)
        if tmp > 0x7fff :
            tmp = tmp - 0x10000
    return tmp


def onsignal_int(a,b):
    print "sigint!"
    global ser
    if ser.isOpen():
        ser.write(stop_data_transfer_cmd)
        time.sleep(0.05)
        ser.write(led_off_cmd)
        ser.close()

signal.signal(signal.SIGINT, onsignal_int)
signal.signal(signal.SIGTERM, onsignal_int)


all_data_transfer_cmd="Transfer For All"
stop_data_transfer_cmd="Stop Data Transfer"
get_sn_cmd="Get SN Param"
led_on_cmd="LED On"
led_off_cmd="LED Off"

# Settings
MAX_COUNT = 1
TEST_COUNT_MAX = 240000
#TEST_COUNT_MAX = 10000
comport = 'COM12'

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

    # Testing ...

    # open serial
    ser.port = comport
    ser.baudrate = 115200
    ser.rts = False
    ser.timeout = 1
    ser.open()

    if ser.isOpen():
        print "Open "+comport+" succeeded."

        #led on
        ser.write(led_on_cmd)
        time.sleep(0.05) 

        ser.write(get_sn_cmd)
        time.sleep(0.05) 
        sn_num = ser.read(16)[2:]
        print "SN : " + sn_num

        #imu test
        ser.write(stop_data_transfer_cmd)
        time.sleep(0.05)
        ft = open(time.strftime('imu_test_%Y-%m-%d_%H_%M_%S',time.localtime(time.time()))+".csv", "w")
        test_count = 0
        ser.write(all_data_transfer_cmd)
        while test_count < TEST_COUNT_MAX:
            #ser.write(all_data_transfer_cmd)
            
            imu_data = ser.read(1)
            if 0 == len(imu_data):
                print "ERR ZERO"
                break
            #if (0x08 == ord(imu_data[0])) and (0x00 == ord(imu_data[1])):
            #    pass
            if (0x08 == ord(imu_data[0])):
                imu_data = ser.read(1)
                if (0x00 == ord(imu_data[0])):
                    pass
                else:
                    print("ERR DATA HEADER")
                    continue
            else:
                print("ERR DATA HEADER")
                continue
            imu_data = ser.read(18)
            checksum = 0x08 + 0x00
            for checksum_tmp in imu_data[:-1]:
                checksum = checksum + int(ord(checksum_tmp))
            checksum = (0 - checksum) & 0xff
            if checksum == int(ord(imu_data[-1])):
                pass
            else:
                print("ERR DATA CHECKSUM")
                print int(ord(imu_data[-1])),checksum
                continue
            #time.sleep(0.05)
            systimestamp=int(ord(imu_data[0])*0x1000000+ord(imu_data[1])*0x10000+ord(imu_data[2])*0x100+ord(imu_data[3]))
            systimestamp=systimestamp/2
            imu_view="%6d," %(test_count)
            imu_view+="%8d," %(systimestamp)
            #imu_view+="0x%02x," %(int(ord(imu_data[0])))
            temp=int(ord(imu_data[6-2]))
            if temp > 0x7f :
                imu_view+="%2d," %(temp-0x100)
            else:
                imu_view+="%2d," %(temp)
            if False:
                for imu_data_byte in imu_data[5:]:
                    imu_view += "0x%02x," %(int(ord(imu_data_byte)))
            else:
                gyro_x = hex_to_short_int(imu_data[7-2],imu_data[8-2],False)
                gyro_y = hex_to_short_int(imu_data[9-2],imu_data[10-2],False)
                gyro_z = hex_to_short_int(imu_data[11-2],imu_data[12-2],False)
                acc_x = hex_to_short_int(imu_data[13-2],imu_data[14-2],True)
                acc_y = hex_to_short_int(imu_data[15-2],imu_data[16-2],True)
                acc_z = hex_to_short_int(imu_data[17-2],imu_data[18-2],True)
                imu_view += "%+6d,%+6d,%+6d,%+6d,%+6d,%+6d" %(gyro_x,gyro_y,gyro_z,acc_x,acc_y,acc_z)
            ft.write(imu_view+"\n") 
            if (test_count % 1 == 0):
                print imu_view
            test_count += 1
        ser.write(stop_data_transfer_cmd)
        ft.close()

        #led off
        time.sleep(0.05)
        ser.write(led_off_cmd)

        # Test end
        ser.close()
        print "Close "+comport
    else:
        print "Error: open "+comport+" failed!"

print "--------------------"
print "All : " + str(count) + " time"
print "Error : " + str(error_count) + " time"
print "--------------------Test End--------------------"
