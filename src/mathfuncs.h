#pragma once

#ifndef MATHFUNCS_H
#define MATHFUNCS_H
#include "strsearch.h"
#include <math.h>
#include "mathfuncs_struct.h"
#define MATHFUNC_ID_START 16
#define VAR_ID_START 3

extern const char* mathfunc_names[]; 
extern const int mathfunc_count;

mathfunc_t** getMathFuncs();
Node* constructFuncNameTrie(mathfunc_t** funcs);
void cleanup(mathfunc_t** funcs);
Node* constructVarTrie(int strc,const char** strv);

#endif 


