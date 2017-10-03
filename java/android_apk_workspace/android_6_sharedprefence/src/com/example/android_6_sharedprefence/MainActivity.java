package com.example.android_6_sharedprefence;

import android.app.Activity;
import android.content.Context;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.os.Bundle;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class MainActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		Button save = (Button) findViewById(R.id.button1);
		Button get = (Button) findViewById(R.id.button2);
		final EditText ed = (EditText) findViewById(R.id.editText1);
		final TextView tv = (TextView) findViewById(R.id.textView1);
		
		final SharedPreferences sp = getSharedPreferences("data", Context.MODE_PRIVATE);
		
		save.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				Editor editor = sp.edit();
				String str = ed.getText().toString();
				editor.putString("key", str);
				editor.commit();
			}
		});
		
		get.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				String str = sp.getString("key", "");
				tv.setText(str);
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
