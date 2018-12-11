#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main()
{
    double a[2][3];
    double b[3];
    int i,j;

    for (i=0;i<2;i++)
    {
	for (j=0;j<3;j++)
	{
	    a[i][j] = (i+1)*(j+1);
	}
    }

    b = a[1];

    return 0;
}
