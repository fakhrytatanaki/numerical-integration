#pragma once
#include "strsearch.h"
#include <math.h>
#ifndef MATHFUNCS_H
#define MATHFUNCS_H


typedef struct{
	int id;
	int nargs;
	double (*func1a)(double);
	double (*func2a)(double,double);
} mathfunc_t;

const char* mathfunc_names[] = {"pow","exp","ln","sin","cos","sinh","cosh","asin","acos","asinh","acosh"};
int funcsCount = sizeof(mathfunc_names)/sizeof(mathfunc_names[0]);

void getMathFuncs(mathfunc_t* mathfuncs){
	for (int i=0;i < funcsCount;i++){
		(mathfuncs+i)->id=i;
		(mathfuncs+i)->nargs=1;
	}

	mathfuncs->nargs=2;
	(mathfuncs+0)->func2a = pow;
	(mathfuncs+1)->func1a = exp;
	(mathfuncs+2)->func1a = log;
	(mathfuncs+3)->func1a = sin;
	(mathfuncs+4)->func1a = cos;
	(mathfuncs+5)->func1a = sinh;
	(mathfuncs+6)->func1a = cosh;
	(mathfuncs+7)->func1a = sin;
	(mathfuncs+8)->func1a = cos;
	(mathfuncs+9)->func1a = sinh;
	(mathfuncs+10)->func1a = cosh;
}



Node* constructFuncNameTrie(mathfunc_t* funcs){
	Node* root = constructTrie(funcsCount,mathfunc_names);	

		linkObjectsToTrieNodes(root,mathfunc_names,funcs);

			printf("end\n");
	return root;
}

#endif 
