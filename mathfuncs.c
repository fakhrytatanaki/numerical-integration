
// typedef struct{
// 	int id;
// 	int nargs;
// 	double (*func1a)(double);
// 	double (*func2a)(double,double);
// } mathfunc_t;


#include "mathfuncs.h"

mathfunc_t* getMathFuncs(){
	mathfunc_t* funcs = malloc(sizeof(mathfunc_t)*funcsCount);
	for (int i=0;i < funcsCount;i++){
		
		(funcs+i)->id=i;
		(funcs+i)->nargs=1;
	}

	funcs->nargs=2;
	(funcs+0)->func2a = pow;
	(funcs+1)->func1a = exp;
	(funcs+2)->func1a = log;
	(funcs+3)->func1a = sin;
	(funcs+4)->func1a = cos;
	(funcs+5)->func1a = sinh;
	(funcs+6)->func1a = cosh;
	(funcs+7)->func1a = sin;
	(funcs+8)->func1a = cos;
	(funcs+9)->func1a = sinh;
	(funcs+10)->func1a = cosh;
	return funcs;
}



Node* constructFuncNameTrie(mathfunc_t* funcs){
	Node* root = constructTrie(funcsCount,mathfunc_names);	
	linkObjectsToTrieNodes(root,mathfunc_names,funcs,funcsCount);
	return root;
}
