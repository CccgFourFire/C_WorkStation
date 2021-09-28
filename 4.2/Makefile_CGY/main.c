#include <stdio.h>
#include<stdlib.h>
#include <time.h>

typedef struct xTreeNode *pxTree;

pxTree pxMainNewNode(int iV);
pxTree pxMainMakeTree(int iN);
pxTree pxMainInsert(pxTree pxT, int iV);
int iMainCheck(pxTree pxT, int iTmp);
int iMainJudge(pxTree pxT, int iN);
void vMainResetT(pxTree pxT);
void vMainFreeTree(pxTree pxT);

typedef struct xTreeNode
{
    int iV;
    pxTree pxLeft;
    pxTree pxRight;
    int iFlag;
} xTreeNode;

pxTree pxMainNewNode(int iV)
{
    pxTree pxT = malloc(sizeof(xTreeNode));
    pxT->iFlag = 0;
    pxT->iV = iV;
    pxT->pxLeft = pxT->pxRight = NULL;
    return pxT;
}

pxTree pxMainMakeTree(int iN)
{
    pxTree pxT;
    int iI, iV;
    scanf("%d", &iV);
    pxT = pxMainNewNode(iV);
    for (iI = 1; iI < iN; iI++)
    {
        scanf("%d", &iV);
        pxT = pxMainInsert(pxT, iV);
    }
    return pxT;
}

pxTree pxMainInsert(pxTree pxT, int iV)
{
    if (pxT == NULL)
    {
        pxT = pxMainNewNode(iV);
    }
    else if (iV > pxT->iV)
    {
        pxT->pxRight = pxMainInsert(pxT->pxRight, iV);
    }
    else if (iV < pxT->iV)
    {
        pxT->pxLeft = pxMainInsert(pxT->pxLeft, iV);
    }
    return pxT;
}

int iMainCheck(pxTree pxT, int iTmp)
{
    if (pxT->iFlag)
    {
        if (iTmp < pxT->iV)
        {
            return iMainCheck(pxT->pxLeft, iTmp);
        }
        else if (iTmp > pxT->iV)
        {
            return iMainCheck(pxT->pxRight, iTmp);
        }
        else
        {
            return 0;
        }
    }
    else
    {
        if (iTmp == pxT->iV)
        {
            pxT->iFlag = 1;
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

int iMainJudge(pxTree pxT, int iN)
{
    int iI, iTmp, iFlag = 0;
    scanf("%d", &iTmp);
    if (pxT->iV != iTmp)
    {
        iFlag = 1;
    }
    else
    {
        pxT->iFlag = 1;
    }
    for (iI = 1; iI < iN; iI++)
    {
        scanf("%d", &iTmp);
        if ((!iFlag) && (iMainCheck(pxT, iTmp) == 0))
        {
            iFlag = 1;
        }
    }
    if (iFlag == 1)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void vMainResetT(pxTree pxT)
{
    if (pxT->pxLeft)
    {
        vMainResetT(pxT->pxLeft);
    }
    if (pxT->pxRight)
    {
        vMainResetT(pxT->pxRight);
    }
    pxT->iFlag = 0;
}

void vMainFreeTree(pxTree pxT)
{
    if (pxT->pxLeft)
    {
        vMainFreeTree(pxT->pxLeft);
    }
    if (pxT->pxRight)
    {
        vMainFreeTree(pxT->pxRight);
    }
    free(pxT);
}

int main(int argc, char* argv[])
{
    int iN, iL, iI;
    pxTree pxT;
    scanf("%d", &iN);
    while (iN)
    {
        scanf("%d", &iL);
        pxT = pxMainMakeTree(iN);
        for (iI = 0; iI < iL; iI++)
        {
            if (iMainJudge(pxT, iN))
            {
                printf("Yes\n\r");
            }
            else
            {
                printf("No\n\r");
            }
            vMainResetT(pxT);
        }
        vMainFreeTree(pxT);
        scanf("%d", &iN);
    }
    return 0;
}

