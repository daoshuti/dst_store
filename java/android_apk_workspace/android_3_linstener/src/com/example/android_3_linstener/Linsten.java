package com.example.android_3_linstener;

import android.content.Context;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Toast;

public class Linsten implements OnClickListener {

	Context context;
	public Linsten(Context cont) {
		// TODO Auto-generated constructor stub
		context = cont;
	}
	@Override
	public void onClick(View v) {
		// TODO Auto-generated method stub
		Toast.makeText(context, "外部类实现监听", Toast.LENGTH_SHORT).show();
	}

}
