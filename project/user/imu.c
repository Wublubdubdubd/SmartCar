#include "imu.h"

float imu_acc[3],imu_gyro[3];//acc gyro ��ʵ����ֵ
// ��ʼ�Ƕ�
float roll = 0.0f;
float pitch = 0.0f;
float yaw = 0.0f;

// ��Ԫ��
float q0 = 1.0f, q1 = 0.0f, q2 = 0.0f, q3 = 0.0f; // ��Ԫ��
//float integralFBx = 0.0f, integralFBy = 0.0f, integralFBz = 0.0f; // ������