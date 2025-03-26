/*********************************************************************************************************************
* AI8051U Opensourec Library ����AI8051U ��Դ�⣩��һ�����ڹٷ� SDK �ӿڵĵ�������Դ��
* Copyright (c) 2022 SEEKFREE ��ɿƼ�
*
* ���ļ���STC ��Դ���һ����
*
* AI8051U ��Դ�� ��������
* �����Ը��������������ᷢ���� GPL��GNU General Public License���� GNUͨ�ù������֤��������
* �� GPL �ĵ�3�棨�� GPL3.0������ѡ��ģ��κκ����İ汾�����·�����/���޸���
*
* ����Դ��ķ�����ϣ�����ܷ������ã�����δ�������κεı�֤
* ����û�������������Ի��ʺ��ض���;�ı�֤
* ����ϸ����μ� GPL
*
* ��Ӧ�����յ�����Դ���ͬʱ�յ�һ�� GPL �ĸ���
* ���û�У������<https://www.gnu.org/licenses/>
*
* ����ע����
* ����Դ��ʹ�� GPL3.0 ��Դ���֤Э�� �����������Ϊ���İ汾
* �������Ӣ�İ��� libraries/doc �ļ����µ� GPL3_permission_statement.txt �ļ���
* ���֤������ libraries �ļ����� �����ļ����µ� LICENSE �ļ�
* ��ӭ��λʹ�ò����������� ���޸�����ʱ���뱣����ɿƼ��İ�Ȩ����������������
*
* �ļ�����          
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          MDK FOR C251
* ����ƽ̨          AI8051U
* ��������          https://seekfree.taobao.com/
*
* �޸ļ�¼
* ����              ����           ��ע
* 2024-08-01        ��W            first version
********************************************************************************************************************/

#include "zf_common_headfile.h"
#include "pid.h"

#define PIT_IMU  (TIM0_PIT) // IMU �ж�Դ TIM0

void pit_hanlder_imu(void); // TIM0 �жϷ�����

//acc gyro ����
float imu_acc[3],imu_gyro[3];

void main()
{
    unsigned char index=0;  //ѭ������
    clock_init(SYSTEM_CLOCK_40M); // ��ر���
		debug_init(); // ��ر���
  
    //GPS��ʼ��
    gps_init();

    //��Ļ��ʼ��
		ips114_init();
		ips114_show_string(0, 16*0, "ISP init successfully.");
    
		//IMU��ʼ��
    while(imu660ra_init()!=0)
      ips114_show_string(0, 16*1, "IMU660RA init error.");                                 // IMU660RA ��ʼ��ʧ��
    
    system_delay_ms(1000); //����ɾ��
    ips114_clear(RGB565_WHITE);//����
    
    //���ٶ�
    ips114_set_color(RGB565_BLUE,RGB565_WHITE);
    ips114_show_string(0,16*0,"Acc: x,y,z");
    ips114_show_char(60,16*1,'g');
    ips114_show_char(140,16*1,'g');
    ips114_show_char(220,16*1,'g');
  
    //���ٶ�
    ips114_set_color(RGB565_PURPLE,RGB565_WHITE);
    ips114_show_string(0,16*2,"Gyro: x,y,z");
    ips114_show_char(60,16*3,'d');
    ips114_show_char(140,16*3,'d');
    ips114_show_char(220,16*3,'d');

    
    //GPS
    ips114_set_color(RGB565_YELLOW,RGB565_WHITE);
    ips114_show_string(0, 16*5, "S: ");//��λ״̬
    ips114_show_string(40, 16*5,"N: ");//������Ŀ
    ips114_show_string(100, 16*5,"H: ");//GPS���߸߶�

    ips114_show_string(0, 16*6, "Lat");//γ��
    ips114_show_string(120, 16*6, "Lon");//����
    ips114_show_string(0, 16*7, "v");//�ٶ�
    ips114_show_string(120, 16*7, "d");//����

    
    //�����жϻص����� 5ms����һ��IMU����
    tim0_irq_handler = pit_hanlder_imu;	
    pit_ms_init(PIT_IMU, 5);
	
		ips114_set_color(RGB565_RED,RGB565_WHITE);
    while(1)
		{
      //IMU
      for(index=0;index<3;index++)
      {
        ips114_show_float(80*index, 16*1 ,imu_acc[index],2,3);//���ٶ���Ϣ �ַ�8x16
        ips114_show_float(80*index, 16*3 ,imu_gyro[index],2,3);//���ٶ���Ϣ
      }
      //GPS
      if(gps_tau1201_flag)
      {
        gps_tau1201_flag = 0;
        if(!gps_data_parse())          //��ʼ��������
        {
				//��ʾGPSλ����Ϣ
        ips114_show_uint8(20, 16*5, gps_tau1201.state);
        ips114_show_uint8(60, 16*5, gps_tau1201.satellite_used);
        ips114_show_float(120, 16*5, gps_tau1201.height, 4, 6);
          
        ips114_show_float(20, 16*6, gps_tau1201.latitude, 4, 6);
        ips114_show_float(140, 16*6, gps_tau1201.longitude, 4, 6);
        ips114_show_float(20, 16*7, gps_tau1201.speed, 4, 6);
        ips114_show_float(140, 16*7, gps_tau1201.direction, 4, 6);

				
//				printf("gps_state       = %d\r\n" , gps_tau1201.state);         //�����ǰ��λ��Чģʽ 1����λ��Ч  0����λ��Ч
//				printf("latitude        = %lf\r\n", gps_tau1201.latitude);      //���γ����Ϣ
//				printf("longitude       = %lf\r\n", gps_tau1201.longitude);     //���������Ϣ
//				printf("speed           = %lf\r\n", gps_tau1201.speed);         //����ٶ���Ϣ
//				printf("direction       = %lf\r\n", gps_tau1201.direction);     //���������Ϣ
//				printf("satellite_used  = %d\r\n" , gps_tau1201.satellite_used);//�����ǰ���ڶ�λ����������
//				printf("height          = %lf\r\n", gps_tau1201.height);        //�����ǰGPS���������߶�
        }
      }
      system_delay_ms(1000);
     }
}
/**
  * @brief TIM0�жϴ���������ȡimu����
  * @param ��
  * @return ��
  */
void pit_hanlder_imu(void)
{
    imu660ra_get_acc();                                                         // ��ȡ IMU660RA �ļ��ٶȲ�����ֵ
    imu660ra_get_gyro();                                                        // ��ȡ IMU660RA �Ľ��ٶȲ�����ֵ
    
    //ת��Ϊʵ������ֵ
	  imu_acc[0]=imu660ra_acc_x/imu660ra_transition_factor[0];
	  imu_acc[1]=imu660ra_acc_y/imu660ra_transition_factor[0];
	  imu_acc[2]=imu660ra_acc_z/imu660ra_transition_factor[0];
	
		imu_gyro[0]=imu660ra_gyro_x/imu660ra_transition_factor[1];
	  imu_gyro[1]=imu660ra_gyro_y/imu660ra_transition_factor[1];
	  imu_gyro[2]=imu660ra_gyro_z/imu660ra_transition_factor[1]; 
}


