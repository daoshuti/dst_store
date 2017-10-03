package com.example.android_car_socket;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.Menu;
import android.view.View;
import android.widget.EditText;

public class MainActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);//设置并启动activity_main.xml页面
		
		//把当前这个类（this）添加进列表
		MyArrayList.list.add(this);
	}
	
	public void submit(View v)
	{
		switch(v.getId())
		{
		case R.id.submitButton:
			//实例化ipEditText的对象，以获得ip地址
			EditText ipaddr = (EditText) findViewById(R.id.ipEditText);
			MyArrayList.ipAddress = ipaddr.getText().toString();
			//实例化一个Intent对象，然后跳转到下个页面
			Intent registerAndLogin = new Intent(MainActivity.this,SecondActivity.class);
			startActivity(registerAndLogin);
			break;
		default:
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
		
		//将该活动页面从列表中删除
		MyArrayList.list.remove(MyArrayList.list.size()-1);
	}
}
