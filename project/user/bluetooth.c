#include "bluetooth.h"
#define buffer_size 64
#define command_size 2*sizeof(char)

uint8 data_buffer[buffer_size];
uint8 data_len;


void blue_tooth_read_loop(void)
{
    data_len = ble6a20_read_buffer(data_buffer, buffer_size);                            // �鿴�Ƿ�����Ϣ Ĭ�ϻ�������BLE6A20_BUFFER_SIZE �ܹ� 64 �ֽ�
    if(data_len != 0)                                                           // �յ�����Ϣ ��ȡ�����᷵��ʵ�ʶ�ȡ�������ݸ���
    {
        ble6a20_send_buffer(data_buffer, data_len);                             // ���յ�����Ϣ���ͻ�ȥ
        ble6a20_send_string("\r\n");
        memset(data_buffer, 0, buffer_size);
        func_uint_to_str((char *)data_buffer, data_len);
        ble6a20_send_string("data len:");                                       // ��ʾʵ���յ���������Ϣ
        ble6a20_send_buffer(data_buffer, strlen((const char *)data_buffer));    // ��ʾ�յ������ݸ���
        ble6a20_send_string(".\r\n");
    }
}

void blue_tooth_read(char* buffer)//��ȡ����
{
    if(ble6a20_read_buffer(data_buffer, buffer_size))                          // �鿴�Ƿ�����Ϣ Ĭ�ϻ�������BLE6A20_BUFFER_SIZE �ܹ� 64 �ֽ�
    {
			ble6a20_send_string("Recived: ");
			ble6a20_send_byte(data_buffer[0]);
			ble6a20_send_string("\r\n");
			memcpy(buffer, data_buffer, command_size);
    }
}
