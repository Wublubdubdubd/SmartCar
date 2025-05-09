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
    char command[command_size];//蓝牙控制命令
  
    char str_buffer[50];//向蓝牙发送信息的buffer
  
    char write_index = 0; //打点索引，测试用
  
    float temp_float = 0; // 零时变量
		
    //科目一开始
    pObject = Object_one_index; 
    cur_object_num = Object_one_num;
		
    //设备初始化
    init();
    
    while(1)
		{
      get_key();
#if IPS_USE     
      IPS114_Show_Info(); //显示必要信息
#endif
			blue_tooth_read(command);
      /*
      命令集:
      s: 记录起始点，计算GPS误差，准备初始化yaw角
      
      b: 刹车 四个电机占空比值 0%
      
      w: 向当前科目的EEPROM区写当前位置的经纬度，写满后不可再写，只有清除后可再次重新写入。何时写满取决与当前科目（未完善）
           
      e：擦除EEPROM第一页，写索引值 0 
      
      */
      if((curState == State_Init) && key2_flag)curState = State_Unlock;
      
      switch(command[0])
      {
        case 's':
        {
          if(curState == State_Unlock)
          {
            //装载 P1 至 target
            LoadPoint();
           
            // 计算gps的漂移
            gps_point_error[0] = gps_tau1201.latitude - target_point[0];
            gps_point_error[1] = gps_tau1201.longitude - target_point[1];
            
            // 输出提示语句
            sprintf(str_buffer,"Start!\r\nGPS Error: lat %lf lon %lf\r\n",gps_point_error[0],gps_point_error[1]);ble6a20_send_string(str_buffer);
            
            // 更新状态
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
          W25Q_Erase4K_20(0, 1);//iap_erase_page(0);write_index = 0;//第一页 512k
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
            EulerToQuaternion();
            //提示信息
            sprintf(str_buffer,"Init! D:%lf Y:%lf\r\n",target_distance,yaw);ble6a20_send_string(str_buffer);
            //装载下一目标点
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
             //到达目标点
             sprintf(str_buffer,"Arrival P%d! D:%lf \r\n",cur_point_num,target_distance);ble6a20_send_string(str_buffer);

             //装载下一目标点
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

      if(cur_point_num == cur_object_num)//先更新为结束状态
      {
        curState = State_Finish;
      }
      
      
    }
}
