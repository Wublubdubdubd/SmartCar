#ifndef __GPS_H_
#define __GPS_H_

#include "zf_device_gps_tau1201.h"
#include "w25qxx.h"

#define point_size 2*sizeof(double)

extern bit gps_date_ready;//gps�����Ƿ�����ɹ� 0:ʧ�� 1:�ɹ�

extern double target_point[];//Ŀ���ľ�γ��

extern double target_distance; //��ǰ�㵽Ŀ���ľ���

extern double gps_point_error[];//�����ϵ���GPS��������

extern uint8* pObject; //ָ��ǰ��ĿĿ��������ָ��
extern uint8 cur_point_num; //��ǰװ�ص�����
extern uint8 cur_object_num; //��ǰ��Ŀ�����Ŀ
extern uint8 write_index; //���������������
//extern bit is_erase;//�������

//extern uint8 Object_one_index[];//��Ŀһ���ĸ���
extern const uint8 Object_one_num; // ��Ŀһ�ĵ���
extern double Object_1_Point[][2];
//����ǰ��д��eeprom
void WritePoint(uint8 offset);
//��flash��ȡ��һ��Ŀ���
void LoadPoint();
//��ȡGPS����
void GetGPSData();
#endif