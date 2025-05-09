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
    char command[command_size];//������������
  
    char str_buffer[50];//������������Ϣ��buffer
  
    char write_index = 0; //���������������
  
    float temp_float = 0; // ��ʱ����
		
    //��Ŀһ��ʼ
    pObject = Object_one_index; 
    cur_object_num = Object_one_num;
		
    //�豸��ʼ��
    init();
    
    while(1)
		{
      get_key();
#if IPS_USE     
      IPS114_Show_Info(); //��ʾ��Ҫ��Ϣ
#endif
			blue_tooth_read(command);
      /*
      ���:
      s: ��¼��ʼ�㣬����GPS��׼����ʼ��yaw��
      
      b: ɲ�� �ĸ����ռ�ձ�ֵ 0%
      
      w: ��ǰ��Ŀ��EEPROM��д��ǰλ�õľ�γ�ȣ�д���󲻿���д��ֻ���������ٴ�����д�롣��ʱд��ȡ���뵱ǰ��Ŀ��δ���ƣ�
           
      e������EEPROM��һҳ��д����ֵ 0 
      
      */
      if((curState == State_Init) && key2_flag)curState = State_Unlock;
      
      switch(command[0])
      {
        case 's':
        {
          if(curState == State_Unlock)
          {
            //װ�� P1 �� target
            LoadPoint();
           
            // ����gps��Ư��
            gps_point_error[0] = gps_tau1201.latitude - target_point[0];
            gps_point_error[1] = gps_tau1201.longitude - target_point[1];
            
            // �����ʾ���
            sprintf(str_buffer,"Start!\r\nGPS Error: lat %lf lon %lf\r\n",gps_point_error[0],gps_point_error[1]);ble6a20_send_string(str_buffer);
            
            // ����״̬
            curState = State_Yaw_Init;
          }
          break;
        }
        case 'b':
        {
          curState = State_Shut;
          sprintf(str_buffer,"Break!\r \n");ble6a20_send_string(str_buffer);
          break;
        }
        case 'w':
        {
          WritePoint(pObject[write_index++]);//W25Q_PageProgram_32(0, write_buf, 2);
          sprintf(str_buffer,"Write P%d!\r\n",write_index);ble6a20_send_string(str_buffer);
          break;
        }
        case 'e':
        {
          W25Q_Erase4K_20(0, 1);//iap_erase_page(0);write_index = 0;//��һҳ 512k
          sprintf(str_buffer,"Erease!\r\n");ble6a20_send_string(str_buffer);
          break;
        }
        case 'A':
        {
          temp_float = func_str_to_float(&command[2]);
          switch(command[1])
          {
            case 'P':angle_KP = temp_float;break;
            case 'I':angle_KI = temp_float;break;
            case 'D':angle_KD = temp_float;break;
          }
          break;
        }
        case 'V':
        {
          temp_float = func_str_to_float(&command[2]);
          switch(command[1])
          {
            case 'P':velocity_KP = temp_float;break;
            case 'I':velocity_KI = temp_float;break;
            case 'D':velocity_KD = temp_float;break;
          }
          break;          
        }
        case 'U':
        {
          curState = State_Yaw_Init;
          sprintf(str_buffer,"Start!\r\n");ble6a20_send_string(str_buffer);
          break;
        }
        default :;
      }
			//sprintf(str_buffer,"%f\r\n%f\r\n",angle_u,velocity_u);ble6a20_send_string(str_buffer);
      memset(command,0,command_size);
      refresh_button();
      
      switch(curState)
      {
        case State_Yaw_Init:
        {
          target_distance = get_two_points_distance(target_point[0],target_point[1],gps_tau1201.latitude,gps_tau1201.longitude);
        
          //sprintf(str_buffer,"D:%lf \r\n",target_distance);ble6a20_send_string(str_buffer);
          
          // �뿪���׺�
          if(target_distance > 2)
          {
            //����yaw��
            yaw = get_two_points_azimuth(target_point[0],target_point[1],gps_tau1201.latitude,gps_tau1201.longitude);
            //������-180~180
            if( (180 <= yaw) && (yaw < 360))
              yaw -= 360;
            //������imu����ϵ
            yaw = - yaw;
            //������Ԫ��
            EulerToQuaternion();
            //��ʾ��Ϣ
            sprintf(str_buffer,"Init! D:%lf Y:%lf\r\n",target_distance,yaw);ble6a20_send_string(str_buffer);
            //װ����һĿ���
            LoadPoint();

            sprintf(str_buffer,"Load P%d!\r\n",cur_point_num);ble6a20_send_string(str_buffer);
            
            curState = State_Subject_1;
            
            target_distance = 999;
          }
          break;
        }
        case State_Subject_1:
        {
          sprintf(str_buffer,"Error:%f!\r\n",angle_error);ble6a20_send_string(str_buffer);

          target_distance = get_two_points_distance(gps_tau1201.latitude,gps_tau1201.longitude,target_point[0],target_point[1]);

          if(target_distance < 2)
          {
             //����Ŀ���
             sprintf(str_buffer,"Arrival P%d! D:%lf \r\n",cur_point_num,target_distance);ble6a20_send_string(str_buffer);

             //װ����һĿ���
             LoadPoint();
             sprintf(str_buffer,"Load P%d!\r\n",cur_point_num);ble6a20_send_string(str_buffer);
          }
          break;
        }
        case State_Finish:
        {
          sprintf(str_buffer,"Finish!\r\n");ble6a20_send_string(str_buffer);
          while(1){};
        }
      }

      if(cur_point_num == cur_object_num)//�ȸ���Ϊ����״̬
      {
        curState = State_Finish;
      }
      
      
    }
}
