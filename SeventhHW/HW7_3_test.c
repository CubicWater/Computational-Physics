//
//  HW7_3_test.c
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
    double* Markov_temp;
    double**  Markov;
    int i,j,k,N0,N,D,step,m,l,s;
    double a;
    double* x;
    
    N0 = 10000;
    D = 5;
    a = 0.2;
    m = 100000;
    step = 50;
    
    N = N0 + m*step;
    
    x = (double *)malloc(sizeof(double) * N);
    free(x);
    /*
    Markov = (double **)malloc(sizeof(double *) * D);
    for (i=0;i<m;i++)
    {
        Markov[i] = (double *)malloc(sizeof(double) * m);
    }
    
    //length = 1000;
    for (j=0;j<D;j++)
    {
        Markov_temp = GetMarkov(a,N,Markov_temp);
        for(k=0;k<m;k++)
        {
            Markov[j][k] = Markov_temp[N0 + k*step];
        }
    }
    */
    
    

    
    return 0;
}
