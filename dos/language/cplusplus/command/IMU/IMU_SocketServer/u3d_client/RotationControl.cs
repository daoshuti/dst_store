using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using UnityEngine;

public class RotationControl : MonoBehaviour {

	#if true
	private IPEndPoint serverIP;
	private Socket udpServer;
	#else
	float w=0.0f;
	float x=0.0f;
	float y=0.0f;
	float z=1.0f;
	#endif

	void Awake(){
		UnityEngine.Debug.Log ("Awake");
	}

	// Use this for initialization
	void Start () {
		UnityEngine.Debug.Log ("Start");
		#if true
		serverIP = new IPEndPoint (0, 50000);
		Console.WriteLine("UDP服务器开始监听" + serverIP.Port + "端口");
		udpServer = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
		udpServer.Bind(serverIP);
		#endif
	}
	
	// Update is called once per frame
	void Update () {
		#if true
		int length = 0;
		byte[] data = new byte[1024];
		IPEndPoint ipep = new IPEndPoint(IPAddress.Any, 0);
		EndPoint Remote = (EndPoint)ipep;

		try{
			length = udpServer.ReceiveFrom(data, ref Remote);//接受来自服务器的数据
		}
		catch (Exception ex){
			Console.WriteLine(string.Format("出现异常：{0}", ex.Message));
			return;
		}

		string datetime = DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss");
		string message = Encoding.UTF8.GetString(data, 0, length);
		string ipport = (Remote as IPEndPoint).Address.ToString() + ":" + (Remote as IPEndPoint).Port.ToString();
		float q_x = (float)Convert.ToDouble(message.Split(',')[0]);
		float q_y = (float)Convert.ToDouble(message.Split(',')[1]);
		float q_z = (float)Convert.ToDouble(message.Split(',')[2]);
		float q_w = (float)Convert.ToDouble(message.Split(',')[3]);
		//UnityEngine.Debug.Log (string.Format("{0} 收到來自{1}的消息：{2}", datetime, ipport, message));
		//UnityEngine.Debug.Log (string.Format("{0},{1},{2}", gyro_x.ToString(), gyro_y.ToString(), gyro_z.ToString()));
		//UnityEngine.Debug.Log (string.Format("{0},{1},{2}", accel_x.ToString(), accel_y.ToString(), accel_z.ToString()));
		//UnityEngine.Debug.Log (string.Format("{0},{1},{2}", mag_x.ToString(), mag_y.ToString(), mag_z.ToString()));
		//UnityEngine.Debug.Log (string.Format("{0},{1},{2}", ypr_x.ToString(), ypr_y.ToString(), ypr_z.ToString()));

		//transform.rotation = Quaternion.AngleAxis (180, new Vector3(ypr_x, ypr_y, ypr_z));
		Quaternion q = new Quaternion(q_x, q_y, q_z, q_w);
		transform.rotation = q;
		transform.Rotate (new Vector3(-90,90,0));
		#else
		//w = w + 0.01f;
		//Quaternion q = new Quaternion(w, x, y, z);
		w = w + 1.0f;
		Quaternion q = Quaternion.AngleAxis(w, new Vector3(x, y, z));;
		transform.rotation = q;
		UnityEngine.Debug.Log (q.ToString());
		#endif
	}

}
