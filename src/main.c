#include "math_expr_parser.h"
#include "numerical_integ.h"
//Numerical Integration
//Fakhry Hussein Tatanaki 100-1271 T0-2

psarr_t inputExp; //struct for postfix expression objects
mathfunc_t** funcs; //struct for math functions
const char* testvars[] = {"x"}; //the name of the variable, only one is needed for the integration
Node* varTrie; //tree data structure for searching variable names in the parsing process
Node* funcTrie; //prefix tree data structure fot searching mathfunction names in the parsing process

double toBeIntegrated(double input){ //a function that will be integrated
	return evaluateFunction(inputExp,&input,funcs); //evaluateFunction evaluates a postfix object from a parsed expression
	//you can remove the parser and put your own hardcoded math function in the place of evaluateFunction
}

int main(int argc,const char** argv){
	
	
	varTrie = constructVarTrie(1,testvars);
	funcs = getMathFuncs();
	funcTrie = constructFuncNameTrie(funcs);


	double a,b; //lower bound and upper bound respectively
	int n; //number of subdivisions
	double final; //result
	char sel; //for selecting options

	char in[128],out[128];	//input string for expression and output postfix string	
	out[0]=0; //clearing the string 

	printf("please input an expression : ");
	scanf("%s",in);
	
	toPostFix(in,out,128,funcTrie,varTrie);
	inputExp = parsePSString(out); //parse postfix string into postfix expression objects

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
