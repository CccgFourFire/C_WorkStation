#include <stdio.h>
#include<stdlib.h>
#include <time.h>


typedef struct xTreeNode *pxTreeNode;



typedef struct xTreeNode
{
    int iData;
    pxTreeNode pxLeft;
    pxTreeNode pxRight;
} xTreeNode;

void vMainPreOrderTraversal(pxTreeNode pxTree)
{
    if (pxTree)
    {
        printf("Data is %d\n\r", pxTree->iData);
        vMainPreOrderTraversal(pxTree->pxLeft);
        vMainPreOrderTraversal(pxTree->pxRight);
    }
}

void vMainInOrderTraversal(pxTreeNode pxTree)
{
    if (pxTree)
    {
        vMainPreOrderTraversal(pxTree->pxLeft);
        printf("Data is %d\n\r", pxTree->iData);
        vMainPreOrderTraversal(pxTree->pxRight);
    }
}

unsigned int uiMainPostOrderGetHigh(pxTreeNode pxTree)
{
    unsigned int uiLeftH = 0, uiRightH = 0, uiMaxH = 0;
    if (pxTree)
    {
        uiLeftH = uiMainPostOrderGetHigh(pxTree->pxLeft);
        uiRightH = uiMainPostOrderGetHigh(pxTree->pxRight);
        uiMaxH = (uiLeftH > uiRightH) ? uiLeftH : uiRightH;
        return (uiMaxH + 1);
    }
    else
    {
        return 0;
    }
}


void vMainPostOrderTraversal(pxTreeNode pxTree)
{
    if (pxTree)
    {
        vMainPreOrderTraversal(pxTree->pxLeft);
        vMainPreOrderTraversal(pxTree->pxRight);
        printf("Data is %d\n\r", pxTree->iData);
    }
}

pxTreeNode pxMainNodeInsert(pxTreeNode pxParent, int iVal)
{
    pxTreeNode pxNewNode;
    pxNewNode = (pxTreeNode)malloc(sizeof(xTreeNode));
    pxNewNode->iData = iVal;
    pxNewNode->pxLeft = NULL;
    pxNewNode->pxRight = NULL;
    if (iVal > pxParent->iData)
    {
        pxParent->pxRight = pxNewNode;
        return pxNewNode;
    }
    else if (iVal < pxParent->iData)
    {
        pxParent->pxLeft = pxNewNode;
        return pxNewNode;
    }
    else
    {
        return NULL;
    }
}


int main(int argc, char* argv[])
{
	clock_t xStarttime, xStoptime;
	double dDuration;
	int iRet,iCnt;
    xTreeNode xRoot;
    pxTreeNode pxNodeTmp;
    xRoot.iData = 10;
    xRoot.pxLeft = NULL;
    xRoot.pxRight = NULL;
	xStarttime = clock();
    pxNodeTmp = pxMainNodeInsert(&xRoot, 9);
    pxMainNodeInsert(pxNodeTmp, 8);
    pxMainNodeInsert(pxNodeTmp, 24);
    pxNodeTmp = pxMainNodeInsert(&xRoot, 11);
    pxMainNodeInsert(pxNodeTmp, 7);
    vMainPreOrderTraversal(&xRoot);
    iRet = uiMainPostOrderGetHigh(&xRoot);
	xStoptime = clock();
	dDuration = (double)(xStoptime - xStarttime) / CLK_TCK;
	printf("Ticks count is %lf\n", (double)(xStoptime - xStarttime));
	printf("Opertaion Time is %6.2e\n", dDuration);
	printf("Result is %d\n", iRet);
	return 0;
}

