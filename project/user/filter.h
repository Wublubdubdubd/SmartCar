/*
滤波器：

1、平滑IMU/GPS数据

2、数据融合

*/
#ifndef _FILTER_H
#define _FILTER_H

#define M_PI 3.1415926535
#define Rad2Ang 180.0f/M_PI

#include "zf_common_typedef.h"
#include "imu.h"

void FOCF(int16* pData,int16* pPreData,float alpha);//一阶互补滤波
void GetEuler(float gyro[], float dt);//获取欧拉角

#endif