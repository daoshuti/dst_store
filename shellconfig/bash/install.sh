#!/bin/bash
# Author: wanghan
# Created Time : Wed May 17 22:03:06 2017
# File Name: install.sh
# Description:

function main()
{
	if [ -f ./userdata ]; then
		cat ./userdata >> ~/.bashrc
	fi
}

# execute
main
