#ifndef MATH_EXPR_PARSER_H
#define MATH_EXPR_PARSER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vector.h"
#include "dvector.h"
#include "strsearch.h"
#include "mathfuncs.h"

extern void charcat(char* str,char c);
extern int precedence(char a);
extern void printPostfix(const char* out);
extern void toPostFix(char* strIn,char* strOut,int l,Node* funcTrie,Node* varTrie);
extern double parseStringToDouble(const char* string);
extern double evaluateFunction(psarr_t in,double* i_arr,mathfunc_t** funcs);
extern double rmul_pow(double x,int y);
extern psarr_t parsePSString(const char* str);


#endif
