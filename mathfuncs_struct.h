#ifndef MATHFUNCS_STRUCT_H
#define MATHFUNCS_STRUCT_H
#define MATHFUNCS_OBJ_VAL 0
#define MATHFUNCS_OBJ_VAR 1
#define MATHFUNCS_OBJ_PRI 2
#define MATHFUNCS_OBJ_FUNC 3

struct _mathfunc_t{
	int id;
	int nargs;
	 double (*func1a)(double);
	 double (*func2a)(double,double);
};


typedef struct _mathfunc_t mathfunc_t;

typedef struct {
	int type;
	int key;
	double val;
} expobj_t;

typedef struct {
	int size;
	int count;
	expobj_t* data;
} psarr_t;
#endif
