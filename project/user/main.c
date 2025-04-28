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
    char command;//蓝牙控制命令 使用轮询方式获取 但应该改为中断 
    char str_buffer[100];//蓝牙信息的buffer
    
    init();  
	
    while(1)
		{
#if IPS_USE     
      IPS114_Show_Info(); //显示必要信息
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
        case 'e':iap_erase_page(0);//第一页 512k
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
