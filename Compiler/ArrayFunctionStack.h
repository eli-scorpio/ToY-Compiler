//
// Created by Mingwei Shi on 29/03/2022.
//

#ifndef NEWFUNCTIONSTACK_ARRAYFUNCTIONSTACK_H
#define NEWFUNCTIONSTACK_ARRAYFUNCTIONSTACK_H



#define UNDEF_SCOPE 0
#define START_SCOPE 1
#define END_SCOPE 2
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#define MAX_SIZE 1024
struct ArrayFunctionFiled
{
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
};
struct ArrayFunctionStack
{
    char functionDeclrationType[MAX_SIZE];
    char  functionName[MAX_SIZE];
    /*
     * For scope checking
     * when encoutner { +1
     * when ecounter } -1
     * init 0
     */
    int numberOfBrackers;

    char functionReturnType[MAX_SIZE];
    struct ArrayFunctionFiled filedList[MAX_SIZE];
    // HashMap* variableExistingChecker;
};

struct ArrayFunctionStackList
{
    struct ArrayFunctionStack functionList[MAX_SIZE];
};

//initilizat functionList
struct ArrayFunctionStackList * Arrayinit_FunctionList(struct ArrayFunctionStackList *thisFunctionList);

// Insertting a function name
//
void ArrayInsertFunctionName(struct ArrayFunctionStackList *thisFunctionList, char *functionName, char* functionDeclrationType);

void ArrayInsertFunctionReturnType(struct ArrayFunctionStackList *thisFunctionList, char *functionName, char* functionReturnType);

void ArrayinsertVariableDeclarationforSpecificFunction(struct ArrayFunctionStackList *thisFunctionList, char *functionName, char *functionDeclartionType, char * variableDeclartionType, char *variableName);

/*
 *  *********************************************
 */

// insert the declartion  of variable


void ArraybracketControlAdd(struct ArrayFunctionStackList *thisFunctionList, char *functionName);
void ArraybracketControlSub(struct ArrayFunctionStackList *thisFunctionList, char *functionName);


void ArrayInsertVariableDeclarationforSpecificFunction(struct ArrayFunctionStackList *thisFunctionList, char *functionName, char *functionDeclartionType, char * variableDeclartionType, char *variableName);

//
/*
 * For a variable with
 * {
 * statemetnlist
 * }
 * for(int i = 0 ;i <1;i++)
 */

void ArraycloseScopeOfVariable(struct ArrayFunctionStackList *thisFunctionList, char * functionName);

void ArraymodifyVariableScope(struct ArrayFunctionStackList *thisFunctionList, char *functionName, char *variableName, int scope_code);
// Next

//
/*
 * Give a variable to check the tigher scope for type checker
 */
int ArraytigherScopeIndexForVariable(struct ArrayFunctionStackList *thisFunctionList,char *functionName,char *variableName);

 

char *ArrayreturnStructureTypeofVariable(struct ArrayFunctionStackList* thisFunctionList, char *functionnName, char *variable);


int ArraycheckUndeclaratedVaraible(struct ArrayFunctionStackList *thisArrayFunctionList, char *functionName,
                              char *variableName);

#endif //NEWFUNCTIONSTACK_ARRAYFUNCTIONSTACK_H
