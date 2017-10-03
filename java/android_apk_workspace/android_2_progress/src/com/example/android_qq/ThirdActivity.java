package com.example.android_qq;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.ProgressBar;

public class ThirdActivity extends Activity {
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		setContentView(R.layout.third);
		
		final ProgressBar pb = (ProgressBar) findViewById(R.id.seekBar1);
		Button bt1 = (Button) findViewById(R.id.bt1);
		Button bt2 = (Button) findViewById(R.id.bt2);
		
		bt1.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				int val = pb.getProgress();
				pb.setProgress(val+10);
				
			}
		});
		
		bt2.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				int val = pb.getProgress();
				pb.setProgress(val-10);
			}
		});
	}
}
