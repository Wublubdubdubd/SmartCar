#ifndef __GPS_H_
#define __GPS_H_

#include "zf_device_gps_tau1201.h"
#include "w25qxx.h"

#define point_size 2*sizeof(double)

extern bit gps_date_ready;//gps数据是否解析成功 0:失败 1:成功

extern bit init_yaw_lock;

extern double origin_point[];//起始点的经纬度

extern double target_point[];//目标点的经纬度

extern uint8* pObject; //指向当前科目目标点数组的指针

extern uint8 Object_one_index[];//科目一的四个点

extern uint8 PID_param_index[];//PID 参数

//将当前点写入eeprom
void WritePoint(uint8 offset);
//从eeprom读取点
void ReadPoint(uint8 offset);
  
#endif