#include "bluetooth.h"

void blue_tooth_read(char* command)//��ȡ����
{
    if(ble6a20_read_buffer(command, command_size))                          // �鿴�Ƿ�����Ϣ Ĭ�ϻ�������BLE6A20_BUFFER_SIZE �ܹ� 64 �ֽ�
    {
			ble6a20_send_string("Recived: ");
			ble6a20_send_byte(command[0]);
			ble6a20_send_string("\r\n");
    }
}
