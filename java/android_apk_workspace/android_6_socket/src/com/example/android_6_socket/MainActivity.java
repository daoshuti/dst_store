package com.example.android_6_socket;

import java.io.IOException;
import java.io.OutputStream;
import java.net.Socket;
import java.net.UnknownHostException;

import android.app.Activity;
import android.os.Bundle;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class MainActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		Button bt = (Button) findViewById(R.id.button1);
		final EditText ipaddr = (EditText) findViewById(R.id.editText2);
		final EditText et = (EditText) findViewById(R.id.editText1);
		
		bt.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				try {
					Socket socket = new Socket(ipaddr.getText().toString(), 8080);
					
					OutputStream out = socket.getOutputStream();
					
					String str = et.getText().toString();
					
					byte[] buffer = str.getBytes();
					
					out.write(buffer, 0, buffer.length);
					
					out.close();
					
					socket.close();
				
					
				} catch (UnknownHostException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				Toast.makeText(MainActivity.this, "发送成功", Toast.LENGTH_SHORT).show();
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
