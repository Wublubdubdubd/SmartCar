/*
�˲�����

1��ƽ��IMU/GPS����

2�������ں�

*/
#ifndef _FILTER_H
#define _FILTER_H

#define M_PI 3.1415926535
#define Rad2Ang 180.0f/M_PI

#include "zf_common_typedef.h"
#include "imu.h"

void FOCF(int16* pData,int16* pPreData,float alpha);//һ�׻����˲�
void GetEuler(float gyro[], float dt);//��ȡŷ����

#endif