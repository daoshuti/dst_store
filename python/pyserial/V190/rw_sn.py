import serial
from time import sleep

get_sn_cmd = "Get SN Param"
set_sn_cmd = "Set SN Param"

sn_num = "12345678901234"
comport = "COM61"

# init serial
ser = serial.Serial()

# open serial
ser.port = comport
ser.baudrate = 115200
ser.rts = False
ser.timeout = 5
ser.open()

if ser.isOpen():
    print "Open "+comport+" succeeded."

    # write SN
    print "write SN : " + sn_num
    ser.write(set_sn_cmd)
    sleep(0.05)
    ser.write("1A00".decode("hex")+sn_num)
    print ser.read(4)

    #read SN
    ser.write(get_sn_cmd)
    sleep(0.05)
    r_sn = ser.read(16)[2:]
    print "read SN : " + r_sn

    #close COM
    ser.close()
    print "Close "+comport+" succeeded."