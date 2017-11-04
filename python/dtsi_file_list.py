#!/usr/bin/env python
#-*- coding:utf-8 -*-

#==============================================
#  history:
#          date    author             content
#     2017.3.18  lct.panguangyi        version beta 1.0, created
#==============================================

import sys
import os

#根据开机抓到的0秒开机log，找到Machine: Qualcomm Technologies, Inc.进而找到关键字
#该函数根据关键字找到对应的路径，并返回该路径的值（file_path变量）
def find_dest_intermediate_dtsi_file(key_word):
	file_path = ""
	found_cnt = 0
	#os.path.exists()路径存在则返回True,路径损坏返回False
	#当路径不对时报错
	if not os.path.exists("obj/KERNEL_OBJ/arch/arm64/boot/dts/qcom"):
		print "Error: this script should be put in path out/target/product/<product>/"
		exit(1)
	else:
		# os.walk()遍历目录
			list_dirs = os.walk("obj/KERNEL_OBJ/arch/arm64/boot/dts/qcom")
			#迭代list_dirs
			for dirpath, dirname, filename in list_dirs:
				for f in filename:
					# startswith(".")，如果字符串以"."开头，则返回True
					# endswith("tmp")，如果字符串以"tmp"结尾，则返回True
					if f.startswith(".") and f.endswith("tmp"):
						# os.path.join把目录和文件名合成一个路径
						for line in open(os.path.join("obj/KERNEL_OBJ/arch/arm64/boot/dts/qcom",f)):
							if key_word in line:
								file_path = os.path.join("obj/KERNEL_OBJ/arch/arm64/boot/dts/qcom",f)
								found_cnt = found_cnt+1
			if found_cnt == 1 :
				return file_path
			else :
				print "Error:found "+str(found_cnt)+" file(s) match the key word, check your key word again!"
				exit(1)

# 根据找到的dtsi文件和关键字，找到以来的dts和dtsi文件，并打印到dtsi_xxx.txt文件中
def get_used_dtsi_list(dest,key_word):
	file_list = []
	#根据dest打开文件，并逐行比较
	for line in open(dest):
		#如果某行含有"boot/dts/qcom"字符串,则:
		if "boot/dts/qcom" in line:
			# os.path.split把path分割成目录和文件名组成的tuple，并返回
			# split()拆分字符串，通过制定分隔符对字符串进行切片，并返回分割后的字符串列表
			file_name = os.path.split(line.split()[2].strip('\"'))[1]
			if not file_name in file_list:
				file_list.append(file_name)
	fw=open("dtsi_"+key_word.replace(' ','_')+".txt","w")
	for item in sorted(file_list):
		fw.writelines(item+"\n")
	#关闭文件
	fw.close();
	#replace()函数是替换字符串把' '替换为'_'
	print "Succeed! Save list to dtsi_"+key_word.replace(' ','_')+".txt"




def main(argv):
	# 传参检查，若没有传参，报错退出
	if len(argv)<=0:
		print "Input key word, please."
		exit(1);
	#选取命令行传入的第一个参数（这里是第0个）
	#因为命令行传参以空格分隔，所以如果关键字中有空格，命令行传参时需要用双引号或者单引号括起来
	key_word = argv[0]
	dest_file = find_dest_intermediate_dtsi_file(key_word)
	get_used_dtsi_list(dest_file,key_word)


# __name__是当前模块名
# __main__是模块被直接运行时的模块名
# if __name__ == '__main__': 表示当模块被用户直接运行时
if __name__ == '__main__':
	# sys.argv[]获得命令行参数
	# 1后面的冒号表示列表的切片操作，即命令行的参数组成一个list，切取这个list的第1个参数到最后一个参数
	# 这时sys.argv[]返回的是一个list
	main(sys.argv[1:])
