#!/usr/bin/env python
# -*- coding=utf8 -*-
"""
# Author: wanghan
# Created Time : 2018/4/16 11:43:56
# File Name: download_key.py
# Description:
"""
import os
import sys
import urllib
import re

# Settings
url_prefix = 'http://api.staging.miglass.mi.com/bootloader/key?id='
DownloadPath = './xiaomi_vr_key/'

# Functions
def Schedule(a,b,c):
    '''''
    a:已经下载的数据块
    b:数据块的大小
    c:远程文件的大小
   '''
    per = 100.0 * a * b / c
    if per > 100 :
        per = 100
    print '%.2f%%' % per

def main(argv):
    # 传参检查，若没有传参，报错退出
    if len(argv)<=0:
        print "Input key word, please."
        exit(1);
    elif len(argv)>1:
        print "The argv error."
    #选取命令行传入的第一个参数（这里是第0个）
    #因为命令行传参以空格分隔，所以如果关键字中有空格，命令行传参时需要用双引号或者单引号括起来
    f = open(argv[0])
    for line in f :
        VR_APSN = line
        print line
        VR_APSN_argv = re.findall(r"([0-9]{5})/([0-9]{8})",VR_APSN)
        VR_APSN_M = VR_APSN_argv[0][0]+'M'+VR_APSN_argv[0][1]
        url = url_prefix+VR_APSN
        if not (os.path.exists(DownloadPath)):
            os.makedirs(DownloadPath)
        local = os.path.join(DownloadPath,"unlock-"+VR_APSN_M+".bin")
        #urllib.urlretrieve(url,local,Schedule)
        urllib.urlretrieve(url,local,None)


# __name__是当前模块名
# __main__是模块被直接运行时的模块名
# if __name__ == '__main__': 表示当模块被用户直接运行时
if __name__ == '__main__':
    # sys.argv[]获得命令行参数
    # 1后面的冒号表示列表的切片操作，即命令行的参数组成一个list，切取这个list的第1个参数到最后一个参数
    # 这时sys.argv[]返回的是一个list
    print(sys.argv)
    main(sys.argv[1:])
