#include <stdio.h>
#include<stdlib.h>
#include <time.h>

#define mainLIST_MAX 100

typedef struct mainList *pmainList;
struct mainList {
	int plData;
	pmainList pxNext;
};

typedef struct mainGList *pmainGList;
struct mainGList {
	int Ltag;
	union {
		int plData;
		pmainGList pxSubList;
	} xRegion;
	pmainGList pxNext;
};

pmainList pxMainMakeHead(void);
pmainList pxMainFind(int lData, pmainList pxList);
pmainList pxMainNumberFind(int lNum, pmainList pxList);
pmainList pxMainInsert(int lData, int lPos, pmainList pList);
pmainList pxMainDelete(int lPos, pmainList pxList);
int lMainLength(pmainList pxList);

int main(int argc, char* argv[])
{
	clock_t xStarttime, xStoptime;
	double dDuration;
	int lRet,lCnt;
	pmainList pxListHead, pxTmp;
	xStarttime = clock();
	pxListHead = pxMainMakeHead();
	pxListHead = pxMainInsert(2, 2, pxListHead);
	pxListHead = pxMainInsert(4, 3, pxListHead);
	pxListHead = pxMainInsert(6, 4, pxListHead);
	lRet = lMainLength(pxListHead);
	printf("Result is %d\n", lRet);
	pxMainFind(4, pxListHead);
	pxMainFind(5, pxListHead);
	pxListHead = pxMainDelete(3, pxListHead);
	lRet = lMainLength(pxListHead);
	xStoptime = clock();
	dDuration = (double)(xStoptime - xStarttime) / CLK_TCK;
	printf("Ticks count is %lf\n", (double)(xStoptime - xStarttime));
	printf("Opertaion Time is %6.2e\n", dDuration);
	printf("Result is %d\n", lRet);
	return 0;
}

pmainList pxMainMakeHead(void)
{
	pmainList pxNew;
	pxNew = malloc(sizeof(struct mainList));
	pxNew->plData = 0;
	pxNew->pxNext = NULL;
	return pxNew;
}

pmainList pxMainNumberFind(int lNum, pmainList pxList)
{
	pmainList pxTmp = pxList;
	int lCnt = 1;
	while ((pxTmp != NULL) && (lCnt < lNum))
	{
		pxTmp = pxTmp->pxNext;
		lCnt++;
	}
	if (lCnt == lNum)
	{
		return pxTmp;
	}
	else
	{
		return NULL;
	}
}

pmainList pxMainFind(int lData, pmainList pxList)
{
	pmainList pxTmp = pxList;
	while (pxTmp)
	{
		if (pxTmp->plData == lData)
		{
			printf("Number is in the list!!\n");
			return pxTmp;
		}
		pxTmp = pxTmp->pxNext;
	}
	printf("Number isn't in the list!!\n");
	return NULL;
}

pmainList pxMainInsert(int lData, int lPos, pmainList pxList)
{
	pmainList pxTmp, pxNew;
	if (lPos == 1)
	{
		pxNew = malloc(sizeof(struct mainList));
		pxNew->plData = lData;
		pxNew->pxNext = pxList;
		return pxNew;
	}
	pxTmp = pxMainNumberFind(lPos - 1, pxList);
	if (pxTmp == NULL)
	{
		return NULL;
	}
	else
	{
		pxNew = malloc(sizeof(struct mainList));
		pxNew->plData = lData;
		pxNew->pxNext = pxTmp->pxNext;
		pxTmp->pxNext = pxNew;
		return pxList;
	}
}

pmainList pxMainDelete(int lPos, pmainList pxList)
{
	pmainList pxTmp, pxDel;
	if (lPos == 1)
	{
		pxTmp = pxList;
		if (pxTmp != NULL)
		{
			pxList = pxTmp->pxNext;
			free(pxTmp);
		}
		else
		{
			return NULL;
		}
		return pxList;
	}
	pxTmp = pxMainNumberFind(lPos - 1, pxList);
	pxDel = pxTmp->pxNext;
	if (pxTmp == NULL)
	{
		return NULL;
	}
	else
	{
		pxTmp->pxNext = pxDel->pxNext;
		free(pxDel);
		return pxList;
	}
}

int lMainLength(pmainList pxList)
{
	pmainList pxTmp = pxList;
	int lCnt = 0;
	while (pxTmp)
	{
		lCnt++;
		pxTmp = pxTmp->pxNext;
	}
	return lCnt;
}