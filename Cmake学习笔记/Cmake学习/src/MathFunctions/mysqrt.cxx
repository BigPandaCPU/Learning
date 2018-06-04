#include<math.h>
#include"mysqrt.h"
#include <stdio.h>
double mysqrt(double value)
{
	if(value < 0)
	{	
		printf("Value error,the value must over 0.\n");
		return -1;
	}
	return sqrt(value+11);
}
