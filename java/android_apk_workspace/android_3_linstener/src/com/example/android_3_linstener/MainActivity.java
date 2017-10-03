package com.example.android_3_linstener;

import android.app.Activity;
import android.os.Bundle;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.Toast;

public class MainActivity extends Activity implements OnClickListener{

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		Button bt1 = (Button) findViewById(R.id.bt1);
		Button bt3 = (Button) findViewById(R.id.bt3);
		Button bt4 = (Button) findViewById(R.id.bt4);
		Button bt5 = (Button) findViewById(R.id.bt5);
		
		bt1.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				Toast.makeText(MainActivity.this, "匿名内部类实现监听", Toast.LENGTH_SHORT).show();
			}
		});
		
		bt3.setOnClickListener(new Bt3());
		bt4.setOnClickListener(this);
		bt5.setOnClickListener(new Linsten(this));
	}
	
	private class Bt3 implements OnClickListener{

		@Override
		public void onClick(View v) {
			// TODO Auto-generated method stub
			Toast.makeText(MainActivity.this, "内部类实现监听", Toast.LENGTH_SHORT).show();
		}
		
	}
	
	public void bit (View v){
		switch (v.getId()){
		case R.id.bt2:
				Toast.makeText(MainActivity.this, "OnClick实现监听", Toast.LENGTH_SHORT).show();
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
	public void onClick(View v) {
		// TODO Auto-generated method stub
		if(v.getId() == R.id.bt4)
			Toast.makeText(MainActivity.this, "本类实现监听", Toast.LENGTH_SHORT).show();
	}

}
