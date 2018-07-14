#!/usr/bin/env python
# -*- coding=utf8 -*-
"""
# Author: wanghan
# Created Time : 2018年06月13日 星期三 16时13分02秒
# File Name: del_device.py
# Description:
"""
import glob
import os
import sys

def get_vendor_and_product_ids(uevent_path):
    # Get the product and product IDs from uevent node
    ids = list()
    with open(uevent_path, 'r') as uevent_file:
        lines = uevent_file.readlines()
        for line in lines:
            line = line.strip()
            if line.startswith('PRODUCT'):
                ids = line.split('=')[1].split('/')
                break
    uevent_file.close()
    return ids

def get_default_edl_device():
    serial_devices = glob.glob('/sys/bus/usb-serial/devices/*')
    print(serial_devices)
    edl_device = None
    for device in serial_devices:
        basedir = os.path.dirname(os.path.realpath(device))
        uevent_path = os.path.join(basedir, 'uevent')
        ids = get_vendor_and_product_ids(uevent_path)
        if ids[0] == '5c6' and ids[1] == '9008':
            edl_device = device
            break
    return None if edl_device is None else os.path.join(os.sep, 'dev', os.path.basename(edl_device))

if __name__=='__main__':
    device = get_default_edl_device()
    print(device)
