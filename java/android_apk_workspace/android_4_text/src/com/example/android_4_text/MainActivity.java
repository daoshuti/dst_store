package com.example.android_4_text;

import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.SeekBar;
import android.widget.SeekBar.OnSeekBarChangeListener;
import android.widget.TextView;

public class MainActivity extends Activity {

	TextView tv;
	SeekBar sb;
	private MyBroadcast mb;
	private Intent intent = null;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		tv = (TextView) findViewById(R.id.tv);
		sb = (SeekBar) findViewById(R.id.sb);
		Button bt = (Button) findViewById(R.id.bt);
		Button bt2 = (Button) findViewById(R.id.bt2);
		
		
		init();
		
		bt.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {
				if(intent == null){
					intent = new Intent(MainActivity.this,MyService.class);
					startService(intent);
				}
			}
		});
		
		bt2.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				if(intent != null)
					stopService(intent);
				intent = null;
			}
		});
		
		sb.setOnSeekBarChangeListener(new OnSeekBarChangeListener() {
			
			@Override
			public void onStopTrackingTouch(SeekBar seekBar) {
				// TODO Auto-generated method stub
//				Log.d("TAG", "停止滑动，计数" + sb.getProgress());				
			}
			
			@Override
			public void onStartTrackingTouch(SeekBar seekBar) {
				// TODO Auto-generated method stub
//				Log.d("TAG", "开始滑动，计数：" + sb.getProgress());
			}
			
			@Override
			public void onProgressChanged(SeekBar seekBar, int progress,
					boolean fromUser) {
				// TODO Auto-generated method stub
				Log.d("TAG", "正在滑动，计数：" + progress);
				Intent intent = new Intent();
				intent.setAction("dota");
				intent.putExtra("key2", progress);
				sendBroadcast(intent);
			}
		});
		
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}
	
	class MyBroadcast extends BroadcastReceiver{

		@Override
		public void onReceive(Context context, Intent intent) {
			// TODO Auto-generated method stub
			int count = intent.getIntExtra("key", 0);
			tv.setText("当前计数值：" + count);
			sb.setProgress(count);
		}
		
	}
	
	private void init() {
		mb = new MyBroadcast();
		IntentFilter inf = new IntentFilter();
		inf.addAction("lol");
		registerReceiver(mb, inf);
	}
	
	@Override
	protected void onDestroy() {
		// TODO Auto-generated method stub
		super.onDestroy();
		unregisterReceiver(mb);
		if(intent != null)
			stopService(intent);
	}
	
}
