#include "init.h"

void init()
{
    clock_init(SYSTEM_CLOCK_40M); // ��ر���
		//debug_init(); // ��ر���
	
		//E2PROM��ʼ��
		//QSPI_Init();
    //W25Q_Enable_QE();
  
    //������ʼ��
    button_init();
  
    //��������ʼ��
    encoder_dir_init(ENCODER_DIR_1, ENCODER_DIR_DIR_1, ENCODER_DIR_PULSE_1);
 
    //��Ļ��ʼ��
    ips114_init();

    //GPS��ʼ��
    gps_init();
	
    //������ʼ��
    while(ble6a20_init());

		//IMU��ʼ��
    while(imu660ra_init()!=0);
  
    IPS114_Show_Unit();//��ʾ��λ
    
    //�жϳ�ʼ��
    my_pit_init();
    
    //pwm��ʼ��
    my_pwm_init();
    
    //״̬������
    curState = State_Init;
}