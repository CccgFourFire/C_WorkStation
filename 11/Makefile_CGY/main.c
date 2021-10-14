#include <stdio.h>
#include<stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#define mainNOT_FOUND -1

typedef int Position_t;

void vMainBuildMatch(char *pcPattern, int *piMatch)
{
    Position_t iI, iJ;
    int iM = strlen(pcPattern);
    piMatch[0] = -1;
    for (iJ = 1; iJ < iM; iJ++)
    {
        iI = piMatch[iJ - 1];
        while ((iI >= 0) && (pcPattern[iJ] != pcPattern[iI + 1]))
        {
            iI = piMatch[iI];
        }
        if (pcPattern[iJ] == pcPattern[iI + 1])
        {
            piMatch[iJ] = iI + 1;
        }
        else
        {
            piMatch[iJ] = -1;
        }
    }
}

Position_t iMainKMP(char *pcString, char *pcPattern)
{
    int iN = strlen(pcString);
    int iM = strlen(pcPattern);
    Position_t iS, iP, *piMatch;
    if (iN < iM)
    {
        return -1;
    }
    piMatch = (Position_t *)malloc(sizeof(Position_t) * iM);
    vMainBuildMatch(pcPattern, piMatch);
    iS = iP = 0;
    while ((iS < iN) && (iP < iM))
    {
        if (pcString[iS] == pcPattern[iP])
        {
            iS++;
            iP++;
        }
        else if (iP > 0)
        {
            iP = piMatch[iP - 1] + 1;
        }
        else
        {
            iS++;
        }
    }
    return (iP == iM) ? (iS - iM) : -1;
}


int main(int argc, char* argv[])
{
    char pcString[] = {"www.aabcabdabcabc.com"};
    char pcPattern[] = {"abcabc"};
    Position_t iPos;
    iPos = iMainKMP(pcString, pcPattern);
    printf("%s", pcString + iPos);
    return 0;
}

