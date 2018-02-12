@echo off
rem set /p APSN=Please input APSN:
for /f "delims=" %%i in ( 'adb shell cat persist/SYSTEM_SN') do set MYAPSN=%%i

adb reboot bootloader
fastboot getvar serialno
fastboot oem set-serial-number %MYAPSN%
fastboot reboot-bootloader
timeout /t 5 /nobreak
fastboot getvar serialno
echo 按任意键重启Headset
pause > nul
fastboot reboot
echo 按任意键退出
pause > nul