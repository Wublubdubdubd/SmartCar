#include "gps.h"

bit gps_date_ready=0;//gps�����Ƿ�������

bit init_yaw_lock = 0;
double target_point[2] = {0};//Ŀ���ľ���γ��

double origin_point[2] = {0};//��ʼ��ľ�γ��

double gps_point_error[2]={0};//�����ϵ���GPS��������

uint8* pObject = NULL; //ָ��ǰ��ĿĿ��������ָ��
/*

��Ŀ1 ʹ���ĸ���

���鱣�棺����EEPROM�ڵ�ƫ�Ƶ�ַ

ʹ�÷����� ReadPoint(Object_xxx_index[y]); 

���ɻ�ȡ�� y + 1 ����ľ���γ��

*/

// �޸�����Ϊ 0��1��2 ... ��дʱ * point_size
uint8 Object_one_index[4] = {0, 1 , 2 , 3 };
uint8 PID_param_index[3] = {4 , 5 , 6 };


//����ǰ��д��eeprom
void WritePoint(uint8 offset)
{
  //iap_write_buff(offset, (uint8 *)&gps_tau1201.latitude, point_size);
	W25Q_PageProgram_32(offset , (uint8 *)&gps_tau1201.latitude, point_size);
}

//��flash��ȡ��һ��Ŀ���
void ReadPoint(uint8 offset)
{
  //iap_read_buff(offset, (uint8 *)target_point, point_size);
	W25Q_FastRead_6B(offset * point_size, (uint8 *)target_point, point_size);
  
  //����
  target_point[0] += gps_point_error[0];
  target_point[1] += gps_point_error[1];
}
