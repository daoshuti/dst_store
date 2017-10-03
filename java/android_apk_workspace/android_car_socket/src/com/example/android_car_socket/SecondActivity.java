package com.example.android_car_socket;

import java.io.IOException;
import java.net.Socket;
import java.net.UnknownHostException;

import android.app.Activity;
import android.content.Intent;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.Toast;

public class SecondActivity extends Activity {
	// 定义数据库相关变量
	private SQLiteDatabase db;
	private MySQLiteOpenHelper helper;
	// 定义EditText相关变量
	private EditText nameEditText;
	private EditText passwdEditText;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);

		setContentView(R.layout.reg_and_login);// 设置并启动r_and_l.xml页面

		// 把当前这个类（this）添加进列表
		MyArrayList.list.add(this);

		// 创建一个sqlite帮助类对象
		helper = new MySQLiteOpenHelper(SecondActivity.this, "register.db",
				null, 1);

		// 创建EditText对象
		nameEditText = (EditText) findViewById(R.id.nameEditText);
		passwdEditText = (EditText) findViewById(R.id.passwdEditText);

		// 创建套接字对象，开始TCP连接
		try {
			// 创建套接字对象
			MyArrayList.socket = new Socket(MyArrayList.ipAddress, 50000);
			// 输出流，初始化为网络输出流，用来发送的数据到服务器
			MyArrayList.out = MyArrayList.socket.getOutputStream();
		} catch (UnknownHostException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public void secondActivityButton(View v) throws IOException {
		Cursor cursor;

		switch (v.getId()) {
		case R.id.registerButton:
			// ***********************************************************//
			// **************************缺省*****************************//
			// ***********************************************************//
			db = helper.getWritableDatabase();

			// rawQuery方法来执行查看books表所有数据，返回查看所有数据的游标
			cursor = db.rawQuery("select * from users where name=?;",
					new String[] { nameEditText.getText().toString() });

			// 让游标移动到books表第一行
			cursor.moveToFirst();

			if (cursor.getCount() == 0) {
				db.execSQL("insert into users(name,passwd) values(?,?)",
						new String[] { nameEditText.getText().toString(),
								passwdEditText.getText().toString() });
				// 吐司打印
				Toast.makeText(SecondActivity.this, "注册成功", Toast.LENGTH_SHORT)
						.show();
			} else {
				// 吐司打印
				Toast.makeText(SecondActivity.this, "账户已存在请重新输入",
						Toast.LENGTH_SHORT).show();
			}
			break;
		case R.id.loginButton:
			// ***********************************************************//
			// **************************缺省*****************************//
			// ***********************************************************//
			db = helper.getWritableDatabase();

			// rawQuery方法来执行查看books表所有数据，返回查看所有数据的游标
			cursor = db.rawQuery(
					"select * from users where name=? and passwd=?;",
					new String[] { nameEditText.getText().toString(),
							passwdEditText.getText().toString() });

			// 让游标移动到books表第一行
			cursor.moveToFirst();

			if (cursor.getCount() == 1) {
				Intent intent = new Intent(SecondActivity.this,
						MoveCarActivity.class);
				startActivity(intent);
				// 吐司打印
				Toast.makeText(SecondActivity.this, "成功登录", Toast.LENGTH_SHORT)
						.show();
			} else {
				Toast.makeText(SecondActivity.this, "登录失败，用户名或密码错误",
						Toast.LENGTH_SHORT).show();
			}
			break;
		default:
			break;
		}
	}

	@Override
	protected void onDestroy() {
		// TODO Auto-generated method stub
		super.onDestroy();

		// 将该活动页面从列表中删除
		MyArrayList.list.remove(MyArrayList.list.size() - 1);

		// 本活动结束时，关闭套接字
		// 使用完毕，关闭输出流
		try {
			MyArrayList.socket.close();
			MyArrayList.out.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
