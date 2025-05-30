#include "gps.h"

bit gps_date_ready=0;//gps�����Ƿ�������

double target_point[2] = {0};//Ŀ���ľ���γ��

double target_distance = 0; //��ǰ�㵽Ŀ���ľ���

double gps_point_error[2]={0};//�����ϵ���GPS��������

uint8* pObject = NULL; //ָ��ǰ��ĿĿ��������ָ��
uint8 cur_point_num = 0; //��ǰװ�ص�����
uint8 cur_object_num = 0; //��ǰ��Ŀ�����Ŀ
uint8 write_index = 0; //���������������
//bit is_erase = 0;//�������
/*

��Ŀ1 ʹ���ĸ���

���鱣�棺����EEPROM�ڵ�ƫ�Ƶ�ַ

ʹ�÷����� ReadPoint(Object_xxx_index[y]); 

���ɻ�ȡ�� y + 1 ����ľ���γ��

*/
const uint8 Object_one_num = 12; // ��Ŀһ�ĵ���
//uint8 Object_one_index[4] = {0 , 1 , 2 , 3}; // FLASH�е�����
double Object_1_Point[12][2]=
{0};

//����ǰ��д��eeprom
void WritePoint(uint8 offset)
{
	//W25Q_PageProgram_32(offset * point_size, (uint8 *)&gps_tau1201.latitude, point_size);
	Object_1_Point[offset][0]=gps_tau1201.latitude;
	Object_1_Point[offset][1]=gps_tau1201.longitude;
	cur_object_num++;
}

//��flash��ȡ��һ��Ŀ���
void LoadPoint()
{
  //uint16 offset;
  
  if(cur_point_num == cur_object_num) return;//�������һ���㣬����װ�أ�׼��������Ŀ
  
  //offset = pObject[cur_point_num];
  
	//W25Q_FastRead_6B(offset * point_size, (uint8 *)target_point, point_size);
  target_point[0] = Object_1_Point[cur_point_num][0];
	target_point[1] = Object_1_Point[cur_point_num][1];
  cur_point_num ++ ;
  
  //����
  target_point[0] += gps_point_error[0];
  target_point[1] += gps_point_error[1];
}

void GetGPSData()
{
	//��ȡgps����
	if(gps_tau1201_flag)
	{
		gps_tau1201_flag = 0;
		gps_date_ready = (!gps_data_parse()) ? 1 : 0;
	}
	else gps_date_ready = 0;
}
