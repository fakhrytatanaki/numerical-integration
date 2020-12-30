#include <stdio.h>
#include <math.h>
#include "numerical_integ.h"


double f1(double x){
	return cos(pow(x,2));
};

double f2(double x){
	return exp(-pow(x,2));
}

double halfcircle(double x){
	return pow(1 - x*x,0.5);
}




int main(){	

	double a,b,h;
	char sel;
	printf("lower bound : ");
	scanf("%lf",&a);
	printf("upper bound : ");
	scanf("%lf",&b);
	printf(" step length :  ");
	scanf("%lf",&h);

	printf("method of integration:\n");
	printf("A : trapezoidal\n");
	printf("B : Simpsons 1/3 rule\n");
	printf("C : Simpsons 3/8 rule\n");
	fflush(stdin);
	sel = getchar();

	if (sel == 'a'){
		printf("result : %lf",trapez_integ(a,b,h,f1));
	}
	else if (sel == 'b'){

		printf("result : %lf",simpson_third(a,b,h,f1));
	}
	else if (sel == 'c'){

		printf("result : %lf",simpson_three_eighth(a,b,h,f1));
	}
	printf("\n");
	


}
