#include "gps.h"

bit gps_date_ready=0;//gps数据是否解析完成

bit init_yaw_lock = 0;

double target_point[2] = {0};//目标点的经、纬度

double origin_point[2] = {0};//起始点的经纬度

uint8* pObject = NULL; //指向当前科目目标点数组的指针
/*

科目1 使用四个点

数组保存：点在EEPROM内的偏移地址

使用方法： ReadPoint(Object_xxx_index[y]); 

即可获取第 y + 1 个点的经、纬度

*/

uint8 Object_one_index[4] = {0, point_size, 2 * point_size, 3 * point_size};
uint8 PID_param_index[3] = {4 * point_size, 5 * point_size, 6 * point_size};


//将当前点写入eeprom
void WritePoint(uint8 offset)
{
  //iap_write_buff(offset, (uint8 *)&gps_tau1201.latitude, point_size);
	W25Q_PageProgram_32(offset, (uint8 *)&gps_tau1201.latitude, point_size);
}

//从eeprom读取点作为目标点
void ReadPoint(uint8 offset)
{
  //iap_read_buff(offset, (uint8 *)target_point, point_size);
	W25Q_FastRead_6B(offset, (uint8 *)target_point, point_size);
}
