@echo off
adb wait-for-device
adb root
adb push charger_test.sh /data/local/tmp/
adb shell chmod a+x /data/local/tmp/charger_test.sh
start
exit 0
rem adb shell 
rem /data/local/tmp/charger_test.sh &
pause