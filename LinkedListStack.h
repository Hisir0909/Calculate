#ifndef LINKEDLISTSTACK_H

#define LINKEDLISTSTACK_H

#include "LinkedList.h"

Status Stack_Pop(LinkedList *pStack,void **pData);
/*
	���ܣ���ջ��Data����
	���룺pStack ָ��ջ�� pData ָ���ŵ������ݵ�ָ��
	���: �ɹ�����OK��ʧ�ܷ���ERROR
*/

Status Stack_Push(LinkedList* pStack, void* pData);
/*
	���ܣ���Dataѹ��ջ
	���룺pSatck ָ��ջ��pData ָ��ѹ������
	������ɹ�����OK��ʧ�ܷ���ERROR
*/

Status Stack_GetTop(LinkedList *pStack,void **pData);
/*
	���ܣ��õ�ջ�������ݣ���ֵ�ŵ�pDataȥ
	���룺pStack ָ��ջ��pData ָ��������Ҫ��ŵĵط�
	������ɹ�����OK��ʧ�ܷ���ERROR
*/

Status Stack_Traverse(LinkedList* pStack, Status (*visit)());
/*
	���ܣ�����ջ
	���룺pStack ָ��ջ��visit()ָ������ĺ����������ΪpData,visit()�ɹ�����OK��ʧ�ܷ���ERROR;
	������ɹ�����OK��ʧ�ܷ���ERROR��
	
*/

int Stack_Length(LinkedList* pStack);
/*
	���ܣ��õ�ջ�ĳ��ȣ�
	���룺pStack ָ��ջ
	������ɹ����طǸ�ֵ��ʧ�ܷ���-1.
*/

#endif