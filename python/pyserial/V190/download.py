import os
import array
import signal
import serial
from time import sleep

COM_PORT = 'COM75'
BIN_FILE = 'LLALM03_Controller_T07C0918_periph_factory_test.bin'
#BIN_FILE = 'led.bin'
MAX_RETRY_CONT = 100
DOWNLOAD_TIMEOUT = 5

class Download(object):

    def __init__(self, com_port, download_file):
        self.com_port = com_port
        self.download_file = download_file

    def check_file(self):
        if not os.path.isfile(self.download_file):
            return False
        return True

    def get_file_size(self):
        return os.path.getsize(self.download_file)

    def download(self):

        # check file
        if not self.check_file():
            print "[Download file] Error : " + self.download_file + " not exist."
            return False

        # check bin file size
        down_file_size = self.get_file_size() + 3
        down_file_size_str = "%04x" %(down_file_size)
        LEN_MSB = (down_file_size_str[0:2]).decode("hex")
        LEN_LSB = (down_file_size_str[2:4]).decode("hex")
        print "[Download file] Size = " + str(down_file_size) + "(0x" + down_file_size_str + ") Bytes"

        # open serial
        ser = serial.Serial()
        ser.port = self.com_port
        ser.baudrate = 57600
        ser.timeout = DOWNLOAD_TIMEOUT
        ser.rts = False
        ser.open()

        if ser.isOpen():
            print "[Download file] Open " + self.com_port + " succeeded."
            print "[Download file] Please reset board. (timeout = " + str(DOWNLOAD_TIMEOUT) + "s)"

            #Auto reset board
            ser.rts = True
            sleep(1)
            ser.rts = False
            print "[Download file] Auto reset board."

            #Wait reset signal
            retry_cont = 0
            while retry_cont < MAX_RETRY_CONT :
                reset_signal = ser.read()
                if len(reset_signal) == 0 :
                    print "[Download file] Error : Timeout!"
                    ser.close()
                    return False
                elif ord(reset_signal) == 0x11 :
                    last_recv = ser.read()
                    if ord(last_recv) == 0x02 :
                        break;
                    else :
                        retry_cont += 1
                        #print "[Download file] Warnning : Signal Error! Recv:0x%02x " %(int(ord(reset_signal))),
                        #print "(retry %d time)" %(retry_cont)
                        continue;
                else :
                    retry_cont += 1
                    #print "[Download file] Warnning : Signal Error! Recv:0x%02x " %(int(ord(reset_signal))),
                    #print "(retry %d time)" %(retry_cont)

            # Send ACK & the file size to board
            if ord(last_recv) == 0x02 :
                send_buff = "01".decode("hex") + LEN_LSB + LEN_MSB
                ser.write(send_buff)
                print "[Download file] Reset"
            else :
                print "[Download file] Error : Not is the reset signal!"
                ser.close()
                return False

            # Wait ACK
            ret_ack = ser.read()
            if ord(ret_ack) == 0x06:
                pass
            elif ord(ret_ack) == 0x15:
                print "[Download file] Error : return NACK!"
                ser.close()
                return False
            else :
                print "[Download file] Error : return not is ACK or NACK!"
                ser.close()
                return False

            # Senf file and CRC calculation
            print "[Download file] Loading ..."
            f = open(self.download_file,"rb")
            crc = 0x00
            send_buff = ""
            for s in f.read():
                crc ^= int(ord(s))
                send_buff += s
            crc ^= 0x01
            crc ^= 0x02
            crc ^= 0x04
            send_buff += "010204".decode("hex")
            ser.write(send_buff)
            f.close()

            # Check CRC value
            print "[Download file] Wait ACK ..."
            recv_crc_val = ser.read(1)
            print "[Download file] CRC code is 0x%02x" %int(ord(recv_crc_val))
            if int(ord(recv_crc_val)) == crc :
                print "[Download file] CRC is right."
            else :
                print "[Download file] Error : CRC failed!"
                ser.close()
                return False

            # Send ACK (End flag)
            ser.write("06".decode("hex"))
            ser.close()
            print "[Download file] Close " + self.com_port
            print "[Download file] Successfully downloaded firmware file to the board."
            return True
        else:
            print "[Download file] Error : Open " + self.com_port + " failed!"
            return False

if __name__ == '__main__':
    # New object
    burn = Download(COM_PORT, BIN_FILE)
    # Download file
    burn.download()