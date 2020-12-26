#include <stdio.h>
#include "treenode.h"
#include "strsearch.h"
#include "vector.h"
#include "mathfuncs.h"

int main(){
	mathfunc_t* funcs = getMathFuncs();
	Node* n = constructFuncNameTrie(funcs);
	Node* found;
	int f;

	

	for (int i=0;i<funcsCount;i++){
		strSearch(mathfunc_names[i],n,&found);

		// printf("obj addr. test: %x\n",found->obj);
		// printf("key : %d\n",((mathfunc_t*)found->obj)->id);
	}
	
	free(funcs);
	
	return 0;
}
