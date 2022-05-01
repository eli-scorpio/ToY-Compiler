//
// Created by Mingwei Shi on 30/03/2022.
//

#include "variableIndexLinkList.h"

void headInsertVariableIndexLinklist(variableLNode *h, int data)
{
    int i;
    variableLNode *p;

    p = (variableLNode *) malloc(sizeof(variableLNode));
    p->data = data;
    // scanf("%d",&p->data);
    p->next = h->next;
    h->next = p;
}

void outputVariableIndexLinklist(variableLNode *h)
{
    variableLNode *p;
    p=(variableLNode *)malloc(sizeof(variableLNode));
    p=h->next;
    while (p!=NULL)
    {
        printf("%d  ",p->data);
        p=p->next;
    }
    printf("\n");
}

variableLNode * variableIndexListInitlization(variableLNode* h) {
    h = (variableLNode *) malloc(sizeof(variableLNode));
    h->next = NULL;
    h->data = -1;
    return h;

}

int getLatestIndexVariableIndexLinklist(variableLNode *h)
{
    int headTop = h->next->data;
    return headTop;
}
int checkEmptyVariableIndexLinklist(variableLNode *h)
{
    if (h->next == NULL) {
        return 0;
    } else {
        return 1;
    }
}
