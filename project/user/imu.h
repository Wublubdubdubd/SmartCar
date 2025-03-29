#ifndef __IMU_H_
#define __IMU_H_

#include "zf_device_imu660ra.h"

// 定点数定义（Q16格式，16位整数+16位小数）
typedef signed long q32;
#define Q16_SCALE 65536L

// 传感器参数（定点数表示）
const q32 GYRO_LSB2DPS = 16400L;  // 16.4LSB/dps → Q16:16400/65536=0.250244140625
const q32 ACC_LSB2G = 2048L;     // 2048LSB/g → Q16:2048/65536=0.03125
const q32 GRAVITY_Q = 980665L;    // 9.80665m/s2 → Q16:980665/65536≈15.09945

// 姿态角（定点数，单位：1/65536弧度）
q32 roll = 0, pitch = 0;
q32 yaw_gyro = 0;  // 陀螺仪累积航向（存在漂移）

// 互补滤波参数（Q16格式，0.98→64228）
const q32 ALPHA_Q = 64228;  // 0.98 * 65536 = 64228.48 → 取整

// 定点数乘法（a*b/Q16_SCALE）
q32 q_mul(q32 a, q32 b) {
    return (a * b) >> 16;
}

//acc gyro 真实物理值
extern float imu_acc[],imu_gyro
  
//

#endif