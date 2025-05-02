#include "filter.h"
/**
  * @brief 一阶互补滤波，用于平滑数据，
  * @param pData: 待滤波的数据  pPreData：前一时刻数据  alpha：滤波参数，表示对当前数据的信任程度
  * @return 无
  * @note 该函数并不更新PreData的数值，需自行在外部更新
  */
void FOCF(int16* pData,int16* pPreData,float alpha)
{
    *pData *= alpha ;
    *pData += (1-alpha)*(*pPreData);
}

/**
  * @brief IMU数据融合获取欧拉角 范围(-inf, inf)
  * @param acc：加速度 gyro：角速度 dt：积分时长
  * @return 无
  * @note (X Y Z)->(Roll Pitch Yaw)
  */
void GetEuler(float acc[], float gyro[], float dt) 
{
    // 从加速度计计算角度
    float acc_roll = atan2(acc[1], acc[2]) * 180.0f / 3.14159f;
    float acc_pitch = atan2(-acc[0], sqrt(acc[1] * acc[1] + acc[2] * acc[2])) * 180.0f / 3.14159f;

    // 从陀螺仪更新角度
    roll += ALPHA * gyro[0] * dt + (1 - ALPHA) * acc_roll;
    pitch += ALPHA * gyro[1] * dt + (1 - ALPHA) * acc_pitch;
    yaw += gyro[2] * dt ;
    
    //如果要与GPS融合 需要归一化到0~360
    //roll=fmod(roll+360,360) ;
    //pitch=fmod(pitch+360,360) ;
		if(yaw > 0)
			yaw=fmod(yaw+180,180) ;
		else
			yaw=fmod(yaw-180,-180) ;
		
		x_v += acc[0] * dt;
		x_p += x_v * dt;
}