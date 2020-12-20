#include "strsearch.h"
#ifndef MATHFUNCS_H
#define MATHFUNCS_H


typedef struct{
	int id;
	int nargs;
} mathfunc_t;

const char* mathfunc_names[7] = {"pow","exp","ln","sin","cos","sinh","cosh"};
mathfunc_t mathfuncs[7];

void getMathFuncs(mathfunc_t* mathfuncs){
	for (int i=0;i < 7;i++){
		(mathfuncs+i)->id=i;
		(mathfuncs+i)->nargs=1;
	}

	mathfuncs->nargs=2;
}


Node* constructFuncNameTrie(mathfunc_t* funcs){
	Node* root = constructTrie(7,mathfunc_names);	
	Node* found;

	]for (int i=0;i < 7;i++){
		strSearch(mathfunc_names[i],root,&found);
		found->obj = (void*) (funcs+i);
	}	
	return root;
}

#endif 
