#ifndef __PWM_H_
#define __PWM_H_

#include "zf_driver_pwm.h"

#define FREQ               (50)                                                // 控制频率为50HZ，最高支持300HZ
#define PWM_1              (PWMB_CH4_P53) //面朝车屁股左 抬升电机
#define PWM_2              (PWMB_CH1_P50) //右 抬升电机
#define PWM_3              (PWMB_CH2_P51) //左 推进电机
#define PWM_4              (PWMB_CH3_P52) //右 推进电机

   
extern uint16 duty[]; //四个电机的占空比

void my_pwm_init(void);//初始化

void Break();//刹车

extern uint8 up_times; // 抬升电机占空比自增计数 自动运行，每次 + 1% 

extern int duty_up_left,duty_up_right;

extern int duty_forward_left,duty_forward_right;

#endif