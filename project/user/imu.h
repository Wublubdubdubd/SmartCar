#ifndef __IMU_H_
#define __IMU_H_

#include "zf_device_imu660ra.h"
#include "zf_driver_delay.h"
#include "math.h"


                                             

//acc gyro ��ʵ����ֵ
extern float imu_acc[],imu_gyro[];

// ��ʼ�Ƕ�
extern float roll;
extern float pitch;
extern float yaw;

// ��Ԫ��
extern float q0, q1, q2, q3; // ��Ԫ��
extern float integralFBx, integralFBy, integralFBz; // ������

#endif