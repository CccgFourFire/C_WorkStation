#include <stdio.h>
#include<stdlib.h>
#include <time.h>

#define mainSTACK_MAX 10

typedef struct mainStack *pmainStack;
struct mainStack {
	int plData[mainSTACK_MAX];
	int lTop;
};

typedef struct mainStack1 *pmainStack1;
struct mainStack1 {
	int plData[mainSTACK_MAX];
	int lTop1;
	int lTop2;
};

void vMainPush(pmainStack pxStack, int lData);
int lMainPop(pmainStack pxStack);
void vMainPush1(pmainStack1 pxStack, int lData, int lTag);
int lMainPop1(pmainStack1 pxStack, int lTag);

int main(int argc, char* argv[])
{
	clock_t xStarttime, xStoptime;
	double dDuration;
	int lRet,lCnt;
	struct mainStack xStack;
	struct mainStack1 xStack1;
	pmainStack pxStack = &xStack;
	pmainStack1 pxStack1 = &xStack1;
	pxStack->lTop = -1;
	pxStack1->lTop1 = -1;
	pxStack1->lTop2 = mainSTACK_MAX;
	xStarttime = clock();
	vMainPush1(pxStack1, 1, 1);
	vMainPush1(pxStack1, 2, 1);
	vMainPush1(pxStack1, 5, 2);
	vMainPush1(pxStack1, 6, 2);
	lRet = lMainPop1(pxStack1, 1);
	printf("Result is %d\n", lRet);
	lRet = lMainPop1(pxStack1, 2);
	// vMainPush(pxStack, 1);
	// vMainPush(pxStack, 10);
	// lRet = lMainPop(pxStack);
	xStoptime = clock();
	dDuration = (double)(xStoptime - xStarttime) / CLK_TCK;
	printf("Ticks count is %lf\n", (double)(xStoptime - xStarttime));
	printf("Opertaion Time is %6.2e\n", dDuration);
	printf("Result is %d\n", lRet);
	return 0;
}

void vMainPush(pmainStack pxStack, int lData)
{
	int lNewTop = pxStack->lTop + 1;
	if (pxStack->lTop == mainSTACK_MAX -1)
	{
		printf("Stack is full!!\n");
	}
	else
	{
		pxStack->plData[++(pxStack->lTop)] = lData;
	}
}

int lMainPop(pmainStack pxStack)
{
	if (pxStack->lTop == -1)
	{
		printf("Stack is empty!!\n");
	}
	else
	{
		return (pxStack->plData[(pxStack->lTop)--]);
	}
}

void vMainPush1(pmainStack1 pxStack, int lData, int lTag)
{
	if (pxStack->lTop1 + 1 == pxStack->lTop2)
	{
		printf("Stack is full!!\n");
	}
	if (lTag == 1)
	{
		pxStack->plData[++(pxStack->lTop1)] = lData;
	}
	else
	{
		pxStack->plData[--(pxStack->lTop2)] = lData;
	}
}

int lMainPop1(pmainStack1 pxStack, int lTag)
{
	if (lTag == 1)
	{
		if (pxStack->lTop1 == -1)
		{
			printf("Stack1 is empty!!\n");
		}
		else
		{
			return (pxStack->plData[(pxStack->lTop1)--]);
		}
	}
	else
	{
		if (pxStack->lTop2 == mainSTACK_MAX)
		{
			printf("Stack2 is empty!!\n");
		}
		else
		{
			return (pxStack->plData[(pxStack->lTop2)++]);
		}
	}
}