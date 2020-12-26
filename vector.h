#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <stdio.h>

#define AS_INT 0
#define AS_INT_HEX 1
#define AS_CHAR 2

typedef struct {
	int maxSize;
	int count;
	int* data;
} Vector;

Vector initVector(int s);
void deleteVector(Vector* v);
void vectorPush(Vector* v,int val);
int vectorPop(Vector* v);
void printVector(Vector* v,int flag);


#endif
