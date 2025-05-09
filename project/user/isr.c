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
#include "isr.h"

void DMA_UART1_IRQHandler (void) interrupt 4
{
    static vuint8 dwon_count = 0;
    if (DMA_UR1R_STA & 0x01)		// 接收完成
    {
        DMA_UR1R_STA &= ~0x01;		// 清标志位
        uart_rx_start_buff(UART_1);	// 设置下一次接收，务必保留
        
        //程序自动下载
        if(uart_rx_buff[UART_1][0] == 0x7F)
        {
            if(dwon_count++ > 20)
            {
                IAP_CONTR = 0x60;
            }
        }
        else
        {
            dwon_count = 0;
        }
        
        if(uart1_irq_handler != NULL)
        {
            uart1_irq_handler(uart_rx_buff[UART_1][0]);
        }
    }
    
    if (DMA_UR1R_STA & 0x02)	//数据丢弃
    {
        DMA_UR1R_STA &= ~0x02;	//清标志位
        uart_rx_start_buff(UART_1);	// 设置下一次接收，务必保留
        // 如果进入了这个中断，则代表UART的数据在没有取走之前被覆盖!
        // 如果进入了这个中断，则代表UART的数据在没有取走之前被覆盖!
        // 如果进入了这个中断，则代表UART的数据在没有取走之前被覆盖!
    }
}



void DMA_UART2_IRQHandler (void) interrupt 8
{

    if (DMA_UR2R_STA & 0x01)		// 接收完成
    {
        DMA_UR2R_STA &= ~0x01;		// 清标志位
        uart_rx_start_buff(UART_2);	// 设置下一次接收，务必保留
        
        if(uart2_irq_handler != NULL)
        {
            uart2_irq_handler(uart_rx_buff[UART_2][0]);
        }
    }
    
    if (DMA_UR2R_STA & 0x02)		//数据丢弃
    {
        DMA_UR2R_STA &= ~0x02;		//清标志位
        uart_rx_start_buff(UART_2);	// 设置下一次接收，务必保留
        // 如果进入了这个中断，则代表UART的数据在没有取走之前被覆盖!
        // 如果进入了这个中断，则代表UART的数据在没有取走之前被覆盖!
        // 如果进入了这个中断，则代表UART的数据在没有取走之前被覆盖!
        
    }
}

void DMA_UART3_IRQHandler (void) interrupt 17
{

    if (DMA_UR3R_STA & 0x01)		// 接收完成
    {
        DMA_UR3R_STA &= ~0x01;		// 清标志位
        uart_rx_start_buff(UART_3);	// 设置下一次接收，务必保留
        
        if(uart3_irq_handler != NULL)
        {
        
            uart3_irq_handler(uart_rx_buff[UART_3][0]);
            
        }
    }
    
    if (DMA_UR3R_STA & 0x02)		//数据丢弃
    {
        DMA_UR3R_STA &= ~0x02;		//清标志位
        uart_rx_start_buff(UART_3);	// 设置下一次接收，务必保留
        // 如果进入了这个中断，则代表UART的数据在没有取走之前被覆盖!
        // 如果进入了这个中断，则代表UART的数据在没有取走之前被覆盖!
        // 如果进入了这个中断，则代表UART的数据在没有取走之前被覆盖!
        
    }
}

void DMA_UART4_IRQHandler (void) interrupt 18
{

    if (DMA_UR4R_STA & 0x01)		// 接收完成
    {
        DMA_UR4R_STA &= ~0x01;		// 清标志位
        uart_rx_start_buff(UART_4);	// 设置下一次接收，务必保留
        
        if(uart4_irq_handler != NULL)
        {
            uart4_irq_handler(uart_rx_buff[UART_4][0]);
            
        }
    }
    
    if (DMA_UR4R_STA & 0x02)	//数据丢弃
    {
        DMA_UR4R_STA &= ~0x02;	//清标志位
        uart_rx_start_buff(UART_4);	// 设置下一次接收，务必保留
        // 如果进入了这个中断，则代表UART的数据在没有取走之前被覆盖!
        // 如果进入了这个中断，则代表UART的数据在没有取走之前被覆盖!
        // 如果进入了这个中断，则代表UART的数据在没有取走之前被覆盖!
        
    }
}


void TM0_IRQHandler() interrupt 1
{
    TIM0_CLEAR_FLAG;
    
    if(tim0_irq_handler != NULL)
    {
        tim0_irq_handler();
    }
}
void TM1_IRQHandler() interrupt 3
{
    TIM1_CLEAR_FLAG;
    
    if(tim1_irq_handler != NULL)
    {
        tim1_irq_handler();
    }
}
void TM2_IRQHandler() interrupt 12
{
    TIM2_CLEAR_FLAG;
    
    if(tim2_irq_handler != NULL)
    {
        tim2_irq_handler();
    }
}
void TM3_IRQHandler() interrupt 19
{
    TIM3_CLEAR_FLAG;
    
    if(tim3_irq_handler != NULL)
    {
        tim3_irq_handler();
    }
}

void TM4_IRQHandler() interrupt 20
{
    TIM4_CLEAR_FLAG;
    
    if(tim4_irq_handler != NULL)
    {
        tim4_irq_handler();
    }
}

void TM11_IRQHandler() interrupt 24
{
    TIM11_CLEAR_FLAG;
    
    if(tim11_irq_handler != NULL)
    {
        tim11_irq_handler();
    }
}

/**
  * @brief TIM0中断处理函数，提取imu数据
  * @param 无
  * @return 无
  */
void pit_hanlder_imu(void)
{ 
    
    //获取传感器数据
    imu660ra_get_acc();  // 加速度
    imu660ra_get_gyro(); // 角速度
  
    //acc滤波
    FOCF(&imu660ra_acc_x,&imu_acc_x_pre,0.1);
    FOCF(&imu660ra_acc_y,&imu_acc_y_pre,0.1);
    FOCF(&imu660ra_acc_z,&imu_acc_z_pre,0.1);
  
    //gyro滤波
    FOCF(&imu660ra_gyro_x,&imu_gyro_x_pre,0.1);
    FOCF(&imu660ra_gyro_y,&imu_gyro_y_pre,0.1);
    FOCF(&imu660ra_gyro_z,&imu_gyro_z_pre,0.1);
  
    //转换为实际物理值，纠正零偏
	  imu_acc[0]=imu660ra_acc_transition(imu660ra_acc_x);
	  imu_acc[1]=imu660ra_acc_transition(imu660ra_acc_y)+0.017;
	  imu_acc[2]=imu660ra_acc_transition(imu660ra_acc_z);
	

    imu_gyro[0]=imu660ra_gyro_transition(imu660ra_gyro_x);
	  imu_gyro[1]=imu660ra_gyro_transition(imu660ra_gyro_y);
	  imu_gyro[2]=imu660ra_gyro_transition(imu660ra_gyro_z);
	
		//数据融合获取欧拉角
		GetEuler(imu_gyro,0.005);
		
//		imu_acc[0] -= (2*(q1*q3 - q0*q2));
//		if(fabs(imu_acc[0])<0.05)imu_acc[0]=0;
//		x_v += (imu_acc[0] * 0.005);
}
/**
  * @brief TIM1中断处理函数，提取gps数据
  * @param 无
  * @return 无
  */
void pit_hanlder_gps(void)
{
    //获取gps数据
    if(gps_tau1201_flag)
    {
      gps_tau1201_flag = 0;
      gps_date_ready = (!gps_data_parse()) ? 1 : 0;
    }
    else gps_date_ready = 0;
}
/**
  * @brief TIM11中断处理函数，更新角度环
  * @param 无
  * @return 无
  */
void pit_hanlder_angle(void)
{
    uint32 angle_duty;

  
    encoder_data = encoder_get_count(ENCODER_DIR_1);  // 获取编码器计数
    encoder_clear_count(ENCODER_DIR_1);               // 清空编码器计数
    
    velocity = encoder_data * encode2vel; 
    
    if( curState < State_Yaw_Init ) return; // 初始化或保护状态，不能运行

    //抬升电机自动运行
    if( up_times < 80)
    {
      duty_up_left += 5;
      duty_up_right += 5;
      duty_forward_left += 3;
      duty_forward_right += 3;
      up_times++;
    }
    
    if( curState >= State_Shut ) 
    {
      Break();
      angle_u = 0;
      velocity_u = 0;
    }
    else
    {
      // 角度环
      angle_u = Angle_Pid_fun(0.01);
      // 速度环
      velocity_u = Velocity_Pid_fun(0.01);
    }
    
    //左 抬升电机
	  angle_duty = constrain_uint32(duty_up_left);
    pwm_set_duty(PWM_1,angle_duty);
	  //右 抬升电机
	  angle_duty = constrain_uint32(duty_up_right);
    pwm_set_duty(PWM_2,angle_duty);
    //左 推进电机
    angle_duty = constrain_uint32(duty_forward_left - angle_u + velocity_u + 20);
    pwm_set_duty(PWM_3,angle_duty);
    //右 推进电机
    angle_duty = constrain_uint32(duty_forward_right + angle_u + velocity_u - 20 );
    pwm_set_duty(PWM_4,angle_duty);
    
}
void my_pit_init()
{
    //1s采样GPS数据
    tim1_irq_handler = pit_hanlder_GPS;	
    pit_ms_init(PIT_GPS, 1000);
    //10ms更新角度环
    tim3_irq_handler = pit_hanlder_angle;
    pit_ms_init(PIT_ANGLE, 10);
    //5ms采样IMU数据
    tim4_irq_handler = pit_hanlder_imu;	
    pit_ms_init(PIT_IMU, 5);
}


//#define     INT0_VECTOR             0       //0003H
//#define     TMR0_VECTOR             1       //000BH
//#define     INT1_VECTOR             2       //0013H
//#define     TMR1_VECTOR             3       //001BH
//#define     UART1_VECTOR            4       //0023H
//#define     ADC_VECTOR              5       //002BH
//#define     LVD_VECTOR              6       //0033H
//#define     PCA_VECTOR              7       //003BH
//#define     UART2_VECTOR            8       //0043H
//#define     SPI_VECTOR              9       //004BH
//#define     INT2_VECTOR             10      //0053H
//#define     INT3_VECTOR             11      //005BH
//#define     TMR2_VECTOR             12      //0063H
//#define     USER_VECTOR             13      //006BH
//#define     INT4_VECTOR             16      //0083H
//#define     UART3_VECTOR            17      //008BH
//#define     UART4_VECTOR            18      //0093H
//#define     TMR3_VECTOR             19      //009BH
//#define     TMR4_VECTOR             20      //00A3H
//#define     CMP_VECTOR              21      //00ABH
//#define     I2C_VECTOR              24      //00C3H
//#define     USB_VECTOR              25      //00CBH
//#define     PWMA_VECTOR             26      //00D3H
//#define     PWMB_VECTOR             27      //00DBH

//#define     RTC_VECTOR              36      //0123H
//#define     P0INT_VECTOR            37      //012BH
//#define     P1INT_VECTOR            38      //0133H
//#define     P2INT_VECTOR            39      //013BH
//#define     P3INT_VECTOR            40      //0143H
//#define     P4INT_VECTOR            41      //014BH
//#define     P5INT_VECTOR            42      //0153H
//#define     P6INT_VECTOR            43      //015BH
//#define     P7INT_VECTOR            44      //0163H
//#define     DMA_M2M_VECTOR          47      //017BH
//#define     DMA_ADC_VECTOR          48      //0183H
//#define     DMA_SPI_VECTOR          49      //018BH
//#define     DMA_UR1T_VECTOR         50      //0193H
//#define     DMA_UR1R_VECTOR         51      //019BH
//#define     DMA_UR2T_VECTOR         52      //01A3H
//#define     DMA_UR2R_VECTOR         53      //01ABH
//#define     DMA_UR3T_VECTOR         54      //01B3H
//#define     DMA_UR3R_VECTOR         55      //01BBH
//#define     DMA_UR4T_VECTOR         56      //01C3H
//#define     DMA_UR4R_VECTOR         57      //01CBH
//#define     DMA_LCM_VECTOR          58      //01D3H
//#define     LCM_VECTOR              59      //01DBH
//#define     DMA_I2CT_VECTOR         60      //01E3H
//#define     DMA_I2CR_VECTOR         61      //01EBH
//#define     I2S_VECTOR              62      //01F3H
//#define     DMA_I2ST_VECTOR         63      //01FBH
//#define     DMA_I2SR_VECTOR         64      //0203H
//#define     DMA_QSPI_VECTOR         65      //020BH
//#define     QSPI_VECTOR             66      //0213H
//#define     TMR11_VECTOR            67      //021BH
//#define     DMA_PWMAT_VECTOR        72      //0243H
//#define     DMA_PWMAR_VECTOR        73      //024BH