#ifndef NUMERICAL_INTEG_H
#define NUMERICAL_INTEG_H
	

double riemann_integ(int a,int b,int n,double (*func)(double));

double trapez_integ(int a,int b,int n,double (*func)(double));

double simpson_third(int a,int b,int n,double (*func)(double));

double simpson_three_eighth(int a,int b,int n,double (*func)(double));

#endif
