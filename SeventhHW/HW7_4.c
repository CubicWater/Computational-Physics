//
//  HW7_4.c
//  
//
//  Created by 三水 on 2018/12/4.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "MonteCarlo.c"

int main()
{
    int i,m,N0,step,D,L,n,temp;
    double a,deltaX,sigma;
    double answer[4];
    
    srand(time(0));
    
    a = 2.0;
    deltaX = 0.1*a;
    step = 50;
    L = 200;
    D = 5;
    m = 10000;
    n = 200;
    temp = 0;
    //N0 = 10000;
    
    N0 = 2000;
    answer[0] = GetSigma(a,deltaX,N0,step,m,D,L);
    N0 = 4000;
    answer[1] = GetSigma(a,deltaX,N0,step,m,D,L);
    N0 = 8000;
    answer[2] = GetSigma(a,deltaX,N0,step,m,D,L);
    N0 = 16000;
    answer[3] = GetSigma(a,deltaX,N0,step,m,D,L);
    
    for (i=0;i<4;i++)
    {
        printf("the %d th answer is %f \n",i,answer[i]);
    }
    
    
    return 0;
}

