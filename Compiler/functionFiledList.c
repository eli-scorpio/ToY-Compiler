//
// Created by Mingwei Shi on 29/03/2022.
//

#include"functionFiledList.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
struct functionFiledList* functionFiledList_initilization()
{
    struct functionFiledList *myFunctionList =NULL;
    myFunctionList =(struct functionFiledList*)malloc(sizeof (struct functionFiledList));
    myFunctionList->myFunctionListHead=NULL;
    return myFunctionList;
}

struct functionFiledNode* functionNodeBuy(char *Declrationtype,char *identificationName,
        int declarated,int scopeingSwtich,int belongtoWhichScope,char* assignnmentType,
        char *assignmentValue)
{
    struct functionFiledNode* pNewNode = (struct functionFiledNode*)malloc(sizeof(struct functionFiledNode));

    // assert(pNewNode);

    pNewNode->pNext = NULL;
    strcpy( pNewNode->Declrationtype,Declrationtype);
    strcpy(pNewNode->identificationName,identificationName);
    pNewNode->decleationed =declarated;
    pNewNode->scopingSwtich = scopeingSwtich;
    pNewNode->belongtoWhichScope = belongtoWhichScope;
    strcpy(pNewNode->assignmentType,assignnmentType);
    strcpy(pNewNode->assignmentValue,assignmentValue);

    return pNewNode;
}

void functionFiledNode_tailInsert(struct functionFiledList* ppHead, char *Declrationtype,char *identificationName,
                                int declarated,int scopeingSwtich,int belongtoWhichScope,char* assignnmentType,
                                char *assignmentValue)
{
    struct functionFiledNode *pNewNode = functionNodeBuy(Declrationtype,identificationName,declarated,
            scopeingSwtich,belongtoWhichScope,assignnmentType,assignmentValue);
    //  assert(ppHead);

    if (ppHead->myFunctionListHead == NULL)
    {
        ppHead->myFunctionListHead= pNewNode;//让指向头结点的指针指向新构建的节点
    }//ppHead为指向存有头结点地址的二级指针

    else{
        struct functionFiledNode * pTailNode = ppHead->myFunctionListHead;
        while (pTailNode->pNext){//尾结点的Next不为空则向前走
            pTailNode = pTailNode->pNext;
        }
        pTailNode->pNext = pNewNode;
    }

}

void functionFiledList_print(struct functionFiledList *myHead)
{
    struct functionFiledNode *pCur = myHead->myFunctionListHead;
    while (pCur)
    {
        //printf("The name of this ID is : %s\n", pCur->identificationName);
        pCur = pCur->pNext;
    }

}