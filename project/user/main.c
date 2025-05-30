/*********************************************************************************************************************
* AI8051U Opensourec Library 即（AI8051U 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
*
* 本文件是STC 开源库的一部分
*
* AI8051U 开源库 是免费软件
* 您可以根据自由软件基金会发布的 GPL（GNU General Public License，即 GNU通用公共许可证）的条款
* 即 GPL 的第3版（即 GPL3.0）或（您选择的）任何后来的版本，重新发布和/或修改它
*
* 本开源库的发布是希望它能发挥作用，但并未对其作任何的保证
* 甚至没有隐含的适销性或适合特定用途的保证
* 更多细节请参见 GPL
*
* 您应该在收到本开源库的同时收到一份 GPL 的副本
* 如果没有，请参阅<https://www.gnu.org/licenses/>
*
* 额外注明：
* 本开源库使用 GPL3.0 开源许可证协议 以上许可申明为译文版本
* 许可申明英文版在 libraries/doc 文件夹下的 GPL3_permission_statement.txt 文件中
* 许可证副本在 libraries 文件夹下 即该文件夹下的 LICENSE 文件
* 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
*
* 文件名称          
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          MDK FOR C251
* 适用平台          AI8051U
* 店铺链接          https://seekfree.taobao.com/
*
* 修改记录
* 日期              作者           备注
* 2024-08-01        大W            first version
********************************************************************************************************************/
#include "init.h"

void main()
{

    char command[64];//蓝牙控制命令
  
    char str_buffer[50];//向蓝牙发送信息的buffer
		
    float temp_float = 0,temp_float2=0; // 零时变量
		int temp_int = 0;
    uint8 index = 0;
    //科目一开始
    //pObject = Object_one_index; 
   
		
    //设备初始化
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
					 get_key();//读取按键状态
				   IPS114_Show_Info(); //显示动态信息
					 GUI_Handle_Key();//处理按键
					 refresh_button();//刷新按键
					  
					 break;
				}
				case State_Unlock:
				{

					//装载 P1 至 target
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

					// 更新状态
					curState = State_Yaw_Init;
					break;
				}
        case State_Yaw_Init:
        {
					/*角度环信息*/
					//sprintf(str_buffer,"T=%f,Y=%f,U=%f,A=%f,O=%f,",target_angle,yaw,angle_outer_out,imu_gyro[2],angle_inner_out);ble6a20_send_string(str_buffer);
					/*速度内环信息*/
					//sprintf(str_buffer,"T=%f,A=%f,O=%f,",velocity_outer_out,imu_acc[0]*9.8,velocity_inner_out);ble6a20_send_string(str_buffer);
					/*速度环信息*/
					//sprintf(str_buffer,"T=%f,Y=%f,U=%f,A=%f,O=%f,",target_velocity,velocity,velocity_outer_out,imu_acc[0]*9.8,velocity_inner_out);ble6a20_send_string(str_buffer);
					
					if(gps_date_ready)
					{
						target_distance = get_two_points_distance(target_point[0],target_point[1],gps_tau1201.latitude,gps_tau1201.longitude);
						sprintf(str_buffer,"E=%f,D=%f,",u_angle,target_distance);ble6a20_send_string(str_buffer);
					}
          //sprintf(str_buffer,"Error:%f V:%f\r\n",target_angle - yaw,velocity);ble6a20_send_string(str_buffer);
          // 离开两米后
          if(target_distance > 2)
          {
            //计算yaw角
            yaw = get_two_points_azimuth(target_point[0],target_point[1],gps_tau1201.latitude,gps_tau1201.longitude);
            //修正至-180~180
            if( (180 <= yaw) && (yaw < 360))
              yaw -= 360;
            //修正到imu坐标系
            yaw = - yaw;
            //修正四元数
						target_angle = yaw;
            EulerToQuaternion();
            //提示信息
            sprintf(str_buffer,"Init!Y:%lf\r\n",yaw);ble6a20_send_string(str_buffer);
            //装载下一目标点
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
             //到达目标点
             sprintf(str_buffer,"Arrival P%d! D:%lf \r\n",cur_point_num,target_distance);ble6a20_send_string(str_buffer);
						 if(cur_point_num == cur_object_num)//暂时更新为结束状态
						 {
								curState = State_Finish;
								sprintf(str_buffer,"Finish!\r\n");ble6a20_send_string(str_buffer);
								break;
						 }
             //装载下一目标点
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
