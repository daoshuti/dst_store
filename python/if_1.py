#!/usr/bin/python
# -*- coding:utf-8 -*-

print('Please input a number.')
s = input()
age = int(s)

#age = 10

if age >= 18:
	print('your age is',age)
	print('adult')
elif age >=6:
	print('your age is',age)
	print('teenager')
else :
	print('your age is',age)
	print('kid')