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

iVertex iMainFindMinDist(pxMGraph pxGraph, iWeightType piDist[])
{
    iVertex iMinV, iV;
    iWeightType iMinDist = mainINFINITY;
    for (iV = 0; iV < pxGraph->iNv; iV++)
    {
        if ((piDist[iV] != 0) && (piDist[iV] < iMinDist))
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

pxLGraph pxMainCreatGraph(int iVertexNum)
{
    iVertex iV;
    pxLGraph pxGraph;
    pxGraph = (pxLGraph)malloc(sizeof(struct xGNode));
    pxGraph->iNv = iVertexNum;
    pxGraph->iNe = 0;
    for (iV = 0; iV < pxGraph->iNv; iV++)
    {
        pxGraph->pxG[iV].pxFirstEdge = NULL;
    }
    return pxGraph;
}

void vMainInsertEdge(pxLGraph pxGraph, pxEdge pxE)
{
    pxAdjVNode pxNewNode;
    pxNewNode = (pxAdjVNode)malloc(sizeof(struct xAdjVNode));
    pxNewNode->iAdjV = pxE->iV2;
    pxNewNode->iWeight = pxE->iWeight;
    pxNewNode->pxNext = pxGraph->pxG[pxE->iV1].pxFirstEdge;
    pxGraph->pxG[pxE->iV1].pxFirstEdge = pxNewNode;
}

int iMainPrim(pxMGraph pxGraph, pxLGraph pxMst)
{
    iWeightType piDist[mainMAXVERTEXNUM], iTotalWeight;
    iVertex piParent[mainMAXVERTEXNUM], iV, iW;
    int iVCount;
    pxEdge pxE;

    for (iV = 0; iV < pxGraph->iNv; iV++)
    {
        piDist[iV] = pxGraph->piG[0][iV];
        piParent[iV] = 0;
    }
    iTotalWeight = 0;
    iVCount = 0;
    pxMst = pxMainCreatGraph(pxGraph->iNv);
    pxE = malloc(sizeof(struct xENode));
    piDist[0] = 0;
    iVCount++;
    piParent[0] = -1;
    while (1)
    {
        iV = iMainFindMinDist(pxGraph, piDist);
        if (iV == -1)
        {
            break;
        }
        pxE->iV1 = piParent[iV];
        pxE->iV2 = iV;
        pxE->iWeight = piDist[iV];
        vMainInsertEdge(pxMst, pxE);
        iTotalWeight += piDist[iV];
        piDist[iV] = 0;
        iVCount++;
        for (iW = 0; iW < pxGraph->iNv; iW++)
        {
            if (piDist[iW] != 0 && pxGraph->piG[iV][iW])
            {
                if (pxGraph->piG[iV][iW] < piDist[iW])
                {
                    piDist[iW] = pxGraph->piG[iV][iW];
                    piParent[iW] = iV;
                }
            }
        }
    }
    if (iVCount < pxGraph->iNv)
    {
        iTotalWeight = -1;
    }
    return iTotalWeight;
}



int main(int argc, char* argv[])
{
    return 0;
}

