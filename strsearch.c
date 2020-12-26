

Node* constructTrie(int strc,const char** strv){

	int maxlen=0;
	int nxtValInd;
	int len[strc];
	Node* found;
	for (int i=0;i<strc;i++){

		len[i] = strlen(strv[i]);

		if (len[i] > maxlen)
			maxlen = len[i];
	}

	Node* root = newRoot(strc);
	Node* current;
	Node* tmp;

	for (int i=0;i < strc;i++){
		current = root;

		for (int j=0;j<len[i];j++){
			nxtValInd = findNextVal(strv[i][j],current,&found);
			if (nxtValInd==-1){
				tmp = newRoot(strc);
				tmp->value = strv[i][j];
				addNode(tmp,current);
				current = tmp;	
			}

			else{
				current=found;
			}
		}

	}

	return root;



}



int strSearch(const char* str,Node* current,Node** foundNode){
	int i = 0;
	for (int j=0;j < current->count;j++){


		if (str[i]==0 && i==0)
			return 0;
		
		if (str[i]==current->next[j]->value) {

			current = current->next[j];
			i++;
			j=-1;
		}

		if (str[i]==0){
			

			if (foundNode!=NULL){
				*foundNode=current;
			}

			return 1;
		}

	}

	
	return 0;
}


void linkObjectsToTrieNodes(Node* root,const char** stringMap,void* objMap,int n){

	int isFound;
	Node* found;

	mathfunc_t hj;

	for (int i=0;i < n;i++){
		printf("obj addr. : %x\n",objMap + i);
		isFound = strSearch(stringMap[i],root,&found);

		if (!isFound){
			printf("TRIE KEY MAP ERROR : no match for string at index %d\n",i);
			exit(-1);
		}

		found->obj = objMap+i;
	}	
}
