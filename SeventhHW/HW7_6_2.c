//
//  HW7_6_2.c
//  
//
//  Created by 三水 on 2018/12/6.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "MonteCarlo.c"

int main()
{
    srand(time(0));
    
    double a,Delta;
    int i,N,N0,step,m,n,temp;
    double* answer;
    
    a = 2.0;
    N0 = 10000;
    step = 50;
    m = 10000;
    N = N0 + m*step;
    n = 625;
    //Delta = 0.4;
    answer = (double *)malloc(sizeof(double) * n);
    
    for (i=0;i<n;i++)
    {
        Delta = 0.04 + 0.04*i;
        temp = GetPassRate(a,N,Delta);
        answer[i] = (double)temp/(double)N;
        printf("the %d th answer is %8f \n",i+1,answer[i]);
        fflush(stdout);
    }
    //写入文件
    FILE *fpWrite = fopen("HW7_6_2.txt","w");
    if(fpWrite==NULL)
    {
        return 0;
    }
    for(i=0;i<n;i++)
    {
        fprintf(fpWrite,"%8f \n",answer[i]);
    }
    //释放内存
    free(answer);
    
    return 0;
    
}
