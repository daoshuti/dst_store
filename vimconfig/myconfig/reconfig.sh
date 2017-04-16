#!/bin/bash
# Author: wanghan
# Created Time : Fri 14 Apr 2017 06:20:01 PM CST
# File Name: reconfig.sh
# Description:

#删除vim的配置   
remove_vimconfig()
{
	echo "Remove vimconfig file..."
	rm -rf $HOME/.vim
	rm $HOME/.vimrc
}

#还原vim配置
reconfig_vim()
{
	echo "Reconfig your vim now !"
	cp $HOME/.bakvim/.vim/  $HOME -a 
	cp $HOME/.bakvim/.vimrc $HOME
}

#主函数
main()
{
	remove_vimconfig
	reconfig_vim
	echo "Done."
}

#执行脚本
main
