@echo off

adb root

rem 解除OCP保护：gpio30  写入0-1-0可以reset OCP芯片，解除OCP保护。

adb wait-for-device
adb devices
adb wait-for-device
adb root
adb wait-for-device
adb root
adb wait-for-device

rem determine what GPIOs are already requested in the drivers cat /sys/kernel/debug/gpio
adb shell cat /sys/kernel/debug/gpio

rem Export the GPIO pin.
echo Export the GPIO pin.
adb shell "echo 30 > /sys/class/gpio/export" 

rem Change the GPIO pin direction to in/out. 
echo Change the GPIO pin direction to output mode.
adb shell "echo "out" > /sys/class/gpio/gpio30/direction"
rem adb shell echo "in" > /sys/class/gpio/gpio30/direction 

rem Change the value 0-1-0.
echo Change the value 0-1-0.
adb shell "echo 0 > /sys/class/gpio/gpio30/value" 
adb shell "echo 1 > /sys/class/gpio/gpio30/value"
adb shell "echo 0 > /sys/class/gpio/gpio30/value"

rem Unexport the GPIO pin.
echo Unexport the GPIO pin. 
adb shell "echo 30 > /sys/class/gpio/unexport"

echo ----------------------------
echo Reset OCP Done.
echo ----------------------------
echo.
echo Rebooting ..............................
echo.
pause