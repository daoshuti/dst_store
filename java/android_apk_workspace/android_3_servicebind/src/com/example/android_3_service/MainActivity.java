package com.example.android_3_service;

import android.app.Activity;
import android.content.ComponentName;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.Bundle;
import android.os.IBinder;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.widget.Toast;

import com.example.android_3_service.MyService.MyBinder;

public class MainActivity extends Activity {

	private Intent intent;
	MyBinder ser;
	
	ServiceConnection conn = new ServiceConnection() {
		
		@Override
		public void onServiceDisconnected(ComponentName name) {
			// TODO Auto-generated method stub
			Log.d("TAG", "服务连接失败");
		}
		
		@Override
		public void onServiceConnected(ComponentName name, IBinder service) {
			// TODO Auto-generated method stub
			Log.d("TAG", "服务连接成功");
			ser = (MyBinder) service;
		}
	};
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		intent = new Intent(MainActivity.this, MyService.class);
	}

	public void bit (View v){
		switch(v.getId()){
		case R.id.start:
			Toast.makeText(MainActivity.this, "开始按键按下", Toast.LENGTH_SHORT).show();
			startService(intent);
			break;
		case R.id.bind:
			bindService(intent, conn, BIND_AUTO_CREATE);
			break;
		case R.id.unbind:
			unbindService(conn);
			break;
		case R.id.stop:
			Toast.makeText(MainActivity.this, "停止按键按下", Toast.LENGTH_SHORT).show();
			stopService(intent);
			break;
		case R.id.get:
			Toast.makeText(MainActivity.this, ser.getCount()+"", Toast.LENGTH_SHORT).show();
			break;
		}
		
	}
	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}
	
	@Override
	protected void onDestroy() {
		// TODO Auto-generated method stub
		super.onDestroy();
		stopService(intent);
	}

}
