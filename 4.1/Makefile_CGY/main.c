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

pxTreeNode pxMainPositionfind(int iData, pxTreeNode pxTree)
{
    pxTreeNode pxLeft, pxRight;
    if (pxTree != NULL)
    {
        if (pxTree->iData == iData)
        {
            return pxTree;
        }
        pxLeft = pxMainPositionfind(iData, pxTree->pxLeft);
        pxRight = pxMainPositionfind(iData, pxTree->pxRight);
        if (pxLeft != NULL)
        {
            return pxLeft;
        }
        if (pxRight != NULL)
        {
            return pxRight;
        }
    }
    return NULL;
}

pxTreeNode pxMainPositionfind1(int iData, pxTreeNode pxTree)
{
    if (pxTree == NULL)
    {
        return NULL;
    }
    if (iData > pxTree->iData)
    {
        pxMainPositionfind1(iData, pxTree->pxRight);
    }
    else if (iData < pxTree->iData)
    {
        pxMainPositionfind1(iData, pxTree->pxLeft);
    }
    else
    {
        return pxTree;
    }
}

pxTreeNode pxMainPositionfindMin(pxTreeNode pxTree)
{
    if (pxTree != NULL)
    {
        if (pxTree->pxLeft != NULL)
        {
            return pxMainPositionfindMin(pxTree->pxLeft);
        }
        return pxTree;
    }
    return NULL;
}

pxTreeNode pxMainPositionfindMax(pxTreeNode pxTree)
{
    if (pxTree != NULL)
    {
        while (pxTree->pxRight)
        {
            pxTree = pxTree->pxRight;
        }
        return pxTree;
    }
    return NULL;
}

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

pxTreeNode pxMainNodeInsert1(int iVal, pxTreeNode pxTree)
{
    if (pxTree == NULL)
    {
        pxTree = malloc(sizeof(xTreeNode));
        pxTree->iData = iVal;
        pxTree->pxLeft = NULL;
        pxTree->pxRight = NULL;
    }
    else
    {
        if (iVal > pxTree->iData)
        {
            pxTree->pxRight = pxMainNodeInsert1(iVal, pxTree->pxRight);
        }
        else if (iVal < pxTree->iData)
        {
            pxTree->pxLeft = pxMainNodeInsert1(iVal, pxTree->pxLeft);
        }
    }
    return pxTree;
}

pxTreeNode pxMainNodeDelete(int iVal, pxTreeNode pxTree)
{
    pxTreeNode pxTmp = NULL, pxTmpMin = NULL;
    if (pxTree == NULL)
    {
        return NULL;
    }
    else
    {
        if (iVal > pxTree->iData)
        {
            pxTmp = pxMainNodeDelete(iVal, pxTree->pxRight);
            if (pxTmp != NULL)
            {
                if ((pxTmp->pxLeft == NULL) && (pxTmp->pxRight == NULL))
                {
                    pxTree->pxRight = NULL;
                    free(pxTmp);
                    return NULL;
                }
                else if (pxTmp->pxLeft == NULL)
                {
                    pxTree->pxRight = pxTmp->pxRight;
                    free(pxTmp);
                    return NULL;
                }
                else if (pxTmp->pxRight == NULL)
                {
                    pxTree->pxRight = pxTmp->pxLeft;
                    free(pxTmp);
                    return NULL;
                }
                else
                {
                    pxTmpMin = pxTmp->pxRight;
                    while (pxTmpMin->pxLeft)
                    {
                        pxTmpMin = pxTmpMin->pxLeft;
                    }
                    pxTree->pxRight = pxTmpMin;
                    pxTmpMin->pxLeft = pxTmp->pxLeft;
                    free(pxTmp);
                    return NULL;
                }
            }
        }
        else if (iVal < pxTree->iData)
        {
            pxTmp = pxMainNodeDelete(iVal, pxTree->pxLeft);
            if (pxTmp != NULL)
            {
                if ((pxTmp->pxLeft == NULL) && (pxTmp->pxRight == NULL))
                {
                    pxTree->pxLeft = NULL;
                    free(pxTmp);
                    return NULL;
                }
                else if (pxTmp->pxLeft == NULL)
                {
                    pxTree->pxLeft = pxTmp->pxRight;
                    free(pxTmp);
                    return NULL;
                }
                else if (pxTmp->pxRight == NULL)
                {
                    pxTree->pxLeft = pxTmp->pxLeft;
                    free(pxTmp);
                    return NULL;
                }
                else
                {
                    pxTmpMin = pxTmp->pxRight;
                    while (pxTmpMin->pxLeft)
                    {
                        pxTmpMin = pxTmpMin->pxLeft;
                    }
                    pxTree->pxLeft = pxTmpMin;
                    pxTmpMin->pxLeft = pxTmp->pxLeft;
                    free(pxTmp);
                    return NULL;
                }
            }
        }
        else
        {
            return pxTree;
        }
    }
    return NULL;
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
    pxNodeTmp = pxMainNodeInsert(&xRoot, 7);
    pxMainNodeInsert(pxNodeTmp, 6);
    pxMainNodeInsert(pxNodeTmp, 8);
    pxNodeTmp = pxMainNodeInsert(&xRoot, 14);
    pxMainNodeInsert(pxNodeTmp, 11);
    pxNodeTmp = pxMainNodeInsert1(9, &xRoot);
    pxNodeTmp = pxMainNodeInsert1(24, &xRoot);
    pxNodeTmp = pxMainNodeDelete(14, &xRoot);
	xStoptime = clock();
	dDuration = (double)(xStoptime - xStarttime) / CLK_TCK;
	printf("Ticks count is %lf\n", (double)(xStoptime - xStarttime));
	printf("Opertaion Time is %6.2e\n", dDuration);
 	printf("Result is %d\n", iRet);
    printf("Pointer is %x", pxNodeTmp);
	return 0;
}

