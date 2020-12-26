#pragma once

#ifndef MATHFUNCS_H
#define MATHFUNCS_H
#include "strsearch.h"
#include <math.h>

typedef struct{
	int id;
	int nargs;
	double (*func1a)(double);
	double (*func2a)(double,double);
} mathfunc_t;

const char* mathfunc_names[] = {"pow","exp","ln","sin","cos","sinh","cosh","asin","acos","asinh","acosh"};
int funcsCount = sizeof(mathfunc_names)/sizeof(mathfunc_names[0]);

mathfunc_t* getMathFuncs();
Node* constructFuncNameTrie(mathfunc_t* funcs);

#endif 