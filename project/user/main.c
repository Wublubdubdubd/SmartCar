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

    char command[64];//������������
  
    char str_buffer[50];//������������Ϣ��buffer
		
    float temp_float = 0,temp_float2=0; // ��ʱ����
		int temp_int = 0;
    uint8 index = 0;
    //��Ŀһ��ʼ
    //pObject = Object_one_index; 
   
		
    //�豸��ʼ��
    init();
    
    while(1)
		{
      GetGPSData();
	
			ble6a20_read_buffer(command, 64);
      switch(command[0])
      {
        case 'b':
        {
          curState = State_Shut;
          sprintf(str_buffer,"Break!\r\n");ble6a20_send_string(str_buffer);
          break;
        }
        case 'A':
        {
          temp_float = func_str_to_float(&command[2]);
          switch(command[1])
          {
            case 'P':angle_outer_pid.kp = temp_float;break;
            case 'I':angle_outer_pid.ki = temp_float;break;
            case 'D':angle_outer_pid.kd = temp_float;break;
						case 'O':angle_outer_pid.outmax = temp_float;break;
						case 'o':angle_outer_pid.out_i = temp_float;break;
						case 't':target_angle = temp_float;break;
          }
          break;
        }
        case 'V':
        {
          temp_float = func_str_to_float(&command[2]);
          switch(command[1])
          {
            case 'P':velocity_outer_pid.kp = temp_float;break;
            case 'I':velocity_outer_pid.ki = temp_float;break;
            case 'D':velocity_outer_pid.kd = temp_float;break;
						case 'O':velocity_outer_pid.outmax = temp_float;break;
						case 'o':velocity_outer_pid.out_i = temp_float;break;
						case 't':target_velocity = temp_float;break;
          }
          break;          
        }
				case 'a':
        {
          temp_float = func_str_to_float(&command[2]);
          switch(command[1])
          {
            case 'P':angle_inner_pid.kp = temp_float;break;
            case 'I':angle_inner_pid.ki = temp_float;break;
            case 'D':angle_inner_pid.kd = temp_float;break;
						case 'O':angle_inner_pid.outmax = temp_float;break;
						case 'o':angle_inner_pid.out_i = temp_float;break;
						//case 't':angle_outer_out = temp_float;break;
          }
          break;
        }
        case 'v':
        {
          temp_float = func_str_to_float(&command[2]);
          switch(command[1])
          {
            case 'P':velocity_inner_pid.kp = temp_float;break;
            case 'I':velocity_inner_pid.ki = temp_float;break;
            case 'D':velocity_inner_pid.kd = temp_float;break;
						case 'O':velocity_inner_pid.outmax = temp_float;break;
						case 'o':velocity_inner_pid.out_i = temp_float;break;
						//case 't':velocity_outer_out = temp_float;break;
          }
          break;          
        }
				case 'S':
			  {   
						curState = State_Unlock;
						sprintf(str_buffer,"Start!\r\n");ble6a20_send_string(str_buffer);
						target_distance = 0;
						break;
				}
				case 'U':
				{
						curState = State_Yaw_Init;
						sprintf(str_buffer,"Unsafe Start!\r\n");ble6a20_send_string(str_buffer);
						target_distance = 0;
						break;
				}
				case 'D':
				{
					temp_int=func_str_to_int(&command[2]);
					 switch(command[1])
          {
            case 'u': basic_up_duty= temp_int;break;
            case 'f': basic_forward_duty = temp_int;break;
            case 'e': forward_feed= temp_int;break;
          }
          break; 
				}
				case 'R':
				{
						basic_duty_up_left=500;
						basic_duty_up_right=500;
						basic_duty_forward_left=500;
						basic_duty_forward_right=500;
						basic_duty_index = 0;
						curState = State_Init;
						velocity_inner_pid.integrator=0;
						angle_inner_pid.integrator=0;
						velocity_outer_pid.integrator=0;
						angle_outer_pid.integrator=0;
					
						roll =0;
						yaw =0;
						pitch =0;
						q0=1;
						q1=0;
						q2=0;
						q3=0;
          
            u_angle = 0;
            u_velocity = 0;
						sprintf(str_buffer,"Reset!\r\n");ble6a20_send_string(str_buffer);
						break;
				}
        default :;
      }
      memset(command,0,64);

      
      switch(curState)
      {
				case State_Init:
				{
					 get_key();//��ȡ����״̬
				   IPS114_Show_Info(); //��ʾ��̬��Ϣ
					 GUI_Handle_Key();//������
					 refresh_button();//ˢ�°���
					  
					 break;
				}
				case State_Unlock:
				{

					//װ�� P1 �� target
					if(!gps_date_ready)break;
          for(index=1;index<=cur_object_num;index++)
          {
            sprintf(str_buffer,"P%d:%lf :%lf\r\n",index,Object_1_Point[index-1][0],Object_1_Point[index-1][1]);ble6a20_send_string(str_buffer);
          }
					LoadPoint();
					gps_point_error[0]=gps_tau1201.latitude-target_point[0];
					gps_point_error[1]=gps_tau1201.longitude-target_point[1];
					target_point[0]=gps_tau1201.latitude;
					target_point[1]=gps_tau1201.longitude;
					sprintf(str_buffer,"GPS Error lat:%lf lon:%lf\r\n",gps_point_error[0],gps_point_error[1]);ble6a20_send_string(str_buffer);
						
					roll =0;
					yaw =0;
					pitch =0;
					q0=1;
					q1=0;
					q2=0;
					q3=0;
					target_distance = 0;
						
					ips114_clear(RGB565_GREEN);
					system_delay_ms(1000);
					ips114_clear(RGB565_YELLOW);
					system_delay_ms(1000);
					ips114_clear(RGB565_RED);
					system_delay_ms(1000);

					// ����״̬
					curState = State_Yaw_Init;
					break;
				}
        case State_Yaw_Init:
        {
					/*�ǶȻ���Ϣ*/
					//sprintf(str_buffer,"T=%f,Y=%f,U=%f,A=%f,O=%f,",target_angle,yaw,angle_outer_out,imu_gyro[2],angle_inner_out);ble6a20_send_string(str_buffer);
					/*�ٶ��ڻ���Ϣ*/
					//sprintf(str_buffer,"T=%f,A=%f,O=%f,",velocity_outer_out,imu_acc[0]*9.8,velocity_inner_out);ble6a20_send_string(str_buffer);
					/*�ٶȻ���Ϣ*/
					//sprintf(str_buffer,"T=%f,Y=%f,U=%f,A=%f,O=%f,",target_velocity,velocity,velocity_outer_out,imu_acc[0]*9.8,velocity_inner_out);ble6a20_send_string(str_buffer);
					
					if(gps_date_ready)
					{
						target_distance = get_two_points_distance(target_point[0],target_point[1],gps_tau1201.latitude,gps_tau1201.longitude);
						sprintf(str_buffer,"E=%f,D=%f,",u_angle,target_distance);ble6a20_send_string(str_buffer);
					}
          //sprintf(str_buffer,"Error:%f V:%f\r\n",target_angle - yaw,velocity);ble6a20_send_string(str_buffer);
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
						target_angle = yaw;
            EulerToQuaternion();
            //��ʾ��Ϣ
            sprintf(str_buffer,"Init!Y:%lf\r\n",yaw);ble6a20_send_string(str_buffer);
            //װ����һĿ���
            LoadPoint();
            sprintf(str_buffer,"Load P%d! lat:%lf lon:%lf \r\n",cur_point_num,target_point[0],target_point[1]);ble6a20_send_string(str_buffer);
            
            curState = State_Subject_1;
            
            target_distance = 999;
          }
          break;
        }
        case State_Subject_1:
        {
					if(gps_date_ready)
					{
					  target_distance = get_two_points_distance(gps_tau1201.latitude,gps_tau1201.longitude,target_point[0],target_point[1]);
						target_angle = get_two_points_azimuth(gps_tau1201.latitude,gps_tau1201.longitude,target_point[0],target_point[1]);
						if( (180 <= target_angle)&&(target_angle < 360))
							target_angle -= 360;
						target_angle = -target_angle;
						sprintf(str_buffer,"E=%f,D=%f,v=%f,",u_angle,target_distance,target_velocity);ble6a20_send_string(str_buffer);
						if(u_angle>60)
						{
							target_velocity = -0.0075*u_angle+1.36;
						}
						else if(u_angle<-60)
						{
							target_velocity = 0.0075*u_angle+1.36;
						}
						else
						{target_velocity=1.0;}
					}
          if(target_distance < 1.0)
          {
             //����Ŀ���
             sprintf(str_buffer,"Arrival P%d! D:%lf \r\n",cur_point_num,target_distance);ble6a20_send_string(str_buffer);
						 if(cur_point_num == cur_object_num)//��ʱ����Ϊ����״̬
						 {
								curState = State_Finish;
								sprintf(str_buffer,"Finish!\r\n");ble6a20_send_string(str_buffer);
								break;
						 }
             //װ����һĿ���
             LoadPoint();
						 target_distance = 999;
             sprintf(str_buffer,"Load P%d! lat:%lf lon:%lf \r\n",cur_point_num,target_point[0],target_point[1]);ble6a20_send_string(str_buffer);
          }
          break;
        }
        case State_Finish:
        {
          break;
        }
      }     
    }
}
