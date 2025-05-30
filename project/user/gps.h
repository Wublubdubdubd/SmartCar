#ifndef __GPS_H_
#define __GPS_H_

#include "zf_device_gps_tau1201.h"
#include "w25qxx.h"

#define point_size 2*sizeof(double)

extern bit gps_date_ready;//gps数据是否解析成功 0:失败 1:成功

extern double target_point[];//目标点的经纬度

extern double target_distance; //当前点到目标点的距离

extern double gps_point_error[];//俩次上电后的GPS点相对误差

extern uint8* pObject; //指向当前科目目标点数组的指针
extern uint8 cur_point_num; //当前装载点的序号
extern uint8 cur_object_num; //当前科目点的数目
extern uint8 write_index; //打点索引，测试用
//extern bit is_erase;//擦除与否

//extern uint8 Object_one_index[];//科目一的四个点
extern const uint8 Object_one_num; // 科目一的点数
extern double Object_1_Point[][2];
//将当前点写入eeprom
void WritePoint(uint8 offset);
//从flash读取上一次目标点
void LoadPoint();
//获取GPS数据
void GetGPSData();
#endif