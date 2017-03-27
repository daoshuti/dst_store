#!/usr/bin/python
# -*- coding=utf8 -*-
"""
# Author: wanghan
# Created Time : 2017年03月27日 16:53:19
# File Name: function.py
# Description: 利用求根公式计算一元二次方程的解
# 		ax^2 + bx + c = 0
"""
import math

def quadratic(a,b,c):
	if not isinstance(a,(int,float)) | isinstance(b,(int,float)) | isinstance(c,(int,float)):
		raise TypeError('Wrong Type inputing!')
	else:
		delta = b*b - 4*a*c
		if delta > 0:
			x1 = (-b + math.sqrt(delta))/(2*a)
			x2 = (-b - math.sqrt(delta))/(2*a)
			return x1,x2
		elif delta == 0:
			return -b/(2*a)
		else:
			print('方程无解')
			return

"""
测试结果应为:
print(quadratic(2, 3, 1)) # => (-0.5, -1.0)
print(quadratic(1, 4, 4)) # => (-2.0)
print(quadratic(1, 3, 4)) # => 方程无解
"""
test1 = quadratic(2, 3, 1)
print(test1)
test2 = quadratic(1, 4, 4)
print(test2)
test3 = quadratic(1, 3, 4)
print(test3)
