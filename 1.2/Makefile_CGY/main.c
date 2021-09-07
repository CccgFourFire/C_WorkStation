#include <stdio.h>
#include <time.h>

#define mainLIST_MAX 100

unsigned int ulDichotomySort(unsigned int *plList, unsigned int ulSize, unsigned int ulNUm);

int main(int argc, char* argv[])
{
	unsigned int ulCnt;
	unsigned int ulList1[mainLIST_MAX];
	unsigned int ulList2[10] = {2, 4, 6, 8, 10, 12, 14, 16 ,18 ,20};
	int lRet;
	clock_t xStarttime, xStoptime;
	double dDuration;
	for (ulCnt = 0; ulCnt < mainLIST_MAX; ulCnt++)
	{
		ulList1[ulCnt] = ulCnt;
	}
	xStarttime = clock();
	lRet = ulDichotomySort(ulList2, 10, 19);
	xStoptime = clock();
	dDuration = (double)(xStoptime - xStarttime) / CLK_TCK;
	printf("Ticks count is %lf\n", (double)(xStoptime - xStarttime));
	printf("Opertaion Time is %6.2e\n", dDuration);

	if (lRet >= 0)
	{
		printf("Num is in the lis %d\n", lRet);
	}
	else
	{
		printf("Num isn't in the list\n");
	}
	return 0;
}

unsigned int ulDichotomySort(unsigned int *plList, unsigned int ulSize, unsigned int ulNUm)
{
	unsigned int ulMiddle = ulSize / 2;
	unsigned int ulCnt;
	if (ulNUm == plList[ulMiddle])
	{
		return ulMiddle;
	}
	else if (ulNUm > plList[ulMiddle])
	{
		for (ulCnt = ulMiddle + 1; ulCnt < ulSize; ulCnt++)
		{
			if (ulNUm == plList[ulCnt])
			{
				return ulCnt;
			}
		}
	}
	else {
		for (ulCnt = 0; ulCnt < ulMiddle - 1; ulCnt++)
		{
			if (ulNUm == plList[ulCnt])
			{
				return ulCnt;
			}
		}
	}
	return -1;
}