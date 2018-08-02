#!/usr/bin/env python
# -*- coding=utf8 -*-
"""
# Author: wanghan
# Created Time : 2018/6/30 15:13:00
# File Name: PsensorDisplayTest.py
# Description:
"""

import os
import re
import sys
import time
import serial

COM_PORT = 'COM37'
DOWNLOAD_TIMEOUT = 5
DEVICE_ID_OF_THE_L_SENSOR_PHONE = '3e0d9bb'
DEVICE_ID_OF_THE_TESTED_PHONE = '3e51865'
LOG_FILE = 'PsensorDisplayTest_{:.0f}.log'.format(time.time())
TOTAL_NUM_OF_TESTS = 100000
TIMEOUT_MAX = 60.0
TIME_THRESHOLD = 5

cur_num_of_test = 0
err_num_of_test = 0
start_time_of_test = 0

# Open log file
f_log = open(LOG_FILE, 'w')

# 将正则表达式编译成Pattern对象
pattern = re.compile(r'^Light.+?Data,.+?:.*?(\d+),.*Conversion:.+?(\d+?.+?\d{6})$')

def output_log(log):
	log_str = time.strftime("%d/%m/%Y") + ' ' + time.strftime("%H:%M:%S") + ' : ' + log
	f_log.write(log_str+'\r\n')
	f_log.flush()
	print(log_str)

def getLightData():
	commandline = 'adb -s ' + DEVICE_ID_OF_THE_L_SENSOR_PHONE + ' shell "sensors_test 1 l | grep Conversion:"'
	result = os.popen(commandline)
	result_str = result.readline()
	lightDataConvertString = re.split(': ',result_str)[2][:-1]
	return float(lightDataConvertString)

def loopTest(frequency):
	global cur_num_of_test,err_num_of_test,start_time_of_test
	count = 0
	while (count < frequency):
		count = count + 1
		output_log('Test Info : No.' + str(cur_num_of_test) + '-' + str(count) + ' times.')
		# Open the shutter
		ser.write("PWM_90\r\n")
		serial_recv = ser.readline()
		output_log('Open the shutter ' + serial_recv)
		# waiting for display_off
		while (1.0 < getLightData()):
			tmp = time.time() - start_time_of_test
			output_log('tmp = ' + str(tmp))
			if ( tmp > TIMEOUT_MAX ):
				output_log('Error: Timeout!')
				return -1
			time.sleep(0.5)
		# Close the shutter
		ser.write("PWM_0\r\n")
		serial_recv = ser.readline()
		output_log('Close the shutter ' + serial_recv)
		since = time.time()
		# waiting for display_on
		while (1.0 > getLightData()):
			tmp = time.time() - start_time_of_test
			output_log('tmp = ' + str(tmp))
			if ( tmp > TIMEOUT_MAX ):
				output_log('Error: Timeout!')
				return -1
			time.sleep(0.5)
		time_elapsed = time.time() - since
		if (time_elapsed > TIME_THRESHOLD):
			err_num_of_test = err_num_of_test + 1
			output_log('Error Info: No.' + str(err_num_of_test) + ' times.')
			adb_command('bugreport > bugreport.log')
			sys.exit(0)
		output_log('Waiting time is {:.0f}s'.format(time_elapsed)) # 打印出来时间
	return None

def adb_command(command):
	commandline = 'adb -s ' + DEVICE_ID_OF_THE_TESTED_PHONE + ' ' + command
	output_log('Exception:' + commandline)
	os.system(commandline)

if __name__ == '__main__':

	# L-sensor Init
	lightData = getLightData()
	output_log('L-sensor Init ' + str(lightData))
	
	# Open serial
	ser = serial.Serial()
	ser.port = COM_PORT
	ser.baudrate = 115200
	ser.timeout = DOWNLOAD_TIMEOUT
	ser.open()
	
	# Device Init
	ser.write("LED_ON\r\n")
	serial_recv = ser.readline()
	output_log(serial_recv)
	raw_input("Press enter to continue.")
	ser.write("LED_OFF\r\n")
	serial_recv = ser.readline()
	output_log(serial_recv)
	raw_input("Press enter to continue.")
	
	# Close the shutter
	ser.write("PWM_0\r\n")
	serial_recv = ser.readline()
	output_log('Close the shutter ' + serial_recv)

	# Global vaiable Init
	cur_num_of_test = 0
	err_num_of_test = 0
	start_time_of_test = 0
	
	while (cur_num_of_test < TOTAL_NUM_OF_TESTS):
		cur_num_of_test = cur_num_of_test + 1
		output_log('\r\n--------------- [ ' + str(cur_num_of_test) + ' ]---------------\r\n')
		# record the time
		start_time_of_test = time.time()
		output_log('start_time_of_test = ' + str(start_time_of_test))
		# Call 112
		output_log('Call to 112')
		if (1.0 > getLightData()):
			adb_command('shell input keyevent KEYCODE_WAKEUP')
			time.sleep(1)
			adb_command('shell input swipe 540 1900 540 800 500')
		adb_command('shell service call phone 1 s16 "112"')
		adb_command('shell input swipe 540 1900 540 1910 500')
		# Loop test the P-sensor
		loopTest(3)
		# End the call
		output_log('End the call')
		adb_command('shell input tap 540 1900')
		# Close the shutter
		ser.write("PWM_0\r\n")
		serial_recv = ser.readline()
		output_log('Close the shutter ' + serial_recv)
		time.sleep(1)
	
	# End of the test
	output_log('\r\n=============================================================\r\n')
	output_log('The total number of test is ' + str(TOTAL_NUM_OF_TESTS) + '.')
	output_log('The error number of test is ' + str(err_num_of_test) + '.')
	output_log('Done.')
	output_log('\r\n=============================================================\r\n')
	raw_input("Press enter to exit.")
	
