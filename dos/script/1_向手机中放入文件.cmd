@echo off
echo -------------------------------------------------------
echo 1. 默认放在手机 /sdcard/Download/ 目录下
echo 2. 文件路径中不要有中文
echo -------------------------------------------------------
echo.
set /p PUSH_FILE=请把文件拖进命令提示符，并回车:
echo.
adb push -p %PUSH_FILE% /sdcard/Download/
echo.
pause