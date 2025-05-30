#ifndef __GUI_H_
#define __GUI_H_
/* 模块说明

名称：图像界面

功能：
  1)确认机器人状态
  2)调整参数
  3)开启机器人
  
*/
#include "ips114.h"
#include 
/*全局变量*/


/*全局函数*/
void IPS114_Show_Unit(void); //显示单位

void IPS114_Show_Info(void); //显示信息

void GUI_Handle_Key(void);

#endif