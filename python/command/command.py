#!/usr/bin/env python
# -*- coding=utf8 -*-
"""
# Author: wanghan
# Created Time : 2018/3/5 14:54:35
# File Name: command.py
# Description:
"""
import os
import sys
import subprocess

if __name__ == '__main__':

    result = os.popen('ping -t www.baidu.com')
    res = result.read()
    for line in res.splitlines():
          print line
    """
    p = subprocess.Popen('ping -t www.baidu.com',shell=True,stdout=subprocess.PIPE)
    out,err = p.communicate()
    for line in out.splitlines():
        print line
    """