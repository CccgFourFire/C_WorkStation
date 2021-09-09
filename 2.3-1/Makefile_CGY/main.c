#include <stdio.h>
#include<stdlib.h>
#include <time.h>

#define mainQUEUE_MAX 4

typedef struct mainQueue *pmainQueue;
struct mainQueue {
	int plData[mainQUEUE_MAX];
	int lFront;
	int lRear;
};

void vMainAddQueue(pmainQueue pQueue, int lData);
int lMainDeldQueue(pmainQueue pQueue);

int main(int argc, char* argv[])
{
	clock_t xStarttime, xStoptime;
	double dDuration;
	int lRet,lCnt;
	struct mainQueue xQueue;
	pmainQueue pxQueue = &xQueue;
	pxQueue->lFront = 0;
	pxQueue->lRear = 0;
	xStarttime = clock();
	lMainDeldQueue(pxQueue);
	vMainAddQueue(pxQueue, 1);
	vMainAddQueue(pxQueue, 2);
	vMainAddQueue(pxQueue, 3);
	vMainAddQueue(pxQueue, 4);
	lRet = lMainDeldQueue(pxQueue);
	printf("Result is %d\n", lRet);
	lRet = lMainDeldQueue(pxQueue);
	printf("Result is %d\n", lRet);
	lRet = lMainDeldQueue(pxQueue);
	printf("Result is %d\n", lRet);
	lRet = lMainDeldQueue(pxQueue);
	xStoptime = clock();
	dDuration = (double)(xStoptime - xStarttime) / CLK_TCK;
	printf("Ticks count is %lf\n", (double)(xStoptime - xStarttime));
	printf("Opertaion Time is %6.2e\n", dDuration);
	printf("Result is %d\n", lRet);
	return 0;
}

int lMainDeldQueue(pmainQueue pQueue)
{
	if (pQueue->lRear == pQueue->lFront)
	{
		printf("Queue is empty!!\n");
		return -1;
	}
	else
	{
		pQueue->lFront = (pQueue->lFront + 1) % mainQUEUE_MAX;
		return pQueue->plData[pQueue->lFront];
	}
}

void vMainAddQueue(pmainQueue pQueue, int lData)
{
	if ((pQueue->lRear + 1) % mainQUEUE_MAX == pQueue->lFront)
	{
		printf("Queue is full!!\n");
		return;
	}
	else
	{
		pQueue->lRear = (pQueue->lRear + 1) % mainQUEUE_MAX;
		pQueue->plData[pQueue->lRear] = lData;
	}
}