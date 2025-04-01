#ifndef __IMU_H_
#define __IMU_H_

#include "zf_device_imu660ra.h"
#include "zf_driver_delay.h"
#include "math.h"


// 互补滤波参数
#define ALPHA 0.99

// 矫正 30秒@100Hz
#define GYRO_CALIB_SAMPLES 3000 
extern float gyro_calib[];

//acc gyro 真实物理值
extern float imu_acc[],imu_gyro[];

// 初始角度
extern float roll;
extern float pitch;
extern float yaw;

// 互补滤波函数
void complementary_filter(float acc[], float gyro[], float dt);
// 矫正函数
void gyro_calibration(void);

extern char str_buffer[];
#endif