#!/usr/bin/env python
# -*- coding=utf8 -*-
"""
# Author: wanghan
# Created Time : Sun 07 Jan 2018 06:27:32 PM CST
# File Name: DeviceTreeMap.py
# Description: Get Devices Tree Map
"""

import sys
import os

class DeviceTreeMap(object):
    def __init__(self, name, parent = None, level = 0):
        self.name = name
        self.level = level
        self.parent = parent
        self.child = []

    def printChild(self):
        n = 0
        if not self.level == 0:
            if self.level > 1:
                while self.level > n:
                    if len(self.parent.parent.child) > self.parent.parent.child.index(self.parent)+1:
                        if self.level != n+1 :
                            print "|",
                    else:
                        if self.level != n+1 :
                            print " ",
                    n = n + 1
            print "L " + self.name
        else:
            print self.name
        n = 0
        while len(self.child) > n:
            self.child[n].printChild()
            n = n + 1

    def printMap(self):
        print ""
        print "-----------------------------------"
        print ""
        self.printChild()

    def createTreeMap(self, childLevel = 1):
        theChild = None
        for line in open(self.name):
            if line.startswith("#include"):
                dtsiName = line.split()[1].strip('\"')
                theChild = DeviceTreeMap(dtsiName, self, childLevel)
                if not dtsiName.endswith(".h>"):
                    self.child.append(theChild)
                    theChild.createTreeMap(childLevel+1)

if __name__ == '__main__':
    argv = sys.argv[1:]
    if len(argv) <= 0:
        print "Input dts file, please."
        exit(1);
    rootDeviceTree = DeviceTreeMap(argv[0])
    rootDeviceTree.createTreeMap()
    rootDeviceTree.printMap()
