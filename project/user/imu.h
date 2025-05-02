#ifndef __IMU_H_
#define __IMU_H_

#include "zf_device_imu660ra.h"
#include "zf_driver_delay.h"
#include "math.h"


// ��ȡŷ���� �ںϲ���
#define ALPHA 0.99

//acc gyro ��ʵ����ֵ
extern float imu_acc[],imu_gyro[];

// ��ʼ�Ƕ�
extern float roll;
extern float pitch;
extern float yaw;

// ��ʼ�ٶ�
extern float x_v;
extern float y_v;
extern float z_v;

// ��ʼλ��
extern float x_p;
extern float y_p;
extern float z_p;


//extern char str_buffer[];
#endif