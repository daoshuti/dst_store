package com.example.android_4_broadcast;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.widget.Toast;

public class MyBroadcastReceiver3 extends BroadcastReceiver {

	@Override
	public void onReceive(Context context, Intent intent) {
		// TODO Auto-generated method stub
		String str = intent.getStringExtra("key");
		
		Bundle bd = new Bundle();
		bd.putString("k2", "呵呵");
		
		Toast.makeText(context, "广播接收器3收到广播"+str, Toast.LENGTH_SHORT).show();
		
		setResultExtras(bd);
	}

}
