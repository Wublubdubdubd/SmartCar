#ifndef __BUTTON_H_
#define __BUTTON_H_

#include "zf_common_headfile.h"

// ���尴������
#define KEY1_PIN    IO_P36
#define KEY2_PIN    IO_P37
#define KEY3_PIN    IO_P45

// ���ر�־λ
extern uint8 key1_flag;
extern uint8 key2_flag;
extern uint8 key3_flag;

void button_init(); //��ʼ��
void get_key(); //��ȡ����״̬
void refresh_button(); //ˢ�±�־λ

#endif