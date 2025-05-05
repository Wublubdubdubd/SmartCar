#include "filter.h"
/**
  * @brief һ�׻����˲�������ƽ������
  * @param pData: ���˲�������  pPreData��ǰһʱ������  alpha���˲�����
  * @return ��
  */
void FOCF(int16* pData, int16* pPreData, float alpha)
{
    *pData *= alpha;
    *pData += (1-alpha)*(*pPreData);
}
/**
  * @brief atan2
  * @param 
  * @return ������
  */
double my_atan2(double y, double x) {
    // ����x = 0�����
    if (x == 0) {
        if (y > 0) {
            return M_PI / 2; // y��������
        } else if (y < 0) {
            return -M_PI / 2; // y�Ḻ����
        } else {
            return 0; // ԭ��
        }
    }
		else{
    // ��������Ƕ�
    double theta = atan(y / x);

    // ����x �� 0�����
    if (x > 0) {
        return theta; // ��һ���޺͵�������
   // ����x < 0�����
    } else {
        if (y >= 0) {
            return theta + M_PI; // �ڶ����޻�x�Ḻ����
        } else {
            return theta - M_PI; // ��������
        }
     }
  }
}
/**
  * @brief ʹ����Ԫ��������IMU�����ںϻ�ȡŷ����
  * @param acc�����ٶȼ����� gyro������������ dt������ʱ��
  * @return ��
  */
void GetEuler(float gyro[], float dt) 
{
    float norm; // ��һ������

    // ����������ת��Ϊ����/�루������gyro[]��λΪ��/s��
    float gx = gyro[0] * 0.0174533f; // ��/s -> rad/s
    float gy = gyro[1] * 0.0174533f;
    float gz = gyro[2] * 0.0174533f;

    // ��Ԫ�����£��������ǻ��֣�
    q0 += (-q1 * gx - q2 * gy - q3 * gz) * 0.5f * dt;
    q1 += ( q0 * gx + q2 * gz - q3 * gy) * 0.5f * dt;
    q2 += ( q0 * gy - q1 * gz + q3 * gx) * 0.5f * dt;
    q3 += ( q0 * gz + q1 * gy - q2 * gx) * 0.5f * dt;

    // ��Ԫ����һ������ֹ��ֵ��ɢ��
    norm = sqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
    if (norm == 0.0f) return;
    q0 /= norm;
    q1 /= norm;
    q2 /= norm;
    q3 /= norm;

    // ��Ԫ��תŷ���ǣ�����ת�Ƕȣ�
    roll  = my_atan2(2.0f * (q0 * q1 + q2 * q3), 1.0f - 2.0f * (q1 * q1 + q2 * q2)) * 57.29578f;
    pitch = asin(2.0f * (q0 * q2 - q3 * q1)) * 57.29578f;
    yaw   = my_atan2(2.0f * (q0 * q3 + q1 * q2), 1.0f - 2.0f * (q2 * q2 + q3 * q3)) * 57.29578f;
}