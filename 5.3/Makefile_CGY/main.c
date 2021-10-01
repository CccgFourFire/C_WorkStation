#include <stdio.h>
#include<stdlib.h>
#include <time.h>

#define mainMAXSIZE 10

typedef struct xSetType *pxSetType;

typedef struct xSetType
{
    int iData;
    int iParent;
} xSetType;

int iMainFind(xSetType pxS[], int iX)
{
    int iI = 0;
    for (iI = 0; iI < mainMAXSIZE && pxS[iI].iData != iX; iI++);
    if (iI >= mainMAXSIZE)
    {
        return -1;
    }
    for ( ; pxS[iI].iParent >= 0; iI = pxS[iI].iParent);
    return iI;
}

void vMainUnion(xSetType pxS[], int iX1, int iX2)
{
    int iRoot1, iRoot2;
    iRoot1 = iMainFind(pxS, iX1);
    iRoot2 = iMainFind(pxS, iX2);
    if (iRoot1 != iRoot2)
    {
        pxS[iRoot1].iParent = iRoot2;
    }
}

int main(int argc, char* argv[])
{
}

