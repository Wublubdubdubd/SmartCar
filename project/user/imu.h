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


//extern char str_buffer[];
#endif