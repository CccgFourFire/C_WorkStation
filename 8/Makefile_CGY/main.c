#include <stdio.h>
#include<stdlib.h>
#include <time.h>

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

int main(int argc, char* argv[])
{
    int piSortSequence[] = {20, 54, 99, 14, 52, 11, 65};
    vMainMerge_Sort(piSortSequence, 7);
    return 0;
}

