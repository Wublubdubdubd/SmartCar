#ifndef __IPS114_H_
#define __IPS114_H_

#include "zf_device_ips114.h"
#include "zf_common_font.h"
#include "imu.h"
#include "gps.h"
#include "button.h"

void IPS114_Show_Unit(void); //显示单位

void IPS114_Show_Info(void); //显示信息

extern uint8 page_num; //页面

#endif
