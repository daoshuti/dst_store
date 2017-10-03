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

public class SecondActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.second);
		
		final Intent intent = getIntent();
		String str = intent.getStringExtra("key");
		TextView tv = (TextView) findViewById(R.id.tv1);
		tv.setText(str);
		
		final EditText ev2 = (EditText) findViewById(R.id.et2);
		Button bt2 = (Button) findViewById(R.id.bt2);
		bt2.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				String str = ev2.getText().toString();
				intent.putExtra("key2", str);
				setResult(123, intent);
				finish();
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
