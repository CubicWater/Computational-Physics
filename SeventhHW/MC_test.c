#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define N 100000
double func(double x);

int main()
{
    //设置随机数种子
    srand(time(0));
    //初始化变量
    double a,b,x,c,result;
    double PI;
    PI = 3.1415926;
    int i,j;
    a = -50.0;
    b = 50.0;
    x = 0.0;
    c = 0.0;
    //开始运行循环
    
    for (i=0;i<N;i++)
    {
	x = a + 100.0 * rand()/RAND_MAX;
	c = c + func(x);
    }

    result = c*(b-a)/N;
    result = result/sqrt(2*PI);
    //x = a + 100.0*rand()/RAND_MAX;
    printf("The answer is %.8f \n",result);

    return 0;
}

double func(double x)
{
    double y;
    y = exp(-1*pow(x,2)+0.5);
    return y;
}

