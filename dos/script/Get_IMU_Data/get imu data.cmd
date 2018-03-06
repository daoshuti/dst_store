@echo off

rem Settings
set LOG_DIR_NAME=LC_LOG

for /f "delims=" %%i in ( 'adb shell cat persist/SYSTEM_SN') do set MYAPSN=%%i

for /f "tokens=2 delims==" %%a in ('wmic path win32_operatingsystem get LocalDateTime /value') do (
  set today=%%a
)
set Today_All=%today:~0,14%
set Today_Date=%today:~0,8%
set Today_Time=%today:~8,6%

set IMU_DATA_FILE=imu_data_%MYAPSN%_%Today_Date%_%Today_Time%.csv

rem Get IMU Data
echo Saving IMU Data ... ...
echo Press 'Ctrl+C' and select 'N' to stop saving the data.
imu > %IMU_DATA_FILE%
adb kill-server
