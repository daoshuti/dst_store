#!/usr/bin/python
# -*- coding=utf8 -*-
"""
# Author: wanghan
# Created Time : 2017年03月27日 17:43:27
# File Name: 默认参数.py
# Description:
"""
def power(x,n=2):
	s = 1
	while n > 0:
		s = s*x
		n = n - 1
	return s

print(power(2))
