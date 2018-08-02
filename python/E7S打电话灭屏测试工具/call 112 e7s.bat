
adb %* shell input keyevent KEYCODE_WAKEUP
adb %* shell service call phone 1 s16 "112"
adb %* shell input swipe 540 1900 540 800 500

rem timeout /t 1 /nobreak
adb %* shell input swipe 540 1900 540 1910 500

timeout /t 1 /nobreak
adb %* shell input tap 540 1900

pause