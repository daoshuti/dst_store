#!/usr/bin/python
# -*- coding : utf-8 -*-
# ------------------------------------------
#小明身高1.75，体重80.5kg。
#请根据BMI公式（体重除以身高的平方）帮小明计算他的BMI指数，并根据BMI指数：
#	低于18.5：过轻
#	18.5-25：正常
#	25-28：过重
#	28-32：肥胖
#	高于32：严重肥胖
# ------------------------------------------

#由用户输入身高和体重的信息
print('请输入身高（单位:m）')
temp = input()
height = float(temp)
temp = input('请输入体重（单位:kg）')
weight = float(temp)

print('--------------------')

# 定义小明身高体重
#height = 1.75 
#weight = 80.5 

# 根据bmi公式计算
bmi = weight / ( height * height )

# 判断小明的bmi标准
if bmi > 32:
	print('bmi is ',bmi)
	print('体重属于【严重肥胖】')
elif bmi >= 28:
	print('bmi is ',bmi)
	print('体重属于【肥胖】')
elif bmi >= 25:
	print('bmi is ',bmi)
	print('体重属于【过重】')
elif bmi >= 18.5:
	print('bmi is ',bmi)
	print('体重属于【正常】')
else:
	print('bmi is ',bmi)
	print('体重属于【过轻】')

print('--------------------')	
print('测评结束，欢迎使用！')