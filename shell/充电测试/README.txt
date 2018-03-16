# [CN]


操作步骤如下：

0. 插上机器
1. 点击test.cmd
2. 在弹出的窗口中依次输入以下两个命令：
	i. adb shell
	ii. /data/local/tmp/charger_test.sh &
3. 拔掉USB线并关闭窗口。

屏幕打印出Please unplug the USB cable and insert the V190 charger. 这句话的时候,表示已经启动脚本了。按照提示从电脑上拔掉USB线，插到充电器上开始测试。

抓取log使用Get Log.cmd脚本。

# [EN]
0. Plug in DUT.
1. Dobule click test.cmd file.
2. Input two command on the jump window.
    i. adb shell
    ii. /data/local/tmp/charger_test.sh &
3. Unplug USB line and close the command window.