package com.example.android_qq;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class ThirdActivity extends Activity {
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		setContentView(R.layout.third);
		
		final TextView tv = (TextView) findViewById(R.id.textView1);
		final EditText ev = (EditText) findViewById(R.id.editText1);
		
		Button bt = (Button) findViewById(R.id.bt1);
		bt.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				String str = ev.getEditableText().toString();
				tv.setText(str);
			}
		});
		
	}
}
