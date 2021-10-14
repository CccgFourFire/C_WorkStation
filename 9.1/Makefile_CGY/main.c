#include <stdio.h>
#include<stdlib.h>
#include <time.h>

#define mainMAXDIGIT 3
#define mainRADIX 10

typedef struct xNode *pxNode;
struct xNode
{
    int iKey;
    pxNode pxNext;
};

struct xHeadNode
{
    pxNode pxHead;
    pxNode pxTail;
};
typedef struct xHeadNode pxBucket[mainRADIX];

int iMainGetDigit(int iX, int iD)
{
    int iY, iI;
    for (iI = 1; iI <= iD; iI++)
    {
        iY = iX % mainRADIX;
        iX /= mainRADIX;
    }
    return iY;
}

void vMainLSDRadixSort(int piA[], int iN)
{
    int iD, iDi, iI;
    pxBucket pxB;
    pxNode pxTmp, pxP, pxList;
    for (iI = 0; iI < mainRADIX; iI++)
    {
        pxB[iI].pxHead = pxB[iI].pxTail = NULL;
    }
    for (iI = 0; iI < iN; iI++)
    {
        pxTmp = (pxNode)malloc(sizeof(struct xNode));
        pxTmp->iKey = piA[iI];
        pxTmp->pxNext = pxList;
        pxList = pxTmp;
    }
    for (iD = 1; iD <= mainMAXDIGIT; iD++)
    {
        pxP = pxList;
        while (pxP)
        {
            iDi = iMainGetDigit(pxP->iKey, iD);
            pxTmp = pxP;
            pxP = pxP->pxNext;
            pxTmp->pxNext = NULL;
            if (pxB[iDi].pxHead == NULL)
            {
                pxB[iDi].pxHead = pxB[iDi].pxTail = pxTmp;
            }
            else
            {
                pxB[iDi].pxTail->pxNext = pxTmp;
                pxB[iDi].pxTail = pxTmp;
            }
        }
        pxList = NULL;
        for (iDi = mainRADIX - 1; iDi>=0; iDi--)
        {
            if (pxB[iDi].pxHead)
            {
                pxB[iDi].pxTail->pxNext = pxList;
                pxList = pxB[iDi].pxHead;
                pxB[iDi].pxHead = pxB[iDi].pxTail = NULL;
            }
        }
    }
    for (iI = 0; iI < iN; iI++)
    {
        pxTmp = pxList;
        pxList = pxList->pxNext;
        piA[iI] = pxTmp->iKey;
        free(pxTmp);
    }
}

void vMainSwap(int *piNum1, int *piNum2)
{
    int iTmp;
    iTmp = *piNum1;
    *piNum1 = *piNum2;
    *piNum2= iTmp;
}

void vMainPercDown(int piA[], int iP, int iN)
{
    int iParent, iChild;
    int iX;
    iX = piA[iP];
    for (iParent = iP; (iParent * 2 + 1) < iN; iParent = iChild)
    {
        iChild = iParent * 2 + 1;
        if ((iChild != iN - 1) && (piA[iChild + 1] > piA[iChild]))
        {
            iChild++;
        }
        if (iX >= piA[iChild])
        {
            break;
        }
        else
        {
            piA[iParent] = piA[iChild];
        }
    }
    piA[iParent] = iX;
}

void vMainHeapSort(int piA[], int iN)
{
    int iI;
    for (iI = iN / 2 - 1; iI>=0; iI--)
    {
        vMainPercDown(piA, iI, iN);
    }
    for (iI = iN - 1; iI > 0; iI--)
    {
        vMainSwap(&piA[0], &piA[iI]);
        vMainPercDown(piA, 0, iI);
    }
}


void vMainBubbleSort(int *piData, int iN)
{
    int iTotal, iFlag, iCnt;
    for (iTotal = iN - 1; iTotal > 0; iTotal--)
    {
        iFlag = 0;
        for (iCnt = 0; iCnt < iTotal; iCnt++)
        {
            if (piData[iCnt] > piData[iCnt + 1])
            {
                vMainSwap(&piData[iCnt], &piData[iCnt + 1]);
                iFlag = 1;
            }
        }
        if (iFlag == 0)
        {
            break;
        }
    }
}

void vMainInsertSort(int *piData, int iN)
{
    int iTurn, iCnt, iTmp;
    for (iTurn = 0; iTurn < iN; iTurn++)
    {
        iTmp = piData[iTurn];
        for (iCnt = iTurn; (iCnt > 0) && (piData[iCnt - 1] > iTmp); iCnt--)
        {
            piData[iCnt] = piData[iCnt - 1];
        }
        piData[iCnt] = iTmp;
    }
}

void vMainShellSort(int *piData, int iN)
{
    int iTurn, iCnt, iTmp, iInterval;
    for (iInterval = iN / 2; iInterval > 0; iInterval /= 2)
    {
        for (iTurn = 0; iTurn < iN; iTurn++)
        {
            iTmp = piData[iTurn];
            for (iCnt = iTurn; (iCnt >= iInterval) && (piData[iCnt - iInterval] > iTmp); iCnt -= iInterval)
            {
                piData[iCnt] = piData[iCnt - iInterval];
            }
            piData[iCnt] = iTmp;
        }
    }
}

void vMainMerge(int piA[], int piTmpA[], int iL, int iR, int iRightEnd)
{
    int iLeftEnd, iNumElements, iTmp;
    int iI;
    iLeftEnd = iR - 1;
    iTmp = iL;
    iNumElements = iRightEnd - iL + 1;
    while (iL <= iLeftEnd && iR <= iRightEnd)
    {
        if (piA[iL] <= piA[iR])
        {
            piTmpA[iTmp++] = piA[iL++];
        }
        else
        {
            piTmpA[iTmp++] = piA[iR++];
        }
    }
    while (iL <= iLeftEnd)
    {
        piTmpA[iTmp++] = piA[iL++];
    }
    while (iR <= iRightEnd)
    {
        piTmpA[iTmp++] = piA[iR++];
    }
    // for (iI = 0; iI < iNumElements; iI++, iRightEnd--)
    // {
    //     piA[iRightEnd] = piTmpA[iRightEnd];
    // }
}

void vMainMsort(int piA[], int piTmpA[], int iL, int iRightEnd)
{
    int iCenter;
    if (iL < iRightEnd)
    {
        iCenter = (iL + iRightEnd) / 2;
        vMainMsort(piA, piTmpA, iL, iCenter);
        vMainMsort(piA, piTmpA, iCenter + 1, iRightEnd);
        vMainMerge(piA, piTmpA, iL, iCenter + 1, iRightEnd);
    }
}

void vMainMerge_pass(int piA[], int piTmpA[], int iN, int iLength)
{
    int iI, iJ;
    for (iI = 0; iI <= iN - 2 * iLength; iI += 2 * iLength)
    {
        vMainMerge(piA, piTmpA, iI, iI + iLength, iI + 2 *iLength - 1);
    }
    if (iI + iLength < iN)
    {
        vMainMerge(piA, piTmpA, iI, iI + iLength, iN - 1);
    }
    else
    {
        for (iJ = iI; iJ < iN; iJ++)
        {
            piTmpA[iJ] = piA[iJ];
        }
    }
}

void vMainMerge_Sort(int piA[], int iN)
{
    int iLength;
    int *piTmpA;
    iLength = 1;
    piTmpA = (int *)malloc(iN * sizeof(int));
    if (piTmpA != NULL)
    {
        while (iLength < iN)
        {
            vMainMerge_pass(piA, piTmpA, iN, iLength);
            iLength *= 2;
            vMainMerge_pass(piTmpA, piA, iN, iLength);
            iLength *= 2;
        }
    }
    free(piTmpA);
}


void vMainMergeSort(int piA[], int iN)
{
    int *piTmpA;
    piTmpA = (int *)malloc(iN * sizeof(int));
    if (piTmpA != NULL)
    {
        vMainMsort(piA, piTmpA, 0, iN - 1);
        free(piTmpA);
    }
}

int iMainMedian3(int piA[], int iLeft, int iRight)
{
    if (iRight > iLeft)
    {
        int iCenter = (iLeft + iRight) / 2;
        if (piA[iLeft] > piA[iCenter])
        {
            vMainSwap(&piA[iLeft], &piA[iCenter]);
        }
        if (piA[iLeft] > piA[iRight])
        {
            vMainSwap(&piA[iLeft], &piA[iRight]);
        }
        if (piA[iCenter] > piA[iRight])
        {
            vMainSwap(&piA[iCenter], &piA[iRight]);
        }
        vMainSwap(&piA[iCenter], &piA[iRight - 1]);
        return piA[iRight - 1];
    }
    return piA[iRight];
}

void vMainQsort(int piA[], int iLeft, int iRight)
{
    int iPivot, iLow, iHigh, iTmp;
    iPivot = iMainMedian3(piA, iLeft, iRight);
    iLow = iLeft; iHigh = iRight - 1;
    if (iHigh > iLow)
    {
        while (1)
        {
            while (piA[++iLow] < iPivot)
            {
                iTmp = 1;
            }
            while (piA[--iHigh] > iPivot)
            {
                iTmp = 1;
            }
            if (iLow < iHigh)
            {
                vMainSwap(&piA[iLow], &piA[iHigh]);
            }
            else
            {
                break;
            }
        }
        vMainSwap(&piA[iLow], &piA[iRight - 1]);
        vMainQsort(piA, iLeft, iLow - 1);
        vMainQsort(piA, iLow + 1, iRight);
    }
}

void vMainMSD(int piA[], int iL, int iR, int iD)
{
    int iDi, iJ, iI;
    pxBucket pxB;
    pxNode pxTmp, pxP, pxList = NULL;
    if (iD == 0)
    {
        return;
    }
    for (iI = 0; iI < mainRADIX; iI++)
    {
        pxB[iI].pxHead = pxB[iI].pxTail = NULL;
    }
    for (iI = iL; iI <= iR; iI++)
    {
        pxTmp = (pxNode)malloc(sizeof(struct xNode));
        pxTmp->iKey = piA[iI];
        pxTmp->pxNext = pxList;
        pxList = pxTmp;
    }
    pxP = pxList;
    while (pxP)
    {
        iDi = iMainGetDigit(pxP->iKey, iD);
        pxTmp = pxP;
        pxP = pxP->pxNext;
        if (pxB[iDi].pxHead == NULL)
        {
            pxB[iDi].pxTail = pxTmp;
        }
        pxTmp->pxNext = pxB[iDi].pxHead;
        pxB[iDi].pxHead = pxTmp;
    }
    iI = iJ = iL;
    for (iDi = 0; iDi < mainRADIX; iDi++)
    {
        if (pxB[iDi].pxHead)
        {
            pxP = pxB[iDi].pxHead;
            while (pxP)
            {
                pxTmp = pxP;
                pxP = pxP->pxNext;
                piA[iJ++] = pxTmp->iKey;
                free(pxTmp);
            }
            vMainMSD(piA, iI, iJ - 1, iD - 1);
            iI = iJ;
        }
    }
}

void vMainMSDRadixSort(int piA[], int iN)
{
    vMainMSD(piA, 0, iN - 1, mainMAXDIGIT);
}


void vMainQuickSort(int piA[], int iN)
{
    vMainQsort(piA, 0, iN - 1);
}

int main(int argc, char* argv[])
{
    int piSortSequence[] = {64, 8, 216, 512, 27, 729, 0, 1, 343, 125};
    vMainMSDRadixSort(piSortSequence, 10);
    return 0;
}

