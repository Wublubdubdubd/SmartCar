#include "gps.h"

bit gps_date_ready=0;

double target_latitude = 0, target_longitude = 0;//目标点的经纬度

/*
科目1 使用四个点
*/

double Object_one_points[4*2]={0};


//将当前点写入eeprom
void WritePoint(uint8 offset)
{
  iap_write_buff(offset, (uint8 *)&gps_tau1201.latitude, point_size);
}

//从eeprom读取点
void ReadPoint(double target_buffer[],uint8 origin_offset,uint8 target_offset)
{
  iap_read_buff(target_offset, (uint8 *)(target_buffer + origin_offset), point_size);
}
