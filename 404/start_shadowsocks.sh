#!/bin/bash
# Author: wanghan
# Created Time : 2018年07月02日 星期一 11时49分20秒
# File Name: start_shadowsocks.sh
# Description:

BASE_PATH=$(cd `dirname $0`; pwd)
LOG_PATH=${BASE_PATH}/my_shadowsocks.log
echo The shadowsocks config file is ${BASE_PATH}/shadowsocks.json.
echo Save log in ${LOG_PATH}.
if [ -f ${BASE_PATH}/shadowsocks.json ]; then
    nohup sslocal -c ${BASE_PATH}/shadowsocks.json > ${LOG_PATH} 2>&1 &
    #sslocal -c ${BASE_PATH}/shadowsocks.json
    if [ $? != 0 ]; then
        echo Failure to the sslocal execute!!!
        exit 1
    fi
else
    echo "The '${BASE_PATH}/shadowsocks.json' file does not exist!"
    exit 78 #EX_CONFIG
fi
echo Start polipo ...
sudo service polipo restart
if [ $? != 0 ]; then
    echo Failure to the polipo execute!!!
    exit 1
export http_proxy="http://127.0.0.1:8123"
export https_proxy="https://127.0.0.1:8123"

