#ifndef STRSEARCH_H
#define STRSEARCH_H

#include <stdio.h>
#include <string.h>
#include "treenode.h"
#include "mathfuncs.h"
#include "strsearch.h"

Node* constructTrie(int strc,const char** strv);
int strSearch(const char* str,Node* current,Node** foundNode);
void linkObjectsToTrieNodes(Node* root,const char** stringMap,void* objMap,int n);

#endif
