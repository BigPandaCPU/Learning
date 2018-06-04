#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "TutorialConfig.h"
#ifdef USE_MYMATH
#include "./MathFunctions/mysqrt.h"
#endif
int main(int argc, char *argv[])
{
	if(argc < 3)
	{
		//fprintf(stdout,"Usage:%s number\n",argv[0]);
		fprintf(stdout,"%s\n Version %d.%d\n",argv[0], Tutorial_VERSION_MAJOR, Tutorial_VERSION_MINOR);
		fprintf(stdout,"Usage:%s number\n",argv[0]);
		//return 1;
	}
	double inputValue  = atof(argv[1]);
	
#ifdef USE_MYMATH
	double outputValue = mysqrt(inputValue);
	fprintf(stdout,"This is my function\n");
#else
	double outputValue = sqrt(inputValue);
#endif

	double result; 

#if defined(HAVE_LOG) && defined(HAVE_EXP)
	result = exp(log(100.0));
	fprintf(stdout,"The result is %.2f\n", result);
#endif
	
	fprintf(stdout,"The square root of %g is %g\n",inputValue,outputValue);
	system("pause");
	return 0;
}    