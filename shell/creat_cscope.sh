#!/bin/bash
#coding = utf-8

# 定义变量
TARGET_DIR=""
PWD=`pwd`
CHID_DIR=""
CHID_NUM=0

# 初始化
init()
{
    echo "请输入源码所在目录(如 /home/wanghan/arm11 )："
	read TARGET_DIR 
	echo "TARGET_DIR = ${TARGET_DIR}"
	if [ -d ${TARGET_DIR} ];then
		echo "请输入需要生成cscope文件的子目录（回车默认全选）："
		read CHID_DIR 
		#判断用户输入几个变量
		CHID_NUM=`echo $CHID_DIR | wc -w`
		if [ ${CHID_NUM} -ne 0 ] ; then
			for test_dir in ${CHID_DIR}
			do
				if ! [ -d "${test_dir}" ];then
					echo "输入有误：${test_dir}不是目录文件!"
					exit
				fi
			done
		fi
	else
		echo "输入错误：${TARGET_DIR} 不是目录文件！"
		exit
	fi
}

# 生成cscope.out文件
run()
{
	if [ ${CHID_NUM}  == 0 ];then
		search_dir=("bionic" "bootable" "build" "developers" "device" 		\
					"external" "frameworks" "hardware" "kernel" "libcore" 	\
					"libnativehelper" "packages" "pdk" "prebuilts" 			\
					"system" "tools" "vendor")
		rm cscope/load.vim 
	else
		search_dir=${CHID_DIR}
	fi

	for dir_name in ${search_dir[@]}
	do
		echo Indexing ${dir_name} ...
		find ${TARGET_DIR}/${dir_name} 									\
			-type f \( -name "*.h" -o -name "*.c" -o -name "*.cpp" -o  	\
						-iname "*.s" -o -iname "*.cc" -o -name "*.java" \
					\) > ${PWD}/${dir_name}.files
		cscope -bkq -i ${dir_name}.files -f ${dir_name}.out
		if [ ${CHID_NUM} == 0 ];then
			echo ":@cs add ${PWD}/${dir_name}.out" >load.vim
		fi
	done
}

# 主程序
main()
{
	init
	run
    #echo "alias vims='vim -S ${PWD}/load.vim'" >> ~/.bashrc
}


main
