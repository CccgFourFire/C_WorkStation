#include <stdio.h>
#include<stdlib.h>
#include <time.h>

#define mainBUFMAXZISE 10

typedef struct xLNode
{
    int iElement[mainBUFMAXZISE];
    int iLen;
} xLNode, *pxLNode;

int iMainSequentialSerch(pxLNode pxList, int iData)
{
    int iCnt;
    pxList->iElement[0] = iData;
    for (iCnt = (pxList->iLen - 1); pxList->iElement[iCnt] != iData; iCnt--)
    {
        ;
    }
    return iCnt;
}

int iMainBinarySerch(pxLNode pxList, int iData)
{
    int iLeft, iRight, iMid;
    iLeft = 0;
    iRight = pxList->iLen - 1;
    while (iLeft <= iRight)
    {
        iMid = (iLeft + iRight) / 2;
        if (pxList->iElement[iMid] == iData)
        {
            return iMid;
        }
        else if (pxList->iElement[iMid] > iData)
        {
            iRight = iMid - 1;
        }
        else
        {
            iLeft = iMid + 1;
        }
    }
    return -1;
}

int main(int argc, char* argv[])
{
	clock_t xStarttime, xStoptime;
	double dDuration;
	int iRet,iCnt;
    xLNode xList;
    for (iCnt = 0; iCnt < 10; iCnt++)
    {
        xList.iElement[iCnt] = iCnt * 2;
    }
    xList.iLen = 10;
	xStarttime = clock();
    iRet = iMainBinarySerch(&xList, 14);
	xStoptime = clock();
	dDuration = (double)(xStoptime - xStarttime) / CLK_TCK;
	printf("Ticks count is %lf\n", (double)(xStoptime - xStarttime));
	printf("Opertaion Time is %6.2e\n", dDuration);
	printf("Result is %d\n", iRet);
	return 0;
}

