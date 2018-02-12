@echo off

set LOG_DIR_NAME=LOG
set /p APSN_NUM=Please input APSN:
set /p TSN_NUM=Please input TSN:

rem settings
for /f "tokens=2 delims==" %%a in ('wmic path win32_operatingsystem get LocalDateTime /value') do (
  set today=%%a
)
set Today_All=%today:~0,14%
set Today_Day=%today:~0,8%
set Today_Time=%today:~8,6%
set LOG_PATH=.\%LOG_DIR_NAME%\%Today_Day%_%Today_Time%_log


rem MKDIR
if not exist %LOG_DIR_NAME% (
	mkdir %LOG_DIR_NAME%
)
if not exist %LOG_PATH% (
	mkdir %LOG_PATH%
)

rem save log
echo Waiting to connect VR device ...
adb wait-for-device
echo Root ...
adb root
echo Get the log in SD card ...
adb pull /sdcard/log %LOG_PATH%\sdcard
echo Save kernel log ...
adb shell dmesg > %LOG_PATH%\kernel.log
echo Save logcat main log ...
adb logcat -d -b main   > %LOG_PATH%\logcat_main.log
echo Save logcat system log ...
adb logcat -d -b system > %LOG_PATH%\logcat_system.log
echo Save logcat radio log ...
adb logcat -d -b radio  > %LOG_PATH%\logcat_radio.log
echo Save logcat events log ...
adb logcat -d -b events > %LOG_PATH%\logcat_events.log
echo Save logcat crash log ...
adb logcat -d -b crash  > %LOG_PATH%\logcat_crash.log
echo Save logcat all log ...
adb logcat -d -b all -v time > %LOG_PATH%\logcat_all.log

rem Save device infomation
echo Save device infomation...
echo ---------------------------------------------->%LOG_PATH%/device_info.txt
echo               PRODUCT INFOMATION              >>%LOG_PATH%/device_info.txt
echo ---------------------------------------------->>%LOG_PATH%/device_info.txt
echo [APSN]>>%LOG_PATH%/device_info.txt 
echo %APSN_NUM%>>%LOG_PATH%/device_info.txt 
echo [TSN]>>%LOG_PATH%/device_info.txt 
echo %TSN_NUM%>>%LOG_PATH%/device_info.txt 
echo ---------------------------------------------->>%LOG_PATH%/device_info.txt
echo               DEVICES INFOMATION              >>%LOG_PATH%/device_info.txt
echo ---------------------------------------------->>%LOG_PATH%/device_info.txt
adb shell getprop >> %LOG_PATH%/device_info.txt

echo Done.
pause