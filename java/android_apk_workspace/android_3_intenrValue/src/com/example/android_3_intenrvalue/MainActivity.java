package com.example.android_3_intenrvalue;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class MainActivity extends Activity {

	TextView tv2;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		final EditText ev = (EditText) findViewById(R.id.et1);
		tv2 = (TextView) findViewById(R.id.tv2);
		
		Button bt = (Button) findViewById(R.id.bt1);
		bt.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				String str = ev.getText().toString();
				Intent intent = new Intent(MainActivity.this, SecondActivity.class);
				intent.putExtra("key", str);
//				startActivity(intent);
				startActivityForResult(intent, 120);
			}
		});
	}

	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		// TODO Auto-generated method stub
		super.onActivityResult(requestCode, resultCode, data);
		if(requestCode == 120 && resultCode ==123){
			String str = data.getStringExtra("key2");
			tv2.setText(str);
		}
	}
	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
