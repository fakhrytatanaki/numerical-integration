#ifndef MATHFUNCS_STRUCT_H
#define MATHFUNCS_STRUCT_H
struct _mathfunc_t{
	int id;
	int nargs;
	 double (*func1a)(double);
	 double (*func2a)(double,double);
};

struct atomic_expression{
	double lval,rval;
	struct _mathfunc_t* func;
};

struct full_function{
	double* varlist;
	int varc;
	struct atomic_expression* seq;
	int seqc;
}; 

typedef struct _mathfunc_t mathfunc_t;
typedef struct atomic_expression atex;
typedef struct full_function full_func_t;

#endif
