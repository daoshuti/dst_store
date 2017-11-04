 @echo off
 set /a tp_num=0 
 
:_start_get_tp_log
	echo ============ 正在抓取 tp log ... ====================
	rem 延时2秒，确保adb连接完成
	ping -n 2 127.0.0.1 > nul
	rem 确认是否连上手机
	adb devices 
	adb root
	adb remount
	rem 检测是否为focaltech
	adb shell cat /proc/tp_info
	adb shell cat /sys/bus/i2c/devices/3-0038/fts_dump_reg || goto _warning_log
	
	rem adb shell "echo /system/etc/Conf_MultipleTest.ini > /sys/bus/i2c/devices/3-0038/fts_test"
	
	echo ==请在Cit中进行自检操作（若tp已经自检，忽略该步骤）==
	echo ============ 自检完成后，按任意键继续 ===============
	pause
	mkdir tp_log%tp_num%
	adb shell "cd /sdcard/ && mkdir tp_log && cp result_* tp_log -a"
	adb pull /sdcard/tp_log ./tp_log%tp_num%
	adb shell "cd /sdcard/ && rm tp_log -rf"
	set /a tp_num+=1
	echo ============ 该手机的tp log抓取完毕 =================
	echo ============ 请换下一部手机 =========================
	pause
	goto _start_get_tp_log
:_warning_log
	echo ============ [Warning] TP不是focaltech或adb连接失败! ==============
	set /p input="Continue?(y/n)" 
	if not "%input%"=="n" (
		goto _start_get_tp_log
	) else (
		exit
	)