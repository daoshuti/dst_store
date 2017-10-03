package com.example.android_4_broadcast;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.widget.Toast;

public class MyBroadcastReceiver2 extends BroadcastReceiver {

	@Override
	public void onReceive(Context context, Intent intent) {
		// TODO Auto-generated method stub
		String str1 = intent.getStringExtra("key");
		
		Bundle bd = getResultExtras(true);
		String str2 = bd.getString("k2");
		
		Toast.makeText(context, "广播接收器2收到广播"+str1+str2, Toast.LENGTH_SHORT).show();
	}

}
