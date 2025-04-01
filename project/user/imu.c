#include "imu.h"

float imu_acc[6],imu_gyro[6];//acc gyro ��ʵ����ֵ
// ��ʼ�Ƕ�
float roll = 0.0f;
float pitch = 0.0f;
float yaw = 0.0f;

char str_buffer[40];


// ������У׼���ڼ��ٶ�У׼����У�
#define GYRO_CALIB_SAMPLES 3000 // 30��@100Hz
float gyro_calib[3] = {0};

void gyro_calibration(void) 
{
    int i=0;
    for (i=0; i<GYRO_CALIB_SAMPLES; i++) {
        imu660ra_get_gyro();
        gyro_calib[0] += imu660ra_gyro_x;
        gyro_calib[1] += imu660ra_gyro_y;
        gyro_calib[2] += imu660ra_gyro_z;
        system_delay_ms(10); // 100Hz����
    }
    for (i=0; i<3; i++) {
        gyro_calib[i] /= GYRO_CALIB_SAMPLES; // ��ƫ
    }
}

// �����˲�����
void complementary_filter(float acc[], float gyro[], float dt) {
    // �Ӽ��ٶȼƼ���Ƕ�
    float acc_roll = atan2(acc[1], acc[2]) * 180.0f / 3.14159f;
    float acc_pitch = atan2(-acc[0], sqrt(acc[1] * acc[1] + acc[2] * acc[2])) * 180.0f / 3.14159f;


    // �������Ǹ��½Ƕ�
    roll += ALPHA * gyro[0] * dt + (1 - ALPHA) * acc_roll;
    pitch += ALPHA * gyro[1] * dt + (1 - ALPHA) * acc_pitch;
    yaw += gyro[2] * dt ;
  
    roll=fmod(roll,360) ;
    pitch=fmod(pitch,360) ;
    yaw=fmod(yaw,360) ;
}