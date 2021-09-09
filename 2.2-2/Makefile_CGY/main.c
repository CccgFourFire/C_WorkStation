#include <stdio.h>
#include<stdlib.h>
#include <time.h>

typedef struct mainListStack *pmainListStack;
struct mainListStack {
	int lData;
	pmainListStack pxNext;
};

pmainListStack pxMainListStackCreat(void);
int lMainIsEmpty(pmainListStack pxList);
void vMainPush(pmainListStack pxList, int lData);
int lMainPop(pmainListStack pxList);

int main(int argc, char* argv[])
{
	clock_t xStarttime, xStoptime;
	double dDuration;
	int lRet,lCnt;
	pmainListStack pxListStack;
	xStarttime = clock();
	pxListStack = pxMainListStackCreat();
	vMainPush(pxListStack, 5);
	vMainPush(pxListStack, 7);
	vMainPush(pxListStack, 10);
	lRet = lMainPop(pxListStack);
	printf("Result is %d\n", lRet);
	lRet = lMainPop(pxListStack);
	printf("Result is %d\n", lRet);
	lRet = lMainPop(pxListStack);
	printf("Result is %d\n", lRet);
	lRet = lMainPop(pxListStack);
	xStoptime = clock();
	dDuration = (double)(xStoptime - xStarttime) / CLK_TCK;
	printf("Ticks count is %lf\n", (double)(xStoptime - xStarttime));
	printf("Opertaion Time is %6.2e\n", dDuration);
	printf("Result is %d\n", lRet);
	return 0;
}

pmainListStack pxMainListStackCreat(void)
{
	pmainListStack pxList;
	pxList = (pmainListStack)malloc(sizeof(struct mainListStack));
	pxList->pxNext = NULL;
	return pxList;
}

int lMainIsEmpty(pmainListStack pxList)
{
	return (pxList->pxNext == NULL);
}

void vMainPush(pmainListStack pxList, int lData)
{
	pmainListStack pxNewList;
	pxNewList = (pmainListStack)malloc(sizeof(struct mainListStack));
	pxNewList->lData = lData;
	pxNewList->pxNext = pxList->pxNext;
	pxList->pxNext = pxNewList;
}

int lMainPop(pmainListStack pxList)
{
	pmainListStack pxTep = pxList->pxNext;
	int lRet;
	if ((lMainIsEmpty(pxList)))
	{
		printf("Stack is empty\n");
		return NULL;
	}
	else
	{
		pxList->pxNext = pxTep->pxNext;
		lRet = pxTep->lData;
		free(pxTep);
		return lRet;
	}
}