#include <stdio.h>
#include<stdlib.h>
#include <time.h>

#define mainMAXVERTEXNUM 100
#define mainINFINITY 65535
#define mainMAXSIZE 100

typedef int iVertex;
typedef int iWeightType;
typedef char iDataType;

typedef struct xENode *pxENode;
struct xENode
{
    iVertex iV1, iV2;
    iWeightType iWeight;
};
typedef pxENode pxEdge;

typedef struct xAdjVNode *pxAdjVNode;
struct xAdjVNode
{
    iVertex iAdjV;
    iWeightType iWeight;
    pxAdjVNode pxNext;
};

typedef struct xVnode
{
    pxAdjVNode pxFirstEdge;
    iDataType iData;
} pxAdiList[mainMAXVERTEXNUM];

typedef struct xGNode *pxGNode;
struct xGNode
{
    int iNv;
    int iNe;
    pxAdiList pxG;
};
typedef pxGNode pxLGraph;


typedef struct xGNode1 *pxGNode1;
struct xGNode1
{
    int iNv;
    int iNe;
    iWeightType piG[mainMAXVERTEXNUM][mainMAXVERTEXNUM];
    iDataType piData[mainMAXVERTEXNUM];
};
typedef pxGNode1 pxMGraph;

typedef iVertex iElementType;
typedef iVertex iSetName;
typedef iElementType piSetType[mainMAXVERTEXNUM];

char cMainTopSort(pxLGraph pxGraph, iVertex piTopOrder[])
{
    int piIndegree[mainMAXVERTEXNUM], iCnt;
    iVertex iV;
    pxAdjVNode  pxW;
    pxQueue pxQ = pxMainCreatQueue(pxGraph->iNv);
    for (iV = 0; iV < pxGraph->iNv; iV++)
    {
        piIndegree[iV] = 0;
    }
    for (iV = 0; iV < pxGraph->iNv; iV++)
    {
        for (pxW = pxGraph->pxG[iV].pxFirstEdge; pxW; pxW = pxW->pxNext)
        {
            piIndegree[pxW->iAdjV]++;
        }
    }
    for (iV = 0; iV < pxGraph->iNv; iV++)
    {
        if (piIndegree[iV] == 0)
        {
            vMainAddQ(pxQ, iV);
        }
    }
    iCnt = 0;
    while (!cMainIsEmpty(pxQ))
    {
        iV = iMainDeleteQ(pxQ);
        piTopOrder[iCnt++] = iV;
        for (pxW = pxGraph->pxG[iV].pxFirstEdge; pxW; pxW = pxW->pxNext)
        {
            if (--piIndegree[pxW->iAdjV] == 0)
            {
                vMainAddQ(pxQ, pxW->iAdjV);
            }
        }
    }
    if (iCnt != pxGraph->iNv)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}



int main(int argc, char* argv[])
{
    return 0;
}

