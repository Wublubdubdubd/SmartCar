#ifndef __GPS_H_
#define __GPS_H_

#include "zf_device_gps_tau1201.h"
#include "zf_driver_eeprom.h"

#define point_size 2*sizeof(double)

extern bit gps_date_ready;//gps�����Ƿ�����ɹ� 0:ʧ�� 1:�ɹ�

extern double target_latitude, target_longitude;//Ŀ���ľ�γ��

extern double Object_one_points[];//��Ŀһ���ĸ���

//����ǰ��д��eeprom
void WritePoint(uint8 offset);

//��eeprom��ȡ��
void ReadPoint(double target_buffer[],uint8 origin_offset,uint8 target_offset);
  
#endif