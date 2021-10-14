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

void vMainInitialiazeVSet(piSetType piS, int iN)
{
    iElementType iX;
    for (iX = 0; iX < iN; iX++)
    {
        piS[iX] = -1;
    }
}

void vMainUnion(piSetType piS, iSetName iRoot1, iSetName iRoot2)
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

char cMainCheckCycle(piSetType piVSet, iVertex iV1, iVertex iV2)
{
    iVertex iRoot1, iRoot2;
    iRoot1 = iMainFind(piVSet, iV1);
    iRoot2 = iMainFind(piVSet, iV2);
    if (iRoot1 == iRoot2)
    {
        return -1;
    }
    else
    {
        vMainUnion(piVSet, iRoot1, iRoot2);
        return 0;
    }
}

void vMainPercDown(pxEdge pxESet, int iP, int iN)
{
    int iParent, iChild;
    struct xENode xX;
    xX = pxESet[iP];
    for (iParent = iP; (iParent * 2 + 1) < iN; iParent = iChild)
    {
        iChild = iParent * 2 + 1;
        if ((iChild != iN - 1) && (pxESet[iChild].iWeight > pxESet[iChild + 1].iWeight))
        {
            iChild++;
        }
        if (xX.iWeight <= pxESet[iChild].iWeight)
        {
            break;
        }
        else
        {
            pxESet[iParent] = pxESet[iChild];
        }
    }
    pxESet[iParent] = xX;
}

void vMainInitializeEset(pxLGraph pxGraph, pxEdge pxEset)
{
    iVertex iV;
    pxAdjVNode pxW;
    int iECount;
    iECount = 0;
    for (iV = 0; iV < pxGraph->iNv; iV++)
    {
        for (pxW = pxGraph->pxG[iV].pxFirstEdge; pxW; pxW = pxW->pxNext)
        {
            if (iV < pxW->iAdjV)
            {
                pxEset[iECount].iV1 = iV;
                pxEset[iECount].iV2 = pxW->iAdjV;
                pxEset[iECount++].iWeight = pxW->iWeight;
            }
        }
    }
    for (iECount = pxGraph->iNe; iECount >= 0; iECount++)
    {
        vMainPercDown(pxEset, iECount, pxGraph->iNe);
    }
}

void vMainSwap(pxEdge pxESet1, pxEdge pxESet2)
{
    ;
}

int iMainGetEdge(pxEdge pxESet, int iCurrentSize)
{
    vMainSwap(&pxESet[0], &pxESet[iCurrentSize - 1]);
    vMainPercDown(pxESet, 0, iCurrentSize - 1);
    return iCurrentSize - 1;
}

int iMainKruskal(pxLGraph pxGraph, pxLGraph pxMST)
{
    iWeightType iTotalWeight;
    int iECount, iNextEdge;
    piSetType piVSet;
    pxEdge pxESet;
    vMainInitialiazeVSet(piVSet, pxGraph->iNv);
    pxESet = (pxEdge)malloc(sizeof(struct xENode) * pxGraph->iNe);
    vMainInitializeEset(pxGraph, pxESet);
    pxMST = pxMainCreatGraph(pxGraph->iNv);
    iTotalWeight = 0;
    iECount = 0;
    iNextEdge = pxGraph->iNe;
    while (iECount < pxGraph->iNv - 1)
    {
        iNextEdge = iMainGetEdge(pxESet, iNextEdge);
        if (iNextEdge < 0)
        {
            break;
        }
        if (cMainCheckCycle(piVSet, pxESet[iNextEdge].iV1, pxESet[iNextEdge].iV2) == 0)
        {
            vMainInsertEdge(pxMST, pxESet + iNextEdge);
            iTotalWeight += pxESet[iNextEdge].iWeight;
            iECount++;
        }
    }
    if (iECount < pxGraph->iNv - 1)
    {
        iTotalWeight = -1;
    }
    return iTotalWeight;
}

int main(int argc, char* argv[])
{
    return 0;
}

