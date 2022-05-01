#ifndef LINKLIST_TAILINSERT_LEXPRESSIONLINKLIST_H
#define LINKLIST_TAILINSERT_LEXPRESSIONLINKLIST_H
#include<stdio.h>
#include<stdlib.h>

    FILE *yyout;

/*
 *
 * This data stucture is for L expression
 *
 */
typedef char* DataType;
typedef struct SlistNode{
    DataType data;
    struct SlistNode *pNext;
}Slist, *PNode;

void LexpressionList_initilization(PNode* pHead);

int Lexpression_length(PNode pHead);

PNode BuySListNode(DataType data);
void LexpressionList_tailInsert(PNode* ppHead, DataType data);

void Lexpression_print(PNode pHead);
void LexpressionLinklist_destory(PNode* ppHead);
char *acquireFirstElementOfLexpressionList(PNode* ppHead);
void LexpressionList_headDelete(PNode* ppHead);
void LexpressionList_headInsert(PNode* ppHead, DataType data);
// 0 empty 1 not
int isEmptyLexpressionList(PNode pHead);
#endif //LINKLIST_TAILINSERT_LEXPRESSIONLINKLIST_H
