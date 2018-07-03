#!/bin/bash
# Author: wanghan
# Created Time : 2018年07月03日 星期二 11时51分57秒
# File Name: start_polipo.sh
# Description:

echo Start polipo ...
sudo service polipo restart
if [ $? != 0 ]; then
    echo Failure to the polipo execute!!!
    exit 1
fi
echo export http_proxy=\"http://127.0.0.1:8123\"
export http_proxy="http://127.0.0.1:8123"
echo export https_proxy=\"https://127.0.0.1:8123\"
export https_proxy="https://127.0.0.1:8123"

echo Done.

