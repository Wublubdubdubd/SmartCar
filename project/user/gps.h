#ifndef __GPS_H_
#define __GPS_H_

#include "zf_device_gps_tau1201.h"
#include "w25qxx.h"

#define point_size 2*sizeof(double)

extern bit gps_date_ready;//gps�����Ƿ�����ɹ� 0:ʧ�� 1:�ɹ�

extern double target_point[];//Ŀ���ľ�γ��

extern uint8* pObject; //ָ��ǰ��ĿĿ��������ָ��

extern uint8 Object_one_index[];//��Ŀһ���ĸ���

//����ǰ��д��eeprom
void WritePoint(uint8 offset);
//��eeprom��ȡ��
void ReadPoint(uint8 offset);
  
#endif