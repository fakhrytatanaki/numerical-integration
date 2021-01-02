#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vector.h"
#include "dvector.h"
#include "strsearch.h"
#include "mathfuncs.h"

#define ui8 unsigned char
void charcat(char* str,char c);
int precedence(char a);
void printPostfix(const char* out);
void toPostFix(char* strIn,char* strOut,int l,Node* funcTrie,Node* varTrie);
double parseStringToDouble(const char* string);
double evaluateFunction(psarr_t in,double* i_arr,mathfunc_t** funcs);
double rmul_pow(double x,int y);
psarr_t parsePSString(const char* str);

int main(int argc,char** argv){
	


	char out[128];			
	out[0]=0;
	
	const char* testvars[] = {"x","y","john"};
	Node* varTrie = constructVarTrie(3,testvars);
	mathfunc_t** funcs = getMathFuncs();
	
	Node* funcTrie = constructFuncNameTrie(funcs);
	toPostFix(argv[1],out,128,funcTrie,varTrie);
	printPostfix(out);
	psarr_t test = parsePSString(out);
	double final = evaluateFunction(test,NULL,funcs);
	printf("RESULT : %lf\n",final);	
	
	
	return 0;
}


void charcat(char* str,char c){ //concatenates a character to a string
	char tmp[2];
	tmp[1]=0;
	tmp[0] = c;
	strcat(str,tmp);
}



int precedence(char a){ // evaluates the precedence of the operator
	switch(a){
		case '+':
		case '-':
			return 1;
		case '*':
		case '/':
			return 2;
		case '~':
			return 3;

		default:
			if (-a >= MATHFUNC_ID_START && -a < MATHFUNC_ID_START + mathfunc_count)
				return 4;

			return -1; // -1 is returned as precedence if the character is not a operator or a function ID

	}
}


void printPostfix(const char* out){
	int i=0;
	while (out[i]!=0){
		if (-out[i] >= MATHFUNC_ID_START && -out[i] < MATHFUNC_ID_START + mathfunc_count)
			printf("%s",mathfunc_names[-out[i] - MATHFUNC_ID_START]);
	
		else
			printf("%c",out[i]);
		i++;
	}
	printf("\n");
}

double rmul_pow(double x,int y){
	double res=1;
	while (y < 0){
		res=res/x;
		y++;
	}

	while (y > 0){
		res=res*x;
		y--;
	}

	return res;
};


double parseStringToDouble(const char* string){
	int n = strlen(string);
	int order;
	int sign= (string[0]=='-')? -1:1;

	ui8 isNegative = sign==-1;
	ui8 pointFound = 0;
	double res = 0;
	
	for (int i=0 + isNegative;i < n;i++){

		if (string[i] == '.'){
			order=i-isNegative-1;
			pointFound = 1;
			break;
		}

		if (!(string[i] >= '0' && string[i] <= '9')){
			printf("DOUBLE PARSE ERROR : \'%c\' is not a decimal ",string[i]);
			exit(-1);
		}
		
	

	} 

	if (!pointFound)
		order = n-1-isNegative;
	
	for (int i=0+isNegative;i < n;i++){

		if (string[i] == '.'){
			continue;
		}
		res+=(string[i]-'0')*rmul_pow(10,order--);

	}

	return sign*res;
	
}

psarr_t parsePSString(const char* str){

	int n = strlen(str);

	psarr_t s = {
		.size=n,
		.count=0,
		.data  = malloc(n*sizeof(expobj_t))
	};

	char tmp[n];
	tmp[0]=0;

	for (int i=0;i < n;i++){
		
		if (str[i]=='['){

			i++;
			while (str[i]!=']' && i < n)
				charcat(tmp,str[i++]);

			s.data[s.count].type =  MATHFUNCS_OBJ_VAL;
			s.data[s.count].val =  parseStringToDouble(tmp);
			tmp[0]=0;
			s.count++;
			
		}


		else if (str[i]=='$'){
			s.data[s.count].type = MATHFUNCS_OBJ_VAR;
			s.data[s.count++].key = -str[++i];
		}

		else if (str[i] > 0) {
			s.data[s.count].type =	MATHFUNCS_OBJ_PRI;
			s.data[s.count++].key = str[i];
		}

		else {

			s.data[s.count].type =	MATHFUNCS_OBJ_FUNC;
			s.data[s.count++].key = -str[i];
		}

	}

	return s;

	
}

double evaluateFunction(psarr_t in,double* i_arr,mathfunc_t** funcs){
	DVector values = initDVector(in.count);
	expobj_t* arr = in.data;
	double lval,rval;
	int fInd;

	for (int i=0;i < in.count;i++){
		printf(" expression object : type : %d, key : %d, value:%f\n",arr[i].type,arr[i].key,arr[i].val);
		if (arr[i].type==MATHFUNCS_OBJ_VAL)
			dVectorPush(&values,arr[i].val);

		else if (arr[i].type==MATHFUNCS_OBJ_PRI){

			switch(arr[i].key){
				case '~':
					rval = dVectorPop(&values);
					dVectorPush(&values,-rval);
					break;


				case '+':
					rval =  dVectorPop(&values);
					lval =  dVectorPop(&values);
					dVectorPush(&values,lval + rval);
					break;
				case '-':
					rval =  dVectorPop(&values);
					lval =  dVectorPop(&values);
					dVectorPush(&values,lval - rval);
					break;
				case '*':
					rval =  dVectorPop(&values);
					lval =  dVectorPop(&values);
					dVectorPush(&values,lval*rval);
					break;
				case '/':
					rval =  dVectorPop(&values);
					lval =  dVectorPop(&values);
					dVectorPush(&values,lval/rval);
					break;

				printf("lval : %lf,rval:%lf\n",lval,rval);
			}

		}
		else if (arr[i].type==MATHFUNCS_OBJ_FUNC){

			printf(" FUNCTION FOUND : type : %d, key : %d, value:%f\n",arr[i].type,arr[i].key,arr[i].val);
			fInd= arr[i].key - MATHFUNC_ID_START;

			if (funcs[fInd]->nargs==1){
				
				rval =  dVectorPop(&values);
				dVectorPush(&values,funcs[fInd]->func1a(rval));
				
			}

			else {

				rval =  dVectorPop(&values);
				lval =  dVectorPop(&values);
				dVectorPush(&values,funcs[fInd]->func2a(lval,rval));
			}
		}
	}

	return dVectorPop(&values);
}

void toPostFix(char* strIn,char* strOut,int l,Node* funcTrie,Node* varTrie){ // converts infix (strIn) to postfix notation (strOut)
 //an implementation of the shunting-yard algorithm
 

	assert(funcTrie!=NULL && varTrie!=NULL);
	char tmp;	
	char tmpString[32];
	tmpString[0]=0;


	int n = strlen(strIn); //strlen calculates the size of a string
	Vector s = initVector(n); //initalising a stack
	
	if (l < n){
		//program aborts if the output string is smaller than the input (infix notation string)
		printf("postfix conv. error: output string array too small\n");
		exit(-1);
	}	
	ui8 decimalFlag=0; //flag for indicating the presence of a decimal number
	ui8 pointFlag=0;
	ui8 prevNumFlag=0;

	char c1,c2;
	int p1,p2; // for storing the precedence of 2 operators to be compared
	
	for (int i=0;i < n;i++){  


		c1 = strIn[i];

		printf("cc:%c,i:%d,pnf:%hhu\n",c1,i,prevNumFlag);

		if (c1==' ') // ignore spaces
			continue;

		else if (c1=='$' || c1=='~'){
			printf("sorry, the symbol '%c' is reserved\n",c1);
			exit(-1);
		}

		//printVector(&s,AS_INT);

		if (c1 >= '0' && c1 <='9'){
			
			if (!decimalFlag)
				charcat(strOut,'['); //the open square bracket denotes the beginning of a decimal
			
			decimalFlag=1; //set flag to 1 to indicate the start of a decimal
			charcat(strOut,c1);
			
			if (i==n-1)
				charcat(strOut,']');

		}

		else if (decimalFlag && c1=='.') {

			if (pointFlag){
				printf("floating point parsing error: extra symbol '.'\n");
				exit(-1);
				//if there are more than one point in one decimal, abort program
			}
			
				pointFlag=1;	
				charcat(strOut,c1);
		}

		else {

			if (prevNumFlag)
				prevNumFlag=0;

			
			if (decimalFlag){
				charcat(strOut,']'); 
				prevNumFlag = 1;
				}//the closed square bracket denotes the ending of a decimal

			//flags for point and decimal are reset	
			decimalFlag=0;
			pointFlag=0;
			
			if (c1==',') 
				continue; 
			
			
			if (c1=='(') //push an opening parenthesis to the stack;
				vectorPush(&s,c1);

			else if (c1==')'){ 
				// when the closing parenthesis is spotted, pop stack elements to output 
				// until the opening parenthesis is found;
				//printf("CPARFIND %d\n",i);


				while (1){

					//printf("CPAR %d\n",i);
					//printVector(&s,AS_INT);

					if (!s.count)
						break;
					
					tmp=vectorPop(&s);

					if (tmp=='(' )
						break;

					charcat(strOut,tmp);
				}	
			}

			else if (precedence(c1)==-1){
				//the character could possibly be the start of a variable/function name
			

				while (i < n ){ 
					//copy the name of a possible function or variable into
					//a temporary string

					if (precedence(c1)!=-1 || c1==' ' || c1=='(' || c1==')')
						break; //the following symbols indicate the end of the name
					
					//printf("%c\n",c1);
					charcat(tmpString,c1);

					c1 = strIn[++i];

				}
				i--; //take one step back in the input string
				

				

				Node* foundObj;	 
				//search for the name of the function or variable in the prefix trees
				int funcIsFound = strSearch(tmpString,funcTrie,&foundObj);
				int varIsFound = strSearch(tmpString,varTrie,&foundObj);

				if (!funcIsFound && !varIsFound){

					//abort program if no variable or function is found;
					printf("ERROR : unknown variable or function name \'%s\'\n",tmpString);
					exit(-1);

				}

					//the ID of a function/variable will be given as a negative char value
					//so the IDs don't overlap with the standard ASCII table
					
				else if (varIsFound){
					//when a variable is found
					
					charcat(strOut,'$'); //variables are denoted by a dollar sign prefix
					charcat(strOut,-foundObj->key); //add the -ve of the ID of a variable to the output
					tmpString[0]=0;
					continue;
				}

				else {
					//when a function is found
					c1 = -((mathfunc_t*)foundObj->obj)->id;
					tmpString[0]=0;
				}

			}

			if (!prevNumFlag && c1=='-')
			 	c1='~';
			 
			p1 = precedence(c1); //get the precedence of the operator/function


		

			if (s.count==0 && p1!=-1){ //if stack is empty and you have an operator in your hand, push it to stack
				vectorPush(&s,c1);
				  }

			else if (s.count && p1!=-1){ 

				//printf("CPRECCOMP\n");
				c2 = vectorPop(&s); //pop a second operator off the stack
				p2 = precedence(c2); // then get its precedence
				
				if (p1 > p2){
					// if op1 (from string) has higher precedence than op2 (from stack)
					vectorPush(&s,c2);
					vectorPush(&s,c1);	
					// push op2 then op1
				}

				else{
					
					// if op1 equal or smaller in precedence
					charcat(strOut,c2); //append op2 to output string
					vectorPush(&s,c1); //push op1 to stack

				}
			} 
			
		}
	
	}
	

	while (s.count){ //pop what is remaining in the stack to the output
		charcat(strOut,vectorPop(&s));
		//printVector(&s,AS_INT);
	}

}


