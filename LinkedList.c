#include <stdio.h>
#include <stdlib.h>
#include "CommonTypes.h"
#include "LinkedList.h"

LinkedListNode* LinkedList_MakeNode(void *pData) {
	LinkedListNode* pTempNode = NULL;
	pTempNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));
	if (pTempNode == NULL) {
		return NULL;
	}
	else {
		pTempNode->pVal = pData;
		pTempNode->pNextNode = NULL;
		return pTempNode;
	}
}

void LinkedList_FreeNode(LinkedListNode* pNode,void (*freeData)()) {
	if (pNode != NULL) {
		freeData(pNode->pVal);
		free(pNode);
	}
}

void* LinkedList_GetData(LinkedListNode* pNode) {
	if (pNode == NULL) {
		return NULL;
	}
	return pNode->pVal;
}

LinkedList* LinkedList_Construct(void) {
	LinkedList* pList = NULL;
	pList = (LinkedList*)malloc(sizeof(LinkedList));
	if (pList == NULL) {
		printf("construct failed.(function)\n");
		return NULL;
	}
	else {
		pList->pHead = NULL;
		pList->pTail = NULL;
		pList->length = 0;
		printf("construct succeed.(function)\n");
		return pList;
	}
}

void LinkedList_Clear(LinkedList* pList,void (*freeData)()) {
	LinkedListNode* pTempNode;
	if (pList != NULL) {
		while (pList->pHead != NULL) {
			pTempNode = pList->pHead;
			pList->pHead = pList->pHead->pNextNode;
			freeData(pTempNode->pVal);
			free(pTempNode);
		}
		pList->pTail = NULL;
		pList->length = 0;
	}
}

void LinkedList_Destruct(LinkedList* pList, void (*freeData)()) {
	if (pList != NULL) {
		LinkedList_Clear(pList,freeData);
		free(pList);
	}
}

int LinkedList_Length(LinkedList* pList) {
	if (pList != NULL) {
		return pList->length;
	}
	else return -1;
}

YesNo LinkedList_IsEmpty(LinkedList *pList) {
	if (pList->length == 0) {
		return YES;
	}
	else return NO;
}

Status LinkedList_InsertAtFornt(LinkedList *pList, void* pData) {
	LinkedListNode* pTempNode;
	pTempNode = LinkedList_MakeNode(pData);
	if (pList == NULL || pTempNode == NULL) {
		return ERROR;
	}
	else {
		pTempNode->pNextNode = pList->pHead;
		pList->pHead = pTempNode;
		pList->length++;
		return OK;
	}
}

Status LinkedList_AppendToEnd(LinkedList* pList, void* pData) {
	LinkedListNode* pNode;
	if (pList != NULL && pData != NULL) {
		pNode = LinkedList_MakeNode(pData);
		if (pNode != NULL) {
			printf("pNode->pVal is %d\n",*(int*)pNode->pVal);
			if (pList->length == 0) {
				pList->pHead = pNode;
				pList->pTail = pNode;
				pList->length++;
				return OK;
			}
			else {
				pList->pTail->pNextNode = pNode;
				pList->pTail = pNode;
				pList->length++;
				return OK;
			}
		}
		else {
			return ERROR;
		}
	}
	else {
		return ERROR;
	}
}

Status LinkedList_InsertAfter(LinkedList *pList,LinkedListNode* pNode, void* pData) {
	LinkedListNode* pNewNode;
	if (pList == NULL) return ERROR;
	if (pList->length == 0) return ERROR;
	if (pNode != NULL) {
		pNewNode = LinkedList_MakeNode(pData);
		if (pNewNode != NULL) {
			pNewNode->pNextNode = pNode->pNextNode;
			pNode->pNextNode = pNewNode;
			pList->length++;
			return OK;
		}
		else return ERROR;
	}
	else return ERROR;
}

Status LinkedList_DeleteFirstNode(LinkedList *pList,void (*freeData)()) {
	LinkedListNode* pTempNode = NULL;
	if (pList == NULL) {
		return ERROR;
	}
	else if (pList->length > 0) {
		pTempNode = pList->pHead;
		pList->pHead = pList->pHead->pNextNode;
		LinkedList_FreeNode(pTempNode, freeData);
		pList->length--;
		if (pList->pHead == NULL) {
			pList->pTail = NULL;
		}
		return OK;
	}
	else return OK;
}

Status LinkedList_DeleteLastNode(LinkedList *pList,void (*freeData)()) {
	LinkedListNode* pTempNode = NULL;
	if (pList != NULL) {
		if (pList->length > 1) {
			pTempNode = pList->pHead;
			while (pTempNode->pNextNode != pList->pTail) {
				pTempNode = pTempNode->pNextNode;
			}
			freeData(pList->pTail->pVal);
			free(pList->pTail);
			pList->length--;
			pList->pTail = pTempNode;
			return OK;
		}
		else if (pList->length == 1) {
			freeData(pList->pHead->pVal);
			free(pList->pHead);
			pList->pHead = NULL;
			pList->pTail = NULL;
			pList->length--;
			return OK;
		}
		else return ERROR;
	}
	else return ERROR;
}

Status LinkedList_DeleteNode(LinkedList* pList, LinkedListNode* pNode, void (*freeData)()) {
	LinkedListNode* pTempNode;
	if (pList != NULL && pNode !=NULL) {
		if (pList->length == 0) {
			return ERROR;
		}
		else if (pList->length == 1) {
			if (pNode != pList->pHead) return ERROR;
			else {
				freeData(pNode->pVal);
				free(pNode);
				pList->length--;
				pList->pHead = pList->pTail = NULL;
				return OK;
			}
		}
		else if (pList->length > 1) {
			if (pNode == pList->pHead) {
				return LinkedList_DeleteFirstNode(pList, freeData);
			}
			else if (pNode == pList->pTail) {
				return LinkedList_DeleteLastNode(pList, freeData);
			}
			else {
				pTempNode = pList->pHead;
				while (pTempNode->pNextNode != pNode && pTempNode != NULL) {
					pTempNode = pTempNode->pNextNode;
				}
				if (pTempNode == NULL) return ERROR;
				else {
					pTempNode->pNextNode = pNode->pNextNode;
					freeData(pNode->pVal);
					free(pNode);
					pList->length--;
					return OK;
				}
			}
		}
		else return ERROR;
	}
	else return ERROR;
}

LinkedListNode* LinkedList_Search(LinkedList *pList,void *pData,YesNo (*Compare)()) {
	LinkedListNode* pTempNode = NULL;
	if (pList == NULL || pData == NULL) {
		return NULL;
	}
	else {
		if (pList->length == 0) {
			return NULL;
		}
		else {
			pTempNode = pList->pHead;
			while (pTempNode != NULL) {
				if (Compare(pTempNode->pVal, pData)) return pTempNode;
				pTempNode = pTempNode->pNextNode;
			}
			if (pTempNode == NULL) return NULL;
			return pTempNode;
		}
	}
}

Status LinkedList_Traverse(LinkedList *pList,Status (*visit)()) {
	LinkedListNode* pNode = NULL;
	if (pList == NULL || visit == NULL) return ERROR;
	else {
		if (pList->length == 0) {
			return ERROR;
		}
		else {
			pNode = pList->pHead;
			while (pNode != NULL) {
				if (!visit(pNode->pVal)) return ERROR;
				else pNode = pNode->pNextNode;
			}
			return OK;
		}
	}
}