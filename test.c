#include <stdio.h>
#include "treenode.h"
#include "strsearch.h"
#include "vector.h"
#include "mathfuncs.h"

int main(){
	mathfunc_t funcs[funcsCount];
	Node* n = constructFuncNameTrie(funcs);
	Node* found;

	for (int i=0;i<funcsCount;i++)
		printf("%s\n",mathfunc_names[i]);

	for (int i=0;i<funcsCount;i++){
		strSearch(mathfunc_names[i],n,&found);
		printf("%d\n",((mathfunc_t*)found->obj)->id);
	}
	
	return 0;
}
