
#include<stdio.h>
#include<stdlib.h>
#include"hashUtil.h"
#include"hashUtil.c"
typedef struct HashNode
{
    char* key;
    char* value;
    struct HashNode* next;
}HashNode;

typedef struct
{
    int size;
    HashNode** hashArr;
}HashMap;

	#define myMalloc  malloc
	#define myCalloc  calloc
	#define myFree    free
	#define myHash    hash

HashMap* CreateHashMap(int n)
{
    HashMap* thishashMap = (HashMap*)myCalloc(1, sizeof(HashMap));
    thishashMap->hashArr = (HashNode**)myCalloc(n, sizeof(HashNode*));
    if (thishashMap==NULL || thishashMap->hashArr==NULL) {
        return NULL;
    }
    thishashMap->size = n;
    return thishashMap;
};


int InsertHashMap(HashMap* hashMap, char* key, char* value)
{

    HashNode* node = (HashNode*)myCalloc(1, sizeof(HashNode));
    if (node == NULL) {
        return 0;
    }


    node->key = strdup(key);
    node->value = strdup(value);
    node->next = NULL;

    int index = myHash(key) % hashMap->size;

    if (hashMap->hashArr[index] == NULL) {
        hashMap->hashArr[index] = node;
    }

    else {

        HashNode *temp = hashMap->hashArr[index];

        HashNode *prev = temp;

        while (temp != NULL) {

            if (strcmp(temp->key, node->key) == 0) {

                myFree(temp->value);

                temp->value = strdup(node->value);
                return 1;
            }
            prev = temp;
            temp = temp->next;
        }

        prev->next = node;
    }
    return 1;
}


char* GetHashMap(HashMap* hashMap, char* key)
{

    int index = myHash(key) % hashMap->size;

    HashNode *temp = hashMap->hashArr[index];

    while (temp != NULL) {

        if (strcmp(temp->key, key) == 0) {
            return temp->value;
        }
        temp = temp->next;
    }
    return NULL;
}
