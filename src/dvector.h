#ifndef DVECTOR_H
#define DVECTOR_H
#include <stdlib.h>
#include <stdio.h>
#include "dvector_struct.h"

extern DVector initDVector(int s);
extern void deleteDVector(DVector* v);
extern void dVectorPush(DVector* v,double val);
extern double dVectorPop(DVector* v);
extern void printDVector(DVector* v);


#endif
