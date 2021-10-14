#include <stdio.h>
#include<stdlib.h>
#include <time.h>

#define mainMAXVERTEXNUM 100
#define mainINFINITY 65535
#define mainMAXSIZE 100

typedef int iVertex;
typedef int iWeightType;
typedef char iDataType;

unsigned char g_pucVisited[100] = {0};

typedef struct xENode *pxENode;
struct xENode
{
    iVertex iV1, iV2;
    iWeightType iWeight;
};
typedef pxENode pxEdge;

typedef struct xGNode *pxGNode;
struct xGNode
{
    int iNv;
    int iNe;
    iWeightType piG[mainMAXVERTEXNUM][mainMAXVERTEXNUM];
    iDataType piData[mainMAXVERTEXNUM];
};
typedef pxGNode pxMGraph;

pxMGraph pxMainCreatGraph(int iVertexNum)
{
    iVertex iV, iW;
    pxMGraph pxGraph;
    pxGraph = (pxMGraph)malloc(sizeof(struct xGNode));
    pxGraph->iNv = iVertexNum;
    pxGraph->iNe = 0;
    for (iV = 0; iV < pxGraph->iNv; iV++)
    {
        for (iW = 0; iW < pxGraph->iNv; iW++)
        {
            pxGraph->piG[iV][iW] = mainINFINITY;
        }
    }
    return pxGraph;
}

void vMainInsertEdge(pxMGraph pxGraph, pxEdge pxE)
{
    pxGraph->piG[pxE->iV1][pxE->iV2] = pxE->iWeight;
    pxGraph->piG[pxE->iV2][pxE->iV1] = pxE->iWeight;
}

pxMGraph pxMainBuildGraph(void)
{
    pxMGraph pxGraph;
    pxEdge pxE;
    iVertex iV;
    int iNv, iI;
    scanf("%d", &iNv);
    pxGraph = pxMainCreatGraph(iNv);
    scanf("%d", &(pxGraph->iNe));
    if (pxGraph->iNe != 0)
    {
        pxE = (pxEdge)malloc(sizeof(struct xENode));
        for (iI = 0; iI < pxGraph->iNe; iI++)
        {
            scanf("%d %d %d", &pxE->iV1, &pxE->iV2, &pxE->iWeight);
            vMainInsertEdge(pxGraph, pxE);
        }
    }
    return pxGraph;
}

unsigned char ucMainIsEdge(pxMGraph pxGraph, iVertex iV, iVertex iW)
{
    return pxGraph->piG[iV][iW] < mainINFINITY ? 1 : 0;
}

iVertex vMainFindMinDist(pxMGraph pxGraph, int piDist[], int piCollected[])
{
    iVertex iMinV, iV;
    int iMinDist = mainINFINITY;
    for (iV = 0; iV < pxGraph->iNv; iV++)
    {
        if ((piCollected[iV] == 0) && (piDist[iV] < iMinDist))
        {
            iMinDist = piDist[iV];
            iMinV = iV;
        }
    }
    if (iMinDist < mainINFINITY)
    {
        return iMinV;
    }
    else
    {
        return -1;
    }
}

char cMainDijkstra(pxMGraph pxGraph, int piDist[], int piPath[], iVertex iS)
{
    int piCollected[mainMAXVERTEXNUM];
    iVertex iV, iW;
    for (iV = 0; iV < pxGraph->iNv; iV++)
    {
        piDist[iV] = pxGraph->piG[iS][iV];
        if (piDist[iV] < mainINFINITY)
        {
            piPath[iV] = iS;
        }
        else
        {
            piPath[iV] = -1;
        }
        piCollected[iV] = 0;
    }
    piDist[iS] = 0;
    piCollected[iS] = 1;
    while (1)
    {
        iV = vMainFindMinDist(pxGraph, piDist, piCollected);
        if (iV == -1)
        {
            break;
        }
        piCollected[iV] = 1;
        for (iW = 0; iW < pxGraph->iNv; iW++)
        {
            if ((piCollected[iW] == 0) && (pxGraph->piG[iV][iW] < mainINFINITY))
            {
                if (piDist[iV] + pxGraph->piG[iV][iW] < piDist[iW])
                {
                    piDist[iW] = piDist[iV] + pxGraph->piG[iV][iW];
                    piPath[iW] = iV;
                }
            }
        }
    }
    return 0;
}

void vMainFindAnimal(pxMGraph pxGraph)
{
    iWeightType piD[mainMAXVERTEXNUM][mainMAXVERTEXNUM], iMaxDist, iMinDist;
    iVertex iAnimal, iI;
    vMainFloyd(pxGraph, piD);
    iMinDist = mainINFINITY;
    for (iI = 0; iI < pxGraph->iNv; iI++)
    {
        iMaxDist = iMainFindMaxDist(piD, iI, pxGraph->iNv);
        if (iMinDist > iMaxDist)
        {
            iMinDist = iMaxDist;
            iAnimal = iI + 1;
        }
    }
    printf("%d %d\n\r", iAnimal, iMinDist);
}


int main(int argc, char* argv[])
{
    pxMGraph pxGraph = pxMainBuildGraph();
    vMainFindAnimal(pxGraph);
    return 0;
}


