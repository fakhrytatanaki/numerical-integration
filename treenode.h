#ifndef TREENODE_H
#define TREENODE_H
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

typedef struct _treenode{
	int value;
	void* obj;
	int max;
	int count;
	struct _treenode** next;	
} Node;

Node* newRoot(int n);
void addNode(Node* node,Node* root);
void destroyTree(Node** rootdptr);
int findNextVal(int k,Node* node,Node** found);
#endif
