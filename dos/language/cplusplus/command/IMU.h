#ifndef __IMU_H__
#define __IMU_H__

#include <math.h>
//#define M_PI  (float)3.1415926535

//Mini IMU AHRS 解算的API
void IMU_init(float now_time);
void IMU_getYawPitchRoll(float * ypr_angles,
                         float gx, float gy, float gz,
                         float ax, float ay, float az,
                         float mx, float my, float mz, float now_time); //更新姿态

#endif

