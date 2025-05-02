#include "filter.h"
/**
  * @brief һ�׻����˲�������ƽ�����ݣ�
  * @param pData: ���˲�������  pPreData��ǰһʱ������  alpha���˲���������ʾ�Ե�ǰ���ݵ����γ̶�
  * @return ��
  * @note �ú�����������PreData����ֵ�����������ⲿ����
  */
void FOCF(int16* pData,int16* pPreData,float alpha)
{
    *pData *= alpha ;
    *pData += (1-alpha)*(*pPreData);
}

/**
  * @brief IMU�����ںϻ�ȡŷ���� ��Χ(-inf, inf)
  * @param acc�����ٶ� gyro�����ٶ� dt������ʱ��
  * @return ��
  * @note (X Y Z)->(Roll Pitch Yaw)
  */
void GetEuler(float acc[], float gyro[], float dt) 
{
    // �Ӽ��ٶȼƼ���Ƕ�
    float acc_roll = atan2(acc[1], acc[2]) * 180.0f / 3.14159f;
    float acc_pitch = atan2(-acc[0], sqrt(acc[1] * acc[1] + acc[2] * acc[2])) * 180.0f / 3.14159f;

    // �������Ǹ��½Ƕ�
    roll += ALPHA * gyro[0] * dt + (1 - ALPHA) * acc_roll;
    pitch += ALPHA * gyro[1] * dt + (1 - ALPHA) * acc_pitch;
    yaw += gyro[2] * dt ;
    
    //���Ҫ��GPS�ں� ��Ҫ��һ����0~360
    //roll=fmod(roll+360,360) ;
    //pitch=fmod(pitch+360,360) ;
		if(yaw > 0)
			yaw=fmod(yaw+180,180) ;
		else
			yaw=fmod(yaw-180,-180) ;
		
		x_v += acc[0] * dt;
		x_p += x_v * dt;
}