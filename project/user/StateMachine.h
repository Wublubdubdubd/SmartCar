/*
״̬����

1����Ŀ�л�

2��Ӧ�Խ���״��

���·�ʽ��

preState = State;
State = Event_xxx[State];

*/
#ifndef _STATEMACHINE_H
#define _STATEMACHINE_H

/*��ǰ״̬����һ״̬*/
extern int State, preState;

/*�¼�����*/
extern const int Event_Finish[];

extern const int Event_Emergency[];

extern const int Event_Restart[];

/*��غ���*/
void StateUpdate(const int * Event);//״̬����


#endif