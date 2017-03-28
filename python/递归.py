#!/usr/bin/python
# -*- coding=utf8 -*-
"""
# Author: wanghan
# Created Time : Tue 28 Mar 2017 11:12:37 PM CST
# File Name: 递归.py
# Description:
"""

def move(n, a, b, c):
	if n == 1:
		#A上面只有一个盘子
		#将A上的盘子放在C上
		print('move', a, '-->', c)
	else:
		#A上有N(N>1)个盘子
		#1.把A上面的N-1个盘子借助C放到B上
		move(n-1, a, c, b)
		#2.把A最下面的盘子放在C上
		print('move', a, '-->', c)
		#3.把B上面所有的盘子(N-1个)，放在C上
		move(n-1, b, a, c)

n = int(input('请输入汉诺塔的层数:'))
move(n, 'A', 'B', 'C')

