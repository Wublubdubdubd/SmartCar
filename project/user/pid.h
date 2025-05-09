#ifndef _PID_H
#define _PID_H

#include "zf_common_headfile.h"
#include "gps.h"

#define max_duty 1000

typedef struct
{
    float                kp;                    //P
    float                ki;                    //I
    float                kd;                    //D
    float                imax;                  //积分限幅

    float                out_p;                 //KP输出
    float                out_i;                 //KI输出
    float                out_d;                 //KD输出
    float                out;                   //pid输出
    float                outmax;                //输出限幅

    float                integrator;            //< 积分值
    float                last_error;            //< 上次误差
    float                last_derivative;       //< 上次误差与上上次误差之差
    unsigned long        last_t;                //< 上次时间
}pid_param_t;

// 角度PID初始化参数
extern float angle_KP, angle_KI,angle_KD, angle_IMAX, angle_OUTMAX;
extern float angle_target;
extern pid_param_t angle_pid;  // 角度PID
extern float angle_error; //角度误差


// 角度PID初始化参数
extern float velocity_KP, velocity_KI,velocity_KD, velocity_IMAX, velocity_OUTMAX;
extern float velocity_target;
extern pid_param_t velocity_pid;  // 速度PID
extern float angle_u,velocity_u;//速度环控制量

float Angle_Pid_fun(float dt); //角度环
float Velocity_Pid_fun(float dt); //速度环

void My_Pid_Init(void);
void Pid_Param_Init(pid_param_t * pid, float kp, float ki, float kd, float imax, float outmax);

float constrain_float(float amt, float low, float high);
short constrain_short(short amt, short low, short high);
unsigned long constrain_uint32(float amt);

float PidLocCtrl(pid_param_t * pid, float error, float t);
float PidIncCtrl(pid_param_t * pid, float error , float t);


#endif
