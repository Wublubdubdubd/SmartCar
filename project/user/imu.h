#ifndef __IMU_H_
#define __IMU_H_

#include "zf_device_imu660ra.h"
#include "zf_driver_delay.h"
#include "math.h"


// �����˲�����
#define ALPHA 0.99

// ���� 30��@100Hz
#define GYRO_CALIB_SAMPLES 3000 
extern float gyro_calib[];

//acc gyro ��ʵ����ֵ
extern float imu_acc[],imu_gyro[];

// ��ʼ�Ƕ�
extern float roll;
extern float pitch;
extern float yaw;

// �����˲�����
void complementary_filter(float acc[], float gyro[], float dt);
// ��������
void gyro_calibration(void);

extern char str_buffer[];
#endif