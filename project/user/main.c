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

BYTE buf[4096];
BYTE write_buf[4096]={1,1};

void main()
{
    // 变量必须先定义 再调用
    char command[2];//蓝牙控制命令 使用轮询方式获取 但应该改为中断 
    char str_buffer[100];//蓝牙信息的buffer
  
    char write_index = 0; //打点索引，测试用
    char read_index = 0; //读点索引，测试用
  
    pObject = Object_one_index; //科目一开始
			
    init();  
	
  
    while(1)
		{
#if IPS_USE     
      IPS114_Show_Info(); //显示必要信息
#endif
			blue_tooth_read(command);
      /*
      命令集：（ 计划废弃 s、1~4 使其自动增加到目标值 ）
      s: 10%占空比启动抬升电机，测试接线
      
      1：抬升电机占空比 + 10%
      2：抬升电机占空比 - 10%
      3：推进电机占空比 + 10%
      4：推进电机占空比 - 10%
      
      b: 刹车 四个电机占空比值 0%
      
      w: 向当前科目的EEPROM区写当前位置的经纬度，写满后不可再写，只有清除后可再次重新写入。何时写满取决与当前科目（未完善）
      r: 读取当前科目下一点到目标点
      
      p: 打印目标点经纬度到蓝牙助手
      
      e：擦除EEPROM第一页，写索引值 0 
      
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
        case 'e':W25Q_Erase4K_20(0, 1);//iap_erase_page(0);write_index = 0;//第一页 512k
        sprintf(str_buffer,"Erease!\r\n");ble6a20_send_string(str_buffer);break;
        default :;
      }
      command[0] = 0 ; //清空
			command[1] = 0 ; 
//      ips114_show_float(0,64,roll,4,4);
//      ips114_show_float(80,64,pitch,4,4);
      //显示已打点数和当前所在点
			
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
