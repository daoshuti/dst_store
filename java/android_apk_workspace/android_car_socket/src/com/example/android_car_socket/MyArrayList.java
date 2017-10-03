package com.example.android_car_socket;

import java.io.OutputStream;
import java.net.Socket;
import java.util.ArrayList;

import android.app.Activity;

public class MyArrayList {
	public static ArrayList<Activity> list = new ArrayList<Activity>();
	public static String ipAddress;
	public static Socket socket;
	public static OutputStream out;
}
