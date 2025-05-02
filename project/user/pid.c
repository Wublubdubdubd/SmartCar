#include "pid.h"

// 角度PID初始化参数
float angle_KP = 2.5, angle_KI = 0,angle_KD = 0.0, angle_IMAX = 20, angle_OUTMAX = 50;

pid_param_t angle_pid; //角度PID
float angle_target = 0;//角度输入
float angle_error = 0; //角度误差

float Angle_Pid_fun()
{  
    //获取当前点到目标点的角度
		angle_target = get_two_points_azimuth(gps_tau1201.latitude, gps_tau1201.longitude, target_point[0], target_point[1]);
		angle_target -= 180; //修正到yaw的范围  yaw : -180 ~ 180 
		angle_error = angle_target - yaw;// error :-360 ~ 360
		//误差修正到 -180~180，即最小的旋转角度
		if(angle_error > 180) angle_error -= 360;
		else if(angle_error < -180) angle_error += 360;
		
    //角度环
    PidLocCtrl(&angle_pid,angle_error,0.01);
	
		return angle_pid.out;
}

/*******************************************************************************
* 函 数 名         : My_Pid_Init
* 函数功能         : PID初始化	
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void My_Pid_Init(void)
{
    Pid_Param_Init(&angle_pid,angle_KP, angle_KI,angle_KD, angle_IMAX, angle_OUTMAX);
}


/*******************************************************************************
* 函 数 名         : Pid_Param_Init
* 函数功能         : PID参数初始化	
* 输    入         : imax:积分项最大值
* 输    出         : 无
*******************************************************************************/
void Pid_Param_Init(pid_param_t * pid, float kp, float ki, float kd, float imax, float outmax)
{
    pid->kp        = kp;
    pid->ki        = ki;
    pid->kd        = kd;
    pid->imax      = imax;
    pid->out_p     = 0;
    pid->out_i     = 0;
    pid->out_d     = 0;
    pid->out       = 0;
    pid->outmax    = outmax;
    pid->integrator= 0;
    pid->last_error= 0;
    pid->last_derivative   = 0;
    pid->last_t    = 0;
}

/*******************************************************************************
* 函 数 名         : PidLocCtrl
* 函数功能	   : 位置式PID控制
* 输    入         : pid, error, t
* 输    出         : float
*******************************************************************************/
float PidLocCtrl(pid_param_t * pid, float error, float t)
{
    /* 累积误差 */
    pid->integrator += error;

    /* 误差限幅 */
    pid->out_i = constrain_float(pid->integrator, -pid->imax, pid->imax);


    pid->out_p = pid->kp * error;
    pid->out_i = pid->ki * t * pid->integrator;
    pid->out_d = pid->kd/t * (error - pid->last_error);

    pid->last_error = error;

    pid->out = pid->out_p + pid->out_i + pid->out_d;

    pid->out = constrain_float(pid->out, -pid->outmax, pid->outmax);

    return pid->out;
}


/*******************************************************************************
* 函 数 名         : PidIncCtrl
* 函数功能	   : 增量式PID控制
* 输    入         : pid, error, t
* 输    出         : float
*******************************************************************************/
float PidIncCtrl(pid_param_t * pid, float error, float t)
{

    pid->out_p = pid->kp * (error - pid->last_error);
    pid->out_i = pid->ki * error * t ;
    pid->out_d = pid->kd/t * ((error - pid->last_error) - pid->last_derivative);

    pid->last_derivative = error - pid->last_error;
    pid->last_error = error;

    pid->out += pid->out_p + pid->out_i + pid->out_d;

    pid->out = constrain_float(pid->out, -pid->outmax, pid->outmax);
    return pid->out;
}

/*******************************************************************************
* 函 数 名         : constrain_float
* 函数功能         : 浮点型数限幅
* 输    入         : amt,low,high
* 输    出         : float
*******************************************************************************/
float constrain_float(float amt, float low, float high)
{
    return ((amt)<(low)?(low):((amt)>(high)?(high):(amt)));
}

/*******************************************************************************
* 函 数 名         : constrain_short
* 函数功能         : 短整型数限幅
* 输    入         : amt,low,high
* 输    出         : short
*******************************************************************************/
short constrain_short(short amt, short low, short high)
{
    return ((amt)<(low)?(low):((amt)>(high)?(high):(amt)));
}

/*******************************************************************************
* 函 数 名         : constrain_uint32
* 函数功能         : 限幅
* 输    入         : amt,low,high
* 输    出         : uint32
*******************************************************************************/
unsigned long constrain_uint32(float amt)
{
    return ((amt)<(0)?(0):((amt)>(max_duty)?(max_duty):(amt)));
}
