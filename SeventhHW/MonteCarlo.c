#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


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

//求蒙特卡洛采样点的函数
//返回一维数组
double* GetMarkov(double a,int N,double Delta,double y[])
{
    double* x;
    double x0,temp,deltaX,temp2;
    int i,j;

    //srand(time(0));
    x = (double *)malloc(sizeof(double) * N);

    x0 = 2 * (rand()/(double)RAND_MAX);
    x[0] = x0;
    for (i = 0;i<(N-2);i++)
    {
        temp = rand()/(double)RAND_MAX;
        deltaX = Delta*(temp - 0.5)*2;
        x[i+1] = x[i] + deltaX;
        while (x[i+1]>a)
        {
            x[i+1] = x[i+1] - a;
        }
        while (x[i+1]<0)
        {
            x[i+1] = x[i+1] + a;
        }
        temp2 = rand()/(double)RAND_MAX;
        if (GetAlpha(x[i],x[i+1])<temp2)
        {
            x[i+1] = x[i];
        }
    }
    y = x;
    free(x);
    return y;
}

// 数组求和函数
// 对数组进行求和，返回求和值
double sum(double *Mat,int length)
{
    double r;
    int i;

    r = 0.0;
    for (i=0;i<length;i++)
    {
	r = r + Mat[i];
    }
    return r;
}

//求均方根的函数
double GetAQS(double* Intm,int L)
{
    int i;
    double QS,AQS;

    QS = 0.0;

    for (i=0;i<L;i++)
    {
	QS = QS + pow(Intm[i],2);
    }
    AQS = QS/L;

    return AQS;
}


//求sigma的函数
//返回sigma的值
double GetSigma(double a,double Delta,int N0,int step,int m,int D,int L)
{
    double*  Markov_temp;
    double*  Markov_temp1;
    //double*  Markov_temp2;
    double**   Markov;
    long int i,j,k,l,s;
    int N;
    double Intm[L];
    double Intm_aver,AQS,sigma;
    double temp1,temp2;

    //参数初始化
    N = N0 + m*step;
    temp1 = 0.0;
    temp2 = 0.0;
    //为一维数组Markov_temp分配空间
    //Markov_temp = (double *)malloc(sizeof(double) * N);
    //为一维数组Markov_temp1分配空间
    Markov_temp1 = (double *)malloc(sizeof(double) * m);
    //为二维数组Markov分配空间
    Markov = (double **)malloc(sizeof(double *) * D);
    for (i=0;i<D;i++)
    {
        Markov[i] = (double *)malloc(sizeof(double) * m);
    }

    for (i=0;i<L;i++)
    {
        for (j=0;j<D;j++)
        {
            Markov_temp = GetMarkov(a,N,Delta,Markov_temp);
            for(k=0;k<m;k++)
            {
                Markov[j][k] = Markov_temp[N0 + k*step];
            }
        }
        for (l=0;l<D;l++)
        {
            for (s=0;s<m;s++)
            {
                Markov[l][s] = 1 + (Markov[l][s]/2);
            }
        }
        for (l=0;l<m;l++)
        {
            Markov_temp1[l] = Markov[0][l];
        }
         
        //Markov_temp = Equal(m,Markov,Markov_temp);
        for (l=0;l<(D-1);l++)
        {
            for (s=0;s<m;s++)
            {
                Markov_temp1[s] = Markov_temp1[s] * Markov[l+1][s];
            }
        }
        temp1 = sum(Markov_temp1,m);
        temp2 = 1.0 - exp((-1)*a);
        Intm[i] = (temp1*(pow(temp2,D)))/m;
        printf("i now is %ld \n",i);
        //fflush(stdout);
    }
    for (i=0; i<D; i++)
    {
        free(*(Markov + i));
    }
    Intm_aver = (sum(Intm,L))/L;
    AQS = GetAQS(Intm,L);
    sigma = sqrt(AQS - pow(Intm_aver,2));
    //free(Markov_temp);
    free(Markov_temp1);

    return sigma;
}

//求两个一维数组前m位的协方差
double GetCov(double Markov1[],double Markov2[],int m)
{
    double temp1[m];
    int i,j;
    double E1,E2,answer;
    
    for (i=0;i<m;i++)
    {
        temp1[i] = Markov1[i]*Markov2[i];
    }
    E1 = sum(temp1,m)/m;
    E2 = (sum(Markov1,m)/m)*(sum(Markov2,m)/m);
    
    answer = E1 - E2;
    
    return answer;
}

int GetPassRate(double a,int N,double Delta)
{
    double* x;
    double x0,temp,deltaX,temp2;
    int i,j,Fail_count,Success_count;
    
    Fail_count = 0;
    Success_count = 0;
    //srand(time(0));
    //给一维数组x创建储存空间
    x = (double *)malloc(sizeof(double) * N);
    
    x0 = 2 * (rand()/(double)RAND_MAX);
    x[0] = x0;
    for (i = 0;i<(N-2);i++)
    {
        temp = rand()/(double)RAND_MAX;
        deltaX = Delta*(temp - 0.5)*2;
        x[i+1] = x[i] + deltaX;
        while (x[i+1]>a)
        {
            x[i+1] = x[i+1] - a;
        }
        while (x[i+1]<0)
        {
            x[i+1] = x[i+1] + a;
        }
        temp2 = rand()/(double)RAND_MAX;
        if (GetAlpha(x[i],x[i+1])<temp2)
        {
            x[i+1] = x[i];
            Fail_count = Fail_count + 1;
        }
    }
    free(x);
    Success_count = N - Fail_count;
    return Success_count;
}

double GetIntm(double a,double Delta,int N0,int step,int m,int D,int L)
{
    double*  Markov_temp;
    double*  Markov_temp1;
    //double*  Markov_temp2;
    double**   Markov;
    long int i,j,k,l,s;
    int N;
    double Intm[L];
    double Intm_aver;
    double temp1,temp2;
    
    //参数初始化
    N = N0 + m*step;
    temp1 = 0.0;
    temp2 = 0.0;
    //为一维数组Markov_temp分配空间
    //Markov_temp = (double *)malloc(sizeof(double) * N);
    //为一维数组Markov_temp1分配空间
    Markov_temp1 = (double *)malloc(sizeof(double) * m);
    //为二维数组Markov分配空间
    Markov = (double **)malloc(sizeof(double *) * D);
    for (i=0;i<D;i++)
    {
        Markov[i] = (double *)malloc(sizeof(double) * m);
    }
    
    for (i=0;i<L;i++)
    {
        for (j=0;j<D;j++)
        {
            Markov_temp = GetMarkov(a,N,Delta,Markov_temp);
            for(k=0;k<m;k++)
            {
                Markov[j][k] = Markov_temp[N0 + k*step];
            }
        }
        for (l=0;l<D;l++)
        {
            for (s=0;s<m;s++)
            {
                Markov[l][s] = 1 + (Markov[l][s]/2);
            }
        }
        for (l=0;l<m;l++)
        {
            Markov_temp1[l] = Markov[0][l];
        }
        
        //Markov_temp = Equal(m,Markov,Markov_temp);
        for (l=0;l<(D-1);l++)
        {
            for (s=0;s<m;s++)
            {
                Markov_temp1[s] = Markov_temp1[s] * Markov[l+1][s];
            }
        }
        temp1 = sum(Markov_temp1,m);
        temp2 = 1.0 - exp((-1)*a);
        Intm[i] = (temp1*(pow(temp2,D)))/m;
        printf("i now is %ld \n",i);
        //fflush(stdout);
    }
    //获得蒙特卡洛积分值
    Intm_aver = (sum(Intm,L))/L;
    
    for (i=0; i<D; i++)
    {
        free(*(Markov + i));
    }
    free(Markov_temp1);
    
    return Intm_aver;
}
