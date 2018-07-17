@echo off
color 0f
set LIST_FILE=list.txt
C:\Python27\python download_key_list.py %LIST_FILE%         || goto download_err
color 2f
echo.
echo PASS
echo.
pause
exit /b 0

:download_err
color 4f
pause
exit /b %errorlevel%