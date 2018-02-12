@echo off
rem settings
for /f "tokens=2 delims==" %%a in ('wmic path win32_operatingsystem get LocalDateTime /value') do (
  set today=%%a
)
set Today_All=%today:~0,14%
set Today_Day=%today:~0,8%
set Today_Time=%today:~8,6%
set SCREENSHOT=screenshot_%Today_Day%_%Today_Time%.png
set SCREEN_DIR_NAME=Screenshot
rem MKDIR
if not exist %SCREEN_DIR_NAME% (
	mkdir .\%SCREEN_DIR_NAME%
)

adb wait-for-device
adb shell input keyevent KEYCODE_WAKEUP
adb shell /system/bin/screencap -p /sdcard/screenshot.png
adb pull /sdcard/screenshot.png .\%SCREEN_DIR_NAME%\%SCREENSHOT%
.\%SCREEN_DIR_NAME%\%SCREENSHOT% || echo FIAL! && pause