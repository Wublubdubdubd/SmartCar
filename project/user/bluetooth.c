#include "bluetooth.h"

void blue_tooth_read(char* command)//读取数据
{
    if(ble6a20_read_buffer(command, command_size))                          // 查看是否有消息 默认缓冲区是BLE6A20_BUFFER_SIZE 总共 64 字节
    {
			ble6a20_send_string("Recived: ");
			ble6a20_send_byte(command[0]);
			ble6a20_send_string("\r\n");
    }
}
