#!/usr/bin/env python
# -*- coding=utf8 -*-
"""
# Author: wanghan
# Created Time : 2018年07月17日 星期二 10时53分57秒
# File Name: get_e7s_mi_jira_bugreport.py
# Description:
"""

import os
import sys
import urllib
import re

LIST_PATH = './list.txt'

# parse list.txt
def parse(list_file):
    dl_list = []
    f = open(list_file)
    for line in f:
        dl_list.append(line.split('\t'))
    return dl_list

if __name__ == '__main__':
    download_list = parse(LIST_PATH)
    #print(download_list)
    os.system('mkdir ./download')
    for loger in download_list:
        if loger[1] == '\r\n':
            print(loger[0] + ',Don\'t have log.')
        else:
            os.system('mkdir -p ' + './download/' + loger[0])
            print(loger[0] + ',Created log floder\'' + loger[0] + '\'')
            urllib.urlretrieve(loger[1][:-2], './download/' + loger[0] + '/batchlog.zip', None)
            print(loger[1][:-2] + ' , ' + './download/' + loger[0] + '/batchlog.zip')


