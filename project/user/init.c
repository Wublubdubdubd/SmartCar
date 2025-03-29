#include "init.h"

void init()
{
    clock_init(SYSTEM_CLOCK_40M); // 务必保留
		debug_init(); // 务必保留
  
#if IPS_USE     
    //屏幕初始化
    ips114_init();
#endif
    
    //GPS初始化
    gps_init();
  
    //蓝牙初始化
    while(ble6a20_init());

		//IMU初始化
    while(imu660ra_init()!=0)
    {
#if IPS_USE      
        ips114_show_string(0, 16*1, "IMU660RA init error.");// IMU660RA 初始化失败
#else
        ble6a20_send_string("IMU660RA init error.\r\n"); 
#endif
    }
    
    // 加速度计转换（LSB→Q16 m/s2）
    q32 ax = (q32)acc[0] * GRAVITY_Q / ACC_LSB2G;
    q32 ay = (q32)acc[1] * GRAVITY_Q / ACC_LSB2G;
    q32 az = (q32)acc[2] * GRAVITY_Q / ACC_LSB2G;
    
    // 初始roll/pitch（atan2定点实现，简化版）
    roll = ay * 100 / az;  // 近似计算，实际需查表法
    pitch = -ax * 100 / (ay>az? ay:az)

#if IPS_USE     
    ips114_clear(RGB565_WHITE);//清屏   
    IPS114_Show_Unit();//显示单位
#endif
    
    //中断初始化
    my_pit_init();
    
    //pwm初始化
    my_pwm_init();
}