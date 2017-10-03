package com.example.android_3_activitymanager;

import android.os.Bundle;
import android.app.Activity;
import android.content.Intent;
import android.view.Menu;
import android.view.View;

public class ThirdActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.third);
		
		MyArrayList.list.add(this);
	}

	public void bit3(View v){
		switch(v.getId()){
		case R.id.bt3_1:
			Intent intent1 = new Intent(ThirdActivity.this, MainActivity.class);
			startActivity(intent1);
			break;
		case R.id.bt3_2:
			Intent intent2 = new Intent(ThirdActivity.this, SecondActivity.class);
			startActivity(intent2);
			break;
		case R.id.bt3_3:
			Intent intent3 = new Intent(ThirdActivity.this, ThirdActivity.class);
			startActivity(intent3);
			break;
		case R.id.bt3_4:
			for (Activity activity : MyArrayList.list) {
				activity.finish();
			}
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
		MyArrayList.list.remove(MyArrayList.list.size() - 1);
	}
}
