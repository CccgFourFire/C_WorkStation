#include <stdio.h>
#include<stdlib.h>
#include <time.h>


typedef struct xAvlTreeNode *pxAvlTreeNode;



typedef struct xAvlTreeNode
{
    int iData;
    pxAvlTreeNode pxLeft;
    pxAvlTreeNode pxRight;
    int iHeight;
} xAvlTreeNode;

int iMainMax ( int iA, int iB )
{
    return iA > iB ? iA : iB;
}

int iMainPostOrderGetHigh(pxAvlTreeNode pxTree)
{
    int iLeftH = 0, iRightH = 0, iMaxH = 0;
    if (pxTree)
    {
        iLeftH = iMainPostOrderGetHigh(pxTree->pxLeft);
        iRightH = iMainPostOrderGetHigh(pxTree->pxRight);
        iMaxH = (iLeftH > iRightH) ? iLeftH : iRightH;
        return (iMaxH + 1);
    }
    else
    {
        return 0;
    }
}

pxAvlTreeNode pxMainSingleLeftRotation (pxAvlTreeNode pxA)
{
    pxAvlTreeNode pxNewRoot = pxA->pxLeft;
    pxA->pxLeft = pxNewRoot->pxRight;
    pxNewRoot->pxRight = pxA;
    pxA->iHeight = iMainMax(iMainPostOrderGetHigh(pxA->pxLeft), iMainPostOrderGetHigh(pxA->pxRight)) + 1;
    pxNewRoot->iHeight = (iMainPostOrderGetHigh(pxNewRoot->pxLeft), pxA->iHeight) + 1;
    return pxNewRoot;
}

pxAvlTreeNode pxMainSingleRightRotation (pxAvlTreeNode pxA)
{
    pxAvlTreeNode pxNewRoot = pxA->pxRight;
    pxA->pxRight = pxNewRoot->pxLeft;
    pxNewRoot->pxLeft = pxA;
    pxA->iHeight = iMainMax(iMainPostOrderGetHigh(pxA->pxLeft), iMainPostOrderGetHigh(pxA->pxRight)) + 1;
    pxNewRoot->iHeight = (iMainPostOrderGetHigh(pxNewRoot->pxRight), pxA->iHeight) + 1;
    return pxNewRoot;
}

pxAvlTreeNode pxMainDoubleLeftRightRotation (pxAvlTreeNode pxA)
{
    pxA->pxLeft = pxMainSingleRightRotation(pxA->pxLeft);
    return (pxMainSingleLeftRotation(pxA));
}

pxAvlTreeNode pxMainDoubleRightLeftRotation (pxAvlTreeNode pxA)
{
    pxA->pxRight = pxMainSingleLeftRotation(pxA->pxRight);
    return (pxMainSingleRightRotation(pxA));
}

pxAvlTreeNode pxMainInsert(pxAvlTreeNode pxT, int iX)
{
    if (!pxT)
    {
        pxT =  malloc(sizeof(xAvlTreeNode));
        pxT->iData = iX;
        pxT->iHeight = 0;
        pxT->pxLeft = NULL;
        pxT->pxRight = NULL;
    }
    else if (iX < pxT->iData)
    {
        pxT->pxLeft = pxMainInsert(pxT->pxLeft, iX);
        if (iMainPostOrderGetHigh(pxT->pxLeft) - iMainPostOrderGetHigh(pxT->pxRight) == 2)
        {
            if(iX < pxT->pxLeft->iData)
            {
                pxT = pxMainSingleLeftRotation(pxT);
            }
            else
            {
                pxT = pxMainDoubleLeftRightRotation(pxT);
            }
        }

    }
    else if (iX > pxT->iData)
    {
        pxT->pxRight = pxMainInsert(pxT->pxRight, iX);
        if (iMainPostOrderGetHigh(pxT->pxRight) - iMainPostOrderGetHigh(pxT->pxLeft) == 2)
        {
            if(iX > pxT->pxRight->iData)
            {
                pxT = pxMainSingleRightRotation(pxT);
            }
            else
            {
                pxT = pxMainDoubleRightLeftRotation(pxT);
            }
        }
    }
    pxT->iHeight = iMainMax(iMainPostOrderGetHigh(pxT->pxLeft), iMainPostOrderGetHigh(pxT->pxRight)) + 1;
    return pxT;
}


int main(int argc, char* argv[])
{
	clock_t xStarttime, xStoptime;
	double dDuration;
	int iRet,iCnt;
    pxAvlTreeNode pxNodeTmp = NULL;
	xStarttime = clock();
    pxNodeTmp = pxMainInsert(pxNodeTmp, 5);
    pxNodeTmp = pxMainInsert(pxNodeTmp, 4);
    pxNodeTmp = pxMainInsert(pxNodeTmp, 10);
    pxNodeTmp = pxMainInsert(pxNodeTmp, 8);
    pxNodeTmp = pxMainInsert(pxNodeTmp, 14);
    pxNodeTmp = pxMainInsert(pxNodeTmp, 15);
	xStoptime = clock();
	dDuration = (double)(xStoptime - xStarttime) / CLK_TCK;
	printf("Ticks count is %lf\n", (double)(xStoptime - xStarttime));
	printf("Opertaion Time is %6.2e\n", dDuration);
 	printf("Result is %d\n", iRet);
    printf("Pointer is %x", pxNodeTmp);
	return 0;
}

