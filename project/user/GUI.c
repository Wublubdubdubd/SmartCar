#include "GUI.h"
#include "ips114.h"
#include "StateMachine.h"

/* 菜单与焦点状态定义 */
typedef enum {
    MENU_STATUS = 0,   // 状态界面
    MENU_PID ,      // PID调整界面
    MENU_SAVEPOINT,
    MENU_RUN       // 运行确认界面
} MenuPage;

typedef enum {
    FOCUS_PID_TYPE = 0,    // 选择PID类型
    FOCUS_PID_PARAM = 1,   // 选择PID参数
    FOCUS_PID_EDIT = 2     // 编辑PID参数
} PIDFocus;

/* 全局变量 */
MenuPage page_num = MENU_STATUS;
PIDFocus pid_focus = FOCUS_PID_TYPE;
uint8 pid_type = 0;      // 0:角度外环 1:角度内环 2:速度外环 3:速度内环
uint8 pid_param = 0;     // 0:KP 1:KI 2:KD

bool page_change = false;
/* PID类型字符串 */
const char* pid_type_str[4] = {
    "AngleOuter",
    "AngleInner",
    "VelOuter",
    "VelInner"
};

/* 获取当前选中的PID结构体指针 */
static pid_param_t* get_pid_ptr(uint8 type) {
    switch(type) {
        case 0: return &angle_outer_pid;
        case 1: return &angle_inner_pid;
        case 2: return &velocity_outer_pid;
        case 3: return &velocity_inner_pid;
        default: return &angle_outer_pid;
    }
}

/* 显示静态内容 */
void IPS114_Show_Unit(void)
{
    uint8 i=0;
    if(page_change)
    {
      ips114_clear(RGB565_WHITE);
      page_change = false;
    }
    switch(page_num)
    {
        case MENU_STATUS:
            ips114_set_color(RGB565_BLUE,RGB565_WHITE);
            ips114_show_string(0,16*0,"Acc: x,y,z  (g)");
            ips114_set_color(RGB565_PURPLE,RGB565_WHITE);
            ips114_show_string(0,16*2,"Gyro: x,y,z (d/s)");
            ips114_set_color(RGB565_PINK,RGB565_WHITE);
            ips114_show_string(0,16*4,"GPS: S N H");
            ips114_show_string(0,16*5,"Lat:      Lon:");
            ips114_show_string(0,16*6,"v:        d:");
            break;

        case MENU_PID:
            ips114_set_color(RGB565_BLUE,RGB565_WHITE);
            ips114_show_string(0,16*0,"PID Param");
            // PID类型
            for(i=0;i<4;i++) {
                char buf[20];
                if(pid_type==i && pid_focus==FOCUS_PID_TYPE)
                    sprintf(buf,"[%s]",pid_type_str[i]);
                else
                    sprintf(buf," %s ",pid_type_str[i]);
                ips114_show_string(0,16*(1+i),buf);
            }
            // PID参数

            ips114_show_string(100,16*1, pid_param==0 ? (pid_focus==FOCUS_PID_PARAM?"[KP]":" KP ") : " KP ");
            ips114_show_string(100,16*2, pid_param==1 ? (pid_focus==FOCUS_PID_PARAM?"[KI]":" KI ") : " KI ");
            ips114_show_string(100,16*3, pid_param==2 ? (pid_focus==FOCUS_PID_PARAM?"[KD]":" KD ") : " KD ");
            
            if(pid_focus==FOCUS_PID_EDIT)
                ips114_show_string(100,16*4,"Edit Mode");
            else
                ips114_show_string(100,16*4,"         ");
            break;
        case MENU_SAVEPOINT:
            ips114_set_color(RGB565_MAGENTA, RGB565_WHITE);
            ips114_show_string(0, 16*0, "Save GPS Point");
            ips114_show_string(0, 16*2, "Press [OK] to Save");
            ips114_show_string(0, 16*3, "Press [Next] to Run");
            ips114_show_string(30, 16*5, "/");
            ips114_show_uint8(50, 16*5,Object_PointNum[0]);
            ips114_show_string(0, 16*6, "Lat ");
            ips114_show_string(0, 16*7, "Lon ");
            break;
        case MENU_RUN:
            ips114_set_color(RGB565_RED,RGB565_WHITE);
            ips114_show_string(0,16*0,"Run Robot?");
            ips114_show_string(0,16*2, run_confirm ? "[YES]" : " YES ");
            ips114_show_string(0,16*3, !run_confirm ? "[NO]" : " NO ");
            break;
    }
}

/* 显示动态内容 */
void IPS114_Show_Info(void)
{
    uint8 i=0;
    switch(page_num)
    {
        case MENU_STATUS:
            // 动态显示IMU、GPS等
            ips114_show_float(100,0,velocity,2,3);
            for(i=0;i<3;i++) {
                ips114_show_float(80*i, 16*1 ,imu_acc[i],2,3);
                ips114_show_float(80*i, 16*3 ,imu_gyro[i],2,3);
            }
            switch(curState)
            {
                case State_Init:     ips114_show_string(0,16*7,"Init  "); break;
                case State_Unlock:   ips114_show_string(0,16*7,"Unlock"); break;
                case State_Yaw_Init: ips114_show_string(0,16*7,"YawInit"); break;
                case State_Subject_1:ips114_show_string(0,16*7,"Object"); break;
            }
            if(gps_date_ready)
            {
                ips114_show_uint8(15, 16*5, gps_tau1201.state);
                ips114_show_uint8(70, 16*5, gps_tau1201.satellite_used);
                ips114_show_float(160, 16*5, gps_tau1201.height, 4, 6);
                ips114_show_float(30, 16*6, gps_tau1201.latitude, 4, 6);
                ips114_show_float(160, 16*6, gps_tau1201.longitude, 4, 6);
                ips114_show_float(30, 16*7, gps_tau1201.speed, 4, 6);
            }
            ips114_show_float(120, 16*4 ,yaw,3,3);

            break;
        case MENU_SAVEPOINT:
            // 可显示当前write_index等信息
            ips114_show_uint8(0, 16*5, write_index);
            ips114_show_float(30, 16*6, gps_tau1201.latitude,4, 6);
            ips114_show_float(30, 16*7, gps_tau1201.longitude,4, 6);
            break;
        case MENU_PID:
        {
            pid_param_t* pid = get_pid_ptr(pid_type);
            ips114_show_float(160,16*1,pid->kp,3,3);
            ips114_show_float(160,16*2,pid->ki,3,3);
            ips114_show_float(160,16*3,pid->kd,3,3);
            break;
        }
        case MENU_RUN:
            ips114_show_string(0,16*5,run_confirm ? "Ready to Run!" : "Waiting...     ");
            break;
    }
}

void GUI_Handle_Key(void)
{
    if(!key1_flag&&!key2_flag&&!key3_flag)return;
    switch(page_num)
    {
        case MENU_STATUS:
            if(key3_flag) { // 右键
                page_num = MENU_PID;
                page_change = true;
                pid_focus = FOCUS_PID_TYPE;
                IPS114_Show_Unit();
            }
            break;

        case MENU_PID:
            if(pid_focus == FOCUS_PID_TYPE) {
                if(key3_flag) {page_num = MENU_SAVEPOINT;page_change = true;} // 右键到下一界面
                if(key2_flag) pid_type = (pid_type + 1) % 4; // 中键下一个
                if(key1_flag) pid_focus = FOCUS_PID_PARAM;   // 左键进入参数选择
            } else if(pid_focus == FOCUS_PID_PARAM) {
              if(key1_flag) pid_focus = FOCUS_PID_TYPE; // 左键到PID选择
                if(key2_flag) pid_param = (pid_param + 1) % 3; // 中键下一个
                if(key3_flag) pid_focus = FOCUS_PID_EDIT;      // 右键进入编辑
            } else if(pid_focus == FOCUS_PID_EDIT) {
                pid_param_t* pid = get_pid_ptr(pid_type);
                float* param = pid_param == 0 ? &pid->kp : (pid_param == 1 ? &pid->ki : &pid->kd);
                if(key1_flag) *param -= 0.1f; // 左键减
                if(key2_flag) *param += 0.1f; // 中键加
                if(key3_flag) pid_focus = FOCUS_PID_PARAM; // 右键退出编辑
            }
            IPS114_Show_Unit();
            break;
        case MENU_SAVEPOINT:
            if(key3_flag) { // 右键下一界面
                page_num = MENU_RUN;
                page_change = true;
                pid_focus = FOCUS_PID_TYPE;
                IPS114_Show_Unit();
            }
						if(key2_flag) { 
                //W25Q_Erase4K_20(4096, 1);// 先擦除
								//ips114_show_string(100, 16*5, "Erease!");
								write_index = 0;
            }
            if(key1_flag&&(write_index<4)) { // 左键记录一次

                WritePoint(write_index++); // 记录
                IPS114_Show_Info(); // 刷新动态内容
            }
            break;
        case MENU_RUN:
            if(key1_flag) curState=State_Unlock; // 左键NO
            if(key3_flag) { // 右键返回主界面
                page_num = MENU_STATUS;
                page_change = true;
                IPS114_Show_Unit();
            }
            break;
    }
}