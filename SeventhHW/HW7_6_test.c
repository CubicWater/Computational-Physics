//
//  HW7_6_test.c
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
    int i,j,m,N0,step,D,L,n,temp;
    double a,Delta,sigma;
    double answer;
    
    srand(time(0));
    
    a = 2.0;
    N0 = 10000;
    step = 50;
    L = 200;
    D = 5;
    m = 10000;
    n = 40;
    temp = 0;
    
    Delta = 0.1*a;
    answer = GetSigma(a,Delta,N0,step,m,D,L);
    /*
    for (i=0;i<n;i++)
    {
        Delta = (0.02 + 0.02*(double)i)*a;
        answer[i] = GetSigma(a,Delta,N0,step,temp,D,L);
        printf("now is the %d th circle \n",i);
        fflush(stdout);
    }
    */
    //将得到的数据写入txt文件
    /*
    FILE *fpWrite = fopen("HW7_6.txt","w");
    if(fpWrite==NULL)
    {
        return 0;
    }
    */
    /*
    for(i=0;i<n;i++)
    {
        fprintf(fpWrite,"%8f \n",answer[i]);
    }
    */
    printf("the answer is %8f \n",answer);
    
    return 0;
}
