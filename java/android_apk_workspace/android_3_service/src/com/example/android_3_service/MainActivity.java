package com.example.android_3_service;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.Menu;
import android.view.View;
import android.widget.Toast;

public class MainActivity extends Activity {

	private Intent intent;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
	}

	public void bit (View v){
		switch(v.getId()){
		case R.id.start:
			Toast.makeText(MainActivity.this, "开始按键按下", Toast.LENGTH_SHORT).show();
			intent = new Intent(MainActivity.this, MyService.class);
			startService(intent);
			break;
		case R.id.stop:
			Toast.makeText(MainActivity.this, "停止按键按下", Toast.LENGTH_SHORT).show();
			stopService(intent);
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
