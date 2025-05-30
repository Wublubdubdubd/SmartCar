#include "pid.h"
pid_param_t angle_outer_pid =  //角度外环PID
{
0.8, //P *
0.0, //I *
1.3, //D *
30,  //积分限幅 *
0,   //积分输出
0,   //pid输出
42, //输出限幅 *
0,   //积分值
0    //上次误差
};
pid_param_t angle_inner_pid =  //角度内环PID
{
0.40, //P *
0.0, //I *
0.55, //D *
0,  //积分限幅 *
0,   //积分输出
0,   //pid输出
10, //输出限幅 *
0,   //积分值
0    //上次误差
};
pid_param_t velocity_outer_pid =  //速度外环PID
{
3.5, //P *
0.0, //I *
6.0, //D *
0,  //积分限幅 *
0,   //积分输出
0,   //pid输出
10, //输出限幅 *
0,   //积分值
0    //上次误差
};
pid_param_t velocity_inner_pid =  //速度内环PID
{
20, //P *
0.0, //I *
20, //D *
0,  //积分限幅 *
0,   //积分输出
0,   //pid输出
10, //输出限幅 *
0,   //积分值
0    //上次误差
};
/*内外环输出量*/
float angle_outer_out = 0, velocity_outer_out = 0; //外环输出 作用于内环
float angle_inner_out = 0, velocity_inner_out = 0; //内环输出 作用于对象
/*外环控制量*/
float u_angle = 0, u_velocity = 0;

int basic_up_duty = 85;//抬升基础值
int basic_forward_duty = 60; // 推进基础值
int forward_feed = 7; // 前馈：左右电机PWM相差2x6%时，恰可走直线

float target_angle = 0; //目标角度
float target_velocity = 1.0; //目标速度
float velocity = 0;//当前速度
int basic_duty_index = 0;
uint32 basic_duty_up_left=500, basic_duty_up_right=500, basic_duty_forward_left=500, basic_duty_forward_right=500;

/*******************************************************************************
* 函 数 名         : PidLocCtrl
* 函数功能	   : 位置式PID控制
* 输    入         : pid, error, t
* 输    出         : float
*******************************************************************************/
float PidLocCtrl(pid_param_t * pid, float error, float t)
{
    /* 误差限幅 */
    pid->integrator += error;
    pid->integrator = (pid->out_i > pid->imax) ? pid->imax: pid->integrator;
    pid->integrator = (pid->out_i < (-pid->imax)) ? (-pid->imax): pid->integrator;

    pid->last_error = error;

    pid->out = pid->kp*error + pid->ki* t * pid->integrator + pid->kd / t  *(error - pid->last_error);
    
    pid->out = (pid->out > pid->outmax) ? pid->outmax: pid->out;
    pid->out = (pid->out < (-pid->outmax)) ? (-pid->outmax): pid->out;
    
    return pid->out;
}