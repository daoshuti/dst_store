@echo off
echo ----------------------------------------------
echo 1. 默认从手机 /sdcard/Download/ 目录下抓取文件
echo 2. 中文名字会乱码
echo ----------------------------------------------
echo.
echo 手机/sdcard/Download/路径下的有文件有：
echo.
adb shell ls /sdcard/Download/
echo.
echo ----------------------------------------------
echo.
set /p PULL_FILE=请输入抓取文件的名字:
echo.
adb pull -p /sdcard/Download/%PULL_FILE% .\
pause