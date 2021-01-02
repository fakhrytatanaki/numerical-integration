#include "numerical_integ.h"	

double trapez_integ(int a,int b,double h,double (*func)(double)){
	double diff = b - a;
	int n = diff/h;

	double res;
	double sum = 0;

	for (int i=0;i < n-1;i++)
		sum+=func(a+h*i);
	
	res = (h/2.0)*(func(a) + func(b) + 2*sum);
	return res;
}

double simpson_third(int a,int b,double h,double (*func)(double)){

	double diff = b - a;
	int n = diff/h;

	double res;
	double sum=0;

	for (int i=1;i < n;i+=2)
			sum+=4*func(a+h*i);
	
	for (int i=0;i < n-1;i+=2)
			sum+=2*func(a+h*i);
	
	
	res = (h/3.0)*(func(a) + func(b) + sum);
	return res;
}

double simpson_three_eighth(int a,int b,double h,double (*func)(double)){

	double diff = b - a;
	int n = diff/h;

	double res;
	double sum=0;

	for (int i=1;i < n;i+=3)	
		sum +=  2*func(a+h*i);

	for (int i=1;i < n;i+=3)	
		sum +=  3*(func(a+h*(i-2)) + func(a+h*(i-1)));

	res = (3.0*h/8.0)*(func(a) + func(b) + sum);
	return res;
}

