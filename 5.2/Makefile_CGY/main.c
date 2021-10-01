#include <stdio.h>
#include<stdlib.h>
#include <time.h>

typedef struct xTreeNode *pxHuffmanTree;

typedef struct xTreeNode
{
    int iWeight;
    pxHuffmanTree pxLeft;
    pxHuffmanTree pxRight;
} xTreeNode;

pxHuffmanTree pxMainHuffmanCreat(pxMinHeap pxH)
{
    int iI;
    pxHuffmanTree pxT;
    vMainBuildMinHeap(pxH);
    for (iI = 1; iI < pxH->iSize; iI++)
    {
        pxT = malloc(sizeof(xTreeNode));
        pxT->pxLeft = pxMainDeleteMin(pxH);
        pxT->pxRight = pxMainDeleteMin(pxH);
        pxT->iWeight = pxT->pxLeft->iWeight + pxT->pxRight->iWeight;
        vMainInsert(pxH,pxT);
    }
    pxT = pxMainDeleteMin(pxH);
    return pxT;
}

int main(int argc, char* argv[])
{
}

