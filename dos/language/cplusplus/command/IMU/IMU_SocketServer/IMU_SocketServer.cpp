#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include "IMU.h"

#pragma comment(lib,"WS2_32.lib ")

#define BUF_SIZE 1024
/* main.c file
编写者：lisn3188
网址：www.chiplab7.com
作者E-mail：lisn3188@163.com
编译环境：MDK-Lite  Version: 4.23
初版时间: 2012-04-25
测试： 本程序已在第七实验室的mini IMU上完成测试
功能：
姿态解算 IMU
将传感器的输出值进行姿态解算。得到目标载体的俯仰角和横滚角 和航向角
------------------------------------
 */

#include <math.h>
#define M_PI  (float)3.1415926535

volatile static float exInt= 0.0, eyInt = 0.0, ezInt = 0.0;  // 误差积分
volatile static float q0 = 1.0f, q1 = 0.0f, q2 = 0.0f, q3 = 0.0f; // 全局四元数
volatile static float lastUpdate = 0.0f; // 采样周期计数 单位 ms

void IMU_init(float now_time)
{
    lastUpdate = now_time;
}

/**************************实现函数********************************************
*函数原型:	   void IMU_AHRSupdate
*功　　能:	 更新AHRS 更新四元数
输入参数： 当前的测量值。
输出参数：没有
*******************************************************************************/
#define Kp 1.0f   // proportional gain governs rate of convergence to accelerometer/magnetometer
#define Ki 0.1f   // integral gain governs rate of convergence of gyroscope biases

float last_ex=0,last_ey=0,last_ez=0;
void IMU_AHRSupdate(float gx, float gy, float gz,
                    float ax, float ay, float az,
                    float mx, float my, float mz, float now_time)//now_time (s)
{
    float norm;
    float hx, hy, hz, bx, bz;
    float vx, vy, vz, wx, wy, wz;
    float ex, ey, ez,halfT;

    // 先把这些用得到的值算好
    float q0q0 = q0*q0;
    float q0q1 = q0*q1;
    float q0q2 = q0*q2;
    float q0q3 = q0*q3;
    float q1q1 = q1*q1;
    float q1q2 = q1*q2;
    float q1q3 = q1*q3;
    float q2q2 = q2*q2;
    float q2q3 = q2*q3;
    float q3q3 = q3*q3;

    halfT = 0.001f;
    //halfT =  (float)(now_time - lastUpdate);
    //halfT =  ((float)(now_time - lastUpdate) / 1000.0f);
    lastUpdate = now_time;	//更新时间

    norm = sqrt(ax*ax + ay*ay + az*az);
    ax = ax / norm;
    ay = ay / norm;
    az = az / norm;

    norm = sqrt(mx*mx + my*my + mz*mz);
    mx = mx / norm;
    my = my / norm;
    mz = mz / norm;

    // compute reference direction of flux
    hx = 2*mx*(0.5f - q2q2 - q3q3) + 2*my*(q1q2 - q0q3) + 2*mz*(q1q3 + q0q2);
    hy = 2*mx*(q1q2 + q0q3) + 2*my*(0.5f - q1q1 - q3q3) + 2*mz*(q2q3 - q0q1);
    hz = 2*mx*(q1q3 - q0q2) + 2*my*(q2q3 + q0q1) + 2*mz*(0.5f - q1q1 - q2q2);
    bx = sqrt((hx*hx) + (hy*hy));
    bz = hz;

    // estimated direction of gravity and flux (v and w)
    vx = 2*(q1q3 - q0q2);
    vy = 2*(q0q1 + q2q3);
    vz = q0q0 - q1q1 - q2q2 + q3q3;
    wx = 2*bx*(0.5 - q2q2 - q3q3) + 2*bz*(q1q3 - q0q2);
    wy = 2*bx*(q1q2 - q0q3) + 2*bz*(q0q1 + q2q3);
    wz = 2*bx*(q0q2 + q1q3) + 2*bz*(0.5 - q1q1 - q2q2);

    // error is sum of cross product between reference direction of fields and direction measured by sensors
    ex = (ay*vz - az*vy) + (my*wz - mz*wy);
    ey = (az*vx - ax*vz) + (mz*wx - mx*wz);
    ez = (ax*vy - ay*vx) + (mx*wy - my*wx);

    if(ex != 0.0f && ey != 0.0f && ez != 0.0f)
    {
        exInt = exInt + ex * Ki * halfT;
        eyInt = eyInt + ey * Ki * halfT;
        ezInt = ezInt + ez * Ki * halfT;

        // adjusted gyroscope measurements
        gx = gx + Kp*ex + exInt;
        gy = gy + Kp*ey + eyInt;
        gz = gz + Kp*ez + ezInt;

        last_ex = ex;
        last_ey = ey;
        last_ez = ez;
    }

    // integrate quaternion rate and normalise
    q0 = q0 + (-q1*gx - q2*gy - q3*gz)*halfT;
    q1 = q1 + (q0*gx + q2*gz - q3*gy)*halfT;
    q2 = q2 + (q0*gy - q1*gz + q3*gx)*halfT;
    q3 = q3 + (q0*gz + q1*gy - q2*gx)*halfT;

    // normalise quaternion
    norm = sqrt(q0*q0 + q1*q1 + q2*q2 + q3*q3);
    q0 = q0 / norm;
    q1 = q1 / norm;
    q2 = q2 / norm;
    q3 = q3 / norm;
}

/**************************实现函数********************************************
*函数原型:	   void IMU_getYawPitchRoll(float * angles)
*功　　能:	 更新四元数 返回当前解算后的姿态数据
输入参数： 将要存放姿态角的数组首地址
输出参数：没有
*******************************************************************************/
void IMU_getYawPitchRoll(float *q, float *ypr_angles,
                         float gx, float gy, float gz,
                         float ax, float ay, float az,
                         float mx, float my, float mz, float now_time) {
    //float q[4]; //　四元数

    //更新四元数
    //将陀螺仪的测量值转成弧度每秒 ( rang : +/- 2000 弧度/s)
    //加速度和磁力计保持 ADC值　不需要转换 (因为会归一化)
    IMU_AHRSupdate(gx, gy, gz, ax, ay, az, mx, my, mz, now_time);

    q[0] = q0; //返回当前值
    q[1] = q1;
    q[2] = q2;
    q[3] = q3;

    ypr_angles[0] = -atan2(2 * q[1] * q[2] + 2 * q[0] * q[3], -2 * q[2]*q[2] - 2 * q[3] * q[3] + 1)* 180/M_PI; // yaw
    ypr_angles[1] = -asin(-2 * q[1] * q[3] + 2 * q[0] * q[2])* 180/M_PI; // pitch
    ypr_angles[2] = atan2(2 * q[2] * q[3] + 2 * q[0] * q[1], -2 * q[1] * q[1] - 2 * q[2] * q[2] + 1)* 180/M_PI; // roll
    //if(ypr_angles[0]<0)ypr_angles[0]+=360.0f;
}

//------------------End of File----------------------------

void get_imu_data(char *buffer,
                    float *timestamp, float *temperature,
                    float *gx, float *gy, float *gz,
                    float *ax, float *ay, float *az,
                    float *mx, float *my, float *mz)
{
    int count = 0;
    char *strsplit = NULL;
    char strvalue[BUF_SIZE];
    float temp[9];

    strsplit = strtok(buffer, ",");
    memset(strvalue,0,sizeof(strvalue));
    strcpy(strvalue, strsplit);
    *timestamp = atof(strvalue);

    strsplit = strtok(NULL, ",");
    memset(strvalue,0,sizeof(strvalue));
    strcpy(strvalue, strsplit);
    *temperature = atoi(strvalue);

    strsplit = strtok(NULL, ",");
    while( strsplit != NULL )
    {
        memset(strvalue,0,sizeof(strvalue));
        strcpy(strvalue, strsplit);
        //printf("%s\n" ,strvalue);
        temp[count] = atof(strvalue);
        strsplit = strtok(NULL, ",");
        count ++;
    }
    *gx = temp[0];*gy = temp[1];*gz = temp[2];
    //*gx = temp[0]*180.0f/M_PI;*gy = temp[1]*180.0f/M_PI;*gz = temp[2]*180.0f/M_PI;
    *ax = temp[3];*ay = temp[4];*az = temp[5];
    *mx = temp[6];*my = temp[7];*mz = temp[8];
#if 0
    printf("%8.3f,%2.1f,%+4.8f,%+4.8f,%+4.8f,%+4.8f,%+4.8f,%+4.8f,%+4.8f,%+4.8f,%+4.8f\n",
            *timestamp, *temperature,
            *gx, *gy, *gz,
            *ax, *ay, *az,
            *mx, *my, *mz);
#endif
    return;
}


int main(int argc, const char *argv[])
{
	//UDP socket
	char buf[BUF_SIZE];
	SOCKET sockfd;
	struct sockaddr_in addr;
	
	//IMU Command
	FILE* pipe = NULL;
	char ch = 0;
	int count = 0;
	int progress_bar = 0;
    unsigned int line_num = 0;
	char buffer[BUF_SIZE];
	float timestamp, temperature, gx, gy, gz, ax, ay, az, mx, my, mz;
    float ypr_angles[3];
	float quaternion[4];

	//WSA
	int ret;
    WORD wVersionRequested = MAKEWORD(2, 2);
    WSADATA wsaData;

    ret = WSAStartup(wVersionRequested, &wsaData);
    if (ret != 0) {
        printf("WSAStartup() called failed!\n");
        return -1;
    }
    else {
        printf("WSAStartup() called success!\n");
    }

    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
        //若不是所请求的版本号2.2,则终止WinSock库的使用
        WSACleanup();
        return -1;
    }

	//UDP Settings
	sockfd = socket(AF_INET,SOCK_DGRAM,0);//IPPROTO_UDP
	if(sockfd == -1)
	{
		perror("Socket Init fail!");
		getchar();
		return -1;
	}
	printf("Socket Init success.\n");

	addr.sin_family = AF_INET;
	addr.sin_port = htons(50000);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");//"172.16.12.244"

#if 0
	if(bind(sockfd,(const struct sockaddr *)&addr,sizeof(addr)) == -1)
	{
		perror("bind fail");
        getchar();
		return -1;
	}
#endif 

	printf("Wait for device ...\n");

	ret = system("adb wait-for-device");
	if (ret != 0)
	{
		printf("Command execution error! ret = %d", ret);
		getchar();
		return -1;
	}

	printf("Adb connection successful. ret = %d\n", ret);

	printf("Press the Enter key to start.\n");
	getchar();
	printf("\n---------------------------\n");

	pipe = _popen("adb shell imutool", "r");
	if (!pipe) return -1;//返回0表示运行失败

	printf("Command Start success.\n");

	printf("Sending IMU data.\n");
	
	printf("Please don't close the window!\n");

	while(!feof(pipe))
	{
		memset(buf,0,sizeof(buf));
        memset(buffer, 0, sizeof(buffer));
		while('\n' != ch)
		{
            ch = fgetc(pipe);
            if ('\t' == ch) ch = ',';
			buffer[count++] = ch;
		}
		buffer[count-1] = '\0';
        ch = count = 0;

		get_imu_data(buffer, &timestamp, &temperature, &gx, &gy, &gz, &ax, &ay, &az, &mx, &my, &mz);
        IMU_getYawPitchRoll(quaternion, ypr_angles, gx, gy, gz, ax, ay, az, mx, my, mz, timestamp); //更新姿态

		//printf("%+3.6f,%+3.6f,%+3.6f\n", ypr_angles[0], ypr_angles[1], ypr_angles[2]);
		//sprintf(buf, "%+3.6f,%+3.6f,%+3.6f", ypr_angles[0], ypr_angles[1], ypr_angles[2]);
		//printf("%+.8f,%+.8f,%+.8f,%+.8f\n", quaternion[0], quaternion[1], quaternion[2], quaternion[3]);
		sprintf(buf, "%+.8f,%+.8f,%+.8f,%+.8f\n", quaternion[0], quaternion[1], quaternion[2], quaternion[3]);
        //sprintf(buf, "%d,%s", line_num++, buffer);
		if (progress_bar%30 == 0)
			sendto(sockfd, buf, strlen(buf)+1, 0, (const struct sockaddr *)&addr, sizeof(addr));
		progress_bar++;
		if (progress_bar > 1000){
			progress_bar = 0;
			printf(".");
		}
	}

	_pclose(pipe);
	closesocket(sockfd);
    WSACleanup();
	return 0;
}
