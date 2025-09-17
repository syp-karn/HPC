#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<time.h>

static long num_steps = 10000000;
double step;


double parallel_pi(double step) {
    double sum = 0.0;
    omp_set_num_threads(4);
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < num_steps; i++) {
        double x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }
    double pi = step * sum;
    return pi;
}



void main()
{
    int i; double x,pi,sum = 0.0;
    step = 1.0/(double) num_steps;
    double par_pi = parallel_pi(step);
    for (i=0;i<num_steps;i++)
    {
        x = (i+0.5)*step;
        sum = sum + 4.0/(1.0+x*x);
    }

    pi = step*sum;
    printf("Pi value sequential: %lf\n",pi);
    printf("Pi value parallel: %lf",par_pi);
}