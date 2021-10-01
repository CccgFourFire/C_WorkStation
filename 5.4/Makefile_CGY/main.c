#include <stdio.h>
#include<stdlib.h>
#include <time.h>

#define mainMAXN 11
#define mainMIN 0x80000000

int piH[mainMAXN], iSize;

void vMainCreat(void)
{
    piH[0] = mainMIN;
    iSize = 0;
}

void vMainInsert(int iX)
{
    int iI;
    for (iI = ++iSize; piH[iI / 2] > iX; iI = iI / 2)
    {
        piH[iI] = piH[iI / 2];
    }
    piH[iI] = iX;
}

int main(int argc, char* argv[])
{
    int iN, iM, iX, iI, iJ;
    scanf("%d%d", &iN, &iM);
    vMainCreat();
    for (iI = 0; iI < iN; iI++)
    {
        scanf("%d", &iX);
        vMainInsert(iX);
    }
    for (iI = 0; iI < iM; iI++)
    {
        scanf("%d", &iJ);
        printf("%d", piH[iJ]);
        while (iJ > 1)
        {
            iJ = iJ / 2;
            printf("%d", piH[iJ]);
        }
        printf("\n");
    }
    return 0;
}

