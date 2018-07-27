#!/usr/bin/env python
# -*- coding=utf8 -*-
"""
# Author: wanghan
# Created Time : 2018年07月23日 14:01:29
# File Name: print.py
# Description:
"""

import os
import sys
import time
#from __future__ import print_function

if __name__ == '__main__':
    #print('hello',end='') # python 3.x
    print'Hello World!',
    sys.stdout.flush()
    time.sleep(1)
    print('\rProcess     ')
    time.sleep(1)
    sys.stdout.flush()
    while True :
        print '\r■■■■■■■■■■ 100%',
        time.sleep(1)
        sys.stdout.flush()
        print '\r■■■■■■■■■  90%',
        time.sleep(1)
        sys.stdout.flush()
        print '\r■■■■■■■■   80%',
        time.sleep(1)
        sys.stdout.flush()
        print '\r■■■■■■■    70%',
        time.sleep(1)
        sys.stdout.flush()
        print '\r■■■■■■     60%',
        time.sleep(1)
        sys.stdout.flush()
        print '\r■■■■■      50%',
        time.sleep(1)
        sys.stdout.flush()
        print '\r■■■■       40%',
        time.sleep(1)
        sys.stdout.flush()
        print '\r■■■        30%',
        time.sleep(1)
        sys.stdout.flush()
        print '\r■■         20%',
        time.sleep(1)
        sys.stdout.flush()
        print '\r■          10%',
        time.sleep(1)
        sys.stdout.flush()
        print '\r            0%',
        time.sleep(1)
        sys.stdout.flush()
