#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vector.h"
#include "strsearch.h"
#define ui8 unsigned char


void charcat(char* str,char c){
	char tmp[2];
	tmp[1]=0;
	tmp[0] = c;
	strcat(str,tmp);
}

int precedence(char a){
	switch(a){
		case '+':
		case '-':
			return 1;
		case '*':
		case '/':
			return 2;
		default:
			return -1;

	}
} 


void toPostFix(char* strIn,char* strOut,int l){

	char tmp[l];	

	int n = strlen(strIn);
	Vector s = initVector(n);
	
	if (l < n){
		printf("postfix conv. error: output string array too small\n");
		exit(-1);
	}	
	ui8 decimalFlag=0;
	ui8 pointFlag = 0;
	int parBalance; 


	char c1,c2;
	int p1,p2;
	
	for (int i=0;i < n;i++){
	
		c1 = strIn[i];

		if (c1==' ')
			continue; 

		p1 = precedence(c1);

		if (c1 >= '0' && c1 <='9'){
			
			if (!decimalFlag)
				charcat(strOut,'[');
			
			decimalFlag=1;
			charcat(strOut,c1);
		}

		else if (decimalFlag && c1=='.') {

			if (pointFlag){
				printf("floating point parsing error: extra symbol '.'\n");
				exit(-1);
			}
			
				pointFlag=1;	
				charcat(strOut,c1);
		}

		else {

			if (decimalFlag)
				charcat(strOut,']');

			decimalFlag=0;
			pointFlag=0;
				

			if(p1==-1){
				if (c1=='(')
					parBalance++;
				else if (c1==')')
					parBalance--;	
				charcat(strOut,c1);
			}			
		
			else if (s.count==0)
				vectorPush(&s,c1);

			else{
				c2 = vectorPop(&s);
				p2 = precedence(c2);
				
				if (p1 > p2){
					vectorPush(&s,c2);
					vectorPush(&s,c1);	
				}

				else{
					
					charcat(strOut,c2);
					vectorPush(&s,c1);
				}
			} 
			
		}
	}
	
	charcat(strOut,']');

	while (s.count)
		charcat(strOut,vectorPop(&s));

}

int main(int argc,char** argv){
	char out[128];			
	out[0]=0;

	toPostFix(argv[1],out,128);
	printf("%s\n",out);
	
	return 0;
}

