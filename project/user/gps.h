#ifndef __GPS_H_
#define __GPS_H_

#include "zf_device_gps_tau1201.h"
#include "zf_driver_eeprom.h"

#define point_size 2*sizeof(double)

extern bit gps_date_ready;//gps数据是否解析成功 0:失败 1:成功

extern double target_latitude, target_longitude;//目标点的经纬度

extern double Object_one_points[];//科目一的四个点

//将当前点写入eeprom
void WritePoint(uint8 offset);

//从eeprom读取点
void ReadPoint(double target_buffer[],uint8 origin_offset,uint8 target_offset);
  
#endif