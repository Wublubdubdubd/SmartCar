#include "imu.h"

float imu_acc[3],imu_gyro[3];//acc gyro ��ʵ����ֵ
// ��ʼ�Ƕ�
float roll = 0.0f;
float pitch = 0.0f;
float yaw = 0.0f;
// ��ʼ�ٶ�
float x_v = 0.0f;
float y_v = 0.0f;
float z_v = 0.0f;
// ��ʼλ��
float x_p = 0.0f;
float y_p = 0.0f;
float z_p = 0.0f;