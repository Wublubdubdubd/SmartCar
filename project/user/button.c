#include "button.h"

// ����״̬����
uint8 key1_status = 1;
uint8 key2_status = 1;
uint8 key3_status = 1;

// ���ر�־λ
uint8 key1_flag = 0;
uint8 key2_flag = 0;
uint8 key3_flag = 0;

void button_init()
{
  gpio_init(KEY1_PIN, GPI, 1, GPI_PULL_UP);
	gpio_init(KEY2_PIN, GPI, 1, GPI_PULL_UP);
	gpio_init(KEY3_PIN, GPI, 1, GPI_PULL_UP);
}

void get_key()
{
  uint8 key1_last_status = key1_status;
  uint8 key2_last_status = key2_status;
  uint8 key3_last_status = key3_status;
  
  //��ȡ��ǰ������״̬
  key1_status = gpio_get_level(KEY1_PIN);
  key2_status = gpio_get_level(KEY2_PIN);
  key3_status = gpio_get_level(KEY3_PIN);
  
  //��⵽��������֮��  ���ſ���λ��־λ
  if(key1_status && !key1_last_status)    key1_flag = 1;
  if(key2_status && !key2_last_status)    key2_flag = 1;
  if(key3_status && !key3_last_status)    key3_flag = 1;
}

void refresh_button()
{
  key1_flag = 0;
  key2_flag = 0;
  key3_flag = 0;
}