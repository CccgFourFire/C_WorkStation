#include <stdio.h>
#include <time.h>

#define mainLIST_MAX 100

int lMaxSubseqSum1(int *plList, unsigned int ulSize);
int lMaxSubseqSum2(int *plList, unsigned int ulSize);
int lMaxSubseqSum3(int *plList, int lLeft, int lRight);
int lMaxSortFromThree(int lLeftMax, int lRightMax, int lCrossMax);
int lMaxSubseqSum4(int *plList, int lSize);


int main(int argc, char* argv[])
{
	clock_t xStarttime, xStoptime;
	double dDuration;
	unsigned int ulCnt;
	unsigned int ulList1[mainLIST_MAX];
	int lList2[8] = {-1, 3, -2, 4, -6, 1, 6, -1};
	int lRet;
	for (ulCnt = 0; ulCnt < mainLIST_MAX; ulCnt++)
	{
		ulList1[ulCnt] = ulCnt;
	}
	xStarttime = clock();
	lRet = lMaxSubseqSum4(lList2, 8);
	xStoptime = clock();
	dDuration = (double)(xStoptime - xStarttime) / CLK_TCK;
	printf("Ticks count is %lf\n", (double)(xStoptime - xStarttime));
	printf("Opertaion Time is %6.2e\n", dDuration);
	printf("Max Sum is %d\n", lRet);
	return 0;
}

int lMaxSubseqSum1(int *plList, unsigned int ulSize)
{
	int lSum, lMaxSum = 0;
	unsigned int ulLeft, ulRight, ulcnt;
	for (ulLeft = 0; ulLeft < ulSize; ulLeft++)
	{
		lSum = 0;
		for (ulRight = ulLeft; ulRight < ulSize; ulRight++)
		{
			lSum += plList[ulRight];
			if (lSum > lMaxSum)
			{
				lMaxSum = lSum;
			}
		}
	}
	return lMaxSum;
}

int lMaxSubseqSum2(int *plList, unsigned int ulSize)
{
	int lSum, lMaxSum = 0;
	unsigned int ulLeft, ulRight, ulcnt;
	for (ulLeft = 0; ulLeft < ulSize; ulLeft++)
	{
		for (ulRight = ulLeft; ulRight < ulSize; ulRight++)
		{
			lSum = 0;
			for (ulcnt = ulLeft; ulcnt <= ulRight; ulcnt++)
			{
				lSum += plList[ulcnt];
			}
			if (lSum > lMaxSum)
			{
				lMaxSum = lSum;
			}
		}
	}
	return lMaxSum;
}

int lMaxSortFromThree(int lLeftMax, int lRightMax, int lCrossMax)
{
	if(lLeftMax > lRightMax)
	{
		if (lLeftMax > lCrossMax)
		{
			return lLeftMax;
		}
		else
		{
			return lCrossMax;
		}
	}
	else
	{
		if (lRightMax > lCrossMax)
		{
			return lRightMax;
		}
		else
		{
			return lCrossMax;
		}
	}
}

int lMaxSubseqSum3(int *plList, int lLeft, int lRight)
{
	unsigned int ulMiddle;
	int lCnt, lLeftMax = 0, lRightMax = 0, lCrossMaxLeft = 0, lCrossMaxRight = 0, lCrossLeftSum = 0, lCrossRightSum = 0, lCrossMax = 0;
	//  if (lRight == (lLeft + 1))
	//  {
	// 	 if (plList[lLeft] > plList[lRight])
	// 	 {
	// 		 return plList[lLeft];
	// 	 }
	// 	 else
	// 	 {
	// 		 return plList[lRight];
	// 	 }
	//  }
	if (lRight == lLeft)
	{
		return plList[lLeft];
	}
	 else
	 {
		 ulMiddle = (lLeft + lRight) / 2;
		 lLeftMax = lMaxSubseqSum3(plList, lLeft, ulMiddle);
		 lRightMax = lMaxSubseqSum3(plList, ulMiddle + 1, lRight);
		 lCrossMaxLeft = plList[ulMiddle];
		 lCrossMaxRight = plList[ulMiddle + 1];
		 for (lCnt = ulMiddle; lCnt >= lLeft; lCnt--)
		 {
			 lCrossLeftSum += plList[lCnt];
			 if (lCrossLeftSum > lCrossMaxLeft)
			 {
				 lCrossMaxLeft = lCrossLeftSum;
			 }
		 }

		for (lCnt = ulMiddle + 1; lCnt <= lRight; lCnt++)
		 {
			 lCrossRightSum += plList[lCnt];
			 if (lCrossRightSum > lCrossMaxRight)
			 {
				 lCrossMaxRight = lCrossRightSum;
			 }
		 }
		 lCrossMax = lCrossMaxLeft + lCrossMaxRight;
	 }
	 return lMaxSortFromThree(lLeftMax, lRightMax, lCrossMax);
}

int lMaxSubseqSum4(int *plList, int lSize)
{
	int lSum = 0, lMaxSum = plList[0], lCnt = 0;
	for (lCnt = 0; lCnt <lSize; lCnt++)
	{
		lSum += plList[lCnt];
		if (lSum > lMaxSum)
		{
			lMaxSum = lSum;
		}
		else if (lSum < 0)
		{
			lSum = 0;
		}
	}
	return lMaxSum;
}