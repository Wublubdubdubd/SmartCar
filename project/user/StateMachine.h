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

typedef enum
{
  State_Bringup,   // ����
  State_Init,      // �豸��ʼ��
  State_Unlock,    // ��ȫ����
 
  State_Yaw_Init,  // ����ǳ�ʼ��
  State_Subject_1, // ��Ŀһ
  State_Subject_2, // ��Ŀ��
  State_Subject_3, // ��Ŀ��
  
  State_Shut,      // ����ֹͣ
  State_Finish     // ȫ�����
  
}StateMachine;

/*��ǰ״̬����һ״̬*/
extern StateMachine curState;


#endif