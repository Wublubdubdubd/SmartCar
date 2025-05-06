#include "gps.h"

bit gps_date_ready=0;//gps数据是否解析完成

bit init_yaw_lock = 0;
double target_point[2] = {0};//目标点的经、纬度

double origin_point[2] = {0};//起始点的经纬度

double gps_point_error[2]={0};//两次上电后的GPS点相对误差

uint8* pObject = NULL; //指向当前科目目标点数组的指针
/*

科目1 使用四个点

数组保存：点在EEPROM内的偏移地址

使用方法： ReadPoint(Object_xxx_index[y]); 

即可获取第 y + 1 个点的经、纬度

*/

// 修改索引为 0、1、2 ... 读写时 * point_size
uint8 Object_one_index[4] = {0, 1 , 2 , 3 };
uint8 PID_param_index[3] = {4 , 5 , 6 };


//将当前点写入eeprom
void WritePoint(uint8 offset)
{
  //iap_write_buff(offset, (uint8 *)&gps_tau1201.latitude, point_size);
	W25Q_PageProgram_32(offset , (uint8 *)&gps_tau1201.latitude, point_size);
}

//从flash读取上一次目标点
void ReadPoint(uint8 offset)
{
  //iap_read_buff(offset, (uint8 *)target_point, point_size);
	W25Q_FastRead_6B(offset * point_size, (uint8 *)target_point, point_size);
  
  //修正
  target_point[0] += gps_point_error[0];
  target_point[1] += gps_point_error[1];
}
