@echo off
echo (请先连接头盔到电脑)
echo 查看头盔已绑定的手柄的MAC地址
echo -------
adb shell cat persist/remote_pairing/factory_pairing.txt
echo -------
adb shell getprop persist.remote1
echo -------
pause