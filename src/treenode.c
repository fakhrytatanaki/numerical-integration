#include "treenode.h"


Node* newRoot(int n){

	Node* root =(Node*) malloc(sizeof(Node));
	root->value=0;
	root->max = n;
	root->count = 0;
	root->next = (Node**) malloc(n*sizeof(void*));
	return root;

};


void addNode(Node* node,Node* root){
	assert(node!=NULL && root!=NULL);

	if (root->count==root->max){
		printf("node tree error : array of next node pointers is full\n");
		exit(-1);	
	}

	root->next[root->count++]=node;
}


void destroyTree(Node** rootdptr){
	
	assert(rootdptr!=NULL);
	Node* root = *rootdptr;
	assert(root!=NULL);

	for (int i=0; i < root->count;i++){
		if (root->next[i]!=NULL){
			destroyTree(&root->next[i]);
			root->next[i]=NULL;
		}
	}


	free(root->next);
	free(root);
	*rootdptr=NULL;
}


int findNextVal(int k,Node* node,Node** found){
	int val;
	for (int i=0;i < node->count;i++){
		val = node->next[i]->value;

		if (val==k){

			if (found!=NULL)
				*found = node->next[i];

			return i;
		}

	}
	return -1;
}
