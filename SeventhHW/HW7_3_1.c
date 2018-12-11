#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "MonteCarlo.c"

int main()
{
    int i,m,N0,step,D,L,n,temp;
    double a,deltaX,sigma;
    double answer[20];
    
    srand(time(0));

    a = 2.0;
    deltaX = 0.1*a;
    N0 = 10000;
    step = 50;
    L = 200;
    D = 8;
    m = 10000;
    n = 20;
    temp = 0;
    
    for (i=0;i<n;i++)
    {
        temp = m + i*5000;
        answer[i] = GetSigma(a,deltaX,N0,step,temp,D,L);
        printf("now is the %d th circle \n",i);
        fflush(stdout);
    }

    FILE *fpWrite = fopen("HW7_3.txt","w");
    if(fpWrite==NULL)
    {
        return 0;
    }
    for(i=0;i<n;i++)
    {
        fprintf(fpWrite,"%8f \n",answer[i]);
    }
    
    return 0;
}
