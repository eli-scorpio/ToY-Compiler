//
// Created by Mingwei Shi on 25/03/2022.
//

#include "LexpressionLinkList.h"

void LexpressionList_initilization(PNode* pHead)
{
    *pHead = NULL;
}
// create new node
PNode BuySListNode(DataType data)
{
    PNode pNewNode = (PNode)malloc(sizeof(Slist));
    // assert(pNewNode);

    pNewNode->pNext = NULL;
    pNewNode->data = data;
    return pNewNode;
}

void LexpressionList_tailInsert(PNode* ppHead, DataType data)
{
    PNode pNewNode = BuySListNode(data);
    //  assert(ppHead);

    if (*ppHead == NULL)//ppHead为指向存有头结点地址的二级指针
        *ppHead = pNewNode;//让指向头结点的指针指向新构建的节点
    else{
        PNode pTailNode = *ppHead;
        while (pTailNode->pNext){//尾结点的Next不为空则向前走
            pTailNode = pTailNode->pNext;
        }
        pTailNode->pNext = pNewNode;
    }

}

void Lexpression_print(PNode pHead) // 打印单链表
{
    PNode pCur = pHead;
    while (pCur)
    {
        //printf("%s \n", pCur->data);
        pCur = pCur->pNext;
    }
   //fprintf(yyout,"NULL\n");
}

char *acquireFirstElementOfLexpressionList(PNode* ppHead) {
    char *temp = NULL;
    PNode pDelNode = NULL;
    pDelNode = *ppHead;
    temp = pDelNode->data;
    return temp;
}

void LexpressionList_headDelete(PNode* ppHead)
{

    PNode pDelNode = NULL;
    if ((*ppHead) == NULL){
        //fprintf(yyout,"The list of L expression is empty\n");
        return;
    }

    pDelNode = *ppHead;
    *ppHead =pDelNode->pNext ;
    free(pDelNode);//
}

void LexpressionLinklist_destory(PNode* ppHead)
{
    PNode pCur = NULL;
    PNode pPreCur = NULL;
    if (*ppHead == NULL)
        return;


    //正向销毁
    while (pCur){
        pPreCur = pCur;
        pCur = pCur->pNext;
        free(pPreCur);
    }
    *ppHead = NULL;
}


int isEmptyLexpressionList(PNode pHead)
{
    PNode  pCur = pHead;
    if(pCur==NULL)
    {
        return 0;
    }
    else{
        return 1;
    }
}

void LexpressionList_headInsert(PNode* ppHead, DataType data)// 头插
{
    PNode NewSlistNow = BuySListNode(data);// 创建结点
    NewSlistNow->pNext = *ppHead;
    *ppHead = NewSlistNow;
}

int Lexpression_length(PNode pHead) //
{
    PNode pCur = pHead;
    int count =0;
    while (pCur)
    {
        //printf("%s->", pCur->data);
        pCur = pCur->pNext;
        count=count+1;
    }
    return count;
}