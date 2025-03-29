#include "init.h"

void init()
{
    clock_init(SYSTEM_CLOCK_40M); // ��ر���
		debug_init(); // ��ر���
  
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
    
    // ���ٶȼ�ת����LSB��Q16 m/s2��
    q32 ax = (q32)acc[0] * GRAVITY_Q / ACC_LSB2G;
    q32 ay = (q32)acc[1] * GRAVITY_Q / ACC_LSB2G;
    q32 az = (q32)acc[2] * GRAVITY_Q / ACC_LSB2G;
    
    // ��ʼroll/pitch��atan2����ʵ�֣��򻯰棩
    roll = ay * 100 / az;  // ���Ƽ��㣬ʵ������
    pitch = -ax * 100 / (ay>az? ay:az)

#if IPS_USE     
    ips114_clear(RGB565_WHITE);//����   
    IPS114_Show_Unit();//��ʾ��λ
#endif
    
    //�жϳ�ʼ��
    my_pit_init();
    
    //pwm��ʼ��
    my_pwm_init();
}