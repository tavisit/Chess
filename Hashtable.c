#include "Hashtable.h"

// The hashing function used on state to get index

 unsigned long hashfct(unsigned char *str) {
	NULL_PARAM_STRUCT_VALIDATION(str)
	
	unsigned int hash = 0;
	int c = *str;

	while (c) {
	    hash += c;
		c = *str++;
	}

	return hash;
}

// Put a new state in the hashtable
void addToHash(hashtable *hash, InfoNode *info) {
	NULL_PARAM_STRUCT_VALIDATION(hash)
	NULL_PARAM_STRUCT_VALIDATION(info)	
	
	unsigned long indexOfElement = hash->hashFunction(info->key) % hash->size;
	
	push(hash->bucket[indexOfElement], info);
}

// Get a state from the hashtable
Node *getFromHash(hashtable *hash, unsigned char *key) {
	NULL_PARAM_STRUCT_VALIDATION(hash)
	NULL_PARAM_STRUCT_VALIDATION(key)
	
	unsigned long indexOfElement = hash->hashFunction(key) % hash->size;

	return getElementByKey(hash->bucket[indexOfElement], key);
}

// Create and initialize the hashtable
hashtable *initHashtable(int size) {
	
	
	hashtable *hash = malloc(sizeof(hashtable));
	hash->size = size;
	hash->hashFunction = &hashfct;

	if (!hash)
	{
		printf("Hash not formed correctly\n");
		return NULL;
	}

	hash->bucket = malloc(sizeof(List *) * size);

	if(hash->bucket == NULL) {
		printf("Buckets not formed correctly\n");
		return NULL;
	}

	for (int i = 0; i < size; i++) {
		hash->bucket[i] = createList();
	}

	return hash;
}

void printAll(hashtable *hash) {
	NULL_PARAM_STRUCT_VALIDATION(hash)

	Node *currentNode;
	for (int i = 0; i < hash->size; ++i)
	{	
		currentNode = hash->bucket[i]->head;
		while (currentNode)
		{
			printf("in bucket[%d] is %s with score: %d\n", i, 
				currentNode->info->key, currentNode->info->score);



			printf("its parents are:\n");
			for (int i = 0; i < currentNode->info->numberOfParents; i++)
			{
				printf("%s\n", currentNode->info->parents[i]);
			}

			printf("its children are:\n");
			for (int i = 0; i < currentNode->info->heap->size; i++)
			{
				printf("%s with score: %d\n", currentNode->info->heap->myHeap[i]->key, 
					currentNode->info->heap->myHeap[i]->score);
			}
			currentNode = currentNode->next;
		}
	}
}

void deleteHash(hashtable *hash) {
	if(!hash) {
		printf("Hashtable is already NULL\n");
		return; 
	}

	for (int i = 0; i < hash->size; i++)
	{
		if (hash->bucket[i]->head)
		{
			deleteList(hash->bucket[i]);
		}
		free(hash->bucket[i]);
	}

	free(hash->bucket);
	free(hash);
}