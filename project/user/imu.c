#include "imu.h"

float imu_acc[3],imu_gyro[3];//acc gyro 真实物理值
// 初始角度
float roll = 0.0f;
float pitch = 0.0f;
float yaw = 0.0f;
// 初始速度
float x_v = 0.0f;
float y_v = 0.0f;
float z_v = 0.0f;
// 初始位置
float x_p = 0.0f;
float y_p = 0.0f;
float z_p = 0.0f;