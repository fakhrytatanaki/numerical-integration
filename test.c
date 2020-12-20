#include <stdio.h>
#include "treenode.h"
#include "strsearch.h"
#include "vector.h"
#include "mathfuncs.h"

int main(){
	getMathFuncs(mathfuncs);
	Node* tree = constructFuncNameTrie(mathfuncs);

	Node* found;
	for (int i=0;i < 7;i++){
		strSearch(mathfunc_names[i],tree,&found);
		printf("%d\n",((mathfunc_t*)found->obj)->id);
	}

	return 0;
}
