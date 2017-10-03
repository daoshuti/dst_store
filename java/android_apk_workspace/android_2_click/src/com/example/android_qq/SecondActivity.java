package com.example.android_qq;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.view.Window;
import android.widget.Toast;


public class SecondActivity extends Activity {
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		requestWindowFeature(Window.FEATURE_NO_TITLE);//隐藏标题栏
		setContentView(R.layout.second);	
	}
	
	public void bitkey(View v) {
		switch(v.getId()){
		case R.id.button1:
			Toast.makeText(SecondActivity.this, "按键1", Toast.LENGTH_SHORT).show();
			break;
		case R.id.button2:
			Toast.makeText(SecondActivity.this, "按键2", Toast.LENGTH_SHORT).show();
			break;
		case R.id.button3:
			Toast.makeText(SecondActivity.this, "按键3", Toast.LENGTH_SHORT).show();
			break;
		case R.id.button4:
			Toast.makeText(SecondActivity.this, "按键4", Toast.LENGTH_SHORT).show();
			break;
		}
	}
	
}
