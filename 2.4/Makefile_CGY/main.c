#include <stdio.h>
#include<stdlib.h>
#include <time.h>

struct mainPolyNode {
	int lcoef;
	int lexpon;
	struct mainPolyNode *pxNext;
};
typedef struct mainPolyNode *pxmainPolyNode;

int lMainPolyAdd(pxmainPolyNode pxAdd1, pxmainPolyNode pxAdd2, pxmainPolyNode pxResult);
pxmainPolyNode pxMainInsert(int lcoef, int lexpon, int lPos, pxmainPolyNode pxList);
pxmainPolyNode pxMainNumberFind(int lNum, pxmainPolyNode pxList);
pxmainPolyNode lMainPolyAdd1(pxmainPolyNode pxAdd1, pxmainPolyNode pxAdd2);
int lMainLength(pxmainPolyNode pxList);
pxmainPolyNode lMainPolyMul(pxmainPolyNode pxMul1, pxmainPolyNode pxMul2);

int main(int argc, char* argv[])
{
	clock_t xStarttime, xStoptime;
	double dDuration;
	int lRet,lCnt;
	struct mainPolyNode xAdd1;
	struct mainPolyNode xAdd2;
	struct mainPolyNode xResult;
	pxmainPolyNode pxAdd1 = &xAdd1;
	pxmainPolyNode pxAdd2 = &xAdd2;
	pxmainPolyNode pxResult = &xResult;
	pxmainPolyNode pxResult1;
	xStarttime = clock();
	// pxMainInsert(3, 4, 1, pxAdd1);
	// pxMainInsert(5, 4, 2, pxAdd1);
	// pxMainInsert(-1, 3, 3, pxAdd1);
	// pxMainInsert(2, 1, 4, pxAdd1);
	// pxMainInsert(-1, 0, 5, pxAdd1);
	pxMainInsert(3, 4, 1, pxAdd2);
	pxMainInsert(-5, 2, 2, pxAdd2);
	pxMainInsert(6, 1, 3, pxAdd2);
	pxMainInsert(-2, 0, 4, pxAdd2);
	pxMainInsert(5, 20, 1, pxAdd1);
	pxMainInsert(-7, 4, 2, pxAdd1);
	pxMainInsert(3, 1, 3, pxAdd1);
	// pxMainInsert(3, 1, 1, pxAdd2);
	// pxMainInsert(3, 0, 3, pxAdd2);
	// pxMainInsert(0, 0, 1, pxResult);
	// pxMainInsert(0, 0, 2, pxResult);
	// pxMainInsert(0, 0, 3, pxResult);
	// pxMainInsert(0, 0, 4, pxResult);
	// pxMainInsert(0, 0, 5, pxResult);
	// lMainPolyAdd(pxAdd1, pxAdd2, pxResult);
	pxResult1 = lMainPolyMul(pxAdd1, pxAdd2);
	xStoptime = clock();
	dDuration = (double)(xStoptime - xStarttime) / CLK_TCK;
	printf("Ticks count is %lf\n", (double)(xStoptime - xStarttime));
	printf("Opertaion Time is %6.2e\n", dDuration);
	printf("Result is %d\n", lRet);
	return 0;
}

void vMainAttach(int lcoef, int lexpon, pxmainPolyNode *ppxRear)
{
	pxmainPolyNode pxNew;
	pxNew = malloc(sizeof(struct mainPolyNode));
	pxNew->lcoef = lcoef;
	pxNew->lexpon = lexpon;
	pxNew->pxNext = NULL;
	(*ppxRear)->pxNext = pxNew;
	*ppxRear = pxNew;
}

pxmainPolyNode pxMainNumberFind(int lNum, pxmainPolyNode pxList)
{
	pxmainPolyNode pxTmp = pxList;
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

pxmainPolyNode pxMainInsert(int lcoef, int lexpon, int lPos, pxmainPolyNode pxList)
{
	pxmainPolyNode pxTmp, pxNew;
	if (lPos == 1)
	{
		pxList->lcoef = lcoef;
		pxList->lexpon = lexpon;
		pxList->pxNext = NULL;
		return pxList;
	}
	pxTmp = pxMainNumberFind(lPos - 1, pxList);
	if (pxTmp == NULL)
	{
		return NULL;
	}
	else
	{
		pxNew = malloc(sizeof(struct mainPolyNode));
		pxNew->lcoef = lcoef;
		pxNew->lexpon = lexpon;
		pxNew->pxNext = NULL;
		pxTmp->pxNext = pxNew;
		return pxList;
	}
}

int lMainLength(pxmainPolyNode pxList)
{
	pxmainPolyNode pxTmp = pxList;
	int lCnt = 0;
	while (pxTmp)
	{
		lCnt++;
		pxTmp = pxTmp->pxNext;
	}
	return lCnt;
}

pxmainPolyNode lMainPolySingleMul(pxmainPolyNode pxMul1, pxmainPolyNode pxSingleMul2)
{
	int lCoefSum, lExponSum;
	pxmainPolyNode pxFront, pxRear, pxTmp;
	pxFront = malloc(sizeof(struct mainPolyNode));
	pxRear = pxFront;
	while (pxMul1)
	{
		lCoefSum = pxMul1->lcoef * pxSingleMul2->lcoef;
		lExponSum = pxMul1->lexpon + pxSingleMul2->lexpon;
		vMainAttach(lCoefSum, lExponSum, &pxRear);
		pxMul1 = pxMul1->pxNext;
	}
	pxRear->pxNext = NULL;
	pxTmp = pxFront;
	pxFront = pxFront->pxNext;
	free(pxTmp);
	return pxFront;
}


pxmainPolyNode lMainPolyMul(pxmainPolyNode pxMul1, pxmainPolyNode pxMul2)
{
	int lLen1 = lMainLength(pxMul1);
	int lLen2 = lMainLength(pxMul2);
	int lCnt, lLenTmp;
	pxmainPolyNode pxSum = NULL;
	pxmainPolyNode pxTmp;
	if (lLen2 > lLen1)
	{
		lLenTmp = lLen2;
		lLen2 = lLen1;
		lLen1 = lLenTmp;
		pxTmp = pxMul2;
		pxMul2 = pxMul1;
		pxMul1 = pxTmp;
	}
	pxmainPolyNode pxTemp[lLen2];
	for (lCnt = 0; lCnt < lLen2; lCnt++)
	{
		pxTemp[lCnt] = lMainPolySingleMul(pxMul1, pxMul2);
		pxMul2 = pxMul2->pxNext;
	}
	for (lCnt = 0; lCnt < lLen2; lCnt++)
	{
		pxSum = lMainPolyAdd1(pxSum, pxTemp[lCnt]);
	}
	return pxSum;
}

pxmainPolyNode lMainPolyAdd1(pxmainPolyNode pxAdd1, pxmainPolyNode pxAdd2)
{
	int lSum;
	pxmainPolyNode pxFront, pxRear, pxTmp;
	pxFront = malloc(sizeof(struct mainPolyNode));
	pxRear = pxFront;
	while (pxAdd1 && pxAdd2)
	{
		if (pxAdd1->lexpon == pxAdd2->lexpon)
		{
			lSum = pxAdd1->lcoef + pxAdd2->lcoef;
			if (lSum)
			{
				vMainAttach(lSum, pxAdd1->lexpon, &pxRear);
			}
			pxAdd1 = pxAdd1->pxNext;
			pxAdd2 = pxAdd2->pxNext;
			continue;
		}
		else if (pxAdd1->lexpon > pxAdd2->lexpon)
		{
			vMainAttach(pxAdd1->lcoef, pxAdd1->lexpon, &pxRear);
			pxAdd1 = pxAdd1->pxNext;
			continue;
		}
		else if (pxAdd1->lexpon < pxAdd2->lexpon)
		{
			vMainAttach(pxAdd2->lcoef, pxAdd2->lexpon, &pxRear);
			pxAdd2 = pxAdd2->pxNext;
			continue;
		}
	}
	if (pxAdd1 == NULL)
	{
		while (pxAdd2 != NULL)
		{
			vMainAttach(pxAdd2->lcoef, pxAdd2->lexpon, &pxRear);
			pxAdd2 = pxAdd2->pxNext;
		}
	}
	else if (pxAdd2 == NULL)
	{
		while (pxAdd1 != NULL)
		{
			vMainAttach(pxAdd1->lcoef, pxAdd1->lexpon, &pxRear);
			pxAdd1 = pxAdd1->pxNext;
		}
	}
	pxRear->pxNext = NULL;
	pxTmp = pxFront;
	pxFront = pxFront->pxNext;
	free(pxTmp);
	return pxFront;
}


int lMainPolyAdd(pxmainPolyNode pxAdd1, pxmainPolyNode pxAdd2, pxmainPolyNode pxResult)
{
	int lCoefResult;
	while ((pxAdd1 != NULL) && (pxAdd2 != NULL))
	{
		if (pxAdd1->lexpon == pxAdd2->lexpon)
		{
			lCoefResult = pxAdd1->lcoef + pxAdd2->lcoef;
			if (lCoefResult != 0)
			{
				pxResult->lcoef = lCoefResult;
				pxResult->lexpon = pxAdd1->lexpon;
				pxResult = pxResult->pxNext;
			}
			pxAdd1 = pxAdd1->pxNext;
			pxAdd2 = pxAdd2->pxNext;
			continue;
		}
		else if (pxAdd1->lexpon > pxAdd2->lexpon)
		{
			pxResult->lcoef = pxAdd1->lcoef;
			pxResult->lexpon = pxAdd1->lexpon;
			pxResult = pxResult->pxNext;
			pxAdd1 = pxAdd1->pxNext;
			continue;
		}
		else if (pxAdd1->lexpon < pxAdd2->lexpon)
		{
			pxResult->lcoef = pxAdd2->lcoef;
			pxResult->lexpon = pxAdd2->lexpon;
			pxResult = pxResult->pxNext;
			pxAdd2 = pxAdd2->pxNext;
			continue;
		}
	}
	if (pxAdd1 == NULL)
	{
		while (pxAdd2 != NULL)
		{
			pxResult->lcoef = pxAdd2->lcoef;
			pxResult->lexpon = pxAdd2->lexpon;
			pxResult = pxResult->pxNext;
			pxAdd2 = pxAdd2->pxNext;
		}
		return 1;
	}
	else if (pxAdd2 == NULL)
	{
		while (pxAdd1 != NULL)
		{
			pxResult->lcoef = pxAdd1->lcoef;
			pxResult->lexpon = pxAdd1->lexpon;
			pxResult = pxResult->pxNext;
			pxAdd1 = pxAdd1->pxNext;
		}
		return 1;
	}
}