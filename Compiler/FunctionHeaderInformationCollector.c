//
// Created by Mingwei Shi on 31/03/2022.
//

#include "FunctionHeaderInformationCollector.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct FunctionHeaderInformationList * initilizaion_functionHeaderinformation(struct FunctionHeaderInformationList *thisFunctionHeaderInformationList)
{
    struct FunctionHeaderInformationList *myFunctionHeaderList;
    myFunctionHeaderList = (struct FunctionHeaderInformationList*)malloc(sizeof (struct FunctionHeaderInformationList));
    for(int i = 0 ;i<MAX_SIZE;i++)
    {
        strcpy(myFunctionHeaderList->functionHeaderList[i].functionName,"NULL");

        strcpy(myFunctionHeaderList->functionHeaderList[i].functionDeclaringType,"NULL");

        strcpy(myFunctionHeaderList->functionHeaderList[i].functionReturnType,"NULL");

        myFunctionHeaderList->functionHeaderList[i].functionParameterNumber=0;

        for(int j = 0 ;j<MAX_SIZE;j++)
        {
            strcpy(myFunctionHeaderList->functionHeaderList[i].functionParameterList[j].parameterType,"NULL");


            strcpy(myFunctionHeaderList->functionHeaderList[i].functionParameterList[j].parameterName,"NULL");

        }


    }
    return myFunctionHeaderList;
}

void addFunctionDeclartionType_ID_InFunctionHeaderList(struct FunctionHeaderInformationList *thisFunctionHeaderInformationList,char *functionDelcaringType,char *functionID)
{
    for(int i = 0 ;i<MAX_SIZE;i++)
    {
        char *emptyString = "NULL";
        if(strcmp(thisFunctionHeaderInformationList->functionHeaderList[i].functionName,emptyString)==0)
        {
            strcpy(thisFunctionHeaderInformationList->functionHeaderList[i].functionName,functionID);
            strcpy(thisFunctionHeaderInformationList->functionHeaderList[i].functionDeclaringType,functionDelcaringType);

            return ;
        }
    }
}

void addFunctionReturnType_InFunctionHeaderList(struct FunctionHeaderInformationList *thisFunctionHeaderInformationList,char *functionName,char *functionReturnType) {
    char copyFunctionName[MAX_SIZE];
    strcpy(copyFunctionName, functionName);
    for (int i = 0; i < MAX_SIZE; i++) {
        //char *copyFunctionName = thisFunctionHeaderInformationList->functionHeaderList[i].functionName;

        if (strcmp(thisFunctionHeaderInformationList->functionHeaderList[i].functionName, copyFunctionName) == 0) {
            strcpy(thisFunctionHeaderInformationList->functionHeaderList[i].functionReturnType, functionReturnType);

            return;
        }
    }
}

void addFunctionFunctionParameterInFunctionHeaderList(struct FunctionHeaderInformationList *thisFunctionHeaderInformationList,char *functionName,char* parameterType,char *parameterID)
{
    char copyFunctionName[MAX_SIZE];
    strcpy(copyFunctionName, functionName);
    for(int i = 0 ;i<MAX_SIZE;i++)
    {


        if (strcmp(thisFunctionHeaderInformationList->functionHeaderList[i].functionName, copyFunctionName) == 0)
        {

            for(int j = 0 ;j<MAX_SIZE;j++)
            {
                char *emptyString = "NULL";
                if(strcmp(thisFunctionHeaderInformationList->functionHeaderList[i].functionParameterList[j].parameterName,emptyString)==0)
                {
                    strcpy(thisFunctionHeaderInformationList->functionHeaderList[i].functionParameterList[j].parameterType,parameterType);


                    strcpy(thisFunctionHeaderInformationList->functionHeaderList[i].functionParameterList[j].parameterName,parameterID);

                    thisFunctionHeaderInformationList->functionHeaderList[i].functionParameterNumber+=1;
                    return;

                }

            }



        }





    }

}

/*
 * Checker function
 *
 *
 */
int checkingFunctionParameterSizeCounter(struct FunctionHeaderInformationList *thisFunctionHeaderInformationList,char *functionName,int expressionListlength)
{
    char copyFunctionName[MAX_SIZE];
    strcpy(copyFunctionName, functionName);

    for (int i = 0; i < MAX_SIZE; i++) {
        //char *copyFunctionName = thisFunctionHeaderInformationList->functionHeaderList[i].functionName;

        if (strcmp(thisFunctionHeaderInformationList->functionHeaderList[i].functionName, copyFunctionName) == 0) {
            int parameterNumber = thisFunctionHeaderInformationList->functionHeaderList[i].functionParameterNumber;
            if(parameterNumber == expressionListlength)
            {
                return Proper_function_Parameter_count;
            }
            else{
                return Missing_Match_function_Parameter_count;
            }

        }
    }
    return Missing_Match_function_Parameter_count;
}

// need to match the global type
int nonVoidFunctionCallChecking(struct FunctionHeaderInformationList *thisFunctionHeaderInformationList,char *functionName,char * globalType)
{
    char copyFunctionName[MAX_SIZE];
    strcpy(copyFunctionName, functionName);

    for (int i = 0; i < MAX_SIZE; i++) {
        //char *copyFunctionName = thisFunctionHeaderInformationList->functionHeaderList[i].functionName;

        if (strcmp(thisFunctionHeaderInformationList->functionHeaderList[i].functionName, copyFunctionName) == 0)
        {
            char functionDelcartionType[MAX_SIZE];
            strcpy(functionDelcartionType,thisFunctionHeaderInformationList->functionHeaderList[i].functionDeclaringType);
            if(strcmp(functionDelcartionType,globalType)==0)
            {
                return VAILD_NON_VOID_FUNCTION_CALL;
            }
            else{
                return INVAILD_NON_VOID_FUNCTION_CALL;
            }

        }
    }
    return INVAILD_NON_VOID_FUNCTION_CALL;
}
// e requriement I think

// A requirement
int functionDeclarationTypeMatchingReturnTypeOrNot(struct FunctionHeaderInformationList *thisFunctionHeaderInformationList,char *functionName)
{
    char copyFunctionName[MAX_SIZE];
    strcpy(copyFunctionName, functionName);
    for (int i = 0; i < MAX_SIZE; i++) {
        //char *copyFunctionName = thisFunctionHeaderInformationList->functionHeaderList[i].functionName;

        if (strcmp(thisFunctionHeaderInformationList->functionHeaderList[i].functionName, copyFunctionName) == 0) {

            char *declarationType = thisFunctionHeaderInformationList->functionHeaderList[i].functionDeclaringType;
            char *returnType      = thisFunctionHeaderInformationList->functionHeaderList[i].functionReturnType;
            if(strcmp(declarationType,returnType)==0)
            {
                return  VAILD_RETURN_DECLARATION_TYPE_CONSITANCE;
            }
            else{
                return NOT_VAILD_RETURN_DECLARATION_TYPE_CONSITANCE;
            }

        }
    }
    return NOT_VAILD_RETURN_DECLARATION_TYPE_CONSITANCE;
}

struct functionHeaderParameterNode* getFunctionParameterList(struct FunctionHeaderInformationList *thisFunctionHeaderInformationList,char *functionName)
{
    char copyFunctionName[MAX_SIZE];
    struct functionHeaderParameterNode* returnNodeEmpty;
    strcpy(copyFunctionName, functionName);
    for (int i = 0; i < MAX_SIZE; i++) {
        //char *copyFunctionName = thisFunctionHeaderInformationList->functionHeaderList[i].functionName;

        if (strcmp(thisFunctionHeaderInformationList->functionHeaderList[i].functionName, copyFunctionName) == 0) {

           struct functionHeaderParameterNode* returnNode = thisFunctionHeaderInformationList->functionHeaderList[i].functionParameterList;

           return returnNode;

        }
    }
    return returnNodeEmpty;
}

int getSpecifificFunctionParameterCount(struct FunctionHeaderInformationList *thisFunctionHeaderInformationList,char *functionName)
{
    char copyFunctionName[MAX_SIZE];
    struct functionHeaderParameterNode* returnNodeEmpty;
    int totalCountParameter;
    strcpy(copyFunctionName, functionName);
    for (int i = 0; i < MAX_SIZE; i++) {
        //char *copyFunctionName = thisFunctionHeaderInformationList->functionHeaderList[i].functionName;

        if (strcmp(thisFunctionHeaderInformationList->functionHeaderList[i].functionName, copyFunctionName) == 0) {

           // struct functionHeaderParameterNode* returnNode = thisFunctionHeaderInformationList->functionHeaderList[i].functionParameterList;
            totalCountParameter =thisFunctionHeaderInformationList->functionHeaderList[i].functionParameterNumber;

            return totalCountParameter;

        }
    }
    return totalCountParameter;
}
