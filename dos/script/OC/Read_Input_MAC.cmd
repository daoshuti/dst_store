@echo off
rem set /p MAC_ADDR=Please input MAC address : 
rem echo.
rem adb shell am broadcast -a com.longcheer.RECORD_MAC --es MAC %MAC_ADDR%
echo.
echo -------------
set /p=Result: <nul
adb shell getprop sys.btmac.input
set /p=Bond MAC address: <nul
adb shell cat persist/remote_pairing/factory_pairing.txt
echo.
echo.
pause