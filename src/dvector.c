#include "dvector.h"



DVector initDVector(int s){
	DVector v = {
		.maxSize = s,
		.count = 0,
		.data = malloc(s*sizeof(double))
	};

	return v;
}

void deleteDVector(DVector* v){
	v->maxSize = 0;
	v->count = 0;
	free(v->data);
	v->data=NULL;
}




void dVectorPush(DVector* v,double val){
	
	printf("to be pushed : %lf\n",val);
	if (v->count==v->maxSize){
		printf("ERROR : DVector is full");
		exit(-1);
	}
	
	v->data[v->count++]=val;
}


double dVectorPop(DVector* v){

	printf("to be popped : %lf\n",v->data[v->count-1]);
	if (!v->count){
		printf("ERROR : DVector is empty");
		exit(-1);
	}

	return v->data[--v->count];
}

void printDVector(DVector* v){
	printf("[");
	for (int i=0;i < v->count;i++){

		printf("%lf",v->data[i]);

		if (i!=v->count-1)
			printf(",");
	}
	printf("]\n");
}





