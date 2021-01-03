
#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <stdio.h>
#include "vector_struct.h"
#define AS_INT 0
#define AS_INT_HEX 1
#define AS_CHAR 2

extern Vector initVector(int s);
extern void deleteVector(Vector* v);
extern void vectorPush(Vector* v,int val);
extern int vectorPop(Vector* v);
extern void printVector(Vector* v,int flag);





#endif
