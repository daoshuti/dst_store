package com.example.android_4_broadcast;

import android.app.Activity;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;



public class MainActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		MyBroadcastReceiver mb1 = new MyBroadcastReceiver();
		MyBroadcastReceiver2 mb2 = new MyBroadcastReceiver2();
		MyBroadcastReceiver3 mb3 = new MyBroadcastReceiver3();
		
		IntentFilter inf1 = new IntentFilter();
		IntentFilter inf2 = new IntentFilter();
		IntentFilter inf3 = new IntentFilter();
		
		inf1.addAction("abc");
		inf2.addAction("abc");
		inf3.addAction("abc");
		
		registerReceiver(mb1, inf1);
		registerReceiver(mb2, inf2);
		registerReceiver(mb3, inf3);
		
		Button bt = (Button) findViewById(R.id.bt);
		bt.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				Intent intent = new Intent();
				intent.setAction("abc");
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

}
