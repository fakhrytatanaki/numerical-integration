#include "math_expr_parser.h"
int main(int argc,char** argv){
	


	char out[128];			
	out[0]=0;
	
	const char* testvars[] = {"x","y","john"};
	Node* varTrie = constructVarTrie(3,testvars);
	mathfunc_t** funcs = getMathFuncs();
	
	Node* funcTrie = constructFuncNameTrie(funcs);
	toPostFix(argv[1],out,128,funcTrie,varTrie);
	printPostfix(out);
	psarr_t test = parsePSString(out);
	double final = evaluateFunction(test,NULL,funcs);
	printf("RESULT : %lf\n",final);	
	
	
	return 0;
}
