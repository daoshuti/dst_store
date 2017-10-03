package com.example.android_qq;

import android.app.Activity;
import android.os.Bundle;
import android.widget.SeekBar;
import android.widget.SeekBar.OnSeekBarChangeListener;
import android.widget.TextView;
import android.widget.Toast;

public class ThirdActivity extends Activity {
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		setContentView(R.layout.third);

		final TextView tv = (TextView) findViewById(R.id.textView2);
		final SeekBar sb = (SeekBar) findViewById(R.id.seekBar1);
		sb.setOnSeekBarChangeListener(new OnSeekBarChangeListener() {
			
			@Override
			public void onStopTrackingTouch(SeekBar seekBar) {
				// TODO Auto-generated method stub
				int val = sb.getProgress();
				tv.setText("滑动停止:"+val);
			}
			
			@Override
			public void onStartTrackingTouch(SeekBar seekBar) {
				// TODO Auto-generated method stub
				int val = sb.getProgress();
				tv.setText("滑动开始:"+val);
				Toast.makeText(ThirdActivity.this, "滑动开始", Toast.LENGTH_SHORT).show();
			}
			
			@Override
			public void onProgressChanged(SeekBar seekBar, int progress,
					boolean fromUser) {
				// TODO Auto-generated method stub
				int val = sb.getProgress();
				tv.setText("滑动中:"+val);
			}
		});
	}
	
	
}
