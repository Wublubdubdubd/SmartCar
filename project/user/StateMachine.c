#include "StateMachine.h"

/*��ǰ״̬����һ״̬*/
int State = 0, preState = 0;

/*״̬���Ͷ���*/
#define State_Init 0 //��ʼ��

#define State_Subject_1 1 //��Ŀһ
#define State_Subject_2 2 //��Ŀ��
#define State_Subject_3 3 //��Ŀ��

#define State_Shut 4 //����ֹͣ

#define State_Finish 5 //���

/*�¼����壻-1��δ�������ת ��-2����������һ״̬*/
const int Event_Finish[]={State_Subject_1,State_Subject_2,State_Subject_3,State_Finish,-1,-1};

const int Event_Emergency[]={-1,State_Shut,State_Shut,State_Shut,-1,State_Shut};

const int Event_Restart[]={-1,-1,-1,-1,-2,-1};

//״̬������
void StateUpdate(const int * Event)
{
    preState = State;
  
    State = Event[State];
  
    if(State == -1)State = preState;
}