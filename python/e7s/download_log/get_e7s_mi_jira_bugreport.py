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

LIST_PATH = 'list.txt'
DOWNLOAD_PATH = 'download'

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
    os.system('mkdir ' + DOWNLOAD_PATH)
    for loger in download_list:
        if loger[1] == '\r\n':
            print(loger[0] + ',Don\'t have log.')
        else:
            local_cmdline = 'mkdir ' + os.path.join(DOWNLOAD_PATH,loger[0])
            os.system(local_cmdline)
            local_dl_path_str = os.path.join(os.path.join(DOWNLOAD_PATH,loger[0]),'batchlog.zip')
            local_dl_url_str = loger[1]
            print(loger[0] + ',Created log : ' + local_dl_path_str)
            print('[URL] ' + local_dl_url_str)
            urllib.urlretrieve(local_dl_url_str, local_dl_path_str, None)


