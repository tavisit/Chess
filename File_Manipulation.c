#include "File_Manipulation.h"

void readFromFile(hashtable *hash) {
    FILE *file;
    file = fopen("myFile", "r");

    if (file == NULL)
    {
        printf("File not found");
        return;
    }

    if(!hash) {
		printf("Hash nonexistent\n");
		return;
	}
    unsigned char *parent = malloc(sizeof(char) * 194);
    unsigned char *child = malloc(sizeof(char) * 194); 
    while (fscanf(file, "%s %s", child, parent) == 2)
    {
        addChildToParent(hash, child, parent);
        printf("%s\n", parent);
        printf("%s\n", child);
    }
    
    fclose(file);
}

void writeToFile(hashtable *hash) {
    FILE *file;
    file = fopen("myFile", "w");

    if (file == NULL)
    {
        printf("File not found");
        return;
    }

    if(!hash) {
		printf("Hash nonexistent\n");
		return;
	}

	Node *currentNode;
	for (int i = 0; i < hash->size; ++i)
	{	
		currentNode = hash->bucket[i]->head;
		while (currentNode)
		{
			for (int i = 0; i < currentNode->info->numberOfParents; i++)
			{
				fprintf(file, "%s %s\n", currentNode->info->parents[i], currentNode->info->key);
			}

			for (int i = 0; i < currentNode->info->heap->size; i++)
			{
				fprintf(file, "%s %s\n",currentNode->info->key, currentNode->info->heap->myHeap[i]->key);
			}
			currentNode = currentNode->next;
		}
	}

    fclose(file);
}