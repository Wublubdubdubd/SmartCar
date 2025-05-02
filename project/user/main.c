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

BYTE buf[4096];
BYTE write_buf[4096]={1,1};

void main()
{
    // ���������ȶ��� �ٵ���
    char command[2];//������������ ʹ����ѯ��ʽ��ȡ ��Ӧ�ø�Ϊ�ж� 
    char str_buffer[100];//������Ϣ��buffer
  
    char write_index = 0; //���������������
    char read_index = 0; //����������������
  
    pObject = Object_one_index; //��Ŀһ��ʼ
			
    init();  
	
  
    while(1)
		{
#if IPS_USE     
      IPS114_Show_Info(); //��ʾ��Ҫ��Ϣ
#endif
			blue_tooth_read(command);
      /*
      ������� �ƻ����� s��1~4 ʹ���Զ����ӵ�Ŀ��ֵ ��
      s: 10%ռ�ձ�����̧����������Խ���
      
      1��̧�����ռ�ձ� + 10%
      2��̧�����ռ�ձ� - 10%
      3���ƽ����ռ�ձ� + 10%
      4���ƽ����ռ�ձ� - 10%
      
      b: ɲ�� �ĸ����ռ�ձ�ֵ 0%
      
      w: ��ǰ��Ŀ��EEPROM��д��ǰλ�õľ�γ�ȣ�д���󲻿���д��ֻ���������ٴ�����д�롣��ʱд��ȡ���뵱ǰ��Ŀ��δ���ƣ�
      r: ��ȡ��ǰ��Ŀ��һ�㵽Ŀ���
      
      p: ��ӡĿ��㾭γ�ȵ���������
      
      e������EEPROM��һҳ��д����ֵ 0 
      
      */
      switch(command[0])
      {
        case 's':;break;
        case '1':duty_up_left+=50;duty_up_right+=50;break;
        case '2':duty_up_left-=50;duty_up_right-=50;break;
        case '3':duty_forward_left+=50;duty_forward_right+=50;break;
        case '4':duty_forward_left-=50;duty_forward_right-=50;break;
        case 'b':duty_up_left=500;duty_up_right=500;duty_forward_left=500;duty_forward_right=500;
        sprintf(str_buffer,"Break!\r \n");ble6a20_send_string(str_buffer);break;
        case 'w':if( write_index < 4 ){WritePoint(pObject[write_index]); write_index++;}//W25Q_PageProgram_32(0, write_buf, 2);//
				sprintf(str_buffer,"Write!\r\n");ble6a20_send_string(str_buffer);break;
        case 'r':ReadPoint(pObject[read_index]); read_index++; read_index %= 4;//W25Q_FastRead_6B(0, buf, 256);//
				sprintf(str_buffer,"Read!\r\n");ble6a20_send_string(str_buffer);break;
        case 'p':sprintf(str_buffer,"Lat:%lf\r\nLon:%lf\r\n", target_point[0], target_point[1]);ble6a20_send_string(str_buffer);break;
        case 'e':W25Q_Erase4K_20(0, 1);//iap_erase_page(0);write_index = 0;//��һҳ 512k
        sprintf(str_buffer,"Erease!\r\n");ble6a20_send_string(str_buffer);break;
        default :;
      }
      command[0] = 0 ; //���
			command[1] = 0 ; 
//      ips114_show_float(0,64,roll,4,4);
//      ips114_show_float(80,64,pitch,4,4);
      //��ʾ�Ѵ�����͵�ǰ���ڵ�
			
			read_index += '1';
			write_index += '0';
      ips114_show_char(0,64,read_index);
      ips114_show_char(20,64,'/');
      ips114_show_char(40,64,write_index);
			read_index -= '1';
			write_index -= '0';
			
      ips114_show_float(160,64,yaw,4,4);
      system_delay_ms(500);
    }
}
