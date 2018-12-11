#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "MonteCarlo.c"
#define L 200
#define m 10000

int main()
{
    //设置随机种子
    srand(time(0));

    //声明变量
    double a;
    double *Markov_temp;
    double Markov[m+1];
    int i,j,N,N0,step;
    double Intm[L];

    //参数初始化
    a = 2.0;
    N = 510000;
    N0 = 10000;
    step = 50;

    for (i=0;i<L;i++)
    {
        Markov_temp = GetMarkov(a,N,Markov_temp);
        for (j=0;j<m;j++)
        {
            Markov[j] = Markov_temp[N0+j*step];
        }
        Intm[i] = ((m*1.0 + ((sum(Markov,m+1))/2.0))*(1.0-exp(-1.0*a)))/m;
        printf("L now is %d \n",i);
        fflush(stdout);
    }

    for (i = 0;i<L;i++)
    {
        printf("The %d th number of Intm is %.8f \n",i+1,Intm[i]);
        fflush(stdout);
    }    
    return 0;
}
