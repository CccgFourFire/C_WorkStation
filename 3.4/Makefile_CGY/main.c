#include <stdio.h>
#include<stdlib.h>
#include <time.h>

#define main_MAXTREE 10
#define main_NULL -1

struct xTreeNode
{
    char cElement;
    int iLeft;
    int iRight;
} pxT1[main_MAXTREE], pxT2[main_MAXTREE];

int iMainBuildTree(struct xTreeNode *pxT)
{
    int iN = 0, iCnt = 0, iRoot = 0;
    char cL = 0, cR = 0;
    char pcCheck[main_MAXTREE];
    scanf("%d\n", &iN);
    if (iN)
    {
        for (iCnt = 0; iCnt < iN; iCnt++)
        {
            pcCheck[iCnt] = 0;
        }
        for (iCnt = 0; iCnt < iN; iCnt++)
        {
            scanf("%c %c %c\n", &pxT[iCnt].cElement, &cL, &cR);
            if (cL != '-')
            {
                pxT[iCnt].iLeft = cL - '0';
                pcCheck[pxT[iCnt].iLeft] = 1;
            }
            else
            {
                pxT[iCnt].iLeft = main_NULL;
            }
            if (cR != '-')
            {
                pxT[iCnt].iRight = cR - '0';
                pcCheck[pxT[iCnt].iRight] = 1;
            }
            else
            {
                pxT[iCnt].iRight = main_NULL;
            }
        }
        for (iCnt = 0; iCnt < iN; iCnt++)
        {
            if (!pcCheck[iCnt])
            {
                break;
            }
        }
        iRoot = iCnt;
    }
    return iRoot;
}

int iMainIsomorphic(int iR1, int iR2)
{
    if ((iR1 == main_NULL) && (iR2 == main_NULL))
    {
        return 1;
    }
    if (((iR1 == main_NULL) && (iR2 != main_NULL)) || ((iR1 != main_NULL) && (iR2 == main_NULL)))
    {
        return 0;
    }
    if (pxT1[iR1].cElement != pxT2[iR2].cElement)
    {
        return 0;
    }
    if ((pxT1[iR1].iLeft == main_NULL) && (pxT2[iR2].iLeft == main_NULL))
    {
        return iMainIsomorphic(pxT1[iR1].iRight, pxT2[iR2].iRight);
    }
    if (((pxT1[iR1].iLeft != main_NULL) && (pxT2[iR2].iLeft != main_NULL)) && \
    ((pxT1[pxT1[iR1].iLeft].cElement) == (pxT2[pxT2[iR2].iLeft].cElement)))
    {
        return (iMainIsomorphic(pxT1[iR1].iLeft, pxT2[iR2].iLeft) && iMainIsomorphic(pxT1[iR1].iRight, pxT2[iR2].iRight));
    }
    else
    {
        return (iMainIsomorphic(pxT1[iR1].iLeft, pxT2[iR2].iRight) && iMainIsomorphic(pxT1[iR1].iRight, pxT2[iR2].iLeft));
    }
}


int main(int argc, char* argv[])
{
    int iR1 = 0, iR2 = 0;
    iR1 = iMainBuildTree(pxT1);
    iR2 = iMainBuildTree(pxT2);
    if (iMainIsomorphic(iR1, iR2))
    {
        printf("Yes");
    }
    else
    {
        printf("No");
    }
}

