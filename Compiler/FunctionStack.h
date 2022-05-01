//
// Created by Mingwei Shi on 18/03/2022.
//
// Firstly we need to store the functon
#ifndef FUNCTION_STACK_H
#define FUNCTION_STACK_H

#define UNDEF_SCOPE 0
#define START_SCOPE 1
#define END_SCOPE 2
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "MemberShipHash.h"
#include "MemberShipHash.c"

#include "functionFiledList.h"



#include "functionFiledList.c"

//  #include "hashUtil.h"
 //       #include "hashMap.h"
     //  #include "hashUtil.c"
//    #include"hashMap.c"

#define  MAX_SIZE 1024
struct functionHeaderNode {

    char functionDeclrationType[MAX_SIZE];
    char  functionName[MAX_SIZE];
    char functionReturnType[MAX_SIZE];
    int numberOfBrackers;

};
struct FunctionStack
{
// A group of information
    struct functionHeaderNode *myfunctionHeader;
// for check declared memeber
     struct memebershipHashTable *myHashMemebership;
    struct memebershipHashTable *myHashIDToTypeTransfer;
     // i thiink it need s type transfer here;
     struct functionFiledList *myFunctionFiledList;
    
   // HashMap* variableExistingChecker;
};

struct FunctionStackList
{
    struct FunctionStack *singleFunctionStack;
    struct FunctionStackList *pNextFunctionStack;
    
};
struct FunctionList {
    struct FunctionStackList *myFunctionList;
};
//initilizat functionList
struct FunctionList * init_FunctionList( struct FunctionList *thisFunctionList);

// Insertting a function name
//
void insertFuncttionName( struct FunctionList *thisFunctionList,char *functionName,char* functionDeclrationType);

void insertFunctionReturnType(struct FunctionList *thisFunctionList,char *functionName,char* functionReturnType);

/*
 *  *********************************************
 */

// insert the declartion  of variable


void bracketControlAdd(struct FunctionList *thisFunctionList, char *functionName);
void bracketControlSub(struct FunctionList *thisFunctionList, char *functionName);


void insertVariableDeclarationforSpecificFunction(struct FunctionList *thisFunctionList, char *functionName, char *functionDeclartionType, char * variableDeclartionType, char *variableName);

//
/*
 * For a variable with
 * {
 * statemetnlist
 * }
 * for(int i = 0 ;i <1;i++)
 */

void closeScopeOfVariable(struct FunctionList *thisFunctionList,char * functionName);

void modifyVariableScope(struct FunctionList *thisFunctionList, char *functionName, char *variableName,int scope_code);
// Next

//
/*
 * Give a variable to check the tigher scope for type checker
 */

/*
 *
 * Scope checking
 */
// Reclaration of variable;
// Varibale assignment in the functiion
// 1 for success 0 zeor
// un-declration varaible detect :traverse linklist


// if we delcration alreay ,not vaild:For node :that is detected :check the element = 1 or not
//1 for has redeclartion 0 not


int checkReDeclaration(struct FunctionList *thisFunctionList, char *functionName,
                       char *variableName);
// 1 DECLrated 0 not delcated before
int checkUndeclaratedVaraible(struct FunctionList *thisFunctionList, char *functionName,
                              char *variableName);



// We also need a function to set variable undelcated when outside sceop


//TBC for typercherks
/*
int variableAssigneent(struct FunctionList *thisFunctionList,
                       char *functionName,char *variableName,char *assignmentType);
*/

char * returnStructureTypeofVariable(struct FunctionList* thisFunctionList,char *functionnName,char *variables);



//----------------------------------------------------------------
//HashMap here

//void print_functionInfo(struct  FunctionList* thisFunctionList,char *functionName);
#endif