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
#include "isr.h"

void DMA_UART1_IRQHandler (void) interrupt 4
{
    static vuint8 dwon_count = 0;
    if (DMA_UR1R_STA & 0x01)		// �������
    {
        DMA_UR1R_STA &= ~0x01;		// ���־λ
        uart_rx_start_buff(UART_1);	// ������һ�ν��գ���ر���
        
        //�����Զ�����
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
    
    if (DMA_UR1R_STA & 0x02)	//���ݶ���
    {
        DMA_UR1R_STA &= ~0x02;	//���־λ
        uart_rx_start_buff(UART_1);	// ������һ�ν��գ���ر���
        // �������������жϣ������UART��������û��ȡ��֮ǰ������!
        // �������������жϣ������UART��������û��ȡ��֮ǰ������!
        // �������������жϣ������UART��������û��ȡ��֮ǰ������!
    }
}



void DMA_UART2_IRQHandler (void) interrupt 8
{

    if (DMA_UR2R_STA & 0x01)		// �������
    {
        DMA_UR2R_STA &= ~0x01;		// ���־λ
        uart_rx_start_buff(UART_2);	// ������һ�ν��գ���ر���
        
        if(uart2_irq_handler != NULL)
        {
            uart2_irq_handler(uart_rx_buff[UART_2][0]);
        }
    }
    
    if (DMA_UR2R_STA & 0x02)		//���ݶ���
    {
        DMA_UR2R_STA &= ~0x02;		//���־λ
        uart_rx_start_buff(UART_2);	// ������һ�ν��գ���ر���
        // �������������жϣ������UART��������û��ȡ��֮ǰ������!
        // �������������жϣ������UART��������û��ȡ��֮ǰ������!
        // �������������жϣ������UART��������û��ȡ��֮ǰ������!
        
    }
}

void DMA_UART3_IRQHandler (void) interrupt 17
{

    if (DMA_UR3R_STA & 0x01)		// �������
    {
        DMA_UR3R_STA &= ~0x01;		// ���־λ
        uart_rx_start_buff(UART_3);	// ������һ�ν��գ���ر���
        
        if(uart3_irq_handler != NULL)
        {
        
            uart3_irq_handler(uart_rx_buff[UART_3][0]);
            
        }
    }
    
    if (DMA_UR3R_STA & 0x02)		//���ݶ���
    {
        DMA_UR3R_STA &= ~0x02;		//���־λ
        uart_rx_start_buff(UART_3);	// ������һ�ν��գ���ر���
        // �������������жϣ������UART��������û��ȡ��֮ǰ������!
        // �������������жϣ������UART��������û��ȡ��֮ǰ������!
        // �������������жϣ������UART��������û��ȡ��֮ǰ������!
        
    }
}

void DMA_UART4_IRQHandler (void) interrupt 18
{

    if (DMA_UR4R_STA & 0x01)		// �������
    {
        DMA_UR4R_STA &= ~0x01;		// ���־λ
        uart_rx_start_buff(UART_4);	// ������һ�ν��գ���ر���
        
        if(uart4_irq_handler != NULL)
        {
            uart4_irq_handler(uart_rx_buff[UART_4][0]);
            
        }
    }
    
    if (DMA_UR4R_STA & 0x02)	//���ݶ���
    {
        DMA_UR4R_STA &= ~0x02;	//���־λ
        uart_rx_start_buff(UART_4);	// ������һ�ν��գ���ر���
        // �������������жϣ������UART��������û��ȡ��֮ǰ������!
        // �������������жϣ������UART��������û��ȡ��֮ǰ������!
        // �������������жϣ������UART��������û��ȡ��֮ǰ������!
        
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
  * @brief TIM0�жϴ���������ȡimu����
  * @param ��
  * @return ��
  */
void pit_hanlder_imu(void)
{ 
    
    //��ȡ����������
    imu660ra_get_acc();  // ���ٶ�
    imu660ra_get_gyro(); // ���ٶ�
  
    //acc�˲�
    FOCF(&imu660ra_acc_x,&imu_acc_x_pre,0.1);
    FOCF(&imu660ra_acc_y,&imu_acc_y_pre,0.1);
    FOCF(&imu660ra_acc_z,&imu_acc_z_pre,0.1);
  
    //gyro�˲�
    FOCF(&imu660ra_gyro_x,&imu_gyro_x_pre,0.1);
    FOCF(&imu660ra_gyro_y,&imu_gyro_y_pre,0.1);
    FOCF(&imu660ra_gyro_z,&imu_gyro_z_pre,0.1);
  
    //ת��Ϊʵ������ֵ��������ƫ
	  imu_acc[0]=imu660ra_acc_transition(imu660ra_acc_x);
	  imu_acc[1]=imu660ra_acc_transition(imu660ra_acc_y)+0.017;
	  imu_acc[2]=imu660ra_acc_transition(imu660ra_acc_z);
	

    imu_gyro[0]=imu660ra_gyro_transition(imu660ra_gyro_x);
	  imu_gyro[1]=imu660ra_gyro_transition(imu660ra_gyro_y);
	  imu_gyro[2]=imu660ra_gyro_transition(imu660ra_gyro_z);
	
		//�����ںϻ�ȡŷ����
		GetEuler(imu_gyro,0.005);
		
//		imu_acc[0] -= (2*(q1*q3 - q0*q2));
//		if(fabs(imu_acc[0])<0.05)imu_acc[0]=0;
//		x_v += (imu_acc[0] * 0.005);
}
/**
  * @brief TIM1�жϴ���������ȡgps����
  * @param ��
  * @return ��
  */
void pit_hanlder_gps(void)
{
    //��ȡgps����
    if(gps_tau1201_flag)
    {
      gps_tau1201_flag = 0;
      gps_date_ready = (!gps_data_parse()) ? 1 : 0;
    }
    else gps_date_ready = 0;
}
/**
  * @brief TIM11�жϴ����������½ǶȻ�
  * @param ��
  * @return ��
  */
void pit_hanlder_angle(void)
{
    uint32 angle_duty;

  
    encoder_data = encoder_get_count(ENCODER_DIR_1);  // ��ȡ����������
    encoder_clear_count(ENCODER_DIR_1);               // ��ձ���������
    
    velocity = encoder_data * encode2vel; 
    
    if( curState < State_Yaw_Init ) return; // ��ʼ���򱣻�״̬����������

    //̧������Զ�����
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
      // �ǶȻ�
      angle_u = Angle_Pid_fun(0.01);
      // �ٶȻ�
      velocity_u = Velocity_Pid_fun(0.01);
    }
    
    //�� ̧�����
	  angle_duty = constrain_uint32(duty_up_left);
    pwm_set_duty(PWM_1,angle_duty);
	  //�� ̧�����
	  angle_duty = constrain_uint32(duty_up_right);
    pwm_set_duty(PWM_2,angle_duty);
    //�� �ƽ����
    angle_duty = constrain_uint32(duty_forward_left - angle_u + velocity_u + 20);
    pwm_set_duty(PWM_3,angle_duty);
    //�� �ƽ����
    angle_duty = constrain_uint32(duty_forward_right + angle_u + velocity_u - 20 );
    pwm_set_duty(PWM_4,angle_duty);
    
}
void my_pit_init()
{
    //1s����GPS����
    tim1_irq_handler = pit_hanlder_GPS;	
    pit_ms_init(PIT_GPS, 1000);
    //10ms���½ǶȻ�
    tim3_irq_handler = pit_hanlder_angle;
    pit_ms_init(PIT_ANGLE, 10);
    //5ms����IMU����
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