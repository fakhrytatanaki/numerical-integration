#include "mathfuncs.h"

const char* mathfunc_names[] = {"pow","exp","ln","sin","cos","sinh","cosh","asin","acos","asinh","acosh","tan","atan","tanh","atanh"};
const int mathfunc_count = sizeof(mathfunc_names)/sizeof(mathfunc_names[0]);

mathfunc_t** getMathFuncs(){
	mathfunc_t** funcs = (mathfunc_t**) malloc(mathfunc_count*sizeof(void*));
	for (int i=0;i < mathfunc_count;i++){
		funcs[i] = (mathfunc_t*) malloc(sizeof(mathfunc_t));
		funcs[i]->id=MATHFUNC_ID_START+i;
		funcs[i]->nargs=1;
	}

	funcs[0]->nargs=2;
	funcs[0]->func2a = pow;
	funcs[1]->func1a = exp;
	funcs[2]->func1a = log;
	funcs[3]->func1a = sin;
	funcs[4]->func1a = cos;
	funcs[5]->func1a = sinh;
	funcs[6]->func1a = cosh;
	funcs[7]->func1a = asin;
	funcs[8]->func1a = acos;
	funcs[9]->func1a = asinh;
	funcs[10]->func1a = acosh;
	funcs[11]->func1a = tan;
	funcs[12]->func1a = atan;
	funcs[13]->func1a = tanh;
	funcs[14]->func1a = atanh;
	return funcs;
}



Node* constructFuncNameTrie(mathfunc_t** funcs){
	Node* root = constructTrie(mathfunc_count,mathfunc_names);	

	linkObjectsToTrieNodes(root,mathfunc_names,(void**)funcs,mathfunc_count);
	return root;
}

void cleanup(mathfunc_t** funcs){
	int n = sizeof(funcs);

	for (int i=0;i < n;i++)
		free(funcs[i]);

	free(funcs);
}


Node* constructVarTrie(int strc,const char** strv){

	Node* varTrie = constructTrie(strc,strv);
	Node* found;

	for (int i=0;i < strc;i++){
		strSearch(strv[i],varTrie,&found);	
		found->key = i+VAR_ID_START;
	}
	
	return varTrie;
}




