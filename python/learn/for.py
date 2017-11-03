#!/usr/bin/python
#-*- coding : utf-8 -*-

# for in 循环例子1
names = ['Michael', 'Bob', 'Tracy']
for name in names:
    print(name)
	
# for in 循环例子2
sum = 0
for x in [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]:
    sum = sum + x
print(sum)

# 关于range()函数，它会自动生成序列
# >>> list(range(5))
# [0, 1, 2, 3, 4]

# for in 循环例子3
sum = 0
for x in range(101):
    sum = sum + x
print(sum)