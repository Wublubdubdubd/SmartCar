/*
状态机：

1、科目切换

2、应对紧急状况

更新方式：

preState = State;
State = Event_xxx[State];

*/
#ifndef _STATEMACHINE_H
#define _STATEMACHINE_H

typedef enum
{
  State_Bringup,   // 唤醒
  State_Init,      // 设备初始化
  State_Unlock,    // 安全解锁
 
  State_Yaw_Init,  // 航向角初始化
  State_Subject_1, // 科目一
  State_Subject_2, // 科目二
  State_Subject_3, // 科目三
  
  State_Shut,      // 紧急停止
  State_Finish     // 全部完成
  
}StateMachine;

/*当前状态与上一状态*/
extern StateMachine curState;


#endif