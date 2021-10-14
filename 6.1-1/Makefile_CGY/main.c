#include <stdio.h>
#include<stdlib.h>
#include <time.h>

#define mainMAXVERTEXNUM 100
#define mainINFINITY 65535

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

int main(int argc, char* argv[])
{
    pxMGraph pxGraph;
    pxGraph = pxMainBuildGraph();
    return 0;
}

