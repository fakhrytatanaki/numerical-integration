#include "mathfuncs.h"
#include <stdio.h>
#include "treenode.h"
#include "strsearch.h"
#include "vector.h"

int main(){
	mathfunc_t** funcs = getMathFuncs();
	Node* n = constructFuncNameTrie(funcs);
	Node* found;
	int f;

	

	for (int i=0;i<funcsCount;i++){
		f = strSearch(mathfunc_names[i],n,&found);
		printf("val : %d\n",((mathfunc_t*) (found->obj))->id );
	}
	
	deleteFuncsFromHeap(funcs);	

	return 0;
}
