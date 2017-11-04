adb shell sendevent /dev/input/event1 3 47 0
adb shell sendevent /dev/input/event1 3 57 0

adb shell sendevent /dev/input/event1 3 58 63

adb shell sendevent /dev/input/event1 3 48 6
adb shell sendevent /dev/input/event1 3 50 6

adb shell sendevent /dev/input/event1 3 53 231
adb shell sendevent /dev/input/event1 3 54 482

adb shell sendevent /dev/input/event1 1 330 1

adb shell sendevent /dev/input/event1 0 0 0




adb shell sendevent /dev/input/event1 3 57 -1
adb shell sendevent /dev/input/event1 3 58 0
adb shell sendevent /dev/input/event1 1 330 0
adb shell sendevent /dev/input/event1 0 0 0
