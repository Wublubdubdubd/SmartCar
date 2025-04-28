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


#include "init.h"


void main()
{
    char command;//������������ ʹ����ѯ��ʽ��ȡ ��Ӧ�ø�Ϊ�ж� 
    char str_buffer[100];//������Ϣ��buffer
    
    init();  
	
    while(1)
		{
#if IPS_USE     
      IPS114_Show_Info(); //��ʾ��Ҫ��Ϣ
#endif
      command=blue_tooth_read();
      switch(command)
      {
        case 's':pwm_set_duty(PWM_1,550);pwm_set_duty(PWM_2,550);break;
        case '1':duty_up_left+=50;duty_up_right+=50;break;
        case '2':duty_up_left-=50;duty_up_right-=50;break;
        case '3':duty_forward_left+=50;duty_forward_right+=50;break;
        case '4':duty_forward_left-=50;duty_forward_right-=50;break;
        case 'b':duty_up_left=500;duty_up_right=500;duty_forward_left=500;duty_forward_right=500;
        sprintf(str_buffer,"Break!\r\n");ble6a20_send_string(str_buffer);break;
        case 'w':WritePoint(0);
				sprintf(str_buffer,"Write!\r\n");ble6a20_send_string(str_buffer);break;
        case 'r':ReadPoint(Object_one_points, 0, 0);
				sprintf(str_buffer,"Read!\r\n");ble6a20_send_string(str_buffer);break;
        case 'p':sprintf(str_buffer,"Lat:%lf\r\nLon:%lf\r\n", Object_one_points[0], Object_one_points[1]);ble6a20_send_string(str_buffer);break;
        case 'e':iap_erase_page(0);//��һҳ 512k
        sprintf(str_buffer,"Erease!\r\n");ble6a20_send_string(str_buffer);break;
        default :;
      }
      
			//ble6a20_send_string("working\r\n");
			//sprintf(str_buffer,"Roll: %.2f, Pitch: %.2f", roll, pitch);
      //ble6a20_send_string(str_buffer);
//      ips114_show_int16(0,64,duty_up_left);
//      ips114_show_int16(80,64,duty_up_right);
      ips114_show_float(0,64,roll,4,4);
      ips114_show_float(80,64,pitch,4,4);
      ips114_show_float(160,64,yaw,4,4);
      system_delay_ms(500);
    }
}
