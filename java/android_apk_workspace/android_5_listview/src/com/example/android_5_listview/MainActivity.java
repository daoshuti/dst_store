package com.example.android_5_listview;

import android.app.Activity;
import android.os.Bundle;
import android.view.Menu;
import android.widget.ArrayAdapter;
import android.widget.ListView;

public class MainActivity extends Activity {

	String[] str = new String [] {"亚楠中心","教堂病房","下水道","旧亚楠","禁忌森林","教会镇","教会镇上层","拜尔维斯","噩梦边境","噩梦边缘","学院","古旧大教堂"};
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		ListView lv = (ListView) findViewById(R.id.Lv);
		
		ArrayAdapter<String> adapter = new ArrayAdapter<String>(MainActivity.this, R.layout.item, R.id.textView1 , str);
		lv.setAdapter(adapter);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
