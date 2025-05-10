#include "encoder.h"

#define wheel_radius 0.034

#define PI 3.1415926535

const float encode2vel = - (2 * PI * wheel_radius / 1024 * 100) ;

int encoder_data = 0;// ±àÂëÆ÷¶ÁÊı

float velocity = 0;// ËÙ¶È

