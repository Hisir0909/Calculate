#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "LinkedList.h"
#include "LinkedListStack.h"
#include "CommonTypes.h"

#define POSITIVE 0
#define NEGATIVE 1

typedef enum {
	SIN = 0, COS = 1, TAN = 2, ARCSIN = 3, ARCCOS = 4, ARCTAN = 5, POWER = 6, MULTIPLY = 7,
	MINUS = 8, PLUS = 9, DIVIDE = 10, LEFT_BRACKET = 11, RIGHT_BRACKET = 12
}  _Operate;      // 用数字替代运算符，避免使用数组


/*
	功能：转化并计算
	输入：pSymbolStack 指向操作符栈，pNumericalStack 指向数值栈  degree 为当前操作符
	输出： 成功返回OK ，失败返回ERROR。
*/
Status TransAndCaculate(LinkedList* pSymbolStack, LinkedList* pNumericalStack, int degree);


/*
	功能：得到数值
	输入：pData 指向所得的数 putFile 指向输入文件 ，pData 指向 返回现在的字符
	输出：成功返回OK；失败返回ERROR
*/
Status GetData(double* pNumber, FILE* putFile, char* pData);


/*
	功能：得到运算符优先度；
	输入：pData 指向运算符
	输出：正确输出优先度，失败输出0
*/
int GetDegree(_Operate operate);


/*
	功能：得到运算符；
	输入：putFile 指向输入文件，pData 指向当前截取到的字符。
	输出：成功返回OK ，失败返回ERROR；

*/
Status GetOperate(FILE* putFile, char* pData, _Operate* pOperate);




Status  TransAndCaculate(LinkedList* pSymbolStack, LinkedList* pNumericalStack, int degree) {
	_Operate* pOperate = NULL;
	int tempDegree = 0;
	double* pData = NULL, * pTempData = NULL;
	int flag = 0;  // flag 2表示运算符是二目, 1表示一目

	if (pSymbolStack == NULL || pNumericalStack == NULL) {
		return ERROR;
	}
	if (Stack_Pop(pSymbolStack, &pOperate) == ERROR) {
		return ERROR;
	}
	else {
		tempDegree = GetDegree(*pOperate);
	}
	while (tempDegree >= degree && tempDegree != 0) {

		flag = 0;
		switch (*pOperate) {
		case SIN:flag = 1; break;
		case COS:flag = 1; break;
		case TAN:flag = 1; break;
		case ARCCOS:flag = 1; break;
		case ARCSIN:flag = 1; break;
		case ARCTAN:flag = 1; break;
		case POWER:flag = 2; break;
		case PLUS:flag = 2; break;
		case MINUS:flag = 2; break;
		case MULTIPLY:flag = 2; break;
		case DIVIDE:flag = 2; break;
		}
		if (flag == 2) {
			if (!Stack_Pop(pNumericalStack, &pData) || !Stack_Pop(pNumericalStack, &pTempData)) {
				printf("Can't pop pNumericalStack.\n");
				exit(EXIT_FAILURE);
			}
			switch (*pOperate) {
			case PLUS:*pTempData += *pData; break;
			case MINUS:*pTempData -= *pData; break;
			case MULTIPLY:*pTempData *= *pData; break;
			case DIVIDE:*pTempData /= *pData; break;
			case POWER:*pTempData = pow(*pTempData, *pData); break;
			}
			free(pOperate);
			free(pData);
			if (Stack_Push(pNumericalStack, pTempData) == ERROR) {
				printf("\tCan't push pNumericalStack.\n");
				exit(EXIT_FAILURE);
			}
		}
		else if (flag == 1) {
			if (!Stack_Pop(pNumericalStack, &pData)) {
				printf("Can't pop pNumericalStack.\n");
				exit(EXIT_FAILURE);
			}
			switch (*pOperate) {
			case SIN:*pData = sin(*pData); break;
			case COS:*pData = cos(*pData); break;
			case TAN:*pData = tan(*pData); break;
			case ARCCOS:
				if (*pData > 1 || *pData < -1) {
					printf("arccosx  -1<=x<=1\n");
					exit(EXIT_FAILURE);
				}
				*pData = acos(*pData); break;
			case ARCSIN:
				if (*pData > 1 || *pData < -1) {
					printf("arccosx  -1<=x<=1\n");
					exit(EXIT_FAILURE);
				}
				*pData = asin(*pData); break;
			case ARCTAN:*pData = atan(*pData); break;
			}
			if (Stack_Push(pNumericalStack, pData) == ERROR) {
				printf("Can't push pNumbericalStack.\n");
				return ERROR;
			}
			free(pOperate);
		}
		if (Stack_Length(pSymbolStack) == 0) {
			return OK;                             //
		}
		else {
			if (Stack_GetTop(pSymbolStack, &pOperate) == ERROR) {
				printf("Can't gettop pSymbol Stack.\n");
				exit(EXIT_FAILURE);
			}
			tempDegree = GetDegree(*pOperate);
		}
		if (*pOperate == LEFT_BRACKET && degree == 1) {
			Stack_Pop(pSymbolStack, &pOperate);
			free(pOperate);
			return OK;
		}
		Stack_Pop(pSymbolStack, &pOperate);
	}
	if (tempDegree < degree) {
		if (Stack_Push(pSymbolStack, pOperate) == ERROR) {
			printf("Can't push pSymbolStack.\n");
			return ERROR;
		}
	}
	return OK;
}


Status GetData(double* pNumber, FILE* putFile, char* pData) {
	if (pNumber == NULL || pData == NULL) exit(EXIT_FAILURE);
	char data = '\0';
	double power = 0.1;
	int integer = 0;
	double decimal = 0;
	integer = (int)*pNumber;
	data = (char)fgetc(putFile);
	while (data >= '0' && data <= '9') {
		integer = integer * 10 + (int)data - (int)'0';
		data = (char)fgetc(putFile);
	}
	if (data == '.') {
		data = fgetc(putFile);
		if (!(data >= '0' && data <= '9')) {
			return ERROR;
		}
		while (data >= '0' && data <= '9') {
			decimal += (double)((long)data - (long)'0') * power;
			power /= 10.0;
			data = fgetc(putFile);
		}
	}
	*pNumber = (double)integer + decimal;
	*pData = data;
	return OK;
}


int GetDegree(_Operate operate) {
	switch (operate) {
	case LEFT_BRACKET:return 1; break;
	case RIGHT_BRACKET:return 1; break;
	case SIN:return 4; break;
	case COS:return 4; break;
	case TAN:return 4; break;
	case ARCCOS:return 4; break;
	case ARCSIN:return 4; break;
	case ARCTAN:return 4; break;
	case POWER:return 5; break;
	case PLUS:return 2; break;
	case MINUS:return 2; break;
	case MULTIPLY:return 3; break;
	case DIVIDE:return 3; break;
	default:return 0; break;
	}
}


Status GetOperate(FILE* putFile, char* pData, _Operate* pOperate) {
	char data = '\0';  // 截取的字符
	int i = 0; // 匹配 三角函数 循环用
	if (putFile == NULL || pData == NULL || pOperate == NULL) {
		printf("In GetOperate address is fault.\n");
		exit(EXIT_FAILURE);
	}
	data = *pData;
	switch (data) {
	case '+':
		*pOperate = PLUS;
		return OK;
		break;
	case '-':
		*pOperate = MINUS;
		return OK;
		break;
	case '*':
		*pOperate = MULTIPLY;
		return OK;
		break;
	case '/':
		*pOperate = DIVIDE;
		return OK;
		break;
	case ')':
		*pOperate = RIGHT_BRACKET;
		return OK;
		break;
	case '^':
		*pOperate = POWER;
		return OK;
		break;
	case '(':
		*pOperate = LEFT_BRACKET;
		return OK;
		break;
	case 's':
		for (i = 0; i < 2; i++) {
			data = fgetc(putFile);
			if (data == EOF) {
				return ERROR;
			}
			switch (i) {
			case 0: if (data != 'i') {
				return ERROR;
			}
				  break;
			case 1: if (data != 'n') {
				return ERROR;
			}
				  break;
			}
		}
		*pOperate = SIN;
		return OK;
		break;
	case 'c':
		for (i = 0; i < 2; i++) {
			data = fgetc(putFile);
			if (data == EOF) {
				return ERROR;
			}
			switch (i) {
			case 0: if (data != 'o') {
				return ERROR;
			}
				  break;
			case 1: if (data != 's') {
				return ERROR;
			}
				  break;
			}
		}
		*pOperate = COS;
		return OK;
		break;
	case 't':
		for (i = 0; i < 2; i++) {
			data = fgetc(putFile);
			if (data == EOF) {
				return ERROR;
			}
			switch (i) {
			case 0: if (data != 'a') {
				return ERROR;
			}
				  break;
			case 1: if (data != 'n') {
				return ERROR;
			}
				  break;
			}
		}
		*pOperate = TAN;
		return OK;
		break;
	case 'a':
		for (i = 0; i < 2; i++) {
			data = fgetc(putFile);
			if (data == EOF) {
				return ERROR;
			}
			switch (i) {
			case 0: if (data != 'r') {
				return ERROR;
			}
				  break;
			case 1: if (data != 'c') {
				return ERROR;
			}
				  break;
			}
		}
		data = fgetc(putFile);
		if (data == EOF) {
			return ERROR;
		}
		switch (data) {
		case 's':
			for (i = 0; i < 2; i++) {
				data = fgetc(putFile);
				if (data == EOF) {
					return ERROR;
				}
				switch (i) {
				case 0: if (data != 'i') {
					return ERROR;
				}
					  break;
				case 1: if (data != 'n') {
					return ERROR;
				}
					  break;
				}
			}
			*pOperate = ARCSIN;
			break;
		case 'c':
			for (i = 0; i < 2; i++) {
				data = fgetc(putFile);
				if (data == EOF) {
					return ERROR;
				}
				switch (i) {
				case 0: if (data != 'o') {
					return ERROR;
				}
					  break;
				case 1: if (data != 's') {
					return ERROR;
				}
					  break;
				}
			}
			*pOperate = ARCCOS;
			break;
		case 't':
			for (i = 0; i < 2; i++) {
				data = fgetc(putFile);
				if (data == EOF) {
					return ERROR;
				}
				switch (i) {
				case 0: if (data != 'a') {
					return ERROR;
				}
					  break;
				case 1: if (data != 'n') {
					return ERROR;
				}
					  break;
				}
			}
			*pOperate = ARCTAN;
			break;
		default:
			return ERROR;
			break;
		}
		return OK;
		break;
	default:
		return ERROR;
		break;
	}

}

//debug

Status PutChar(void* pdata) {
	switch (*(_Operate*)pdata) {
	case 0:printf(" sin "); break;
	case 1:printf(" cos "); break;
	case 2:printf(" tan "); break;
	case 3:printf(" arccos "); break;
	case 4:printf(" arcsin "); break;
	case 5:printf(" arctan "); break;
	case 6:printf(" ^ "); break;
	case 7:printf(" * "); break;
	case 8:printf(" - "); break;
	case 9:printf(" + "); break;
	case 10:printf(" / "); break;
	case 11:printf(" ( "); break;
	case 12:printf(" ) "); break;
	}
	return OK;
}

Status PutNumber(void* pdata) {
	printf(" %lf ", *(double*)pdata);
	return OK;
}

int main(int argc, char* argv[]) {
	LinkedList* pSymbolStack = NULL, * pNumericalStack = NULL;  // pSymbolStack 指向操作符栈，pNumericalStack 指向数值栈
	int i = 0;                                      // i        表示第几次
	int flag = POSITIVE;                            // flag     表示数字的正负
	int	degree = 0, tempDegree = 0;                 // degree   表示当前的运算符优先度,tempdegree表示栈顶运算符优先度 
	_Operate* pOperate = NULL, * pTempOperate = NULL;   // pOperate 指向当前操作符 ，pTempOperate 指向栈顶操作符
	char data;                                      // data     存储当前截取到的字符
	double* pNumber = NULL, result = 0.0;           // pNumer   指向取到数值，result 为结果
	FILE* putFile = NULL, * outFile = NULL;         // putfile  指向输入文件  putFile 指向输出文件
	_Operate operate = -1;                          // operate  存放操作符

	if (argc != 3) {                              // 命令参数错误
		printf("Usage: %s filename\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	if (fopen_s(&putFile, argv[1], "r") != 0 || (fopen_s(&outFile, argv[2], "w") != 0)) {  //文件打开失败  fopen_s()为安全版
		printf("Can't open %s or %s\n", argv[0], argv[1]);
	}
	pSymbolStack = LinkedList_Construct();
	pNumericalStack = LinkedList_Construct();
	if (pSymbolStack == NULL || pNumericalStack == NULL) {  //初始化失败
		fprintf(outFile, "Inital Stack failed.");
		exit(EXIT_FAILURE);
	}
	data = fgetc(putFile);
	while (data != EOF) {

#if DEBUG		
		printf("第%d次\n", ++i);
		printf("	pNumericalStack :");
		if (Stack_Length(pNumericalStack) != 0) {
			Stack_Traverse(pNumericalStack, PutNumber);

		}
		printf("\n");
		printf("	pSymbolStack :");
		if (Stack_Length(pSymbolStack) != 0) {
			Stack_Traverse(pSymbolStack, PutChar);

		}
		printf("\n");
#endif

		if (data >= '0' && data <= '9') {
			pNumber = (double*)malloc(sizeof(double));
			if (pNumber == NULL) {
				printf("\tpNumber malloc failed.\n");
				exit(EXIT_FAILURE);
			}
			*pNumber = data - '0';
			if (GetData(pNumber, putFile, &data) == ERROR) {
				fprintf(outFile, "式子有错.\n");
				exit(EXIT_FAILURE);
			}
			*pNumber *= pow(-1, flag);
			flag = POSITIVE;

#if DEBUG
			printf("	number = %lf\n", *pNumber);
#endif

			if (Stack_Push(pNumericalStack, pNumber) == ERROR) {
				printf("\tPush pNumbericalStack failed.\n");
				exit(EXIT_FAILURE);
			}
		}
		else {

#if DEBUG
			printf("	operate = %c\n", data);
#endif

			if (data == ' ' || data == '\n') {
				data = fgetc(putFile);
				continue;
			}
			if (data == '=') {
				degree = 0;
				TransAndCaculate(pSymbolStack, pNumericalStack, degree);
				if (Stack_Length(pSymbolStack) != 0) {
					printf("RIGHT_BRACKET lost.\n");
					exit(EXIT_FAILURE);
				}
				if (!Stack_Pop(pNumericalStack, &pNumber)) {
					printf("Can't pop pNumericalStack.\n");
					exit(EXIT_FAILURE);
				}
				result = *pNumber;
				free(pNumber);
				fprintf(outFile, "%f \n", result);
				data = fgetc(putFile);
				continue;
			}
			if (data == '-') {
				if (Stack_Length(pNumericalStack) == 0) {
					flag = NEGATIVE;
					data = fgetc(putFile);
					continue;
				}
				else if (Stack_Length(pSymbolStack) != 0) {
					if (Stack_GetTop(pSymbolStack, &pTempOperate) == ERROR) {
						printf("Can't gettop pSymbolStack.\n");
						exit(EXIT_FAILURE);
					}
					if (*pTempOperate == LEFT_BRACKET) {
						flag = NEGATIVE;
						data = fgetc(putFile);
						continue;
					}
				}
			}
			pOperate = (_Operate*)malloc(sizeof(_Operate));
			if (pOperate == NULL) {
				printf("malloc pOperate failed.\n");
				exit(EXIT_FAILURE);
			}
			if (GetOperate(putFile, &data, pOperate) == ERROR) {  // 匹配运算符
				fprintf(outFile, "Please enter valid symbol.\n");
				exit(EXIT_FAILURE);
			}
			operate = *pOperate;
			if (operate == LEFT_BRACKET) {
				if (!Stack_Push(pSymbolStack, pOperate)) {
					printf("Can't push pSymbolStack .\n");
					exit(EXIT_FAILURE);
				}
				data = fgetc(putFile);
				continue;
			}
			degree = GetDegree(operate);
			if (Stack_Length(pSymbolStack) == 0) {
				tempDegree = 0;
			}
			else {
				if (Stack_GetTop(pSymbolStack, &pTempOperate) == ERROR) {
					printf("Can't pop pSymbolStack.\n");
					exit(EXIT_FAILURE);
				}
				tempDegree = GetDegree(*pTempOperate);
			}
			if (degree <= tempDegree) {                                         /*比较优先度 */
				TransAndCaculate(pSymbolStack, pNumericalStack, degree);
			}
			if (operate == RIGHT_BRACKET) {
				data = (char)fgetc(putFile);
				free(pOperate);
				continue;
			}
			if (Stack_Push(pSymbolStack, pOperate) == ERROR) {
				printf("Can't pop pSymbolStack.\n");
				exit(EXIT_FAILURE);
			}
			data = fgetc(putFile);
		}
	}
	if (Stack_Length(pSymbolStack) != 0) {
		degree = 0;
		TransAndCaculate(pSymbolStack, pNumericalStack, degree);
		if (Stack_Length(pSymbolStack) != 0) {
			fprintf(outFile, "RIGHT_BRACKET lost.\n");
			exit(EXIT_FAILURE);
		}
		if (Stack_Pop(pNumericalStack, &pNumber) == ERROR) {
			printf("Can't pop pNumericalStack.\n");
			exit(EXIT_FAILURE);
		}
		result = *pNumber;
		free(pNumber);
		fprintf(outFile, "%f \n", result);
	}
	if (fclose(outFile) != 0 || fclose(putFile) != 0) {
		fprintf(stdout, "Can't %s or %s", argv[1], argv[2]);
		exit(EXIT_FAILURE);
	}
	return 0;
}
