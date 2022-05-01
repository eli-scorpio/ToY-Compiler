//
// Created by Mingwei Shi on 18/03/2022.
//

#include "FunctionStack.h"
#include<stdlib.h>
#include<string.h>

#include "functionFiledList.h"


#include "MemberShipHash.h"

//#include "MemberShipHash.c"

struct FunctionList * init_FunctionList( struct FunctionList *thisFunctionList)
{
   
    struct FunctionList *myFunctionListCollection;
    myFunctionListCollection = malloc(sizeof(struct FunctionList));
    myFunctionListCollection->myFunctionList=NULL;
    return myFunctionListCollection;

   
}

void insertFuncttionName( struct FunctionList *thisFunctionList,char *functionName,char* functionDeclrationType)
{
    // header
    // Temperpal Pnode
    struct functionHeaderNode* pNodeFunctionHeader;
    pNodeFunctionHeader = (struct functionHeaderNode*)malloc(sizeof(struct functionHeaderNode));


    strcpy(pNodeFunctionHeader->functionName,functionName);
    strcpy(pNodeFunctionHeader->functionDeclrationType,functionDeclrationType);
    strcpy(pNodeFunctionHeader->functionReturnType,"void");
    pNodeFunctionHeader->numberOfBrackers =1;
// Stack
    struct FunctionStack *myFunctionStack;
    myFunctionStack = (struct FunctionStack*) malloc(sizeof (struct FunctionStack));
    myFunctionStack->myfunctionHeader=pNodeFunctionHeader;
    myFunctionStack->myFunctionFiledList=functionFiledList_initilization( myFunctionStack->myFunctionFiledList);
    myFunctionStack->myHashMemebership=initilizationOfMemebershipHashtable(myFunctionStack->myHashMemebership);
    myFunctionStack->myHashIDToTypeTransfer =initilizationOfMemebershipHashtable(    myFunctionStack->myHashIDToTypeTransfer);
    //  thisFunctionList->myFunctionList->singleFunctionStack->myHashMemebership=initilizationOfMemebershipHashtable( thisFunctionList->myFunctionList->singleFunctionStack->myHashMemebership);
    //
// Stack List
    //myFunctionStack->pNextFunctionStack=NULL;
    //myFunctionStack->singleFunctionStack->myfunctionHeader=pNodeFunctionHeader;
    struct  FunctionStackList *tempFunctionStackList;
    tempFunctionStackList =(struct FunctionStackList*) malloc(sizeof (struct FunctionStackList));
    //.myfunctionHeader=pNodeFunctionHeader;

    tempFunctionStackList->singleFunctionStack=myFunctionStack;
    tempFunctionStackList->pNextFunctionStack=NULL;
    // Then copy into function

    if(thisFunctionList->myFunctionList==NULL)
    {
        thisFunctionList->myFunctionList=tempFunctionStackList;
       // myFunctionStack->singleFunctionStack=myFunctionStack;
    }
    else
    {
        struct FunctionStackList * pTailNode = thisFunctionList->myFunctionList;

        while(pTailNode->pNextFunctionStack)
        {

            pTailNode =pTailNode->pNextFunctionStack;
        }
        pTailNode->pNextFunctionStack=tempFunctionStackList;


    }




}
// matching functioname;
void insertFunctionReturnType(struct FunctionList *thisFunctionList,char *functionName,char* functionReturnType)
{
    struct FunctionStackList *tempFunctionStackList = thisFunctionList->myFunctionList;
    while(tempFunctionStackList!=NULL)
    {
        // Mateching here
        // 1 level pointer
        struct FunctionStack *tempFunctionStack =tempFunctionStackList->singleFunctionStack;
        // two level pointer
        struct functionHeaderNode* tempFunctionNode =tempFunctionStack->myfunctionHeader;
        // 3 level pointer
        char tempFunctionName[1024];
        strcpy(tempFunctionName,tempFunctionNode->functionName);

        if(strcmp(tempFunctionName,functionName)==0)
        {
            strcpy(thisFunctionList->myFunctionList->singleFunctionStack->myfunctionHeader->functionReturnType,functionReturnType);
        }

        tempFunctionStackList=tempFunctionStackList->pNextFunctionStack;
    }

}

void bracketControlAdd(struct FunctionList *thisFunctionList, char *functionName)
{

    struct FunctionStackList *tempFunctionStackList = thisFunctionList->myFunctionList;
    while(tempFunctionStackList!=NULL)
    {
        // Mateching here
        // 1 level pointer
        struct FunctionStack *tempFunctionStack =tempFunctionStackList->singleFunctionStack;
        // two level pointer
        struct functionHeaderNode* tempFunctionNode =tempFunctionStack->myfunctionHeader;
        // 3 level pointer
        char tempFunctionName[1024];
        strcpy(tempFunctionName,tempFunctionNode->functionName);

        if(strcmp(tempFunctionName,functionName)==0)
        {
            thisFunctionList->myFunctionList->singleFunctionStack->myfunctionHeader->numberOfBrackers+=1;

            //strcpy(thisFunctionList->myFunctionList->singleFunctionStack->myfunctionHeader->functionReturnType,functionReturnType);
        }

        tempFunctionStackList=tempFunctionStackList->pNextFunctionStack;
    }


}
void bracketControlSub(struct FunctionList *thisFunctionList, char *functionName)
{
    struct FunctionStackList *tempFunctionStackList = thisFunctionList->myFunctionList;
    while(tempFunctionStackList!=NULL)
    {
        // Mateching here
        // 1 level pointer
        struct FunctionStack *tempFunctionStack =tempFunctionStackList->singleFunctionStack;
        // two level pointer
        struct functionHeaderNode* tempFunctionNode =tempFunctionStack->myfunctionHeader;
        // 3 level pointer
        char tempFunctionName[1024];
        strcpy(tempFunctionName,tempFunctionNode->functionName);

        if(strcmp(tempFunctionName,functionName)==0)
        {
            thisFunctionList->myFunctionList->singleFunctionStack->myfunctionHeader->numberOfBrackers-=1;

            //strcpy(thisFunctionList->myFunctionList->singleFunctionStack->myfunctionHeader->functionReturnType,functionReturnType);
        }

        tempFunctionStackList=tempFunctionStackList->pNextFunctionStack;
    }


}


void insertVariableDeclarationforSpecificFunction(struct FunctionList *thisFunctionList, char *functionName, char *functionDeclartionType, char * variableDeclartionType, char *variableName)
{

   // struct FunctionStackList *tempFunctionStackList = thisFunctionList->myFunctionList;
    while(thisFunctionList->myFunctionList!=NULL)
    {
        // Mateching here
        // 1 level pointer
        struct FunctionStack *tempFunctionStack =thisFunctionList->myFunctionList->singleFunctionStack;
        // two level pointe
        struct functionHeaderNode* tempFunctionNode =thisFunctionList->myFunctionList->singleFunctionStack->myfunctionHeader;
        // 3 level pointer
        char tempFunctionName[1024];
        strcpy(tempFunctionName,tempFunctionNode->functionName);

        if(strcmp(tempFunctionName,functionName)==0)
        {
            //thisFunctionList->myFunctionList->singleFunctionStack->myfunctionHeader->numberOfBrackers-=1;
            //thisFunctionList->myFunctionList->singleFunctionStack->myHashMemebership=initilizationOfMemebershipHashtable( thisFunctionList->myFunctionList->singleFunctionStack->myHashMemebership);
            // Hashtable install
            installNewKeyAndValueInMembershipHashTable(thisFunctionList->myFunctionList->singleFunctionStack->myHashMemebership,variableName,"used");
            installNewKeyAndValueInMembershipHashTable(thisFunctionList->myFunctionList->singleFunctionStack->myHashIDToTypeTransfer,variableName,variableDeclartionType);
            //Fileddcopy
            int thisFunctionScopeCurrently=thisFunctionList->myFunctionList->singleFunctionStack->myfunctionHeader->numberOfBrackers;
            functionFiledNode_tailInsert(thisFunctionList->myFunctionList->singleFunctionStack->myFunctionFiledList,variableDeclartionType,variableName,1,START_SCOPE,thisFunctionScopeCurrently
            ,"NULL","NULL");
           // strcpy(thisFunctionList->myFunctionList->singleFunctionStack->myFunctionFiledList.)

            //strcpy(thisFunctionList->myFunctionList->singleFunctionStack->myfunctionHeader->functionReturnType,functionReturnType);
        }

        thisFunctionList->myFunctionList=thisFunctionList->myFunctionList->pNextFunctionStack;
    }

}
/*
int variableAssigneent(struct FunctionList *thisFunctionList,char *functionName,
        char *variableName,char *OurassignmentType);

{
    struct FunctionList *temFunctioneList = thisFunctionList;
    int i;
    for(i = 0 ;i<MAX_SIZE;i++)
    {
        // First loop is for iterateed each function
        char *tempFunctionName = temFunctioneList->functionList[i].functionName;
        if(strcmp(tempFunctionName,functionName)==0)
        {
            // Inseerting list;
            int j;
            struct functionFiled *tempFunctionFiledList = temFunctioneList->functionList[i].filedList;
            for(j = 0 ;j<MAX_SIZE;j++)
            {

                char *tempVariableID = tempFunctionFiledList[j].identificationName;
                int delcated = tempFunctionFiledList[j].decleationed;

                if((delcated ==1)&&(strcmp(tempVariableID,variableName)==0))
                {
                    thisFunctionList->functionList[i].filedList[j].assignmentType =OurassignmentType;
                    return 1;
                }


            }

        }

    }
    return 0;
}
*/
/*
 *
 *  int a;
 *  for(i = 0 ;i<10;i++)
 *  {
 *      int a;
 *      a = i;
 *  }
 */
// Close all the variable scope equla to cuurent function scope
void closeScopeOfVariable(struct FunctionList *thisFunctionList,char * functionName)
{

    struct FunctionStackList *tempFunctionStackList = thisFunctionList->myFunctionList;
    while(tempFunctionStackList!=NULL)
    {
        // Mateching here
        // 1 level pointer
        struct FunctionStack *tempFunctionStack =tempFunctionStackList->singleFunctionStack;
        // two level pointer
        struct functionHeaderNode* tempFunctionNode =tempFunctionStack->myfunctionHeader;
        // 3 level pointer
        char tempFunctionName[1024];
        strcpy(tempFunctionName,tempFunctionNode->functionName);

        if(strcmp(tempFunctionName,functionName)==0)
        {
            int functionScope = thisFunctionList->myFunctionList->singleFunctionStack->myfunctionHeader->numberOfBrackers;


            struct  functionFiledList *tempFiledList = thisFunctionList->myFunctionList->singleFunctionStack->myFunctionFiledList;
            struct functionFiledNode *filedNodeTemp = tempFiledList->myFunctionListHead;
            char tempVaribaleName[MAX_SIZE];

            while(filedNodeTemp)
            {

                strcpy(tempVaribaleName,filedNodeTemp->identificationName);


                if((thisFunctionList->myFunctionList->singleFunctionStack->myFunctionFiledList->myFunctionListHead->decleationed==1)
                   &&(functionScope==thisFunctionList->myFunctionList->singleFunctionStack->myFunctionFiledList->myFunctionListHead->belongtoWhichScope))
                {
                    thisFunctionList->myFunctionList->singleFunctionStack->myFunctionFiledList->myFunctionListHead->scopingSwtich=END_SCOPE;
                    thisFunctionList->myFunctionList->singleFunctionStack->myFunctionFiledList->myFunctionListHead->decleationed=0;
                }
                filedNodeTemp =filedNodeTemp->pNext;
                //tempFiledList->myFunctionListHead =tempFunctionStackList.
                thisFunctionList->myFunctionList->singleFunctionStack->myFunctionFiledList->myFunctionListHead=thisFunctionList->myFunctionList->singleFunctionStack->myFunctionFiledList->myFunctionListHead->pNext;

            }
        }

        tempFunctionStackList=tempFunctionStackList->pNextFunctionStack;
    }




}

//1 for has redeclartion 0 not
// we need to think about scope checking code here
/*
 * int a;
 * int i; decleared 1 switchScope START
 *
 * for(i =0;i<10;i++)
 * {
 *  int a;DECLEARTED = 1,scope = START
 * }
 */



int checkReDeclaration(struct FunctionList *thisFunctionList, char *functionName,
                       char *variableName)
{


    struct FunctionStackList *tempFunctionStackList = thisFunctionList->myFunctionList;
    while(tempFunctionStackList!=NULL)
    {
        // Mateching here
        // 1 level pointer
        struct FunctionStack *tempFunctionStack =tempFunctionStackList->singleFunctionStack;
        // two level pointer
        struct functionHeaderNode* tempFunctionNode =tempFunctionStack->myfunctionHeader;
        // 3 level pointer
        char tempFunctionName[1024];
        strcpy(tempFunctionName,tempFunctionNode->functionName);

        if(strcmp(tempFunctionName,functionName)==0)
        {
            int functionScope = thisFunctionList->myFunctionList->singleFunctionStack->myfunctionHeader->numberOfBrackers;


            struct  functionFiledList *tempFiledList = thisFunctionList->myFunctionList->singleFunctionStack->myFunctionFiledList;
            struct functionFiledNode *filedNodeTemp = tempFiledList->myFunctionListHead;
            char tempVaribaleName[MAX_SIZE];

            while(filedNodeTemp)
            {

                strcpy(tempVaribaleName,filedNodeTemp->identificationName);


                if((strcmp(tempVaribaleName,variableName)==0)&&(thisFunctionList->myFunctionList->singleFunctionStack->myFunctionFiledList->myFunctionListHead->decleationed==1)
                &&(functionScope==thisFunctionList->myFunctionList->singleFunctionStack->myFunctionFiledList->myFunctionListHead->belongtoWhichScope))
                {
                   return 1;

                }
                filedNodeTemp =filedNodeTemp->pNext;
                //tempFiledList->myFunctionListHead =tempFunctionStackList.
                thisFunctionList->myFunctionList->singleFunctionStack->myFunctionFiledList->myFunctionListHead=thisFunctionList->myFunctionList->singleFunctionStack->myFunctionFiledList->myFunctionListHead->pNext;

            }
        }

        tempFunctionStackList=tempFunctionStackList->pNextFunctionStack;
    }


    return 0;

}
// 1 undeclration 0 not
// Check scope here
/*
 * void function2()
 * {
 *  int a;
 *  int i;
 *  for(i = 0;i<10;i++)
 *  {
 *      int j;
 *      for(j = 0 ;j<10;j++)
 *      {
 *          c= 0;
 *      }
 *  }
 * }
 * for this case deal with all the tigeher checker ;
 * if no any of it
 */
int checkUndeclaratedVaraible(struct FunctionList *thisFunctionList, char *functionName,
                              char *variableName)
{


    struct FunctionStackList *tempFunctionStackList = thisFunctionList->myFunctionList;
    while(tempFunctionStackList!=NULL)
    {
        // Mateching here
        // 1 level pointer
        struct FunctionStack *tempFunctionStack =tempFunctionStackList->singleFunctionStack;
        // two level pointer
        struct functionHeaderNode* tempFunctionNode =tempFunctionStack->myfunctionHeader;
        // 3 level pointer
        char tempFunctionName[1024];
        strcpy(tempFunctionName,tempFunctionNode->functionName);

        if(strcmp(tempFunctionName,functionName)==0)
        {
            int functionScope = thisFunctionList->myFunctionList->singleFunctionStack->myfunctionHeader->numberOfBrackers;

           // char *returnType = getValueFromKeyMemebershipHashtable(thisFunctionList->myFunctionList->singleFunctionStack->myHashIDToTypeTransfer,)
            struct  functionFiledList *tempFiledList = thisFunctionList->myFunctionList->singleFunctionStack->myFunctionFiledList;
            struct functionFiledNode *filedNodeTemp = tempFiledList->myFunctionListHead;
            char tempVaribaleName[MAX_SIZE];

            while(filedNodeTemp)
            {

                strcpy(tempVaribaleName,filedNodeTemp->identificationName);


                if((strcmp(tempVaribaleName,variableName)==0))
                {
                    return 0;

                }
                filedNodeTemp =filedNodeTemp->pNext;
                //tempFiledList->myFunctionListHead =tempFunctionStackList.
                thisFunctionList->myFunctionList->singleFunctionStack->myFunctionFiledList->myFunctionListHead=thisFunctionList->myFunctionList->singleFunctionStack->myFunctionFiledList->myFunctionListHead->pNext;

            }
        }

        tempFunctionStackList=tempFunctionStackList->pNextFunctionStack;
    }


    return 1;

}

/*
 *
 * Priate function
 */


char * returnStructureTypeofVariable(struct FunctionList* thisFunctionList,char *functionnName,char *variables) {
    int i;
    // HashMap here
    //har tempType[MAX_SIZE];
    //char *tempNull = "NULL";


    struct FunctionStackList *tempFunctionStackList = thisFunctionList->myFunctionList;
    while(tempFunctionStackList!=NULL)
    {
        // Mateching here
        // 1 level pointer
        struct FunctionStack *tempFunctionStack =tempFunctionStackList->singleFunctionStack;
        // two level pointer
        struct functionHeaderNode* tempFunctionNode =tempFunctionStack->myfunctionHeader;
        // 3 level pointer
        char tempFunctionName[1024];
        strcpy(tempFunctionName,tempFunctionNode->functionName);

        if(strcmp(tempFunctionName,functionnName)==0)
        {
            //printf("Current function name**** is %s\n",tempFunctionName);
            char *returnTypeT = getValueFromKeyMemebershipHashtable(thisFunctionList->myFunctionList->singleFunctionStack->myHashIDToTypeTransfer,variables);
            return returnTypeT;
           // printf("The return type is %s\n",returnTypeT);
            //strcpy(*returnType,returnTypeT);
            //int functionScope = thisFunctionList->myFunctionList->singleFunctionStack->myfunctionHeader->numberOfBrackers;


           // struct  functionFiledList *tempFiledList = thisFunctionList->myFunctionList->singleFunctionStack->myFunctionFiledList;
           // struct functionFiledNode *filedNodeTemp = tempFiledList->myFunctionListHead;
           // char tempVaribaleName[MAX_SIZE];

           
        }

        tempFunctionStackList=tempFunctionStackList->pNextFunctionStack;
    }




    return NULL;

    //return tempType;
}

