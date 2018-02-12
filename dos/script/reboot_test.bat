@echo off

set TIME_NUM=0
set /p SERAIL=Please input serail number:
set /p LOG_PATH=Please input log name:

:while_loop
echo Wait for Devices ...
adb -s %SERAIL% wait-for-device
set /a TIME_NUM+=1
echo --- reboot %TIME_NUM% time ---
echo --- reboot %TIME_NUM% time --- >> %LOG_PATH%
adb -s %SERAIL% shell getprop sys.boot_completed | findstr 1 > nul && echo REBOOT OK || goto boot_fail
rem save log
echo Save kernel log ...
adb -s %SERAIL% shell dmesg >> %LOG_PATH%
adb -s %SERAIL% reboot
goto while_loop


:boot_fail
echo REBOOT FAIL
echo REBOOT FAIL >> %LOG_PATH%
timeout /t 5 /nobreak
goto while_loop
