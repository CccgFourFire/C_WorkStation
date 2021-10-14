#include <stdio.h>
#include<stdlib.h>
#include <time.h>
#include <math.h>

#define mainMAXTABLESIZE 10
typedef int iElementType;
typedef int iIndex;
typedef iIndex iPosition;

typedef enum
{
    LEGITIMATE,
    EMPTY,
    DELETED
} eEntryType;

typedef struct xHashEntry
{
    iElementType iData;
    eEntryType eInfo;
} xCell, *pxCell;

typedef struct xTblNode
{
    int iTableSize;
    pxCell pxCells;
} xHashTable, *pxHashTable;

int iMainNextPrime(int iN)
{
    int iI, iP = (iN % 2) ? (iN + 2) : (iN + 1);
    while (iP <= mainMAXTABLESIZE)
    {
        for(iI = (int)sqrt(iP); iI > 2; iI--)
        {
            if (!(iP % iI))
            {
                break;
            }
        }
        if (iI == 2)
        {
            break;
        }
        else
        {
            iP += 2;
        }
    }
    return iP;
}

pxHashTable pxMainCreatTable(int iTableSize)
{
    pxHashTable pxH;
    int iI;
    pxH = (pxHashTable)malloc(sizeof(xHashTable));
    pxH->iTableSize = iMainNextPrime(iTableSize);
    pxH->pxCells = (pxCell)malloc(pxH->iTableSize * sizeof(xCell));
    for (iI = 0; iI < pxH->iTableSize; iI++)
    {
        pxH->pxCells[iI].eInfo = EMPTY;
    }
    return pxH;
}

iPosition iMainFind(pxHashTable pxH, iElementType iKey)
{
    iPosition iCurrentPos, iNewPos;
    int CNum = 0;
    iNewPos = iCurrentPos = iKey % (pxH->iTableSize);
    while ((pxH->pxCells[iNewPos].eInfo != EMPTY) && (pxH->pxCells[iNewPos].iData != iKey))
    {
        if (++CNum % 2)
        {
           iNewPos = iCurrentPos + (CNum + 1) * (CNum + 1) / 4;
           if (iNewPos >= pxH->iTableSize)
           {
               iNewPos = iNewPos % pxH->iTableSize;
           }
        }
        else
        {
            iNewPos = iCurrentPos - CNum * CNum / 4;
            while (iNewPos < 0)
            {   
                iNewPos += pxH->iTableSize;
            }
            
        }
    }
    return iNewPos;
}

char cMainInsert(pxHashTable pxH, iElementType iKey)
{
    iPosition iPos = iMainFind(pxH, iKey);
    if (pxH->pxCells[iPos].eInfo != LEGITIMATE)
    {
        pxH->pxCells[iPos].eInfo = LEGITIMATE;
        pxH->pxCells[iPos].iData = iKey;
        return 0;
    }
    else
    {
        return -1;
    }
}


int main(int argc, char* argv[])
{
    pxCell pxC;
    pxHashTable pxH;
    iPosition iRet = 0;
    pxH = pxMainCreatTable(10);
    pxC = pxH->pxCells;
    cMainInsert(pxH, 47);
    cMainInsert(pxH, 7);
    cMainInsert(pxH, 29);
    cMainInsert(pxH, 11);
    cMainInsert(pxH, 9);
    cMainInsert(pxH, 84);
    cMainInsert(pxH, 54);
    cMainInsert(pxH, 20);
    cMainInsert(pxH, 30);
    iRet = iMainFind(pxH, 1);
    return 0;
}

