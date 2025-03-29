#ifndef __IMU_H_
#define __IMU_H_

#include "zf_device_imu660ra.h"

// ���������壨Q16��ʽ��16λ����+16λС����
typedef signed long q32;
#define Q16_SCALE 65536L

// ��������������������ʾ��
const q32 GYRO_LSB2DPS = 16400L;  // 16.4LSB/dps �� Q16:16400/65536=0.250244140625
const q32 ACC_LSB2G = 2048L;     // 2048LSB/g �� Q16:2048/65536=0.03125
const q32 GRAVITY_Q = 980665L;    // 9.80665m/s2 �� Q16:980665/65536��15.09945

// ��̬�ǣ�����������λ��1/65536���ȣ�
q32 roll = 0, pitch = 0;
q32 yaw_gyro = 0;  // �������ۻ����򣨴���Ư�ƣ�

// �����˲�������Q16��ʽ��0.98��64228��
const q32 ALPHA_Q = 64228;  // 0.98 * 65536 = 64228.48 �� ȡ��

// �������˷���a*b/Q16_SCALE��
q32 q_mul(q32 a, q32 b) {
    return (a * b) >> 16;
}

//acc gyro ��ʵ����ֵ
extern float imu_acc[],imu_gyro
  
//

#endif