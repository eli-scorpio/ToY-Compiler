//
// Created by Mingwei Shi on 29/03/2022.
//

#include "ArrayFunctionStack.h"
#include<stdlib.h>
#include<string.h>

#include "IndexLinklist.h"
#include "IndexLinklist.c"

struct ArrayFunctionStackList * Arrayinit_FunctionList(struct ArrayFunctionStackList *thisFunctionList) {

    thisFunctionList = (struct ArrayFunctionStackList *) malloc(sizeof(struct ArrayFunctionStackList));
 //   int i
    for (int i = 0; i < MAX_SIZE; i++) {
        // First loop is for iterateed each function
        //struct FunctionStack tempFunctionStack =  result->functionList[i];
        strcpy(thisFunctionList->functionList[i].functionName, "NULL");

        //thisFunctionList->functionList[i].functionName ="NULL";

        //thisFunctionList->functionList[i].functionDeclrationType ="NULL";
        strcpy(thisFunctionList->functionList[i].functionDeclrationType, "NULL");


        strcpy(thisFunctionList->functionList[i].functionReturnType, "void");

        //thisFunctionList->functionList[i].functionReturnType ="void";

        thisFunctionList->functionList[i].numberOfBrackers = 0;
        //thisFunctionList->functionList[i].variableExistingChecker = CreateHashMap(MAX_SIZE);
        // curent
        //int j;

        for (int j = 0; j < MAX_SIZE; j++) {


            //thisFunctionList->functionList[i].filedList[j].Declrationtype ="NULL";
            strcpy(thisFunctionList->functionList[i].filedList[j].Declrationtype, "NULL");

            //thisFunctionList->functionList[i].filedList[j].identificationName="NULL";

            strcpy(thisFunctionList->functionList[i].filedList[j].identificationName, "NULL");

            thisFunctionList->functionList[i].filedList[j].decleationed = 0;

            //thisFunctionList->functionList[i].filedList[j].assignmentValue="NULL";

            strcpy(thisFunctionList->functionList[i].filedList[j].assignmentValue, "NULL");

            //thisFunctionList->functionList[i].filedList[j].assignmentType="NULL";

            strcpy(thisFunctionList->functionList[i].filedList[j].assignmentType, "NULL");
            thisFunctionList->functionList[i].filedList[j].scopingSwtich = UNDEF_SCOPE;
            thisFunctionList->functionList[i].filedList[j].belongtoWhichScope = 0;


        }


    }
    return thisFunctionList;

}

void ArrayInsertFunctionName(struct ArrayFunctionStackList *thisFunctionList, char *functionName, char* functionDeclrationType) {
    struct ArrayFunctionStackList *temFunctioneList = thisFunctionList;
   //int i;
    for (int i = 0; i < MAX_SIZE; i++) {
        char *tempName = temFunctioneList->functionList[i].functionName;
        char *tempFunctionDelcationType = temFunctioneList->functionList[i].functionDeclrationType;
        char *empatyString = "NULL";
        if ((strcmp(tempName, empatyString) == 0)) {

            //thisFunctionList->functionList[i].functionName = functionName;
            strcpy(thisFunctionList->functionList[i].functionName, functionName);
            //thisFunctionList->functionList[i].functionDeclrationType = functionDeclrationType;
            strcpy(thisFunctionList->functionList[i].functionDeclrationType, functionDeclrationType);
            return;
        }

    }
}
void ArrayInsertFunctionReturnType(struct ArrayFunctionStackList *thisFunctionList, char *functionName, char* functionReturnType)
{
    struct ArrayFunctionStackList *temFunctioneList = thisFunctionList;
    //int i;
    for(int i = 0 ;i<MAX_SIZE;i++)
    {
        char *tempName = temFunctioneList->functionList[i].functionName;
        //   char *tempFunctionDelcationType = temFunctioneList->functionList[i].functionDeclrationType;
        char *matchingFunctionName = functionName;
        if((strcmp(tempName,matchingFunctionName)==0))
        {
            //thisFunctionList->functionList[i].functionReturnType = functionReturnType;
            strcpy(thisFunctionList->functionList[i].functionReturnType,functionReturnType);
            return;
        }

    }
}

void ArraybracketControlAdd(struct ArrayFunctionStackList *thisFunctionList, char *functionName)
{

    for(int i = 0 ;i<MAX_SIZE;i++) {
        char *temp = thisFunctionList->functionList[i].functionName;
        if (strcmp(temp, functionName) == 0) {
            thisFunctionList->functionList[i].numberOfBrackers += 1;
        }
    }
}
void ArraybracketControlSub(struct ArrayFunctionStackList *thisFunctionList, char *functionName)
{

    for(int i = 0 ;i<MAX_SIZE;i++) {
        char *temp = thisFunctionList->functionList[i].functionName;
        if (strcmp(temp, functionName) == 0) {
            thisFunctionList->functionList[i].numberOfBrackers -= 1;
        }
    }
}
void ArrayInsertVariableDeclarationforSpecificFunction(struct ArrayFunctionStackList *thisFunctionList, char *functionName, char *functionDeclartionType, char * variableDeclartionType, char *variableName)
{
    struct ArrayFunctionStackList *temFunctioneList = thisFunctionList;

   for(int i = 0 ;i<MAX_SIZE;i++)
    {
        // First loop is for iterateed each function
        char *tempFunctionName = temFunctioneList->functionList[i].functionName;
        if(strcmp(tempFunctionName,functionName)==0)
        {
            // Inseerting list;

            int currentSceop = thisFunctionList->functionList[i].numberOfBrackers;
            struct ArrayFunctionFiled *tempFunctionFiledList = temFunctioneList->functionList[i].filedList;
            for(int j = 0 ;j<MAX_SIZE;j++)
            {
                char *empatyString = "NULL";
                char *tempVariableType = tempFunctionFiledList[j].Declrationtype;
                char *tempVairblaeName = tempFunctionFiledList[j].identificationName;
                if((strcmp(tempVariableType,empatyString)==0)&&(strcmp(tempVairblaeName,empatyString)==0))
                {
                    //       InsertHashMap( thisFunctionList->functionList[i].variableExistingChecker,variableName);
                    //  thisFunctionList->functionList[i].variableExistingChecker
                    // thisFunctionList->functionList[i].filedList[j].Declrationtype = variableDeclartionType;
                    strcpy(thisFunctionList->functionList[i].filedList[j].Declrationtype,variableDeclartionType);

                    thisFunctionList->functionList[i].filedList[j].decleationed = 1;
                    // strcpy()

                    //    thisFunctionList->functionList[i].filedList[j].identificationName = variableName;

                    strcpy(thisFunctionList->functionList[i].filedList[j].identificationName,variableName);

                    thisFunctionList->functionList[i].filedList[j].scopingSwtich=START_SCOPE;

                    thisFunctionList->functionList[i].filedList[j].belongtoWhichScope =currentSceop;

                    // thisFunctionList->functionList[i].filedList[j].decleationed =1;



                }

            }

        }

    }
}

void ArraycloseScopeOfVariable(struct ArrayFunctionStackList *thisFunctionList, char * functionName) {
    struct ArrayFunctionStackList *tempList = thisFunctionList;

    for (int i = 0; i < MAX_SIZE; i++) {
        char *tempFunName = tempList->functionList[i].functionName;
        int currentBigScope = tempList->functionList[i].numberOfBrackers;
        if (strcmp(tempFunName, functionName) == 0) {

            for (int j = 0; j < MAX_SIZE; j++) {
                //Checking the global scope is the as
                int variableSceop = tempList->functionList[i].filedList[j].belongtoWhichScope;
                // char * tempVariable = tempList->functionList[i].filedList[j].identificationName;
                if (variableSceop == currentBigScope) {
                    int theTigerindex = ArraytigherScopeIndexForVariable(thisFunctionList, functionName, tempFunName);
                    char *variabeleToModify = thisFunctionList->functionList[i].filedList[theTigerindex].identificationName;
                    ArraymodifyVariableScope(thisFunctionList, functionName, variabeleToModify, END_SCOPE);
                }
            }

        }
    }
}
void ArraymodifyVariableScope(struct ArrayFunctionStackList *thisFunctionList, char *functionName, char *variableName, int scope_code) {
    struct ArrayFunctionStackList *tempFunctionList = thisFunctionList;

    for (int i = 0; i < MAX_SIZE; i++) {
        char *tempFunctionName = tempFunctionList[i].functionList->functionName;
        // char *tempFunctionDeclrationType  = tempFunctionList[i].functionList->functionDeclrationType;
        /*
         *
         * Finding the lastscope variable here
         */
        if ((strcmp(tempFunctionName, functionName) == 0)) {
// we only deal with variable that appear
/*int a
 * for(int i = 0 ;i<10;i++_
 * {
 * int a;
 * a = 5;

 * }
 */
//      we guarrante here it has variable since we need to modify existing
//  variable
            int tigerIndex = ArraytigherScopeIndexForVariable(thisFunctionList, functionName, variableName);

            thisFunctionList->functionList->filedList[tigerIndex].scopingSwtich = scope_code;

        }
    }
}

int ArraytigherScopeIndexForVariable(struct ArrayFunctionStackList *thisFunctionList,char *functionName,char *variableName)
{
    LNode *myIndexList = indexListInitlization(myIndexList);
    int largerestIndex =0;


    // Using Max Heap to return the largerest index currenttl
    char tempFunctionName[MAX_SIZE];

    for(int i = 0 ; i <MAX_SIZE;i++)
    {
        //  char *tempFunctionName = thisFunctionList->functionList[i].functionName;
        strcpy(tempFunctionName,thisFunctionList->functionList[i].functionName);
        if(strcmp(tempFunctionName,functionName)==0)
        {

            for(int j = 0;j<MAX_SIZE;j++)
            {
                char *tempVariableName = thisFunctionList[i].functionList->filedList[j].identificationName;
                int tempDeclaration =thisFunctionList[i].functionList->filedList[j].decleationed;
                int tempScopeSwtich = thisFunctionList[i].functionList->filedList[j].scopingSwtich;
                if((strcmp(tempVariableName,variableName)==0) &&(tempDeclaration == 1)&&(tempScopeSwtich ==START_SCOPE))
                {

                    // headInsertIndexLinklist(myIndexList,j);
                    headInsertIndexLinklist(myIndexList,j);

                }
            }

        }
    }


    if(checkEmpty(myIndexList)==0)
    {
        // error
        return -1;
    }
    else
    {
        largerestIndex = getLatestIndex(myIndexList);
        return largerestIndex;
    }
}
char *ArrayreturnStructureTypeofVariable(struct ArrayFunctionStackList* thisFunctionList, char *functionnName, char *variable)
{

    char tempType[MAX_SIZE];
    char *tempNull = "NULL";
    for (int i = 0; i < MAX_SIZE; i++) {


        char *tempFunctionName = thisFunctionList->functionList[i].functionName;
        if (strcmp(tempFunctionName, functionnName) == 0) {

            //int tigherIndex = tigherScopeIndexForVariable(thisFunctionList, functionnName, variable);

            for(int j = 0 ;j<MAX_SIZE ;j++)
            {
               // int swithOnStatus;
                char *tempVariable = thisFunctionList->functionList[j].filedList[j].identificationName;
                if(strcmp(tempVariable,variable)==0)
                {
                    strcpy(tempType,thisFunctionList->functionList[i].filedList[j].Declrationtype);
                    char *returnvalue =tempType;
                    return returnvalue;
                }
                //tempType = thisFunctionList[i].functionList->filedList[tigherIndex].Declrationtype;
                //  return tempType;
            }

        }
    }
    return tempNull;
    //return tempType;
}

void ArrayinsertVariableDeclarationforSpecificFunction(struct ArrayFunctionStackList *thisFunctionList, char *functionName, char *functionDeclartionType, char * variableDeclartionType, char *variableName)
{
      struct ArrayFunctionStackList *temFunctioneList = thisFunctionList;

    for(int i = 0 ;i<MAX_SIZE;i++)
    {
        // First loop is for iterateed each function
        char *tempFunctionName = temFunctioneList->functionList[i].functionName;
        if(strcmp(tempFunctionName,functionName)==0)
        {
            // Inseerting list;

            int currentSceop = thisFunctionList->functionList[i].numberOfBrackers;
            struct ArrayFunctionFiled *tempFunctionFiledList = temFunctioneList->functionList[i].filedList;
            for(int j = 0 ;j<MAX_SIZE;j++)
            {
                char *empatyString = "NULL";
                char *tempVariableType = tempFunctionFiledList[j].Declrationtype;
                char *tempVairblaeName = tempFunctionFiledList[j].identificationName;
                if((strcmp(tempVariableType,empatyString)==0)&&(strcmp(tempVairblaeName,empatyString)==0))
                {
             //       InsertHashMap( thisFunctionList->functionList[i].variableExistingChecker,variableName);
                  //  thisFunctionList->functionList[i].variableExistingChecker
                   // thisFunctionList->functionList[i].filedList[j].Declrationtype = variableDeclartionType;
                    strcpy(thisFunctionList->functionList[i].filedList[j].Declrationtype,variableDeclartionType);

                    thisFunctionList->functionList[i].filedList[j].decleationed = 1;
                   // strcpy()
                    
                //    thisFunctionList->functionList[i].filedList[j].identificationName = variableName;

                    strcpy(thisFunctionList->functionList[i].filedList[j].identificationName,variableName);

                    thisFunctionList->functionList[i].filedList[j].scopingSwtich=START_SCOPE;

                    thisFunctionList->functionList[i].filedList[j].belongtoWhichScope =currentSceop;

                   // thisFunctionList->functionList[i].filedList[j].decleationed =1;



                }

            }

        }

    }
}


int ArraycheckUndeclaratedVaraible(struct ArrayFunctionStackList *thisArrayFunctionList, char *functionName,
                              char *variableName)
{
      struct ArrayFunctionStackList *temFunctioneList = thisArrayFunctionList;
   //int i;
     char tempFunctionName[MAX_SIZE];
    for(int i = 0 ;i<MAX_SIZE;i++)
    {
        // First loop is for iterateed each function
        //char *tempFunctionName = temFunctioneList->functionList[i].functionName;
        strcmp(tempFunctionName,temFunctioneList->functionList[i].functionName);
        if(strcmp(tempFunctionName,functionName)==0)
        {
            // Inseerting list;
            //int j;
            /*
             *  int tigherIndex = tigherScopeIndexForVariable(thisFunctionList,functionName,variableName);
            if(tigherIndex == -1)
            {
                return 1;
            }
            else
            {
               return 0;
            }
             */

            for(int j = 0 ;j<MAX_SIZE;j++)
            {
                int variableScope = thisArrayFunctionList->functionList[i].filedList->scopingSwtich;
                char tempVaribaleName[MAX_SIZE];
                strcmp(tempVaribaleName,thisArrayFunctionList->functionList[i].filedList[j].identificationName);
                //char *tempVaribaleName = thisArrayFunctionList->functionList[i].filedList[j].identificationName;
                if((strcmp(tempVaribaleName,variableName)==0)&&(variableScope==START_SCOPE))
                {
                    return 1;
                }
            }
        }

    }
    return 0;
}