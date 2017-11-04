#!/system/bin/sh

#测试之前需要手机自带root权限
#然后执行以下命令
#adb root
#adb remount
#adb disable-verity
#adb reboot
#adb root
#adb remount
#adb push monkey.sh /system/bin/
#adb shell chmod 777 /system/bin
#adb shell "monkey.sh &"
#如有问题请联系我

mkdir -p /data/local/tmp/count
chmod 777 /data/local/tmp/count
echo test > /sys/power/wake_lock  # 保持手机唤醒
echo 1 > /sys/module/msm_poweroff/parameters/download_mode  # 打开download 模式


start_time=`date +%s`

echo ${start_time} > /data/local/tmp/count/start.txt # 记录测试的开始时间

function catch_bugreport(){
    now_time=`date +%Y%m%d%H%M%S`
    bugreport > /sdcard/bugreport_${now_time}.log
}

function close_audio(){
    input keyevent KEYCODE_MUTE
    input keyevent KEYCODE_VOLUME_MUTE
}

for i in $(seq 2000000); do
    close_audio
    end_time=`date +%s`
    echo ${end_time} > /data/local/tmp/count/end.txt # 记录测试的结束时间
    soc=`ps | grep monkey`   # 获取monkey进程
    for j in $(seq 20); do
        input keyevent KEYCODE_VOLUME_DOWN  # 关闭音量
    done
    for k in $(seq 20); do
        input keyevent 3  # 回到HOME界面
    done
    input keyevent KEYCODE_VOLUME_MUTE # 关闭音量
    echo $soc
    if [ "$soc" != "" ];  # 如果Monkey进程存在，则直接跳过这个cycle
    then
        echo "test is  undergoing ....."
    else
        catch_bugreport  # 如果monkey进程消失，重新起来一个monkey进程
        monkey --pkg-blacklist-file /sdcard/blacklist.txt --ignore-crashes --ignore-timeouts --pct-syskeys 0 --ignore-security-exceptions --throttle 300 9999999 & 
    sleep 1
    fi
done
