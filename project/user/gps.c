#include "gps.h"

bit gps_date_ready=0;//gps�����Ƿ�������

bit init_yaw_lock = 0;

double target_point[2] = {0};//Ŀ���ľ���γ��

double origin_point[2] = {0};//��ʼ��ľ�γ��

uint8* pObject = NULL; //ָ��ǰ��ĿĿ��������ָ��
/*

��Ŀ1 ʹ���ĸ���

���鱣�棺����EEPROM�ڵ�ƫ�Ƶ�ַ

ʹ�÷����� ReadPoint(Object_xxx_index[y]); 

���ɻ�ȡ�� y + 1 ����ľ���γ��

*/

uint8 Object_one_index[4] = {0, point_size, 2 * point_size, 3 * point_size};
uint8 PID_param_index[3] = {4 * point_size, 5 * point_size, 6 * point_size};


//����ǰ��д��eeprom
void WritePoint(uint8 offset)
{
  //iap_write_buff(offset, (uint8 *)&gps_tau1201.latitude, point_size);
	W25Q_PageProgram_32(offset, (uint8 *)&gps_tau1201.latitude, point_size);
}

//��eeprom��ȡ����ΪĿ���
void ReadPoint(uint8 offset)
{
  //iap_read_buff(offset, (uint8 *)target_point, point_size);
	W25Q_FastRead_6B(offset, (uint8 *)target_point, point_size);
}
