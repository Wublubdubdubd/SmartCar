#include "init.h"

void init()
{
    clock_init(SYSTEM_CLOCK_40M); // 务必保留
		//debug_init(); // 务必保留
	
		//E2PROM初始化
		//QSPI_Init();
    //W25Q_Enable_QE();
  
    //按键初始化
    button_init();
  
    //编码器初始化
    encoder_dir_init(ENCODER_DIR_1, ENCODER_DIR_DIR_1, ENCODER_DIR_PULSE_1);
 
    //屏幕初始化
    ips114_init();

    //GPS初始化
    gps_init();
	
    //蓝牙初始化
    while(ble6a20_init());

		//IMU初始化
    while(imu660ra_init()!=0);
  
    IPS114_Show_Unit();//显示单位
    
    //中断初始化
    my_pit_init();
    
    //pwm初始化
    my_pwm_init();
    
    //状态机更新
    curState = State_Init;
}