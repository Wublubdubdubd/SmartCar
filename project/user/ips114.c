#include "ips114.h"

uint8 page_num = 0; //页面

/**
  * @brief 显示单位
  * @param 无
  * @return 无
  */
void IPS114_Show_Unit(void) 
{  
    switch(page_num)
    {
      case 0:
      {
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
        ips114_set_color(RGB565_PINK,RGB565_WHITE);
        ips114_show_string(0, 16*5, "S: ");//定位状态
        ips114_show_string(50, 16*5,"N: ");//卫星数目
        ips114_show_string(130, 16*5,"H: ");//GPS天线高度

        ips114_show_string(0, 16*6, "Lat:");//纬度
        ips114_show_string(130, 16*6, "Lon:");//经度
        ips114_show_string(0, 16*7, "v:");//速度
        ips114_show_string(130, 16*7, "d:");//方向
        
        ips114_set_color(RGB565_RED,RGB565_WHITE);
         break;
      }
      case 1:
      {
        //角度环
        ips114_set_color(RGB565_BLUE,RGB565_WHITE);
        ips114_show_string(0,16*0,"Angle");
        ips114_show_char(0,16*1,'P');
        ips114_show_char(40,16*1,'I');
        ips114_show_char(120,16*1,'D');

        //角速度
        ips114_set_color(RGB565_PURPLE,RGB565_WHITE);
        ips114_show_string(0,16*2,"Velocity");
        ips114_show_char(0,16*3,'P');
        ips114_show_char(80,16*3,'I');
        ips114_show_char(160,16*3,'D');
        break;
      }
    }

}
/**
  * @brief 显示信息
  * @param 无
  * @return 无
  */
void IPS114_Show_Info(void)
{   
    //循环变量
    unsigned char index=0;
    if(key1_flag)
    {
      page_num++; 
      page_num %= 2;
      ips114_clear(RGB565_WHITE);
      IPS114_Show_Unit();//显示单位
    }
    switch(page_num)
    {
      case 0:
      {
        //IMU
        ips114_show_float(100,0,velocity,2,3);
        for(index=0;index<3;index++)
        {
          ips114_show_float(80*index, 16*1 ,imu_acc[index],2,3);//加速度信息 字符8x16
          ips114_show_float(80*index, 16*3 ,imu_gyro[index],2,3);//角速度信息
        }
        switch(curState)
        {
          case State_Init:ips114_show_string(0,16*4,"Init  ");break;
          case State_Unlock:ips114_show_string(0,16*4,"Unlock");break;
          case State_Yaw_Init:ips114_show_string(0,16*4,"YawInit");break;
          case State_Subject_1:ips114_show_string(0,16*4,"Object");break;
        }
        //GPS
        if(gps_date_ready)
        {
          //显示GPS位置信息
          ips114_show_uint8(15, 16*5, gps_tau1201.state);
          ips114_show_uint8(70, 16*5, gps_tau1201.satellite_used);
          ips114_show_float(160, 16*5, gps_tau1201.height, 4, 6);
            
          ips114_show_float(30, 16*6, gps_tau1201.latitude, 4, 6);
          ips114_show_float(160, 16*6, gps_tau1201.longitude, 4, 6);
          ips114_show_float(30, 16*7, gps_tau1201.speed, 4, 6);
          ips114_show_float(160, 16*7, gps_tau1201.direction, 4, 6);
        }
        // 航向角
        ips114_show_float(160,64,yaw,4,4);
        break;
      }
      case 1:
      {
        ips114_show_float(10, 16*1 ,angle_KP,3,3);
        ips114_show_float(90, 16*1 ,angle_KI,3,3);
        ips114_show_float(170, 16*1 ,angle_KD,3,3);
        
        ips114_show_float(10, 16*3 ,velocity_KP,3,3);
        ips114_show_float(90, 16*3 ,velocity_KI,3,3);
        ips114_show_float(170, 16*3 ,velocity_KD,3,3);
        
        break;
      }
    }

}