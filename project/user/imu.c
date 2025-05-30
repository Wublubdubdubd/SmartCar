#include "imu.h"

float imu_acc[3],imu_gyro[3];//acc gyro 真实物理值
// 初始角度
float roll = 0.0f;
float pitch = 0.0f;
float yaw = 0.0f;

// 四元数
float q0 = 1.0f, q1 = 0.0f, q2 = 0.0f, q3 = 0.0f; // 四元数
//float integralFBx = 0.0f, integralFBy = 0.0f, integralFBz = 0.0f; // 积分项