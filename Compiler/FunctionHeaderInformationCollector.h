//
// Created by Mingwei Shi on 31/03/2022.
//

#ifndef FUNCTIONHEADERINFORMATIONCOLLECTOR_FUNCTIONHEADERINFORMATIONCOLLECTOR_H
#define FUNCTIONHEADERINFORMATIONCOLLECTOR_FUNCTIONHEADERINFORMATIONCOLLECTOR_H


/*
 *
 * This strucure is for function type checking
 */
#define VAILD_VOLD_FUNCTION_CALL 1
#define NOVAILD_VOID_FUNCTION_CALL 0

#define VAILD_NON_VOID_FUNCTION_CALL 1
#define INVAILD_NON_VOID_FUNCTION_CALL 0

#define VAILD_RETURN_DECLARATION_TYPE_CONSITANCE 1
#define NOT_VAILD_RETURN_DECLARATION_TYPE_CONSITANCE 0
#define Proper_function_Parameter_count 1
#define Missing_Match_function_Parameter_count 0
#include<stdio.h>
#define MAX_SIZE 1024
struct functionHeaderParameterNode
{
    char parameterType[MAX_SIZE];
    char parameterName[MAX_SIZE];

};
struct FunctionHeader
{
    char functionName[MAX_SIZE];
    char functionDeclaringType[MAX_SIZE];
    char functionReturnType[MAX_SIZE];
    int functionParameterNumber;
    struct functionHeaderParameterNode functionParameterList[MAX_SIZE];

};

struct FunctionHeaderInformationList
{
    struct FunctionHeader functionHeaderList[MAX_SIZE];
};
/*
 *
 * Construction
 */
struct FunctionHeaderInformationList * initilizaion_functionHeaderinformation(struct FunctionHeaderInformationList *thisFunctionHeaderInformationList);

void addFunctionDeclartionType_ID_InFunctionHeaderList(struct FunctionHeaderInformationList *thisFunctionHeaderInformationList,char *functionDelcaringType,char *functionID);


void addFunctionReturnType_InFunctionHeaderList(struct FunctionHeaderInformationList *thisFunctionHeaderInformationList,char *functionName,char *functionReturnType);


void addFunctionFunctionParameterInFunctionHeaderList(struct FunctionHeaderInformationList *thisFunctionHeaderInformationList,char *functionName,char* parameterType,char *parameterID);

int getSpecifificFunctionParameterCount(struct FunctionHeaderInformationList *thisFunctionHeaderInformationList,char *functionName);

struct functionHeaderParameterNode* getFunctionParameterList(struct FunctionHeaderInformationList *thisFunctionHeaderInformationList,char *functionName);




/*
 *
 */


/*
 * 1 is calling function size is right
 * 0 not right
 */
// e reuqirment
int checkingFunctionParameterSizeCounter(struct FunctionHeaderInformationList *thisFunctionHeaderInformationList,char *functionName,int expressionListlength);

/*
 * 1 all right ,
 * 0 not all right
 *
 */
// e quriement
// this function is basd on the assumption of function parameter size right
// i think we don't need this
// Since func(a +1,I would test it for expression
//int checkingFunctionParamterTypeChecker(struct FunctionHeaderInformationList *thisFunctionHeaderInformationList,char *functionName,int expressionListlength)
// Parameter type is checking be ID and we scope check and expresion check

//e requriment global type is the type of LHS ,ID = funct();
int nonVoidFunctionCallChecking(struct FunctionHeaderInformationList *thisFunctionHeaderInformationList,char *functionName,char * globalType);
// e requriement I think

// A requirement
int functionDeclarationTypeMatchingReturnTypeOrNot(struct FunctionHeaderInformationList *thisFunctionHeaderInformationList,char *functionName);

#endif //FUNCTIONHEADERINFORMATIONCOLLECTOR_FUNCTIONHEADERINFORMATIONCOLLECTOR_H
