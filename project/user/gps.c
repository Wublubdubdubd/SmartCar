#include "gps.h"

bit gps_date_ready=0;//gps数据是否解析完成

double target_point[2] = {0};//目标点的经、纬度

double target_distance = 0; //当前点到目标点的距离

double gps_point_error[2]={0};//两次上电后的GPS点相对误差

uint8* pObject = NULL; //指向当前科目目标点数组的指针
uint8 cur_point_num = 0; //当前装载点的序号
uint8 cur_object_num = 0; //当前科目点的数目
uint8 write_index = 0; //打点索引，测试用
//bit is_erase = 0;//擦除与否
/*

科目1 使用四个点

数组保存：点在EEPROM内的偏移地址

使用方法： ReadPoint(Object_xxx_index[y]); 

即可获取第 y + 1 个点的经、纬度

*/
const uint8 Object_one_num = 12; // 科目一的点数
//uint8 Object_one_index[4] = {0 , 1 , 2 , 3}; // FLASH中的索引
double Object_1_Point[12][2]=
{0};

//将当前点写入eeprom
void WritePoint(uint8 offset)
{
	//W25Q_PageProgram_32(offset * point_size, (uint8 *)&gps_tau1201.latitude, point_size);
	Object_1_Point[offset][0]=gps_tau1201.latitude;
	Object_1_Point[offset][1]=gps_tau1201.longitude;
	cur_object_num++;
}

//从flash读取上一次目标点
void LoadPoint()
{
  //uint16 offset;
  
  if(cur_point_num == cur_object_num) return;//到达最后一个点，不再装载，准备更换科目
  
  //offset = pObject[cur_point_num];
  
	//W25Q_FastRead_6B(offset * point_size, (uint8 *)target_point, point_size);
  target_point[0] = Object_1_Point[cur_point_num][0];
	target_point[1] = Object_1_Point[cur_point_num][1];
  cur_point_num ++ ;
  
  //修正
  target_point[0] += gps_point_error[0];
  target_point[1] += gps_point_error[1];
}

void GetGPSData()
{
	//获取gps数据
	if(gps_tau1201_flag)
	{
		gps_tau1201_flag = 0;
		gps_date_ready = (!gps_data_parse()) ? 1 : 0;
	}
	else gps_date_ready = 0;
}
