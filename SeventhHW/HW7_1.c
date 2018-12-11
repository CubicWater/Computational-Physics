#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "MonteCarlo.c"
/*
double P_x(double x);
double GetAlpha(double x_1,double x_2);
*/
int main()
{
    srand(time(0));

    double x0,a,temp,deltaX,temp2;
    int i,j,N;
    float x[20000];
    a = 2.0;
    N = 20000;
    x0 = 2*(rand()/(double)RAND_MAX);
    x[0] = x0;
    
    for (i=0;i<(N-2);i++)
    {
	temp = rand()/(double)RAND_MAX;
	deltaX = 0.2*(temp - 0.5)*2;
	x[i+1] = x[i] + deltaX;
	if (x[i+1] > a)
	{
	    x[i+1] = x[i+1] - a;
	}
	if (x[i+1] < 0)
	{
	    x[i+1] = x[i+1] + a;
	}
	temp2 = rand()/(double)RAND_MAX;
	if (GetAlpha(x[i],x[i+1])<temp2)
	{
	    x[i+1] = x[i];	
	}
    }
    
    printf("The 10000th number of the sequence is %f \n",x[10000]);
    return 0;
}
/*
//计算p(x)的函数
double P_x(double x)
{
    double y;
    double deno;
    deno = 1-exp(-2);
    //deno = pow(deno,5);
    y = exp(-1*x)/deno;
    
    return y;
}

//返回游动判定结果的函数
double GetAlpha(double x_1,double x_2)
{
    double p1,p2,Omega;
    p1 = P_x(x_1);
    p2 = P_x(x_2);
    Omega = p2/p1;

    return Omega;
}
*/
