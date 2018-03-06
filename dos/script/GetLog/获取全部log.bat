@echo off

set LOG_DIR_NAME=LC_LOG
for /f "delims=" %%i in ( 'adb shell cat persist/SYSTEM_SN') do set MYAPSN=%%i

rem settings
for /f "tokens=2 delims==" %%a in ('wmic path win32_operatingsystem get LocalDateTime /value') do (
  set today=%%a
)
set Today_All=%today:~0,14%
set Today_Day=%today:~0,8%
set Today_Time=%today:~8,6%
set LOG_PATH=.\%LOG_DIR_NAME%\%MYAPSN%_%Today_Day%_%Today_Time%


rem MKDIR
if not exist %LOG_DIR_NAME% (
	mkdir .\%LOG_DIR_NAME%
)
if not exist %LOG_PATH% (
	mkdir .\%LOG_PATH%
)

rem save log
echo Wait for VR Devices ...
adb wait-for-device
adb root
adb wait-for-device
if not exist %LOG_PATH%\runin (
	mkdir %LOG_PATH%\runin
	adb pull /data/data/com.longcheertel.runintest/RuninTestII %LOG_PATH%\runin
	adb pull /data/data/com.longcheertel.runintest/shared_prefs/com.longcheertel.runintest_preferences.xml %LOG_PATH%\runin
)

if not exist %LOG_PATH%\sdcard (
	mkdir %LOG_PATH%\sdcard
	adb pull /sdcard/log %LOG_PATH%\sdcard
)
if not exist %LOG_PATH%\persist (
	mkdir %LOG_PATH%\persist
	adb pull /persist %LOG_PATH%\persist
)
if not exist %LOG_PATH%\tombstones (
	mkdir %LOG_PATH%\tombstones
	adb pull /data/tombstones %LOG_PATH%\tombstones
)
if not exist %LOG_PATH%\tempcal (
	mkdir %LOG_PATH%\tempcal
	adb pull /data/tmp/tempcal %LOG_PATH%\tempcal
)

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

rem Save device information
echo Save device information...
echo ---------------------------------------------->%LOG_PATH%/device_info.txt
echo               PRODUCT INFORMATION             >>%LOG_PATH%/device_info.txt
echo ---------------------------------------------->>%LOG_PATH%/device_info.txt

echo [Current Time] >> %LOG_PATH%/device_info.txt
adb shell date >> %LOG_PATH%/device_info.txt
echo. >>%LOG_PATH%/device_info.txt
echo [Up Time] >> %LOG_PATH%/device_info.txt
adb shell uptime >> %LOG_PATH%/device_info.txt
echo. >>%LOG_PATH%/device_info.txt
echo [LC Version]>> %LOG_PATH%/device_info.txt 
adb shell getprop ro.build.version.internal >> %LOG_PATH%/device_info.txt
echo. >>%LOG_PATH%/device_info.txt
echo [SN]>> %LOG_PATH%/device_info.txt 
adb shell getprop sys.nv.serialno >> %LOG_PATH%/device_info.txt
echo. >>%LOG_PATH%/device_info.txt
echo [APSN]>> %LOG_PATH%/device_info.txt 
adb shell cat persist/SYSTEM_SN >> %LOG_PATH%/device_info.txt
echo. >>%LOG_PATH%/device_info.txt
echo. >>%LOG_PATH%/device_info.txt

echo ---------------------------------------------->>%LOG_PATH%/device_info.txt
echo               DEVICES INFORMATION             >>%LOG_PATH%/device_info.txt
echo ---------------------------------------------->>%LOG_PATH%/device_info.txt
adb shell getprop >> %LOG_PATH%/device_info.txt

pause