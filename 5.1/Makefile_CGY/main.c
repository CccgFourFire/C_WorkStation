#include <stdio.h>
#include<stdlib.h>
#include <time.h>

typedef struct xHeapStruct *pxMaxHeap;

typedef struct xHeapStruct
{
    int *piElement;
    int iSize;
    int iCapacity;
} xMaxHeap;

pxMaxHeap pxMainMaxHeapCreat(int iMaxSize)
{
    pxMaxHeap pxNewHeap = malloc(sizeof(xMaxHeap));
    pxNewHeap->iSize = 0;
    pxNewHeap->piElement = malloc(sizeof(int) * (iMaxSize + 1));
    pxNewHeap->iCapacity = iMaxSize;
    pxNewHeap->piElement[0] = 0x7fffffff;
    return pxNewHeap;
}

void vMainMaxHeapInsert(pxMaxHeap pxHeap, int iData)
{
    int iCurPos = ++pxHeap->iSize;
    // if (iMainIsFull(pxHeap))
    // {
    //     printf("Full!!\n\r");
    // }
    for ( ; pxHeap->piElement[iCurPos / 2] < iData; iCurPos = iCurPos / 2)
    {
        pxHeap->piElement[iCurPos] = pxHeap->piElement[iCurPos / 2];
    }
    pxHeap->piElement[iCurPos] = iData;
}

void vMainPercDown(pxMaxHeap pxH, int iP)
{
    int iParent, iChild, iX;
    iX = pxH->piElement[iP];
    for (iParent = iP; iParent * 2 <= pxH->iSize; iParent = iChild)
    {
        iChild = iParent * 2;
        if ((iChild != pxH->iSize) && (pxH->piElement[iChild] < pxH->piElement[iChild + 1]))
        {
            iChild++;
        }
        if (iX > pxH->piElement[iChild])
        {
            break;
        }
        else
        {
            pxH->piElement[iParent] = pxH->piElement[iChild];
        }
    }
    pxH->piElement[iParent] = iX;
}

void vMainBuildHeap(pxMaxHeap pxH)
{
    int iI;
    for (iI = pxH->iSize / 2; iI > 0; iI--)
    {
        vMainPercDown(pxH, iI);
    }
}

int iMainMaxHeapDelete(pxMaxHeap pxHeap)
{
    int iMaxData, iParent, iChild, iTmp;
    iMaxData = pxHeap->piElement[1];
    iTmp = pxHeap->piElement[pxHeap->iSize--];
    // if (iMainIsEmpty(pxHeap))
    // {
    //     printf("Empty!!\n\r");
    // }
    for (iParent = 1; iParent * 2 <= pxHeap->iSize; iParent = iChild)
    {
        iChild = iParent * 2;
        if ((iChild != pxHeap->iSize))
        {
            if (pxHeap->piElement[iChild + 1] > pxHeap->piElement[iChild])
            {
                iChild++;
            }
        }
        if (iTmp > pxHeap->piElement[iChild])
        {
            break;
        }
        pxHeap->piElement[iParent] = pxHeap->piElement[iChild];
    }
    pxHeap->piElement[iParent] = iTmp;
    return iMaxData;
}

int main(int argc, char* argv[])
{
    pxMaxHeap pxHeap;
    pxHeap = pxMainMaxHeapCreat(10);
    vMainMaxHeapInsert(pxHeap, 44);
    vMainMaxHeapInsert(pxHeap, 25);
    vMainMaxHeapInsert(pxHeap, 31);
    vMainMaxHeapInsert(pxHeap, 18);
    vMainMaxHeapInsert(pxHeap, 10);
    vMainMaxHeapInsert(pxHeap, 58);
    iMainMaxHeapDelete(pxHeap);
    return 0;
}

