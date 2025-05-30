#ifndef _PID_H
#define _PID_H

#include "imu.h"
typedef struct
{
    float                kp;                    //P
    float                ki;                    //I
    float                kd;                    //D
    float                imax;                  //积分限幅
  
    float                out_i;                 //积分输出
    float                out;                   //pid输出
    float                outmax;                //输出限幅

    float                integrator;            //积分值
    float                last_error;            //上次误差
}pid_param_t;

extern pid_param_t angle_outer_pid;  //角度外环PID
extern pid_param_t angle_inner_pid;  //角度内环PID
extern pid_param_t velocity_outer_pid;  //速度外环PID
extern pid_param_t velocity_inner_pid;  //速度内环PID

extern float angle_outer_out, velocity_outer_out; //外环输出 作用于内环
extern float angle_inner_out,velocity_inner_out;//内环输出 作用于对象

extern float u_angle, u_velocity;/*外环控制量*/

extern float target_angle; //目标角度
extern float target_velocity; //目标速度
extern float velocity;//当前速度

extern int basic_up_duty; //抬升基础值
extern int basic_forward_duty; // 推进基础值
extern int forward_feed; // 前馈：左右电机PWM相差2x6%时，恰可走直线

extern int basic_duty_index;
extern uint32 basic_duty_up_left, basic_duty_up_right, basic_duty_forward_left, basic_duty_forward_right;//实际的基础值

float PidLocCtrl(pid_param_t * pid, float error, float t);//位置式控制
#endif
