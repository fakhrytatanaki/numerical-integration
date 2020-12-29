#include <stdio.h>

#define sumMAC(a) int arr[] tmp = (a); \sum(tmp)

int testFunc(int* arr,int s){
	int sum=0;
	
	for (int i=0;i < s;i++)
		sum+=arr[i];

	return sum;

}

int main(){
	int arr[] = {1,2,3,4};
	int res = testFunc(arr,4);
	printf("%d\n",res);
	return 0;
}
