package com.example.android_5_iosteam;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;

import android.app.Activity;
import android.os.Bundle;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;


public class MainActivity extends Activity {

	private EditText et;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);

		et = (EditText) findViewById(R.id.editText1);
		Button bt = (Button) findViewById(R.id.button1);
		Button bt2 = (Button) findViewById(R.id.button2);

		bt.setOnClickListener(new OnClickListener() {

			private FileInputStream fin;
			private FileOutputStream fout;
			protected int len;

			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				try {
					fin = new FileInputStream("/mnt/sdcard/p1.png");
					fout = new FileOutputStream("/mnt/sdcard/p2.png");
					byte[] buffer = new byte[5];

					while ((len = fin.read(buffer, 0, buffer.length)) != -1) {
						fout.write(buffer, 0, len);
					}
				} catch (FileNotFoundException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		});

		bt2.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				try {
					FileOutputStream fout = new FileOutputStream(
							"/mnt/sdcard/log.txt");
					byte[] buffer = et.getText().toString().getBytes();
					try {
						fout.write(buffer, 0, buffer.length);
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				} catch (FileNotFoundException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
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
