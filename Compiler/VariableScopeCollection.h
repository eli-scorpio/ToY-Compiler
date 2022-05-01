//
// Created by Mingwei Shi on 30/03/2022.
//

#ifndef VARAIBLESCOPECOLLECTION_VARIABLESCOPECOLLECTION_H
#define VARAIBLESCOPECOLLECTION_VARIABLESCOPECOLLECTION_H



#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE 1024
#define SWITCH_ON 1
#define SWITH_OFF 0

#define RECLRATED 0
#define NOT_RECLARED 1


#define UNDELCARED 0
#define NOT_UNCLEATION 1

#define Having_Assignment_Value 1
#define Not_Having_Assignment_value 0
struct VariableWithScope
{
    char variableType[MAX_SIZE];
    char variableID[MAX_SIZE];
    int theScopeOfThisVarible;
    // we could use this variable1
    int vailedUsageRange;
    // Having assignment
    int assignmentChecker;
};
struct VariableScopeArray
{
    // I would creat the 1024 size for intilization
    struct VariableWithScope myVariableScopeArray[MAX_SIZE];
};

struct VariableScopeArray*  initilization_And_Reset_variableScopearray(struct VariableScopeArray* thisVariableScopeArray);

void inserionOfVaraibelScopeArray(struct VariableScopeArray* thisVariableScopeArray,char *variableType,char *variableID,int scopeOFvarable);
void closeUsageOfVariable(struct VariableScopeArray* thisVariableScopeArray,int scopeTobeclose);

int checkVariableRecelarationVariableScopeArray(struct VariableScopeArray* thisVariableScopeArray,char *variableId,int globalScope);


int checkVariableUndeclarationVariableScopeArray(struct VariableScopeArray* thisVariableScopeArray,char *variableId,int globalScope);

char* returnTypeOfVaribleInVaribaleScopeArray(struct VariableScopeArray* thisVariableScopeArray,char *variableId,int globalScope);
/*
 * Checking unsignmentOrnot for expression use
 * Before using this expresion like
 * int i;
 * i = 5 ;// we need to type check here
 *          // If we check LHS = RHS type open assignmentChecker
 *          then using it into the expression to fill the daflute type value
 *
 *
 */
 void assignmentCheckerOpenForVariableScopeArray(struct VariableScopeArray* thisVariableScopeArray,char *variableId,int globalScope);
 void assignmentCheckerCloseForVariableScopeArray(struct VariableScopeArray* thisVariableScopeArray,char *variableId,int globalScope);
 
 int checkAssignedAlreadyVariableInVariabelScopeArray(struct VariableScopeArray* thisVariableScopeArray,char *variableId,int globalScope);
 //void assignmentCheckerCloseForVariableScopeArray(struct VariableScopeArray* thisVariableScopeArray,char *variableId,int globalScope);
 

#endif