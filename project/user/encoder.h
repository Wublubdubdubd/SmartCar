#ifndef _ENCODER_H
#define _ENCODER_H

#define ENCODER_DIR_1                 	(TIM0_ENCOEDER)                         // ������������Ӧʹ�õı������ӿ� ����ʹ��QTIMER1��ENCOEDER1
#define ENCODER_DIR_DIR_1              	(IO_P35)            				 	// DIR ��Ӧ������
#define ENCODER_DIR_PULSE_1            	(TIM0_ENCOEDER_P34)            			// PULSE ��Ӧ������

extern const float encode2vel;

extern int encoder_data;// ����������

extern float velocity;// �ٶ�

#endif