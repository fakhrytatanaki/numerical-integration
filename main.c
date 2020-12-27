#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vector.h"
#include "strsearch.h"
#include "mathfuncs.h"
#define ui8 unsigned char


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

		default:
			if (a >= MATHFUNC_ID_START && a < MATHFUNC_ID_START + mathfunc_count)
				return 3;

			return -1; // -1 is returned as precedence if the character is not a operator or a function

	}
}


void printPostfix(const char* out){
	int i=0;
	while (out[i]!=0){
		if (out[i] >= MATHFUNC_ID_START && out[i] < MATHFUNC_ID_START + mathfunc_count)
			printf("%s",mathfunc_names[out[i] - MATHFUNC_ID_START]);
		
		else
			printf("%c",out[i]);
		i++;
	}
	printf("\n");
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


	char c1,c2;
	int p1,p2; // for storing the precedence of 2 operators to be compared
	
	for (int i=0;i < n;i++){  
		
		printf("%c,i:%d\n",c1,i);
		c1 = strIn[i];

		if (c1==' ')
			continue; 

		else if (c1==','){
			pointFlag=0;
			decimalFlag=0;
			continue;

		}
		printVector(&s,AS_INT);

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

			if (decimalFlag)
				charcat(strOut,']'); //the closed square bracket denotes the ending of a decimal

			//flags for point and decimal are reset	
			decimalFlag=0;
			pointFlag=0;
			
			
			if (c1=='(')
				vectorPush(&s,c1);

			else if (c1==')'){
				printf("CPARFIND %d\n",i);


				while (1){

					printf("CPAR %d\n",i);
					printVector(&s,AS_INT);

					if (!s.count)
						break;
					
					tmp=vectorPop(&s);

					if (tmp=='(' )
						break;

					charcat(strOut,tmp);
				}	
			}

			else if (precedence(c1)==-1){
			

				while (i < n ){

					c1 = strIn[i++];

					if (precedence(c1)!=-1 || c1==' ' || c1=='(' || c1==')')
						break;
					
					printf("%c\n",c1);
					charcat(tmpString,c1);

				}
				i--;

				Node* foundObj;	
				int funcIsFound = strSearch(tmpString,funcTrie,&foundObj);
				int varIsFound = strSearch(tmpString,varTrie,&foundObj);

				if (!funcIsFound && !varIsFound){

					printf("ERROR : unknown variable or function name \'%s\'\n",tmpString);
					exit(-1);

				}
				else if (varIsFound){
					strcat(strOut,tmpString);
					tmpString[0]=0;
					continue;
				}

				else {
					c1 = ((mathfunc_t*)foundObj->obj)->id;
					tmpString[0]=0;
				}

			}

			p1 = precedence(c1);
			
			if (s.count==0 && p1!=-1){ //if stack is empty and you have an operator in your hand, push it to stack
				vectorPush(&s,c1);
				  }

			else if (s.count && p1!=-1){ 

				printf("CPRECCOMP\n");
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
	

		printf("end,count : %d\n",s.count);
	while (s.count){
		printf("end\n");
		charcat(strOut,vectorPop(&s));
		printVector(&s,AS_INT);
	}

}

int main(int argc,char** argv){
	char out[128];			
	out[0]=0;
	
	const char* testvars[] = {"x","y","john"};
	Node* varTrie = constructTrie(3,testvars);
	mathfunc_t** funcs = getMathFuncs();
	Node* funcTrie = constructFuncNameTrie(funcs);

	toPostFix(argv[1],out,128,funcTrie,varTrie);
	printPostfix(out);
	
	return 0;
}

