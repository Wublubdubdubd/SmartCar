/*
�˲�����

1��ƽ��IMU/GPS����

2�������ں�

*/
#ifndef _FILTER_H
#define _FILTER_H

#include "zf_common_typedef.h"
#include "imu.h"

void FOCF(int16* pData,int16* pPreData,float alpha);//һ�׻����˲�
void GetEuler(float gyro[], float dt);//��ȡŷ����
void EulerToQuaternion(void);//ŷ����ת����Ԫ��
#endif