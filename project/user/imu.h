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


//extern char str_buffer[];
#endif