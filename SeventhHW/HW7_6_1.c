//
//  HW7_6.c
//  
//
//  Created by 三水 on 2018/12/5.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "MonteCarlo.c"

int main()
{
    int i,j,m,N0,step,D,L,n;
    double a,Delta,sigma;
    double answer[40];
    
    srand(time(0));
    
    a = 2.0;
    N0 = 10000;
    step = 50;
    L = 200;
    D = 5;
    m = 10000;
    n = 30;
    
    for (i=0;i<n;i++)
    {
        Delta = (0.01 + 0.01*i)*a;
        answer[i] = GetSigma(a,Delta,N0,step,m,D,L);
        printf("now is the %d th circle \n",i);
        fflush(stdout);
    }
    //将得到的数据写入txt文件
    FILE *fpWrite = fopen("HW7_6_1.txt","w");
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
