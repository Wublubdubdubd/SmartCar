#ifndef __IPS114_H_
#define __IPS114_H_

#include "zf_device_ips114.h"
#include "zf_common_font.h"
#include "imu.h"
#include "gps.h"
#include "button.h"
#include "pid.h"
#include "StateMachine.h"

void IPS114_Show_Unit(void); //��ʾ��λ

void IPS114_Show_Info(void); //��ʾ��Ϣ

void GUI_Handle_Key(void);

#endif
