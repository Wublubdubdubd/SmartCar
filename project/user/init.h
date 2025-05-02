#ifndef __INIT_H_
#define __INIT_H_

#define IPS_USE (1) // «∑Ò π”√∆¡ƒª

#include "zf_common_headfile.h"

#include "pid.h"
#include "ips114.h"
#include "imu.h"
#include "gps.h"
#include "bluetooth.h"
#include "pwm.h"
#include "filter.h"
#include "StateMachine.h"
#include "qspi.h"
#include "w25qxx.h"

void init(void);



#endif