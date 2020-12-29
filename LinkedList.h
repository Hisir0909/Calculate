#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "CommonTypes.h"
/*����Status���͵Ķ���*/

typedef struct _Node{
	void* pVal;
	struct _Node* pNextNode;
}LinkedListNode;
/*����ڵ�Ķ���*/

typedef struct {
	LinkedListNode* pHead;
	LinkedListNode* pTail;
	int length;
}LinkedList;
/*����Ķ���*/

LinkedListNode* LinkedList_MakeNode(void* pData);
/*
	���ܣ�����һ������ڵ�
	���룺pData ָ�����ݣ�
	������ɹ�����ڵ��ַ,ʧ�����NULL��
*/

void LinkedList_FreeNode(LinkedListNode* pNode, void (*freeData)());
/*
	���ܣ��ͷŽڵ�
	���룺pNode ָ��ڵ�  freeData()���ͷŽڵ������ݵĺ���
*/

void* LinkedList_GetData(LinkedListNode* pNode);
/*
	���ܣ���ýڵ������
	���룺pNode ָ��ĳһ�ڵ�
	������ɹ�������ݵ�ַ��ʧ�������NULL��
*/

LinkedList* LinkedList_Construct(void);
/*
	���ܣ�����һ������
	������ɹ���������ĵ�ַ��ʧ�ܷ���NULL��
*/

void LinkedList_Clear(LinkedList* pList,void (*freeData)());
/*
	���ܣ��������
	���룺pList ָ������ freeDataָ��������ݵĺ�������Ϊ���ݵ�ָ�룻
*/

void LinkedList_Destruct(LinkedList* pList,void (*freeData)());
/*
	���ܣ��⹹����
	���룺pList ָ������
*/

int LinkedList_Length(LinkedList* pList);
/*
	���ܣ��������ĳ���
	���룺pList ָ������
	���������ĳ���  �ɹ����طǸ�����ʧ�ܷ���-1��
*/

YesNo LinkedList_IsEmpty(LinkedList* pList);
/*
	���ܣ��ж������Ƿ�Ϊ��
	���룺pList ָ������
	�����YESΪ�գ�NOΪ��Ϊ��
*/

Status LinkedList_InsertAtFornt(LinkedList* pList,void* pData);
/* 
	���ܣ������ݲ�������ͷ��
	���룺pList ָ������ ��pData ָ������
	������ɹ�����OK ʧ�ܷ���ERROR
*/

Status LinkedList_AppendToEnd(LinkedList* pList,void* pData);
/*
	���ܣ������ݼ�������β��
	���룺pList ָ������pData ָ������
	������ɹ�����OK ʧ�ܷ���ERROR
*/

Status LinkedList_InsertAfter(LinkedList* pList,LinkedListNode* pNode,void* pData);
/*
	���ܣ������ݲ��뵽ĳ���ڵ�֮��
	���룺pList ָ������pNode ָ��ڵ㣬pData ָ������
	������ɹ�����OK��ʧ�ܷ���ERROR
*/

Status LinkedList_DeleteFirstNode(LinkedList* pList, void (*freeData)());
/*
	���ܣ�ɾ�������һ���ڵ�
	���룺pList ָ������ freeDataָ���ͷ����ݵĺ���
	������ɹ�����OK��ʧ�ܷ���ERROR
*/

Status LinkedList_DeleteLastNode(LinkedList* pList,void (*freeData)());
/*
	���ܣ�ɾ������β���ڵ�
	���룺pList ָ������  freeDataָ���ͷ����ݵĺ���
	������ɹ�����OK��ʧ�ܷ���ERROR
*/

Status LinkedList_DeleteNode(LinkedList* pList,LinkedListNode* pNode,void (*freeData)());
/*
	���ܣ�ɾ��ָ���ڵ�
	���룺pList ָ������ pNode ָ��Ҫ��ɾ���Ľڵ� freeDataָ���ͷ����ݵĺ���
	������ɹ�����OK��ʧ�ܷ���ERROR
*/

LinkedListNode* LinkedList_Search(LinkedList* pList,void* pData,YesNo (*Compare)());
/*
	���ܣ�Ѱ�������е�����
	���룺pList ָ������pDataָ������
	������ɹ����ؽڵ�ĵ�ַ��ʧ�ܷ���NULL
*/

Status LinkedList_Traverse(LinkedList* pList,Status (*visit)());
/*
	���ܣ���visit������������ visit������ָ��Ϊ����
	���룺pList ָ������visitָ����Ҫ���еĺ���
	������ɹ�����OK��ʧ�ܷ���ERROR
*/

#endif