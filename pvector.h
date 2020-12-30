#include <stdlib.h>
#include <stdio.h>
#ifndef PVECTOR_H
#define PVECTOR_H 
typedef struct {
	int maxSize;
	int count;
	int** data;
} PVector;

PVector initPVector(int s){
	PVector v = {
		.maxSize = s,
		.count = 0,
		.data = malloc(s*sizeof(int*))
	};

	return v;
}

void deletePVector(PVector* v){
	v->maxSize = 0;
	v->count = 0;
	free(v->data);
	v->data=NULL;
}




void PVectorPush(PVector* v,int* val){
	
	if (v->count==v->maxSize){
		printf("ERROR : PVector is full");
		exit(-1);
	}
	
	v->data[v->count++]=val;
}


int* PVectorPop(PVector* v){

	if (!v->count){
		printf("ERROR : PVector is empty");
		exit(-1);
	}

	return v->data[--v->count];
}

void printPVector(PVector* v){
	printf("[");
	for (int i=0;i < v->count;i++){

	printf("%x",v->data[i]);

		if (i!=v->count-1)
			printf(",");
	}
	printf("]\n");
}





#endif

