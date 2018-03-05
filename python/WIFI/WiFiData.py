#!/usr/bin/python
# -*- coding: UTF-8 -*- 

import os
import sys
import time
import re

class device_data(object):
    def __init__(self,apsn_num):
        self.apsn = apsn_num
        self.ble = ble_data()
        self.wifi0 = wifi_data()
        self.wifi1 = wifi_data()

class ble_data(object):
    def __init__(self):
        self.Power=[]
        self.RSSI=[]

class wifi_data(object):
    def __init__(self):
        self.Power=[]
        self.RSSI=[]


# 【重要】 该函数为脚本的核心函数
# 功能：该函数用来处理数据
# switcher字典中列表的含义如下：
#       1. 处理数据的函数
#           i. 若为None表示为寻找的关键字，找到后仅打印信息就结束操作
#           ii. 若为函数，则交由相应函数处理数据
#       2. 关键字
#       3. 存放数据的列表
#       4. 数据在列表的索引（即位置）
def data_processing(step, linestring, device_list):
    switcher = {
        0:[None, "NSFT_BlueTooth_Test_Result"],
        1:[None, "Item"],
        2:[insert_data, "BLE Power Avg", device_list[-1].ble.Power, 0],#"1, BLE Power Avg,"
        3:[insert_data, "BT RX RSSI", device_list[-1].ble.RSSI, 0],#"3, BT RX RSSI,"
        4:[None, "NSFT_WIFI_11n_Result"],
        5:[None, "Item"],
        6:[insert_data, "PowerAvg", device_list[-1].wifi0.Power, 0],#"5, PowerAvg,"
        7:[insert_data, "WLAN RX RSSI", device_list[-1].wifi0.RSSI, 0],#"7, WLAN RX RSSI,"
        8:[insert_data, "PowerAvg", device_list[-1].wifi0.Power, 1],#"9, PowerAvg,"
        9:[insert_data, "WLAN RX RSSI", device_list[-1].wifi0.RSSI, 1],#"11, WLAN RX RSSI,*"
        10:[insert_data, "PowerAvg", device_list[-1].wifi0.Power, 2],#"13, PowerAvg,*"
        11:[insert_data, "WLAN RX RSSI", device_list[-1].wifi0.RSSI, 2],#"15, WLAN RX RSSI,*"
        12:[insert_data, "PowerAvg", device_list[-1].wifi0.Power, 3],#"17, PowerAvg,*"
        13:[insert_data, "WLAN RX RSSI", device_list[-1].wifi0.RSSI, 3],#"19, WLAN RX RSSI,*"
        14:[insert_data, "PowerAvg", device_list[-1].wifi0.Power, 4],#"21, PowerAvg,*"
        15:[insert_data, "WLAN RX RSSI", device_list[-1].wifi0.RSSI, 4],#"23, WLAN RX RSSI,*"
        16:[None, "NSFT_WIFI_11n_Result"],#"NSFT_WIFI_11n_Result"
        17:[None, "Item"],
        18:[insert_data, "PowerAvg", device_list[-1].wifi1.Power, 0],#"25, PowerAvg,*"
        19:[insert_data, "WLAN RX RSSI", device_list[-1].wifi1.RSSI, 0],#"27, WLAN RX RSSI,*"
        20:[insert_data, "PowerAvg", device_list[-1].wifi1.Power, 1],#"29, PowerAvg,*"
        21:[insert_data, "WLAN RX RSSI", device_list[-1].wifi1.RSSI, 1],#"31, WLAN RX RSSI,*"
        22:[insert_data, "PowerAvg", device_list[-1].wifi1.Power, 2],#"33, PowerAvg,*"
        23:[insert_data, "WLAN RX RSSI", device_list[-1].wifi1.RSSI, 2],#"35, WLAN RX RSSI,*"
        24:[insert_data, "PowerAvg", device_list[-1].wifi1.Power, 3],#"37, PowerAvg,*"
        25:[insert_data, "WLAN RX RSSI", device_list[-1].wifi1.RSSI, 3],#"39, WLAN RX RSSI,*"
        26:[insert_data, "PowerAvg", device_list[-1].wifi1.Power, 4],#"41, PowerAvg,*"
        27:[insert_data, "WLAN RX RSSI", device_list[-1].wifi1.RSSI, 4],#"43, WLAN RX RSSI,*"
        28:[switcher_end, None, None, None],
    }
    if step >= len(switcher)+1 :
        return 0
    keywordlist = switcher.get(step, "nothing")
    if keywordlist[0] == None:
        keyword = keywordlist[1]
        return analysis(step, linestring, keyword)
    else:
        func = keywordlist[0]
        keyword = keywordlist[1]
        if len(keywordlist) >= 2 :
            datalist = keywordlist[2]
            index = keywordlist[3]
        else:
            datalist = index = None
        return func(step, datalist, index, linestring, keyword)

def analysis(step, linestring, keyword):
    if None == re.search(keyword, linestring):
        return step
    print "step" + str(step) + " : " + keyword
    return step + 1

def switcher_end(step, datalist, index, linestring, keyword):
    return step

def insert_data(step, datalist, index, linestring, keyword):
    if None == re.search(keyword, linestring):
        #print linestring
        return step
    temp = linestring.split(',')[5]
    datalist.insert(index, temp)
    print "step" + str(step) + " : " + keyword + " --- " + datalist[index]
    return step + 1

if __name__ == '__main__':

    #########
    # Setting
    #########
    device_list = []
    excelname = "Result.csv"

    ##########
    # Get Data
    ##########

    # get dirs
    list_dirs = os.walk(".")

    # get files
    for dirpath, dirname, filename in list_dirs:
        for f in filename:
            if f.endswith("_PASS.csv"):
                #print f #打印文件名
                APSN_number = re.findall(r"(.{14})_\d+?_PASS.csv",f).pop()
                device_list.append(device_data(APSN_number))
                print "APSN :" + APSN_number #打印APSN
                step = 0
                for line in open(f, "r"):
                    step = data_processing(step, line, device_list)
                print "-----------------------------------"

    #############
    # Wirte Excel
    #############

    # create file
    ft = open(excelname, "w")
    ft.write(",,Average,APSN\n")

    # APSN
    ft.write(",,")
    for device in device_list:
        ft.write("," + device.apsn)
    ft.write("\n")
    
    # BLE
    ft.write("BLE")
    # BLE Power
    ft.write(",Power,")
    for device in device_list:
        ft.write("," + device.ble.Power[0])
    ft.write("\n")
    # BLE RSSI
    ft.write(",RSSI,")
    for device in device_list:
        ft.write("," + device.ble.RSSI[0])
    ft.write("\n")

    # WIFI_0
    ft.write("WIFI_0")
    # WIFI_0 Power Channel 1
    ft.write(",Power/1,")
    for device in device_list:
        ft.write("," + device.wifi0.Power[0])
    ft.write("\n")
    # WIFI_0 Power Channel 7
    ft.write(",Power/7,")
    for device in device_list:
        ft.write("," + device.wifi0.Power[1])
    ft.write("\n")
    # WIFI_0 Power Channel 13
    ft.write(",Power/13,")
    for device in device_list:
        ft.write("," + device.wifi0.Power[2])
    ft.write("\n")
    # WIFI_0 Power Channel 36
    ft.write(",Power/36,")
    for device in device_list:
        ft.write("," + device.wifi0.Power[3])
    ft.write("\n")
    # WIFI_0 Power Channel 165
    ft.write(",Power/165,")
    for device in device_list:
        ft.write("," + device.wifi0.Power[4])
    ft.write("\n")
    # WIFI_0 RSSI Channel 1
    ft.write(",RSSI/1,")
    for device in device_list:
        ft.write("," + device.wifi0.Power[0])
    ft.write("\n")
    # WIFI_0 RSSI Channel 7
    ft.write(",RSSI/7,")
    for device in device_list:
        ft.write("," + device.wifi0.Power[1])
    ft.write("\n")
    # WIFI_0 RSSI Channel 13
    ft.write(",RSSI/13,")
    for device in device_list:
        ft.write("," + device.wifi0.Power[2])
    ft.write("\n")
    # WIFI_0 RSSI Channel 36
    ft.write(",RSSI/36,")
    for device in device_list:
        ft.write("," + device.wifi0.Power[3])
    ft.write("\n")
    # WIFI_0 RSSI Channel 165
    ft.write(",RSSI/165,")
    for device in device_list:
        ft.write("," + device.wifi0.Power[4])
    ft.write("\n")

    # WIFI_1
    ft.write("WIFI_1")
    # WIFI_1 Power Channel 1
    ft.write(",Power/1,")
    for device in device_list:
        ft.write("," + device.wifi1.Power[0])
    ft.write("\n")
    # WIFI_1 Power Channel 7
    ft.write(",Power/7,")
    for device in device_list:
        ft.write("," + device.wifi1.Power[1])
    ft.write("\n")
    # WIFI_1 Power Channel 13
    ft.write(",Power/13,")
    for device in device_list:
        ft.write("," + device.wifi1.Power[2])
    ft.write("\n")
    # WIFI_1 Power Channel 36
    ft.write(",Power/36,")
    for device in device_list:
        ft.write("," + device.wifi1.Power[3])
    ft.write("\n")
    # WIFI_1 Power Channel 165
    ft.write(",Power/165,")
    for device in device_list:
        ft.write("," + device.wifi1.Power[4])
    ft.write("\n")
    # WIFI_1 RSSI Channel 1
    ft.write(",RSSI/1,")
    for device in device_list:
        ft.write("," + device.wifi1.Power[0])
    ft.write("\n")
    # WIFI_1 RSSI Channel 7
    ft.write(",RSSI/7,")
    for device in device_list:
        ft.write("," + device.wifi1.Power[1])
    ft.write("\n")
    # WIFI_1 RSSI Channel 13
    ft.write(",RSSI/13,")
    for device in device_list:
        ft.write("," + device.wifi1.Power[2])
    ft.write("\n")
    # WIFI_1 RSSI Channel 36
    ft.write(",RSSI/36,")
    for device in device_list:
        ft.write("," + device.wifi1.Power[3])
    ft.write("\n")
    # WIFI_1 RSSI Channel 165
    ft.write(",RSSI/165,")
    for device in device_list:
        ft.write("," + device.wifi1.Power[4])
    ft.write("\n")

    # flush and close file
    ft.flush()
    ft.close()
