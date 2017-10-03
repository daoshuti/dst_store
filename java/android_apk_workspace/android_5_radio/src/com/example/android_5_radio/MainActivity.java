package com.example.android_5_radio;

import android.app.Activity;
import android.os.Bundle;
import android.view.Menu;
import android.view.View;
import android.widget.CheckBox;
import android.widget.RadioGroup;
import android.widget.RadioGroup.OnCheckedChangeListener;
import android.widget.TextView;

public class MainActivity extends Activity {

	private CheckBox checkBox1;
	private CheckBox checkBox2;
	private CheckBox checkBox3;
	private TextView tv2;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		final TextView tv1 = (TextView) findViewById(R.id.tv1);
		tv2 = (TextView) findViewById(R.id.tv2);
		
		RadioGroup radioGroup = (RadioGroup) findViewById(R.id.radioGroup);
//		RadioButton radioButton1 = (RadioButton) findViewById(R.id.radioButton1);
//		RadioButton radioButton2 = (RadioButton) findViewById(R.id.radioButton2);
		
		checkBox1 = (CheckBox) findViewById(R.id.checkBox1);
		checkBox2 = (CheckBox) findViewById(R.id.checkBox2);
		checkBox3 = (CheckBox) findViewById(R.id.checkBox3);
		
		radioGroup.setOnCheckedChangeListener(new OnCheckedChangeListener() {
			
			@Override
			public void onCheckedChanged(RadioGroup group, int checkedId) {
				// TODO Auto-generated method stub
				if(checkedId == R.id.radioButton1){
					tv1.setText("你的性别：男");
				}else{
					tv1.setText("你的性别：女");
				}
			}
		});
	}

	public void bit(View v){
		switch (v.getId()){
		case R.id.checkBox1:
			if (checkBox1.isChecked()) {
				tv2.setText(tv2.getText() + "  LOL");
			}else{
				tv2.setText(tv2.getText().toString().replace("  LOL", ""));
			}
			break;
		case R.id.checkBox2:
			if (checkBox2.isChecked()) {
				tv2.setText(tv2.getText() + "  dota");
			}else{
				tv2.setText(tv2.getText().toString().replace("  dota", ""));
			}
			break;
		case R.id.checkBox3:
			if (checkBox3.isChecked()) {
				tv2.setText(tv2.getText() + "  BloodBorne");
			}else{
				tv2.setText(tv2.getText().toString().replace("  BloodBorne", ""));
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

}
