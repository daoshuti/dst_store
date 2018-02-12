@echo off
adb shell dumpsys battery
echo -------------------------------
echo 电量百分比：
adb shell cat /sys/class/power_supply/battery/capacity
echo.
pause