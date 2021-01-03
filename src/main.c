#include "math_expr_parser.h"
#include "numerical_integ.h"

psarr_t inputExp;
mathfunc_t** funcs;
const char* testvars[] = {"x"};
Node* varTrie;
Node* funcTrie; 

double toBeIntegrated(double input){
	return evaluateFunction(inputExp,&input,funcs);
}

int main(int argc,const char** argv){
	
	
	varTrie = constructVarTrie(1,testvars);
	funcs = getMathFuncs();
	funcTrie = constructFuncNameTrie(funcs);


	double a,b;
	int n;
	double final;
	char sel;

	char in[128],out[128];			
	out[0]=0;

	printf("please input an expression : ");
	scanf("%s",in);
	
	toPostFix(in,out,128,funcTrie,varTrie);
	inputExp = parsePSString(out);

	printf(" lower bound : ");
	scanf("%lf",&a);
	printf(" upper bound : ");
	scanf("%lf",&b);
	printf(" number of subdivisions : ");
	scanf("%d",&n);
	printf("select a method for numerical integration :\n\n");
	
	printf("A - Riemann\n");
	printf("B - Trapezoid\n");
	printf("C - Simpson's 1/3\n");
	printf("D - Simpson's 3/8\n");
	printf("\nyour option : ");

	fflush(stdin);
	sel = getchar();

	printf("\n");
	printf("computing using ");
	switch(sel){
		case 'A':
		case 'a':

			printf("Riemann's rule");
			final = riemann_integ(a,b,n,toBeIntegrated);
			break;
			
			
		case 'B':
		case 'b':

			printf("trapezoid rule");
			final = trapez_integ(a,b,n,toBeIntegrated);
			break;


		case 'C':
		case 'c':

			printf("Simpson's 1/3 rule");
			final = simpson_third(a,b,n,toBeIntegrated);
			break;


		case 'D':
		case 'd':

			printf("Simpson's 3/8 rule");
			final = simpson_three_eighth(a,b,n,toBeIntegrated);
			break;

	}	

	printf("\n\n");

	printf("result = %.4lf unit^2 \n\n",final);
	return 0;
}
