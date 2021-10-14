#include <stdio.h>
#include<stdlib.h>
#include <time.h>

#define mainMAXVERTEXNUM 10
#define mainINFINITY 65535

typedef int iVertex;
typedef int iWeightType;
typedef char iDataType;

int g_piDist[mainMAXVERTEXNUM] = {-1};
int g_piPath[mainMAXVERTEXNUM] = {-1};

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

pxLGraph pxMainBuildGraph(void)
{
    pxLGraph pxGraph;
    pxEdge pxE;
    iVertex iV;
    int iNv, iI;
    scanf("%d", &iNv); 
    pxGraph = pxMainCreatGraph(iNv); 
    scanf("%d", &(pxGraph->iNe)); 
    if (pxGraph->iNe != 0) 
    { 
        pxE = (pxEdge)malloc( sizeof(struct xENode) );
        for (iI=0; iI < pxGraph->iNe; iI++) {
            scanf("%d %d %d", &pxE->iV1, &pxE->iV2, &pxE->iWeight); 
            vMainInsertEdge(pxGraph, pxE);
        }
    }
    return pxGraph;
}

void vMainUnweighted(pxLGraph pxGraph, int piDist[], int piPath, iVertex iS)
{
    pxQueue pxQ;
    iVertex iV;
    pxAdjVNode pxW;
    pxQ = pxMainCreatQueue(pxGraph->iNv);
    g_piDist[iS] = 0;
    vMainAddQ(pxQ, iS);
    while (!cMainIsEmpty(pxQ))
    {
        iV = iMainDeleteQ(pxQ);
        for (pxW = pxGraph->pxG[iV].pxFirstEdge; pxW; pxW = pxW->pxNext)
        {
            if (g_piDist[pxW->iAdjV] == -1)
            {
                g_piDist[pxW->iAdjV] = g_piDist[iV] + 1;
                g_piPath[pxW->iAdjV] = iV;
                vMainAddQ(pxQ, pxW->iAdjV);
            }
        }
    }
}




int main(int argc, char* argv[])
{
    pxLGraph pxGraph;
    pxGraph = pxMainBuildGraph();
    return 0;
}

