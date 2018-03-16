@echo off

set /p NUM=请输入机器编号:

for /f "tokens=2 delims==" %%a in ('wmic path win32_operatingsystem get LocalDateTime /value') do (
  set today=%%a
)
set Today_All=%today:~0,14%
set Today_Day=%today:~0,8%
set Today_Time=%today:~8,6%
set LOG_PATH=.\logs\%NUM%#_%Today_Day%_%Today_Time%


rem MKDIR
if not exist .\logs (
	mkdir .\logs
)
if not exist %LOG_PATH% (
	mkdir .\%LOG_PATH%
)

adb root
adb pull -p /sdcard/logs/ .\%LOG_PATH%

echo.
echo.
echo.
echo 机器的开机时间如下：
adb shell uptime
echo.
echo.
echo.
pause