#include <stdio.h>
#include<stdlib.h>
#include <time.h>

#define mainMAXN 10

typedef int iElementType;
typedef int iSetName;
typedef iElementType piSetType[mainMAXN];

iSetName iMainFind(piSetType piS, iElementType iX)
{
    if (piS[iX] < 0)
    {
        return iX;
    }
    else
    {
        return piS[iX] = iMainFind(piS, piS[iX]);
    }
}

void vMainUnion(piSetType piS, iSetName iRoot1, iSetName iRoot2)
{
    if (piS[iRoot2] < piS[iRoot1])
    {
        piS[iRoot1] = iRoot2;
    }
    else if (piS[iRoot2] == piS[iRoot1])
    {
        piS[iRoot2] = iRoot1;
        piS[iRoot1]--;
    }
    else
    {
        piS[iRoot2] = iRoot1;
    }
}

void vMainUnion1(piSetType piS, iSetName iRoot1, iSetName iRoot2)
{
    if (piS[iRoot2] < piS[iRoot1])
    {
        piS[iRoot2] += piS[iRoot1];
        piS[iRoot1] = iRoot2;
    }
    else
    {
        piS[iRoot1] += piS[iRoot2];
        piS[iRoot2] = iRoot1;
    }
}

void vMainInitialization(piSetType piS, int iN)
{
    int iI;
    for (iI = 0; iI< iN; iI++)
    {
        piS[iI] = -1;
    }
}

void vMainInputConnection(piSetType piS)
{
    iElementType iU, iV;
    iSetName iRoot1, iRoot2;
    scanf("%d %d\n", &iU, &iV);
    iRoot1 = iMainFind(piS, iU - 1);
    iRoot2 = iMainFind(piS, iV - 1);
    if (iRoot1 != iRoot2)
    {
        vMainUnion(piS, iRoot1, iRoot2);
    }
}

void vMainCheckConnection(piSetType piS)
{
    iElementType iU, iV;
    iSetName iRoot1, iRoot2;
    iRoot1 = iMainFind(piS, iU - 1);
    iRoot2 = iMainFind(piS, iV - 1);
    if (iRoot1 == iRoot2)
    {
        printf("Yes\n\r");
    }
    else
    {
        printf("No\n\r");
    }
}

void vMainCheckNetWork(piSetType piS, int iN)
{
    int iI, iCounter = 0;
    for (iI = 0; iI < iN; iI++)
    {
        if (piS[iCounter] < 0)
        {
            iCounter++;
        }
    }
    printf("%d Network\n\r", iCounter);
}

int main(int argc, char* argv[])
{
    piSetType piS;
    int iN;
    char cIn;
    scanf("%d\n", &iN);
    vMainInitialization(piS, iN);
    do
    {
        scanf("%c", &cIn);
        switch (cIn)
        {
            case 'I':
                vMainInputConnection(piS);
                break;
            case 'C':
                vMainCheckConnection(piS);
                break;
            case 'S':
                vMainCheckNetWork(piS, iN);
                break;
        }
    } while (cIn != 'S');
    return 0;
}

