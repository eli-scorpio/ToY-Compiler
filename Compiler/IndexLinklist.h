
#ifndef INDEXLINKLIST_INDEXLINKLIST_H
#define INDEXLINKLIST_INDEXLINKLIST_H

#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    // Scope level
   int data;
    struct node *next;
} LNode;


void headInsertIndexLinklist(LNode *h,int data);
void output(LNode *h);
LNode * indexListInitlization(LNode* h);
int getLatestIndex(LNode *h);
int checkEmpty(LNode *h);
#endif //INDEXLINKLIST_INDEXLINKLIST_H
