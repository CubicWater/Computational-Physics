//
//  HW7_5.c
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
    //设置随机种子
    srand(time(0));
    
    //声明变量
    double a;
    double* Cov;
    int m,i,j,N,N0,step,number,step_Max;
    int StartOfM2,EndOfM1;
    double* Markov;
    double* Markov1;
    double* Markov2;
    
    //初始化参量
    a = 2.0;
    N0 = 10000;
    m = 10000;
    number = 50000;
    step_Max = 1000;
    N = N0 + 1000000;
    //给一维数组Cov设置存储空间
    Cov = (double *)malloc(sizeof(double) * step_Max);
    
    for (step=2;step<step_Max;step++)
    {
        StartOfM2 = N0 + step +1;
        EndOfM1 = N - step - 1;
        
        //给一维数组Markov设置存储空间
        Markov = (double *)malloc(sizeof(double) * N);
        Markov1 = (double *)malloc(sizeof(double) * EndOfM1);
        Markov2 = (double *)malloc(sizeof(double) * EndOfM1);
        
        //求长度为N的Markov链
        Markov = GetMarkov(a,N,0.2,Markov);
        
        //求x_l与x_(l+N0+1)
        for (i=N0;i<EndOfM1;i++)
        {
            Markov1[i-N0] = Markov[i];
        }
        for (j=StartOfM2;j<N;j++)
        {
            Markov2[j-StartOfM2] = Markov[j];
        }
        
        //求协方差
        Cov[step-2] = GetCov(Markov1,Markov2,number);
        //free(Markov);
        free(Markov1);
        free(Markov2);
        printf("The step now is %d \n",step);
        fflush(stdout);
    }
    //将得到的数据写入txt文件
    FILE *fpWrite = fopen("HW7_5.txt","w");
    if(fpWrite==NULL)
    {
        return 0;
    }
    for(i=2;i<step_Max;i++)
    {
        fprintf(fpWrite,"%8f \n",Cov[i-2]);
    }
    
    return 0;
    
}
