#ifndef __IMU_H_
#define __IMU_H_

#include "zf_device_imu660ra.h"
#include "zf_driver_delay.h"
#include "math.h"


// 获取欧拉角 融合参数
#define ALPHA 0.99

//acc gyro 真实物理值
extern float imu_acc[],imu_gyro[];

// 初始角度
extern float roll;
extern float pitch;
extern float yaw;

// 初始速度
extern float x_v;
extern float y_v;
extern float z_v;

// 初始位置
extern float x_p;
extern float y_p;
extern float z_p;


//extern char str_buffer[];
#endif