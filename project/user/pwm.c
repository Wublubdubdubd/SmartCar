#include "pwm.h"

uint16 duty[4]={0}; //四个电机的占空比

int duty_up_left=500,duty_up_right=500;

int duty_forward_left=500,duty_forward_right=500;

void my_pwm_init(void)
{
    pwm_init(PWM_1, FREQ, 0);                                                   // PWM 通道1 初始化频率 50Hz  占空比初始为 0
    pwm_init(PWM_2, FREQ, 0);                                                   // PWM 通道2 初始化频率 50Hz  占空比初始为 0
	  pwm_init(PWM_3, FREQ, 0);                                                   // PWM 通道1 初始化频率 50Hz  占空比初始为 0
    pwm_init(PWM_4, FREQ, 0);                                                   // PWM 通道2 初始化频率 50Hz  占空比初始为 0
  
    // 电调控制是看高电平时间，范围： 1ms-2ms
    // 1ms 为 0%
    // 2ms 为 100%
    // 计算无刷电调转速   （1ms - 2ms）/20ms * 10000（10000是PWM的满占空比时候的值）
    // 在50Hz的控制频率下，无刷电调转速 0%   为 500
    // 在50Hz的控制频率下，无刷电调转速 20%  为 600
    // 在50Hz的控制频率下，无刷电调转速 40%  为 700
    // 在50Hz的控制频率下，无刷电调转速 60%  为 800
    // 在50Hz的控制频率下，无刷电调转速 80%  为 900
    // 在50Hz的控制频率下，无刷电调转速 100% 为 1000
}
