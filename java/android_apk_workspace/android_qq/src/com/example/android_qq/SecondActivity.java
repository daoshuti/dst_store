package com.example.android_qq;

import android.app.Activity;
import android.os.Bundle;
import android.view.Window;

public class SecondActivity extends Activity {
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		requestWindowFeature(Window.FEATURE_NO_TITLE);//隐藏标题栏
		setContentView(R.layout.second);//启动页面二
	}
}
