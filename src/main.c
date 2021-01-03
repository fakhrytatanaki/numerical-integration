#include "math_expr_parser.h"
#include "numerical_integ.h"

psarr_t inputExp;
mathfunc_t** funcs;
const char* testvars[] = {"x"};
Node* varTrie;
Node* funcTrie; 

double func(double input){
	return evaluateFunction(inputExp,&input,funcs);
}

int main(int argc,const char** argv){
	
	
	varTrie = constructVarTrie(1,testvars);
	funcs = getMathFuncs();
	funcTrie = constructFuncNameTrie(funcs);


	double a,b,h;
	double final;
	//char sel;

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
	printf(" step size : ");
	scanf("%lf",&h);
	final = simpson_third(a,b,h,func);
	printf("result = %lf\n",final);
	return 0;
}
