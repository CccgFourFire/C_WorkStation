#include <stdio.h>
#include<stdlib.h>
#include <time.h>

#define mainLIST_MAX 100

typedef struct mainList *pmainList;
struct mainList {
	int plData[mainLIST_MAX];
	int lLast;
};

pmainList pxMainMakeEmpty(void);
int lMainFind(int lData, pmainList pList);
int lMainInsert(int lData, int lPos, pmainList pList);
int lMainDelete(int lPos, pmainList pList);

int main(int argc, char* argv[])
{
	clock_t xStarttime, xStoptime;
	double dDuration;
	int lRet,lCnt;
	pmainList pList;
	xStarttime = clock();
	pList = pxMainMakeEmpty();
	pList->lLast = 10;
	for (lCnt = 0; lCnt <= pList->lLast; lCnt++)
	{
		pList->plData[lCnt] = lCnt * 2;
	}
	lMainInsert(3, 3, pList);
	lMainDelete(4, pList);
	lRet = lMainFind(4, pList);
	xStoptime = clock();
	dDuration = (double)(xStoptime - xStarttime) / CLK_TCK;
	printf("Ticks count is %lf\n", (double)(xStoptime - xStarttime));
	printf("Opertaion Time is %6.2e\n", dDuration);
	printf("Result is %d\n", lRet);
	return 0;
}

pmainList pxMainMakeEmpty(void)
{
	pmainList pList = malloc(sizeof(struct mainList));
	pList->lLast = -1;
	return pList;
}

int lMainFind(int lData, pmainList pList)
{
	int lCnt;
	for (lCnt = 0; lCnt <= pList->lLast; lCnt++)
	{
		if (pList->plData[lCnt] == lData)
		{
			return lCnt;
		}
	}
	return -1;
}

int lMainInsert(int lData, int lPos, pmainList pList)
{
	int lCnt;
	if (pList->lLast == (mainLIST_MAX - 1))
	{
		return -1;
	}
	if (lPos < 0 || lPos > (pList->lLast + 1))
	{
		return -1;
	}
	for (lCnt = pList->lLast; lCnt >= lPos; lCnt--)
	{
		pList->plData[lCnt + 1] = pList->plData[lCnt];
	}
	pList->plData[lPos] = lData;
	pList->lLast += 1;
	return 0;
}

int lMainDelete(int lPos, pmainList pList)
{
	int lCnt;
	if (pList->lLast == -1)
	{
		return -1;
	}
	if (lPos < 0 || lPos > pList->lLast)
	{
		return -1;
	}
	for (lCnt = lPos; lCnt < pList->lLast; lCnt++)
	{
		pList->plData[lCnt] = pList->plData[lCnt + 1];
	}
	pList->lLast -= 1;
	return 0;
}