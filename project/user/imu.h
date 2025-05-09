#ifndef __IMU_H_
#define __IMU_H_

#include "zf_device_imu660ra.h"
#include "zf_driver_delay.h"
#include "math.h"


                                             

//acc gyro 真实物理值
extern float imu_acc[],imu_gyro[];

// 初始角度
extern float roll;
extern float pitch;
extern float yaw;

// 四元数
extern float q0, q1, q2, q3; // 四元数
extern float integralFBx, integralFBy, integralFBz; // 积分项

#endif