#ifndef LINKEDLISTSTACK_H

#define LINKEDLISTSTACK_H

#include "LinkedList.h"

Status Stack_Pop(LinkedList *pStack,void **pData);
/*
	功能：把栈顶Data弹出
	输入：pStack 指向栈， pData 指向存放弹出数据的指针
	输出: 成功返回OK，失败返回ERROR
*/

Status Stack_Push(LinkedList* pStack, void* pData);
/*
	功能：把Data压入栈
	输入：pSatck 指向栈，pData 指向压入数据
	输出：成功返回OK，失败返回ERROR
*/

Status Stack_GetTop(LinkedList *pStack,void **pData);
/*
	功能：得到栈顶的数据，把值放到pData去
	输入：pStack 指向栈，pData 指向数据所要存放的地方
	输出：成功返回OK，失败返回ERROR
*/

Status Stack_Traverse(LinkedList* pStack, Status (*visit)());
/*
	功能：遍历栈
	输入：pStack 指向栈，visit()指向遍历的函数，其参数为pData,visit()成功返回OK，失败返回ERROR;
	输出：成功返回OK，失败返回ERROR。
	
*/

int Stack_Length(LinkedList* pStack);
/*
	功能：得到栈的长度；
	输入：pStack 指向栈
	输出：成功返回非负值，失败返回-1.
*/

#endif