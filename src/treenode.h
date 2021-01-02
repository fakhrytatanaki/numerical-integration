#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#ifndef TREENODE_H
#define TREENODE_H

typedef struct _treenode{
	int value;
	int key;
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
