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

#include "zf_common_headfile.h"
#include "pid.h"

#define PIT_IMU  (TIM0_PIT) // IMU 中断源 TIM0

void pit_hanlder_imu(void); // TIM0 中断服务函数

//acc gyro 参数
float imu_acc[3],imu_gyro[3];

void main()
{
    unsigned char index=0;  //循环变量
    clock_init(SYSTEM_CLOCK_40M); // 务必保留
		debug_init(); // 务必保留
  
    //GPS初始化
    gps_init();

    //屏幕初始化
		ips114_init();
		ips114_show_string(0, 16*0, "ISP init successfully.");
    
		//IMU初始化
    while(imu660ra_init()!=0)
      ips114_show_string(0, 16*1, "IMU660RA init error.");                                 // IMU660RA 初始化失败
    
    system_delay_ms(1000); //后期删除
    ips114_clear(RGB565_WHITE);//清屏
    
    //加速度
    ips114_set_color(RGB565_BLUE,RGB565_WHITE);
    ips114_show_string(0,16*0,"Acc: x,y,z");
    ips114_show_char(60,16*1,'g');
    ips114_show_char(140,16*1,'g');
    ips114_show_char(220,16*1,'g');
  
    //角速度
    ips114_set_color(RGB565_PURPLE,RGB565_WHITE);
    ips114_show_string(0,16*2,"Gyro: x,y,z");
    ips114_show_char(60,16*3,'d');
    ips114_show_char(140,16*3,'d');
    ips114_show_char(220,16*3,'d');

    
    //GPS
    ips114_set_color(RGB565_YELLOW,RGB565_WHITE);
    ips114_show_string(0, 16*5, "S: ");//定位状态
    ips114_show_string(40, 16*5,"N: ");//卫星数目
    ips114_show_string(100, 16*5,"H: ");//GPS天线高度

    ips114_show_string(0, 16*6, "Lat");//纬度
    ips114_show_string(120, 16*6, "Lon");//经度
    ips114_show_string(0, 16*7, "v");//速度
    ips114_show_string(120, 16*7, "d");//方向

    
    //设置中断回调函数 5ms采样一次IMU数据
    tim0_irq_handler = pit_hanlder_imu;	
    pit_ms_init(PIT_IMU, 5);
	
		ips114_set_color(RGB565_RED,RGB565_WHITE);
    while(1)
		{
      //IMU
      for(index=0;index<3;index++)
      {
        ips114_show_float(80*index, 16*1 ,imu_acc[index],2,3);//加速度信息 字符8x16
        ips114_show_float(80*index, 16*3 ,imu_gyro[index],2,3);//角速度信息
      }
      //GPS
      if(gps_tau1201_flag)
      {
        gps_tau1201_flag = 0;
        if(!gps_data_parse())          //开始解析数据
        {
				//显示GPS位置信息
        ips114_show_uint8(20, 16*5, gps_tau1201.state);
        ips114_show_uint8(60, 16*5, gps_tau1201.satellite_used);
        ips114_show_float(120, 16*5, gps_tau1201.height, 4, 6);
          
        ips114_show_float(20, 16*6, gps_tau1201.latitude, 4, 6);
        ips114_show_float(140, 16*6, gps_tau1201.longitude, 4, 6);
        ips114_show_float(20, 16*7, gps_tau1201.speed, 4, 6);
        ips114_show_float(140, 16*7, gps_tau1201.direction, 4, 6);

				
//				printf("gps_state       = %d\r\n" , gps_tau1201.state);         //输出当前定位有效模式 1：定位有效  0：定位无效
//				printf("latitude        = %lf\r\n", gps_tau1201.latitude);      //输出纬度信息
//				printf("longitude       = %lf\r\n", gps_tau1201.longitude);     //输出经度信息
//				printf("speed           = %lf\r\n", gps_tau1201.speed);         //输出速度信息
//				printf("direction       = %lf\r\n", gps_tau1201.direction);     //输出方向信息
//				printf("satellite_used  = %d\r\n" , gps_tau1201.satellite_used);//输出当前用于定位的卫星数量
//				printf("height          = %lf\r\n", gps_tau1201.height);        //输出当前GPS天线所处高度
        }
      }
      system_delay_ms(1000);
     }
}
/**
  * @brief TIM0中断处理函数，提取imu数据
  * @param 无
  * @return 无
  */
void pit_hanlder_imu(void)
{
    imu660ra_get_acc();                                                         // 获取 IMU660RA 的加速度测量数值
    imu660ra_get_gyro();                                                        // 获取 IMU660RA 的角速度测量数值
    
    //转换为实际物理值
	  imu_acc[0]=imu660ra_acc_x/imu660ra_transition_factor[0];
	  imu_acc[1]=imu660ra_acc_y/imu660ra_transition_factor[0];
	  imu_acc[2]=imu660ra_acc_z/imu660ra_transition_factor[0];
	
		imu_gyro[0]=imu660ra_gyro_x/imu660ra_transition_factor[1];
	  imu_gyro[1]=imu660ra_gyro_y/imu660ra_transition_factor[1];
	  imu_gyro[2]=imu660ra_gyro_z/imu660ra_transition_factor[1]; 
}


