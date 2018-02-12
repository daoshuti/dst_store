@echo off
echo ======================================
echo ===   FFBM mode to Normal mode     ===
echo ======================================
echo.
echo wait for devices ... ...
adb wait-for-devices
echo adb devices ... ...
adb devices
echo adb reboot bootloader ... ...
adb reboot bootloader
echo fastboot erase misc ... ...
fastboot erase misc
echo Rebooting ... ...
fastboot reboot
echo Done.
pause
