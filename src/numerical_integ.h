#ifndef NUMERICAL_INTEG_H
#define NUMERICAL_INTEG_H
	

double trapez_integ(int a,int b,double h,double (*func)(double));

double simpson_third(int a,int b,double h,double (*func)(double));

double simpson_three_eighth(int a,int b,double h,double (*func)(double));

#endif
