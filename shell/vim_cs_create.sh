#!/bin/bash
# Author: wanghan
# Created Time : 2017年04月12日 星期三 16时06分03秒
# File Name: create_cscope.sh
# Description:

# 定义变量
PWD=`pwd` #获取当前路径
DIR_NAME=${PWD##*/} #获取当前目录的名字

# 生成cscope.out文件
run()
{
	find ${PWD} -type f \( -name "*.h" -o -name "*.c" -o -name "*.cpp" -o  	\
		-iname "*.s" -o -iname "*.cc" -o -name "*.java" \) > ${PWD}/${DIR_NAME}.files
	cscope -bkq -i ${DIR_NAME}.files -f ${DIR_NAME}.out
}

# 主程序
main()
{
	run
}


main

