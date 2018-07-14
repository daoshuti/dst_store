#!/bin/bash
# Author: wanghan
# Created Time : 2018年06月13日 星期三 15时41分38秒
# File Name: dump_sdm660_partiton.sh
# Description:

echo "**************************************************"
echo "*                                                *"
echo "*               Dump Sdm660 Partiton             *"
echo "*                                                *"
echo "**************************************************"
echo Plase input COM port number:
port=`python get_edl_device.py`
echo Port is ${port}

# Sending prog_emmc_firehose_Sdm660_ddr.elf to device
echo ----------------------------------------------
echo 发送 prog_emmc_firehose_Sdm660_ddr.elf 文件到设备
echo ----------------------------------------------
./kickstart -s 13:prog_emmc_firehose_Sdm660_ddr.elf -p ${port}

echo ----------------------------------------------
echo 等待并确认发送完成 3s
echo ----------------------------------------------
sleep 3

# echo ----------------------------------------------
# echo 发送 rawprogram_upgrade.xml 文件到设备
# echo ----------------------------------------------
# fh_loader --memoryname=emmc --sendxml=rawprogram_upgrade.xml --convertprogram2read --port=${port} --mainoutputdir=out

echo ----------------------------------------------
echo 发送 rawprogram0.xml 文件到设备
echo ----------------------------------------------
./fh_loader --memoryname=emmc --sendxml=rawprogram0.xml --convertprogram2read --port=${port} --mainoutputdir=out


echo
echo
echo
echo "**************************************************"
echo "*                                                *"
echo "*                     Done.                      *"
echo "*                     完成！                     *"
echo "*                                                *"
echo "**************************************************"
echo
echo
echo
