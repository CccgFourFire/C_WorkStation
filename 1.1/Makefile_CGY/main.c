#include <stdio.h>
#include <time.h>

#define mainPOLYNOMIAL_MAX 101
#define mainCALL_MAX 1E7

void vMainPrintN1(unsigned int lNum);
void vMainPrintN2(unsigned int lNum);
double dMainPolynomialCal(unsigned int ulOrder, double dTerm[], double dBasis);

clock_t xStarttime, xStoptime;
double dDuration;


int main(int argc, char* argv[])
{
	unsigned int ulCnt;
	double dResult;
	double dTerm[mainPOLYNOMIAL_MAX];
	unsigned int lNum = 10000;
	for (ulCnt = 0; ulCnt < mainPOLYNOMIAL_MAX; ulCnt++)
	{
		if (ulCnt == 0){
			dTerm[ulCnt] = 1;
		}
		else
		{
			dTerm[ulCnt] = 1 /(double)ulCnt;	
		}
	}
	xStarttime = clock();
	// vMainPrintN2(lNum);
	dResult = dMainPolynomialCal(mainPOLYNOMIAL_MAX - 1, dTerm, (double)1.1);
	xStoptime = clock();
	dDuration = (double)(xStoptime - xStarttime) / CLK_TCK;
	printf("Result is %lf\n", dResult);
	printf("Ticks count is %lf\n", (double)(xStoptime - xStarttime));
	printf("Opertaion Time is %6.2e\n", dDuration);
	// printf("Opertaion Time is %6.2e\n", dDuration / mainCALL_MAX);
	return 0;
}

void vMainPrintN1(unsigned int lNum)
{
	unsigned int lCnt;
	for (lCnt = 0; lCnt <= lNum; lCnt++)
	{
		printf("%d\n", lCnt);
	}
}

void vMainPrintN2(unsigned int lNum)
{
	if (lNum)
	{
		vMainPrintN2(lNum - 1);
		printf("%d\n", lNum);
	}
}

double dMainPolynomialCal(unsigned int ulOrder, double dTerm[], double dBasis)
{
	unsigned int ulCnt;
	double dSum = dTerm[ulOrder];
	for (ulCnt = ulOrder; ulCnt > 0; ulCnt--)
	{
		dSum = dTerm[ulCnt - 1] + dSum * dBasis;
	}
	return dSum;
}