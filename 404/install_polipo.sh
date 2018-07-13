#!/bin/bash
# Author: wanghan
# Created Time : 2018年07月13日 星期五 16时10分23秒
# File Name: install_polipo.sh
# Description:

BASE_PATH=$(cd `dirname $0`; pwd)

echo Install polipo ..
sudo apt-get install polipo
sudo cp ${BASE_PATH}/etc_polipo_config.backup /etc/polipo/config

echo Start polipo ...
sudo service polipo restart
if [ $? != 0 ]; then
    echo Failure to the polipo execute!!!
    exit 1
fi

#export http_proxy="http://127.0.0.1:8123"
echo export http_proxy=\"http://127.0.0.1:8123\"
#export https_proxy="https://127.0.0.1:8123"
echo export https_proxy=\"https://127.0.0.1:8123\"

echo Done.
