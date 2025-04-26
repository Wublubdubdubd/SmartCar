#include "StateMachine.h"

/*当前状态与上一状态*/
int State = 0, preState = 0;

/*状态类型定义*/
#define State_Init 0 //初始化

#define State_Subject_1 1 //科目一
#define State_Subject_2 2 //科目二
#define State_Subject_3 3 //科目三

#define State_Shut 4 //紧急停止

#define State_Finish 5 //完成

/*事件定义；-1：未定义的跳转 ；-2：回溯至上一状态*/
const int Event_Finish[]={State_Subject_1,State_Subject_2,State_Subject_3,State_Finish,-1,-1};

const int Event_Emergency[]={-1,State_Shut,State_Shut,State_Shut,-1,State_Shut};

const int Event_Restart[]={-1,-1,-1,-1,-2,-1};

//状态机更新
void StateUpdate(const int * Event)
{
    preState = State;
  
    State = Event[State];
  
    if(State == -1)State = preState;
}