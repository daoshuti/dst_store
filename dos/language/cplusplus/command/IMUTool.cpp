#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IMU.h"

#define BUF_SIZE 1024

//#define M_PI  (float)3.1415926535
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

int main(int argc, const char* argv[])
{
    FILE* pipe = NULL;
    char ch = 0;
    int ret = 0, count = 0;
    unsigned int line_num = 0;
    float timestamp, temperature, gx, gy, gz, ax, ay, az, mx, my, mz;
    char buffer[BUF_SIZE];
    float ypr_angles[3];

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

    printf("No,Time (s),Temperature (C),Gyro_x,Gyro_y,Gyro_z,Accel_x,Accel_y,Accel_z,Mag_x,Mag_y,Mag_z\n");
    while(!feof(pipe))
    {
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
        IMU_getYawPitchRoll(ypr_angles, gx, gy, gz, ax, ay, az, mx, my, mz, timestamp); //更新姿态
#if 0
        printf("%8.3f,%2.1f,%+4.8f,%+4.8f,%+4.8f,%+4.8f,%+4.8f,%+4.8f,%+4.8f,%+4.8f,%+4.8f\n",
            timestamp, temperature,
            gx, gy, gz,
            ax, ay, az,
            mx, my, mz);
#endif

        printf("%f,%f,%f\n", ypr_angles[0], ypr_angles[1], ypr_angles[2]);

        //printf("%d,%s\n", line_num++, buffer);
    }
    _pclose(pipe);

    getchar();
    return 0;
}

