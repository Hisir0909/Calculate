#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "CommonTypes.h"
/*包含Status类型的定义*/

typedef struct _Node{
	void* pVal;
	struct _Node* pNextNode;
}LinkedListNode;
/*链表节点的定义*/

typedef struct {
	LinkedListNode* pHead;
	LinkedListNode* pTail;
	int length;
}LinkedList;
/*链表的定义*/

LinkedListNode* LinkedList_MakeNode(void* pData);
/*
	功能：制造一个链表节点
	输入：pData 指向数据；
	输出：成功输出节点地址,失败输出NULL；
*/

void LinkedList_FreeNode(LinkedListNode* pNode, void (*freeData)());
/*
	功能：释放节点
	输入：pNode 指向节点  freeData()是释放节点上数据的函数
*/

void* LinkedList_GetData(LinkedListNode* pNode);
/*
	功能：获得节点的数据
	输入：pNode 指向某一节点
	输出：成功输出数据地址，失败则输出NULL；
*/

LinkedList* LinkedList_Construct(void);
/*
	功能：构造一个链表
	输出：成功返回链表的地址，失败返回NULL；
*/

void LinkedList_Clear(LinkedList* pList,void (*freeData)());
/*
	功能：清空链表
	输入：pList 指向链表 freeData指向清除数据的函数参数为数据的指针；
*/

void LinkedList_Destruct(LinkedList* pList,void (*freeData)());
/*
	功能：解构链表
	输入：pList 指向链表
*/

int LinkedList_Length(LinkedList* pList);
/*
	功能：输出链表的长度
	输入：pList 指向链表
	输出：链表的长度  成功返回非负数，失败返回-1；
*/

YesNo LinkedList_IsEmpty(LinkedList* pList);
/*
	功能：判断链表是否为空
	输入：pList 指向链表
	输出：YES为空，NO为不为空
*/

Status LinkedList_InsertAtFornt(LinkedList* pList,void* pData);
/* 
	功能：把数据插入链表头部
	输入：pList 指向链表 ，pData 指向数据
	输出：成功返回OK 失败返回ERROR
*/

Status LinkedList_AppendToEnd(LinkedList* pList,void* pData);
/*
	功能：把数据加载链表尾部
	输入：pList 指向链表，pData 指向数据
	输出：成功返回OK 失败返回ERROR
*/

Status LinkedList_InsertAfter(LinkedList* pList,LinkedListNode* pNode,void* pData);
/*
	功能：把数据插入到某个节点之后
	输入：pList 指向链表，pNode 指向节点，pData 指向数据
	输出：成功返回OK，失败返回ERROR
*/

Status LinkedList_DeleteFirstNode(LinkedList* pList, void (*freeData)());
/*
	功能：删除链表第一个节点
	输入：pList 指向链表 freeData指向释放数据的函数
	输出：成功返回OK，失败返回ERROR
*/

Status LinkedList_DeleteLastNode(LinkedList* pList,void (*freeData)());
/*
	功能：删除链表尾部节点
	输入：pList 指向链表  freeData指向释放数据的函数
	输出：成功返回OK，失败返回ERROR
*/

Status LinkedList_DeleteNode(LinkedList* pList,LinkedListNode* pNode,void (*freeData)());
/*
	功能：删除指定节点
	输入：pList 指向链表 pNode 指向要被删除的节点 freeData指向释放数据的函数
	输出：成功返回OK，失败返回ERROR
*/

LinkedListNode* LinkedList_Search(LinkedList* pList,void* pData,YesNo (*Compare)());
/*
	功能：寻找链表中的数据
	输入：pList 指向链表，pData指向数据
	输出：成功返回节点的地址，失败返回NULL
*/

Status LinkedList_Traverse(LinkedList* pList,Status (*visit)());
/*
	功能：用visit函数遍历链表 visit以数据指针为参数
	输入：pList 指向链表，visit指向所要进行的函数
	输出：成功返回OK，失败返回ERROR
*/

#endif