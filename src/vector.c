#include "vector.h"


Vector initVector(int s){
	Vector v = {
		.maxSize = s,
		.count = 0,
		.data = malloc(s*sizeof(int))
	};

	return v;
}

void deleteVector(Vector* v){
	v->maxSize = 0;
	v->count = 0;
	free(v->data);
	v->data=NULL;
}




void vectorPush(Vector* v,int val){
	
	printf("to be pushed : %c : %d\n",val,val);
	if (v->count==v->maxSize){
		printf("ERROR : Vector is full");
		exit(-1);
	}
	
	v->data[v->count++]=val;
}


int vectorPop(Vector* v){

	printf("to be popped : %c : %d\n",v->data[v->count-1],v->data[v->count-1]);
	if (!v->count){
		printf("ERROR : Vector is empty");
		exit(-1);
	}

	return v->data[--v->count];
}

void printVector(Vector* v,int flag){
	printf("[");
	for (int i=0;i < v->count;i++){

                switch (flag){
                        case AS_CHAR:
                                printf("%c",v->data[i]);
                                break;
                        case AS_INT_HEX:
                                printf("%x",v->data[i]);
                                break;
                        default:
                                printf("%d",v->data[i]);
		}

		if (i!=v->count-1)
			printf(",");
	}
	printf("]\n");
}





