#!/system/bin/sh

#Settings
CHG_LOG_PATH=/sdcard/logs
CHG_LOG_CSV=$CHG_LOG_PATH/battery_data.csv
mkdir -p $CHG_LOG_PATH
touch $CHG_LOG_CSV

#Save logcat log 
logcat -b events -f $CHG_LOG_PATH/logcat_events.log &
#logcat -d -b events >> $CHG_LOG_PATH/logcat_events.log
logcat -b main -f $CHG_LOG_PATH/logcat_main.log &
#logcat -d -b main >> $CHG_LOG_PATH/logcat_main.log
logcat -b system -f $CHG_LOG_PATH/logcat_system.log &
#logcat -d -b system >> $CHG_LOG_PATH/logcat_system.log
logcat -b all -v time -f $CHG_LOG_PATH/logcat_all.log &
#logcat -d -b all -v time >> $CHG_LOG_PATH/logcat_all.log


#Get charger log
echo "TIME,SOC(%),CURRENT_NOW(uA),VOLTAGE_NOW(uV),TEMP,STATUS,HEALTH,CHARGETYPE" >> $CHG_LOG_CSV
INTERVAL=10
intialSec=$(date +%s)
until [ 0 -eq 1 ]
do

	timeSec=$(date +%s)

	deltaTime=$(($timeSec-$intialSec))
	SOC=$(cat /sys/class/power_supply/battery/capacity)
	cnow=$(cat /sys/class/power_supply/battery/current_now)
	vnow=$(cat /sys/class/power_supply/battery/voltage_now)
	batteryTemp=$(cat /sys/class/power_supply/battery/temp)
	batteryStatus=$(cat /sys/class/power_supply/battery/status)
	batteryHealth=$(cat /sys/class/power_supply/battery/health)
	batterychrgType=$(cat /sys/class/power_supply/battery/charge_type)

	echo "$deltaTime,$SOC,$cnow,$vnow,$batteryTemp,$batteryStatus,$batteryHealth,$batterychrgType" >> $CHG_LOG_CSV
    #Save kernel log 
    dmesg -c >> $CHG_LOG_PATH/kernel.log
    echo Please unplug the USB cable and insert the V190 charger.

	sleep ${INTERVAL}
done

exit 0

