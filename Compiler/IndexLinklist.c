//
// Created by Mingwei Shi on 22/03/2022.
//

#include "IndexLinklist.h"


void headInsertIndexLinklist(LNode *h,int data)
{
    int i;
    LNode *p;

    p=(LNode *)malloc (sizeof(LNode));
    p->data =data;
    // scanf("%d",&p->data);
    p->next=h->next;
    h->next=p;


}
void output(LNode *h)
{
    LNode *p;
    p=(LNode *)malloc(sizeof(LNode));
    p=h->next;
    while (p!=NULL)
    {
        //printf("%d  ",p->data);
        p=p->next;
    }
    //printf("\n");
}

int checkEmpty(LNode *h) {
    if (h->next == NULL) {
        return 0;
    } else {
        return 1;
    }
}

int getLatestIndex(LNode *h)
{
    int headTop = h->next->data;
    return headTop;
}
LNode * indexListInitlization(LNode* h){
    h = (LNode *) malloc(sizeof(LNode));
    h->next = NULL;
    h->data = -1;
    return h;
}