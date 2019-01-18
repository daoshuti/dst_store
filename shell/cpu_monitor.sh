# Author: wanghan
# Created Time : 2019年01月18日 星期五 16时01分19秒
# File Name: cpu_monitor.sh
# Description:

function cpuinfo_cur_freq_monitor
{
	echo "$(date +%s),\
	cpu0:$(cat /sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_cur_freq),\
	cpu1:$(cat /sys/devices/system/cpu/cpu1/cpufreq/cpuinfo_cur_freq),\
	cpu2:$(cat /sys/devices/system/cpu/cpu2/cpufreq/cpuinfo_cur_freq),\
	cpu3:$(cat /sys/devices/system/cpu/cpu3/cpufreq/cpuinfo_cur_freq),\
	cpu4:$(cat /sys/devices/system/cpu/cpu4/cpufreq/cpuinfo_cur_freq),\
	cpu5:$(cat /sys/devices/system/cpu/cpu5/cpufreq/cpuinfo_cur_freq),\
	cpu6:$(cat /sys/devices/system/cpu/cpu6/cpufreq/cpuinfo_cur_freq),\
	cpu7:$(cat /sys/devices/system/cpu/cpu7/cpufreq/cpuinfo_cur_freq)\
	" | tee -a cpufreq.csv
}

function scaling_cur_freq_monitor
{
	echo "$(date +%s),\
	cpu0:$(cat /sys/devices/system/cpu/cpu0/cpufreq/scaling_cur_freq),\
	cpu1:$(cat /sys/devices/system/cpu/cpu1/cpufreq/scaling_cur_freq),\
	cpu2:$(cat /sys/devices/system/cpu/cpu2/cpufreq/scaling_cur_freq),\
	cpu3:$(cat /sys/devices/system/cpu/cpu3/cpufreq/scaling_cur_freq),\
	cpu4:$(cat /sys/devices/system/cpu/cpu4/cpufreq/scaling_cur_freq),\
	cpu5:$(cat /sys/devices/system/cpu/cpu5/cpufreq/scaling_cur_freq),\
	cpu6:$(cat /sys/devices/system/cpu/cpu6/cpufreq/scaling_cur_freq),\
	cpu7:$(cat /sys/devices/system/cpu/cpu7/cpufreq/scaling_cur_freq)\
	" | tee -a cpufreq.csv
}

function main
{
	while true; do
		
		# Monitor '/sys/devices/system/cpu/cpu0~7/cpufreq/cpuinfo_cur_freq' node.
		#cpuinfo_cur_freq_monitor
		
		# Monitor '/sys/devices/system/cpu/cpu0~7/cpufreq/scaling_cur_freq_monitor' node.
		scaling_cur_freq_monitor
		
		#delay
		sleep 1

	done
}

#exec
main

