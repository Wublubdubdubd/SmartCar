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

/*当前状态与上一状态*/
extern int State, preState;

/*事件定义*/
extern const int Event_Finish[];

extern const int Event_Emergency[];

extern const int Event_Restart[];

/*相关函数*/
void StateUpdate(const int * Event);//状态更新


#endif