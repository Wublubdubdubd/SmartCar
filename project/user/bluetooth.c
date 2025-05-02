#include "bluetooth.h"
#define buffer_size 64
#define command_size 2*sizeof(char)

uint8 data_buffer[buffer_size];
uint8 data_len;


void blue_tooth_read_loop(void)
{
    data_len = ble6a20_read_buffer(data_buffer, buffer_size);                            // 查看是否有消息 默认缓冲区是BLE6A20_BUFFER_SIZE 总共 64 字节
    if(data_len != 0)                                                           // 收到了消息 读取函数会返回实际读取到的数据个数
    {
        ble6a20_send_buffer(data_buffer, data_len);                             // 将收到的消息发送回去
        ble6a20_send_string("\r\n");
        memset(data_buffer, 0, buffer_size);
        func_uint_to_str((char *)data_buffer, data_len);
        ble6a20_send_string("data len:");                                       // 显示实际收到的数据信息
        ble6a20_send_buffer(data_buffer, strlen((const char *)data_buffer));    // 显示收到的数据个数
        ble6a20_send_string(".\r\n");
    }
}

void blue_tooth_read(char* buffer)//读取数据
{
    if(ble6a20_read_buffer(data_buffer, buffer_size))                          // 查看是否有消息 默认缓冲区是BLE6A20_BUFFER_SIZE 总共 64 字节
    {
			ble6a20_send_string("Recived: ");
			ble6a20_send_byte(data_buffer[0]);
			ble6a20_send_string("\r\n");
			memcpy(buffer, data_buffer, command_size);
    }
}
