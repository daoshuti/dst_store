package com.example.android_1_helloworld;

import android.app.Activity;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.Window;
import android.widget.Button;
import android.widget.Toast;

public class MainActivity extends Activity {
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		requestWindowFeature(Window.FEATURE_NO_TITLE);//隐藏标题栏
		setContentView(R.layout.activity_main);//启动
		
		Button bt = (Button)findViewById(R.id.button1);//绑定事件源
		bt.setOnClickListener(new OnClickListener(){

			@Override
			public void onClick(View v) {//产生按键事件后调用该方法
				// TODO Auto-generated method stub
				Log.d("按键", "按键被按下");
				Toast.makeText(MainActivity.this, "成功点击按键",Toast.LENGTH_SHORT).show();
				
				Intent intent = new Intent(Intent.ACTION_VIEW);
				intent.setData(Uri.parse("http://www.baidu.com"));
				startActivity(intent);
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
