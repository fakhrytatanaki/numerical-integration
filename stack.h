#define AS_INT 0
#define AS_INT_HEX 1
#define AS_CHAR 2
#include <stdlib.h>
#include <stdio.h>

typedef struct{
	int* data;
	int maxSize;
	int top;
} Stack;

Stack initStack(int n){
	Stack s = {
		.data = malloc(n*sizeof(int)),
		.maxSize = n,
		.top=0
		};
	return s;
}

void stackPush(Stack* s,int val){
	if (s->top==s->maxSize){
		printf("ERROR : Stack is full");
		exit(-1);
	}
	
	s->data[s->top++]=val;
}


int stackPop(Stack* s){
	if (!s->top){
		printf("ERROR : Stack is empty");
		exit(-1);
	}

	return s->data[--s->top];
}

void deleteStack(Stack* s){
	free(s->data);
	s->data=NULL;
	s->maxSize=0;
	s->top=0;
}

void displayStack(Stack* s,int flag){
	printf("$ ");	
	for (int i=0;i < s->top;i++){
		
		switch (flag){
			case AS_CHAR:
				printf("%c ",s->data[i]);
				break;
			case AS_INT_HEX:
				printf("%x ",s->data[i]);
				break;
			default:
				printf("%d ",s->data[i]);
		}
}
	printf("\n");
}

