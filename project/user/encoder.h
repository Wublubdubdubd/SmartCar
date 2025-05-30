#ifndef _ENCODER_H
#define _ENCODER_H

#include "zf_device_gps_tau1201.h"

#define ENCODER_DIR_1                 	(TIM0_ENCOEDER)                         // 正交编码器对应使用的编码器接口 这里使用QTIMER1的ENCOEDER1
#define ENCODER_DIR_DIR_1              	(IO_P35)            				 	// DIR 对应的引脚
#define ENCODER_DIR_PULSE_1            	(TIM0_ENCOEDER_P34)            			// PULSE 对应的引脚

extern const float encode2vel;

extern int encoder_data;// 编码器读数

#endif