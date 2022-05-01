//
// Created by Mingwei Shi on 29/03/2022.
//

#ifndef FUNCTIONFILEDLIST_FUNCTIONFILEDLIST_H
#define FUNCTIONFILEDLIST_FUNCTIONFILEDLIST_H

#define  MAX_SIZE 1024
struct functionFiledNode {
    char Declrationtype[MAX_SIZE];
    char identificationName[MAX_SIZE];
    // 1 for decleation  0 for not

    int decleationed;
    //1 is for starting
    // 0 Undefine
    // 1 Start scoping
    // 2 end scopeing

    // if mutiple one select the larger index one
    int scopingSwtich;
    /*
     * Iniltization 0
     * assignment value as the numberOfBrackerr;
     * when } modify all the scope for with the same number as
     * numberOfBracket
     */
    int belongtoWhichScope;
    char assignmentType[MAX_SIZE];
    char assignmentValue[MAX_SIZE];
    struct functionFiledNode *pNext;
};
struct functionFiledList
{
    struct functionFiledNode *myFunctionListHead;
};

struct functionFiledList* functionFiledList_initilization(struct functionFiledList* pHead);

//nt Lexpression_length(PNode pHead);

struct functionFiledNode* functionNodeBuy(char *Declrationtype,char *identificationName,
                                          int declarated,int scopeingSwtich,int belongtoWhichScope,char* assignnmentType,
                                          char *assignmentValue);

void functionFiledNode_tailInsert(struct functionFiledList* ppHead, char *Declrationtype,char *identificationName,
                                  int declarated,int scopeingSwtich,int belongtoWhichScope,char* assignnmentType,
                                  char *assignmentValue);
//int isEmptyLexpressionList(struct functionFiledList *pHead);

void functionFiledList_print(struct functionFiledList *myHead);

#endif //FUNCTIONFILEDLIST_FUNCTIONFILEDLIST_H
