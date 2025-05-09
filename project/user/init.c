#include "init.h"

void init()
{
    clock_init(SYSTEM_CLOCK_40M); // 务必保留
		debug_init(); // 务必保留
	
		//E2PROM初始化
		QSPI_Init();
    W25Q_Enable_QE();
  
    //按键初始化
    button_init();
  
    //编码器初始化
    encoder_dir_init(ENCODER_DIR_1, ENCODER_DIR_DIR_1, ENCODER_DIR_PULSE_1);
  
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

#if IPS_USE     
    ips114_clear(RGB565_WHITE);//清屏   
    IPS114_Show_Unit();//显示单位
#endif
    
    //pid初始化
    My_Pid_Init();
    
    //中断初始化
    my_pit_init();
    
    //pwm初始化
    my_pwm_init();
    
    //状态机更新
    curState = State_Init;
}