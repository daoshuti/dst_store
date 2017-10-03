package com.example.android_6_sqlit;

import android.app.Activity;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.widget.EditText;
import android.widget.Toast;

public class MainActivity extends Activity {

	private EditText author;
	private EditText pages;
	private EditText name;
	private EditText price;
	private SQLiteDatabase db;
	private MySQLiteOpenHelper helper;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		author = (EditText) findViewById(R.id.editText1);
		pages = (EditText) findViewById(R.id.editText2);
		name = (EditText) findViewById(R.id.editText3);
		price = (EditText) findViewById(R.id.editText4);
		helper = new MySQLiteOpenHelper(MainActivity.this, "datebase.db", null, 1);
	}

	public void bit (View v){
		switch (v.getId()) {
		case R.id.button1:
			db = helper.getWritableDatabase();
			Toast.makeText(MainActivity.this, "创建成功", Toast.LENGTH_SHORT).show();
			break;
		case R.id.button2:
			db = helper.getWritableDatabase();
			db.execSQL("insert into books(author,pages,name,price) values(?,?,?,?)",
					new String[]{author.getText().toString(),pages.getText().toString(),
					name.getText().toString(),price.getText().toString()});
			Toast.makeText(MainActivity.this, "插入成功", Toast.LENGTH_SHORT).show();
			break;
		case R.id.button3:
			db = helper.getWritableDatabase();
			db.execSQL("update books set pages = 900 where pages = ?",
					new String[]{pages.getText().toString()});//将某个页数改为900页
			Toast.makeText(MainActivity.this, "修改成功", Toast.LENGTH_SHORT).show();
			break;
		case R.id.button4:
			db = helper.getWritableDatabase();
			db.execSQL("delete from books where name = ?",
					new String[]{name.getText().toString()});
			Toast.makeText(MainActivity.this, "删除成功", Toast.LENGTH_SHORT).show();
			break;
		case R.id.button5:
			db = helper.getWritableDatabase();
			Cursor cursor = db.rawQuery("select * from books", null);
			cursor.moveToFirst();
			do {
				String author = cursor.getString(cursor.getColumnIndex("author"));
				String pages = cursor.getString(cursor.getColumnIndex("pages"));
				String name = cursor.getString(cursor.getColumnIndex("name"));
				String price = cursor.getString(cursor.getColumnIndex("price"));
				Log.d("TAG", author+"  "+pages+"  "+name+"  "+price);
			} while (cursor.moveToNext());
			Toast.makeText(MainActivity.this, "打印成功", Toast.LENGTH_SHORT).show();
			break;
		default:
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
