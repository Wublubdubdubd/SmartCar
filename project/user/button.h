#ifndef __BUTTON_H_
#define __BUTTON_H_

#include "zf_common_headfile.h"

// 定义按键引脚
#define KEY1_PIN    IO_P36
#define KEY2_PIN    IO_P37
#define KEY3_PIN    IO_P45

// 开关标志位
extern uint8 key1_flag;
extern uint8 key2_flag;
extern uint8 key3_flag;

void button_init(); //初始化
void get_key(); //获取按键状态
void refresh_button(); //刷新标志位

#endif