#pragma once

#ifndef MATHFUNCS_H
#define MATHFUNCS_H
#include "strsearch.h"
#include <math.h>
#include "mathfuncs_struct.h"
#define MATHFUNC_ID_START 16


const char* mathfunc_names[] = {"pow","exp","ln","sin","cos","sinh","cosh","asin","acos","asinh","acosh"};
const int mathfunc_count = sizeof(mathfunc_names)/sizeof(mathfunc_names[0]);

mathfunc_t** getMathFuncs(){
	mathfunc_t** funcs = malloc(mathfunc_count*sizeof(void*));
	for (int i=0;i < mathfunc_count;i++){
		funcs[i] = malloc(sizeof(mathfunc_t));
		funcs[i]->id=MATHFUNC_ID_START+i;
		funcs[i]->nargs=1;
	}

	(*funcs)->nargs=2;
	funcs[0]->func2a = pow;
	funcs[1]->func1a = exp;
	funcs[2]->func1a = log;
	funcs[3]->func1a = sin;
	funcs[4]->func1a = cos;
	funcs[5]->func1a = sinh;
	funcs[6]->func1a = cosh;
	funcs[7]->func1a = sin;
	funcs[8]->func1a = cos;
	funcs[9]->func1a = sinh;
	funcs[10]->func1a = cosh;
	return funcs;
}



Node* constructFuncNameTrie(mathfunc_t** funcs){
	Node* root = constructTrie(mathfunc_count,mathfunc_names);	

	linkObjectsToTrieNodes(root,mathfunc_names,(void**)funcs,mathfunc_count);
	return root;
}

void deleteFuncsFromHeap(mathfunc_t** funcs){
	int n = sizeof(funcs);

	for (int i=0;i < n;i++)
		free(funcs[i]);

	free(funcs);
}
#endif 


