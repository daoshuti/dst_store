@echo off
echo.
echo 若能成功看到设备ID，则说明adb驱动安装成功了,设备也连接上了。
echo.
adb root
echo.
echo 设备ID：
adb devices
echo.

pause