#ifndef __PWM_H_
#define __PWM_H_

#include "zf_driver_pwm.h"

#define FREQ               (50)                                                // 控制频率为50HZ，最高支持300HZ
#define PWM_1              (PWMA_CH2P_P12)
#define PWM_2              (PWMA_CH4P_P26)
#define PWM_3              (PWMB_CH1_P50)
#define PWM_4              (PWMB_CH4_P53)

extern uint16 duty[]; //四个电机的占空比

void my_pwm_init(void);//初始化

#endif