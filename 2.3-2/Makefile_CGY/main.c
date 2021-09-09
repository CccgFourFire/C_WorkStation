#include <stdio.h>
#include<stdlib.h>
#include <time.h>

typedef struct mainListQueue *pmainListQueue;
typedef struct mainQueue *pmainQueue;

struct mainListQueue {
	int lData;
	pmainListQueue pxNext;
};

struct mainQueue {
	pmainListQueue pxFront;
	pmainListQueue pxRear;
};

int lMainDeldQueue(pmainQueue pxQueue);

void vMainAddQueue(pmainQueue pxQueue, int lData);

int main(int argc, char* argv[])
{
	clock_t xStarttime, xStoptime;
	double dDuration;
	int lRet,lCnt;
	struct mainQueue xQueueHead;
	pmainQueue pxQueueHead = &xQueueHead;
	pxQueueHead->pxFront = NULL;
	pxQueueHead->pxRear = NULL;
	xStarttime = clock();
	vMainAddQueue(pxQueueHead, 3);
	vMainAddQueue(pxQueueHead, 6);
	vMainAddQueue(pxQueueHead, 9);
	lRet = lMainDeldQueue(pxQueueHead);
	printf("Result is %d\n", lRet);
	lRet = lMainDeldQueue(pxQueueHead);
	printf("Result is %d\n", lRet);
	lRet = lMainDeldQueue(pxQueueHead);
	printf("Result is %d\n", lRet);
	lRet = lMainDeldQueue(pxQueueHead);
	xStoptime = clock();
	dDuration = (double)(xStoptime - xStarttime) / CLK_TCK;
	printf("Ticks count is %lf\n", (double)(xStoptime - xStarttime));
	printf("Opertaion Time is %6.2e\n", dDuration);
	printf("Result is %d\n", lRet);
	return 0;
}

int lMainDeldQueue(pmainQueue pxQueue)
{
	int lRet;
	pmainListQueue pxDelQueue = pxQueue->pxFront;
	if (pxQueue->pxFront == NULL)
	{
		printf("List is empty!!\n");
		return -1;
	}
	if (pxQueue->pxFront == pxQueue->pxRear)
	{
		pxQueue->pxFront = NULL;
		pxQueue->pxRear = NULL;
	}
	else
	{
		pxQueue->pxFront = pxDelQueue->pxNext;
	}
	lRet = pxDelQueue->lData;
	free(pxDelQueue);
	return lRet;
}

void vMainAddQueue(pmainQueue pxQueue, int lData)
{
	pmainListQueue pxNewQueue = malloc(sizeof(struct mainListQueue));
	if (pxQueue->pxFront == NULL)
	{
		pxQueue->pxFront = pxNewQueue;
	}
	pxNewQueue->lData = lData;
	pxNewQueue->pxNext = NULL;
	if (pxQueue->pxRear == NULL)
	{
		pxQueue->pxRear = pxNewQueue;
		return;
	}
	else
	{
		pxQueue->pxRear->pxNext = pxNewQueue;
		pxQueue->pxRear = pxNewQueue;
	}
}