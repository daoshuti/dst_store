package com.example.android_5_simplelistview;

import java.util.ArrayList;
import java.util.HashMap;

import android.app.Activity;
import android.os.Bundle;
import android.view.Menu;
import android.widget.ListView;
import android.widget.SimpleAdapter;

public class MainActivity extends Activity {

	String[] name = new String [] {"圣职人员怪兽","老太太","神父","渴血兽","三基佬","天庭使者","宇宙女","拜尔维斯","躲猫猫","热情村民"};
	int[] picture = new int[] {R.drawable.p1,R.drawable.p2,R.drawable.p3,R.drawable.p4,R.drawable.p5,R.drawable.p6,
			R.drawable.p7,R.drawable.p8,R.drawable.p9,R.drawable.p10};
	String[] say = new String [] {"我在亚楠中心","我在教堂病房","我在下水道","我在旧亚楠","我在禁忌森林","我在教会镇","我在教会镇上层","我在拜尔维斯","我在噩梦边境","我在古旧大教堂"};
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		ListView lv = (ListView) findViewById(R.id.lv);
		
		ArrayList<HashMap<String, Object>> data = new ArrayList<HashMap<String,Object>>();
		for (int i = 0; i < name.length; i++) {
			HashMap<String, Object> map = new HashMap<String, Object>();
			map.put("name", name[i]);
			map.put("picture", picture[i]);
			map.put("say", say[i]);
			data.add(map);
		}
		
		SimpleAdapter adapter = new SimpleAdapter(MainActivity.this, data, R.layout.item,
				new String []{"name","picture","say"}, new int[] {R.id.tv2,R.id.image,R.id.tv1});
		
		lv.setAdapter(adapter);
		
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
