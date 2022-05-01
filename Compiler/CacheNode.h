//
// Created by Mingwei Shi on 18/03/2022.
//
#ifndef CACHE_NODE_H
#define CACHE_NODE_H
#include<stdio.h>
#include <stdlib.h>
#include<stdbool.h>
struct CacheLinklist{
    char* data;
    struct CacheLinklist *next;
};

typedef struct
{
    struct CacheLinklist* head;
    struct CacheLinklist *tail;
}List;
//Initialize List
void initList(List* lp);
//Create node and return reference of it.

struct CacheLinklist* createNode(char * item);
//Add new item at begning of the list.

void addAtHeadCacheNode(List* lp, char* item);

char* acquireHeadOfListCache(List *lp);

int exsitingInCachenode(List *lp,char *item);

int lengthOfCacheNodeForFunctionLengthChecking(List *lp);
#endif


