//
//  HW7_3_2.c
//  
//
//  Created by 三水 on 2018/12/8.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "MonteCarlo.c"

int main()
{
    int i,m,N0,step,D,L,n,temp;
    double a,deltaX,sigma,I_exact,error;
    double* answer;
    double* axis;
    
    //设置随机种子
    srand(time(0));
    
    I_exact = pow(1.1617,5);
    a = 2.0;
    deltaX = 0.1*a;
    N0 = 10000;
    step = 50;
    D = 5;
    m = 10000;
    n = 200;
    error = 0.0;
    sigma = 0.0;

    //给answer创建储存空间
    answer = (double*)malloc(sizeof(double) * n);
    axis = (double*)malloc(sizeof(double) * n);
    
    for (i = 0;i<n;i++)
    {
        L = i+1;
        sigma = GetSigma(a,deltaX,N0,step,m,D,L);
        axis[i] = sigma/sqrt((double)L);
        error = I_exact - (GetIntm(a,deltaX,N0,step,m,D,L));
        error = fabs(error);
        answer[i] = error;
        printf("The i now is %d \n",i);
        fflush(stdout);
    }
    
    
    FILE *fpWrite = fopen("HW7_3_2.txt","w");
    if(fpWrite==NULL)
    {
        return 0;
    }
    for(i=0;i<n;i++)
    {
        fprintf(fpWrite,"%8f ;%8f \n",axis[i],answer[i]);
    }
    //释放内存
    free(answer);
    free(axis);
    
    return 0;
}
