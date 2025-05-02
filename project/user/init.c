#include "init.h"

void init()
{
    clock_init(SYSTEM_CLOCK_40M); // ��ر���
		debug_init(); // ��ر���
	
		//E2PROM��ʼ��
		QSPI_Init();
    W25Q_Enable_QE();
  
#if IPS_USE     
    //��Ļ��ʼ��
    ips114_init();
#endif
    
    //GPS��ʼ��
    gps_init();
	
    //������ʼ��
    while(ble6a20_init());

		//IMU��ʼ��
    while(imu660ra_init()!=0)
    {
#if IPS_USE      
        ips114_show_string(0, 16*1, "IMU660RA init error.");// IMU660RA ��ʼ��ʧ��
#else
        ble6a20_send_string("IMU660RA init error.\r\n"); 
#endif
    }

#if IPS_USE     
    ips114_clear(RGB565_WHITE);//����   
    IPS114_Show_Unit();//��ʾ��λ
#endif
    

        
    //pid��ʼ��
    My_Pid_Init();
    
    //�жϳ�ʼ��
    my_pit_init();
    
    //pwm��ʼ��
    my_pwm_init();
    
    //״̬������
    StateUpdate(Event_Finish);
}