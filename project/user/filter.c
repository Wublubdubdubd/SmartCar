#include "filter.h"
/**
  * @brief 一阶互补滤波，用于平滑数据
  * @param pData: 待滤波的数据  pPreData：前一时刻数据  alpha：滤波参数
  * @return 无
  */
void FOCF(int16* pData, int16* pPreData, float alpha)
{
    *pData *= alpha;
    *pData += (1-alpha)*(*pPreData);
}
/**
  * @brief atan2
  * @param 
  * @return 弧度制
  */
double my_atan2(double y, double x) {
    // 处理x = 0的情况
    if (x == 0) {
        if (y > 0) {
            return M_PI / 2; // y轴正半轴
        } else if (y < 0) {
            return -M_PI / 2; // y轴负半轴
        } else {
            return 0; // 原点
        }
    }
		else{
    // 计算基础角度
    double theta = atan(y / x);

    // 处理x ≠ 0的情况
    if (x > 0) {
        return theta; // 第一象限和第四象限
   // 处理x < 0的情况
    } else {
        if (y >= 0) {
            return theta + M_PI; // 第二象限或x轴负半轴
        } else {
            return theta - M_PI; // 第三象限
        }
     }
  }
}
/**
  * @brief 使用四元数法进行IMU数据融合获取欧拉角
  * @param acc：加速度计数据 gyro：陀螺仪数据 dt：积分时长
  * @return 无
  */
void GetEuler(float gyro[], float dt) 
{
    float norm; // 归一化因子

    // 陀螺仪数据转换为弧度/秒（因输入gyro[]单位为°/s）
    float gx = gyro[0] * 0.0174533f; // °/s -> rad/s
    float gy = gyro[1] * 0.0174533f;
    float gz = gyro[2] * 0.0174533f;

    // 四元数更新（仅陀螺仪积分）
    q0 += (-q1 * gx - q2 * gy - q3 * gz) * 0.5f * dt;
    q1 += ( q0 * gx + q2 * gz - q3 * gy) * 0.5f * dt;
    q2 += ( q0 * gy - q1 * gz + q3 * gx) * 0.5f * dt;
    q3 += ( q0 * gz + q1 * gy - q2 * gx) * 0.5f * dt;

    // 四元数归一化（防止数值发散）
    norm = sqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
    if (norm == 0.0f) return;
    q0 /= norm;
    q1 /= norm;
    q2 /= norm;
    q3 /= norm;

    // 四元数转欧拉角（弧度转角度）
    roll  = my_atan2(2.0f * (q0 * q1 + q2 * q3), 1.0f - 2.0f * (q1 * q1 + q2 * q2)) * 57.29578f;
    pitch = asin(2.0f * (q0 * q2 - q3 * q1)) * 57.29578f;
    yaw   = my_atan2(2.0f * (q0 * q3 + q1 * q2), 1.0f - 2.0f * (q2 * q2 + q3 * q3)) * 57.29578f;
}