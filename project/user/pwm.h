#ifndef __PWM_H_
#define __PWM_H_

#include "zf_driver_pwm.h"

#define FREQ               (50)                                                // ����Ƶ��Ϊ50HZ�����֧��300HZ
#define PWM_1              (PWMB_CH4_P53) //�泯��ƨ���� ̧�����
#define PWM_2              (PWMB_CH1_P50) //�� ̧�����
#define PWM_3              (PWMB_CH2_P51) //�� �ƽ����
#define PWM_4              (PWMB_CH3_P52) //�� �ƽ����

   
extern uint16 duty[]; //�ĸ������ռ�ձ�

void my_pwm_init(void);//��ʼ��

void Break();//ɲ��

extern uint8 up_times; // ̧�����ռ�ձ��������� �Զ����У�ÿ�� + 1% 

extern int duty_up_left,duty_up_right;

extern int duty_forward_left,duty_forward_right;

#endif