#!/usr/bin/python
#-*- coding : utf-8 -*-

# while 循环例子1
# 计算100以内所有奇数之和
sum = 0
n = 99
while n > 0:
    sum = sum + n
    n = n - 2
print(sum)
