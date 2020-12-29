#include "CommonTypes.h"
#include <stdio.h>
#include "LinkedList.h"
#include "LinkedListStack.h"

Status Stack_Pop(LinkedList* pStack, void **pData) {
	if (pStack == NULL ) {
		return ERROR;
	}
	else if(pStack->length == 0) {
		return ERROR;
	}
	else {
		*pData = pStack->pHead->pVal;
		if (pStack->length == 1) {
			pStack->pHead = NULL;
			pStack->pTail = NULL;
		}
		else {
			pStack->pHead = pStack->pHead->pNextNode;
		}
		pStack->length--;
		return OK;
	}
}

Status Stack_Push(LinkedList *pStack,void *pData) {
	return LinkedList_InsertAtFornt(pStack, pData);
}

int Stack_Length(LinkedList* pStack) {
	if (pStack == NULL) return -1;
	return pStack->length;
}

Status Stack_GetTop(LinkedList* pStack,void **pData) {
	if (pStack == NULL) {
		return ERROR;
	}
	else if (pStack->length == 0) {
		return ERROR;
	}
	else {
		*pData = pStack->pHead->pVal;
		return OK;
	}
}

Status Stack_Traverse(LinkedList* pStack, Status (*visit)()) {
	if (pStack == NULL || visit == NULL) {
		return ERROR;
	}
	else {
		if (pStack->length == 0) {
			return ERROR;
		}
		else {
			LinkedListNode* pTempNode = pStack->pHead;
			while (pTempNode != NULL && visit(pTempNode->pVal)) pTempNode = pTempNode->pNextNode;
			if (pTempNode != NULL) {
				return ERROR;
			}
			else return OK;	
		}
	}
}
