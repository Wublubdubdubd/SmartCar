#include "gps.h"

bit gps_date_ready=0;

double target_latitude = 0, target_longitude = 0;//Ŀ���ľ�γ��

/*
��Ŀ1 ʹ���ĸ���
*/

double Object_one_points[4*2]={0};


//����ǰ��д��eeprom
void WritePoint(uint8 offset)
{
  iap_write_buff(offset, (uint8 *)&gps_tau1201.latitude, point_size);
}

//��eeprom��ȡ��
void ReadPoint(double target_buffer[],uint8 origin_offset,uint8 target_offset)
{
  iap_read_buff(target_offset, (uint8 *)(target_buffer + origin_offset), point_size);
}
