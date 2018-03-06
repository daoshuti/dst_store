@echo off

rem ======================================
rem              Settings
rem ======================================

set LOG_DIR_NAME=LOGS

for /f "tokens=2 delims==" %%a in ('wmic path win32_operatingsystem get LocalDateTime /value') do (
  set today=%%a
)
set Today_All=%today:~0,14%
set Today_Date=%today:~0,8%
set Today_Time=%today:~8,6%

set SCREENSHOT=screenshot_%Today_Date%_%Today_Time%.png

:: The current log save path
set LOG_PATH=.\%LOG_DIR_NAME%\%Today_Date%_%Today_Time%

rem ======================================
rem             Make directory
rem ======================================
if not exist %LOG_DIR_NAME% (
	mkdir .\%LOG_DIR_NAME%
)
if not exist %LOG_PATH% (
	mkdir .\%LOG_PATH%
)

rem ======================================
rem               Save log
rem ======================================

echo Wait for Devices ...
adb wait-for-device
adb root
adb wait-for-device

:: wakeup devices
adb shell input keyevent KEYCODE_WAKEUP

echo Save kernel log ...
adb shell dmesg > %LOG_PATH%\kernel.log

echo Save logcat all log ...
adb logcat -d -b all -v time > %LOG_PATH%\logcat_all.log

:: save screenshot
adb shell /system/bin/screencap -p /sdcard/screenshot.png
adb pull /sdcard/screenshot.png %LOG_PATH%\%SCREENSHOT%

rem ======================================
rem        Save device information
rem ======================================
echo Save device information...
echo ---------------------------------------------->%LOG_PATH%/device_info.txt
echo               DEVICES INFORMATION             >>%LOG_PATH%/device_info.txt
echo ---------------------------------------------->>%LOG_PATH%/device_info.txt
echo. >>%LOG_PATH%/device_info.txt
echo === Current machine time === >> %LOG_PATH%/device_info.txt
echo. >>%LOG_PATH%/device_info.txt
adb shell date >> %LOG_PATH%/device_info.txt
echo. >>%LOG_PATH%/device_info.txt
echo === Total boot time === >> %LOG_PATH%/device_info.txt
echo. >>%LOG_PATH%/device_info.txt
adb shell uptime >> %LOG_PATH%/device_info.txt
echo. >>%LOG_PATH%/device_info.txt
echo === Software version === >> %LOG_PATH%/device_info.txt 
echo. >>%LOG_PATH%/device_info.txt
adb shell "getprop | grep version" >> %LOG_PATH%/device_info.txt
echo. >>%LOG_PATH%/device_info.txt

pause