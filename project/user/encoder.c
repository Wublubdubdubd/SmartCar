#include "encoder.h"

#define wheel_radius 0.017

const float encode2vel = - (2 * PI * wheel_radius / 1024) ;

int encoder_data = 0;// ±àÂëÆ÷¶ÁÊı
