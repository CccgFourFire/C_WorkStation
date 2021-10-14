#include <stdio.h>
#include<stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#define mainNUM_LEN 11
#define mainMAX_TABLE_SIZE 10000
#define mainMAX_D 5

typedef char ptrElementType_t[mainNUM_LEN + 1];
typedef int Index_t;

typedef struct tagLNode_T *ptrLNode_T;
typedef struct tagLNode_T
{
    ptrElementType_t pcData;
    int iCount;
    ptrLNode_T ptNext;
} LNode_T;
typedef ptrLNode_T ptrPosition_T;
typedef ptrLNode_T ptrList_T;


typedef struct tagHashTable_T *ptrHashTable_T;
typedef struct tagHashTable_T
{
    int iTableSize;
    ptrList_T ptHeads;
} HashTable_T;

int iMainHash(int iKey, int iP);
ptrHashTable_T ptMainCreatTable(int iTableSize);

int iMainNextPrime(int iN)
{
    int iI, iP = (iN % 2) ? (iN + 2) : (iN + 1);
    while (iP <= mainMAX_TABLE_SIZE)
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

ptrPosition_T ptMainFind(ptrHashTable_T ptH, ptrElementType_t pcKey)
{
    ptrPosition_T ptP;
    Index_t iPos;
    iPos = iMainHash(atoi(pcKey + mainNUM_LEN - mainMAX_D), ptH->iTableSize);
    ptP = ptH->ptHeads[iPos].ptNext;
    while (ptP && strcmp(ptP->pcData, pcKey))
    {
        ptP = ptP->ptNext;
    }
    return ptP;
}

int iMainHash(int iKey, int iP)
{
    return iKey % iP;
}

ptrHashTable_T ptMainCreatTable(int iTableSize)
{
    ptrHashTable_T ptH;
    int iI;
    ptH = (ptrHashTable_T)malloc(sizeof(HashTable_T));
    ptH->iTableSize = iMainNextPrime(iTableSize);
    ptH->ptHeads = (ptrList_T)malloc(sizeof(LNode_T) * ptH->iTableSize);
    for (iI = 0; iI < ptH->iTableSize; iI++)
    {
        ptH->ptHeads[iI].pcData[0] = '\0';
        ptH->ptHeads[iI].ptNext = NULL;
        ptH->ptHeads[iI].iCount = 0;
    }
    return ptH;
}

char cMainInsert(ptrHashTable_T ptH, ptrElementType_t pcKey)
{
    ptrPosition_T ptP, ptNewCell;
    Index_t iPos;
    ptP = ptMainFind(ptH, pcKey);
    if (!ptP)
    {
        ptNewCell = (ptrPosition_T)malloc(sizeof(LNode_T));
        strcpy(ptNewCell->pcData, pcKey);
        ptNewCell->iCount = 1;
        iPos = iMainHash(atoi(pcKey + mainNUM_LEN - mainMAX_D), ptH->iTableSize);
        ptNewCell->ptNext = ptH->ptHeads[iPos].ptNext;
        ptH->ptHeads[iPos].ptNext = ptNewCell;
        return 0;
    }
    else
    {
        ptP->iCount++;
        return -1;
    }
}


void vMainScanAndOutput(ptrHashTable_T ptH)
{
    int iI, iMaxCnt = 0, iPCnt = 0;
    ptrElementType_t pcMinPhone;
    ptrList_T ptPtr;
    pcMinPhone[0] = '\0';
    for (iI = 0; iI < ptH->iTableSize; iI++)
    {
        ptPtr = ptH->ptHeads[iI].ptNext;
        while (ptPtr)
        {
            if (ptPtr->iCount > iMaxCnt)
            {
                iMaxCnt = ptPtr->iCount;
                strcpy(pcMinPhone, ptPtr->pcData);
                iPCnt = 1;
            }
            else if (ptPtr->iCount == iMaxCnt)
            {
                iPCnt++;
                if (strcmp(pcMinPhone, ptPtr->pcData) > 0)
                {
                   strcpy(pcMinPhone, ptPtr->pcData); 
                }
            }
            ptPtr = ptPtr->ptNext;
        }
    }
    printf("%s %d ", pcMinPhone, iMaxCnt);
    if (iPCnt > 1)
    {
        printf("%d", iPCnt);
    }
    printf("\n");
}


int main(int argc, char* argv[])
{
    int iN, iI;
    ptrElementType_t pcKey;
    ptrHashTable_T ptH;
    scanf("%d", &iN);
    ptH = ptMainCreatTable(iN * 2);
    for (iI = 0; iI < iN; iI++)
    {
        scanf("%s", pcKey);
        cMainInsert(ptH, pcKey);
        scanf("%s", pcKey);
        cMainInsert(ptH, pcKey);
    }
    vMainScanAndOutput(ptH);
    return 0;
}

