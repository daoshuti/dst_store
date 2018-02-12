@echo off
adb root
set /p APK_PATH=把apk拖进cmd窗口:
echo.
adb install -r -g %APK_PATH%
echo.
echo 若显示Success,则安装成功；否则，请重新安装
pause