package com.example.android_4_text;

import android.app.Service;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.IBinder;
import android.util.Log;

public class MyService extends Service {

	static int count = 0;
	boolean flag = true;
	private MyBroadcastService mbs;
	
	@Override
	public IBinder onBind(Intent intent) {
		// TODO Auto-generated method stub
		return null;
	}
	
	@Override
	public void onCreate() {
		// TODO Auto-generated method stub
		super.onCreate();
		
		Log.d("TAG", "服务创建");
	}
	
	@Override
	public int onStartCommand(Intent intent, int flags, int startId) {
		// TODO Auto-generated method stub
		Log.d("TAG", "服务启动");
		init();
		new Thread(new Runnable() {
			Intent intent = new Intent();
			@Override
			public void run() {
				// TODO Auto-generated method stub
				while(flag){
					if(count >= 200)
						break;
					count++;
					Log.d("TAG", "count:"+count);
					intent.setAction("lol");
					intent.putExtra("key", count);
					sendBroadcast(intent);
					try {
						Thread.sleep(500);
					} catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
			}
		}).start();
		return super.onStartCommand(intent, flags, startId);
	}
	
	class MyBroadcastService extends BroadcastReceiver{

		@Override
		public void onReceive(Context context, Intent intent) {
			// TODO Auto-generated method stub
//			MainActivity ma = (MainActivity)context;
			int count1 = intent.getIntExtra("key2", 0);
			count = count1;
//			ma.setProgress(count1);
			Log.d("TAG", "收到广播，计数：" + count);
		}
		
	}
	private void init() {
		mbs = new MyBroadcastService();
		IntentFilter inf = new IntentFilter();
		inf.addAction("dota");
		registerReceiver(mbs, inf);
	}
	
	@Override
	public void onDestroy() {
		// TODO Auto-generated method stub
		super.onDestroy();
		flag = false;
		unregisterReceiver(mbs);
		Log.d("TAG", "服务结束");
	}
	
}
