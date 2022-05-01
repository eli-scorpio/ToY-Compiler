
#include "VariableScopeCollection.h"
#include "variableIndexLinkList.h"
#include "variableIndexLinkList.c"
//#include "variableIndexLinkList.c"
struct VariableScopeArray*  initilization_And_Reset_variableScopearray(struct VariableScopeArray* thisVariableScopeArray) {
    thisVariableScopeArray = malloc(sizeof(struct VariableScopeArray));

    for (int i = 0; i < MAX_SIZE; i++) {
        strcpy(thisVariableScopeArray->myVariableScopeArray[i].variableID, "NULL");
        strcpy(thisVariableScopeArray->myVariableScopeArray[i].variableType, "NULL");
        thisVariableScopeArray->myVariableScopeArray[i].theScopeOfThisVarible = 0;
        thisVariableScopeArray->myVariableScopeArray[i].vailedUsageRange = SWITH_OFF;
        thisVariableScopeArray->myVariableScopeArray[i].assignmentChecker=Not_Having_Assignment_value;
        //strcpy()
    }
    return thisVariableScopeArray;
}

void inserionOfVaraibelScopeArray(struct VariableScopeArray* thisVariableScopeArray,char *variableType,char *variableID,int scopeOFvarable) {
    //struct VariableScopeArray *tempVariableList = thisVariableScopeArray;

    char tempName[1024];
    char *tempVariableCopy = variableID;
    for (int i = 0; i < MAX_SIZE; i++) {
        char *empatyString = "NULL";
        //char *tempName =thisVariableScopeArray->myVariableScopeArray[i].variableID;

        //char *tempName = tempVariableList->myVariableScopeArray[i].variableID;
        strcpy(tempName, thisVariableScopeArray->myVariableScopeArray[i].variableID);
        if (strcmp(tempName, empatyString) == 0) {
            strcpy(thisVariableScopeArray->myVariableScopeArray[i].variableID, variableID);
            strcpy(thisVariableScopeArray->myVariableScopeArray[i].variableType, variableType);
            thisVariableScopeArray->myVariableScopeArray[i].vailedUsageRange = SWITCH_ON;
            thisVariableScopeArray->myVariableScopeArray[i].theScopeOfThisVarible = scopeOFvarable;
            return;

        }
    }

}

//when } close all the scope with gloabl scope
void closeUsageOfVariable(struct VariableScopeArray* thisVariableScopeArray,int scopeTobeclose)
{
    //struct VariableScopeArray *tempVariableList = thisVariableScopeArray;
    //int i;
    // char tempName[1024];
    int scopeToBeClose = scopeTobeclose;
    for(int i = 0;i<MAX_SIZE;i++)
    {
        int tempScope = thisVariableScopeArray->myVariableScopeArray[i].theScopeOfThisVarible;
        if(tempScope==scopeToBeClose)
        {
            thisVariableScopeArray->myVariableScopeArray->vailedUsageRange=SWITH_OFF;
        }
    }

    return;
}
/*
 * int a
 * for(
 * {
 *  int a
 * }
 *
 */
int checkVariableRecelarationVariableScopeArray(struct VariableScopeArray* thisVariableScopeArray,char *variableId,int globalScope)
{

    // nt i
    variableLNode  *myScopeList;
    myScopeList = variableIndexListInitlization(myScopeList);
    int gloablScopeCopy = globalScope;
    //
    for(int i = 0;i<MAX_SIZE;i++)
    {
        // int tempScope = thisVariableScopeArray->myVariableScopeArray[i].theScopeOfThisVarible;
        char *tempName=thisVariableScopeArray->myVariableScopeArray[i].variableID;
        //int tempScope = thisVariableScopeArray->myVariableScopeArray[i].vailedUsageRange;
        //  strcpy(tempName,thisVariableScopeArray->myVariableScopeArray[i].variableID);
        if((strcmp(tempName,variableId)==0))
        {
            int tempScope = thisVariableScopeArray->myVariableScopeArray[i].theScopeOfThisVarible;
            /*
             * int a;1
             * for()
             * {
             *      int a; 2
             *      int a;
             * }
             */
            headInsertVariableIndexLinklist(myScopeList,tempScope);

        }

    }
    //no ID
    int empptyCheck = checkEmptyVariableIndexLinklist(myScopeList);
    if(empptyCheck==0)
    {
        return NOT_RECLARED;
    }
    else{
        // 1
        int headOfScope = getLatestIndexVariableIndexLinklist(myScopeList);
        if(headOfScope<gloablScopeCopy)
        {
            return NOT_RECLARED;
        }
        else if(headOfScope>=gloablScopeCopy){
            return RECLRATED;
        }
    }

    return NOT_RECLARED;
}
// Matching with globalsCOP
/*
 * For int a1
 * for(int i =0;i<9;i++)
 * {
 *     // int a;
 *      a = 5; 2
 * }
 */
int checkVariableUndeclarationVariableScopeArray(struct VariableScopeArray* thisVariableScopeArray,char *variableId,int globalScope)
{
    // int i;
    int gloablScopeCopy = globalScope;
    //char tempName[1024];
    variableLNode  *myList;
    myList = variableIndexListInitlization(myList);
    for(int i = 0;i<MAX_SIZE;i++)
    {
        int tempScope = thisVariableScopeArray->myVariableScopeArray[i].theScopeOfThisVarible;
        // strcpy(tempName,thisVariableScopeArray->myVariableScopeArray[i].variableID);
        char *tempName =thisVariableScopeArray->myVariableScopeArray[i].variableID ;
        int currentUsage=thisVariableScopeArray->myVariableScopeArray[i].vailedUsageRange;
        if((strcmp(tempName,variableId)==0)&&(currentUsage==SWITCH_ON))
        {
            if(tempScope<=gloablScopeCopy)
            {
                // vailed
                // Adding a linklist
                //eturn 1;
                headInsertVariableIndexLinklist(myList,i);

            }

        }

    }
    // then checking linklis is empty or not
    if( checkEmptyVariableIndexLinklist(myList)==0)
    {
        return UNDELCARED;
    }
    else
    {
        return NOT_UNCLEATION;
    }

}
/*
 * Func1()
 * {
 *  int i;
 *  for()
 *  {
 *      bool b;
 *      i
 *  }
 * }
 */
char* returnTypeOfVaribleInVaribaleScopeArray(struct VariableScopeArray* thisVariableScopeArray,char *variableId,int globalScope)
{
    for(int i = 0 ;i<MAX_SIZE;i++)
    {
        char *tempId = thisVariableScopeArray->myVariableScopeArray[i].variableID;
        int tempScope = thisVariableScopeArray->myVariableScopeArray[i].theScopeOfThisVarible;
        int tempUsage = thisVariableScopeArray->myVariableScopeArray[i].vailedUsageRange;
        if(strcmp(tempId,variableId)==0&&(tempUsage==SWITCH_ON)&&(tempScope<=globalScope))
        {
            char *tempType = thisVariableScopeArray->myVariableScopeArray[i].variableType;
            return tempType;
        }
    }
    return NULL;
}
/*
 * int i;
 * i //undeclarc chec = 5;tpe cher;After selcom for assignment
 * Then open the checker
 */
void assignmentCheckerOpenForVariableScopeArray(struct VariableScopeArray* thisVariableScopeArray,char *variableId,int globalScope)
{
    for(int i = 0 ;i<MAX_SIZE;i++)
    {
        char *tempId = thisVariableScopeArray->myVariableScopeArray[i].variableID;
        int tempScope = thisVariableScopeArray->myVariableScopeArray[i].theScopeOfThisVarible;
        int tempUsage = thisVariableScopeArray->myVariableScopeArray[i].vailedUsageRange;
        if(strcmp(tempId,variableId)==0&&(tempUsage==SWITCH_ON)&&(tempScope<=globalScope))
        {
            thisVariableScopeArray->myVariableScopeArray[i].assignmentChecker=Having_Assignment_Value;

            return ;
        }
    }

}
int checkAssignedAlreadyVariableInVariabelScopeArray(struct VariableScopeArray* thisVariableScopeArray,char *variableId,int globalScope)
{
    for(int i = 0 ;i<MAX_SIZE;i++)
    {
        char *tempId = thisVariableScopeArray->myVariableScopeArray[i].variableID;
        int tempScope = thisVariableScopeArray->myVariableScopeArray[i].theScopeOfThisVarible;
        int tempUsage = thisVariableScopeArray->myVariableScopeArray[i].vailedUsageRange;
        if(strcmp(tempId,variableId)==0&&(tempUsage==SWITCH_ON)&&(tempScope<=globalScope))
        {
            if(thisVariableScopeArray->myVariableScopeArray[i].assignmentChecker==Having_Assignment_Value)
            {
                return Having_Assignment_Value;
            }
            else if(thisVariableScopeArray->myVariableScopeArray[i].assignmentChecker==Not_Having_Assignment_value)
            {
                return Not_Having_Assignment_value;
            }


        }
    }
    return Not_Having_Assignment_value;
}

 void assignmentCheckerCloseForVariableScopeArray(struct VariableScopeArray* thisVariableScopeArray,char *variableId,int globalScope)
 {
      for(int i = 0 ;i<MAX_SIZE;i++)
    {
        char *tempId = thisVariableScopeArray->myVariableScopeArray[i].variableID;
        int tempScope = thisVariableScopeArray->myVariableScopeArray[i].theScopeOfThisVarible;
        int tempUsage = thisVariableScopeArray->myVariableScopeArray[i].vailedUsageRange;
        if(strcmp(tempId,variableId)==0&&(tempUsage==SWITCH_ON)&&(tempScope<=globalScope))
        {
            thisVariableScopeArray->myVariableScopeArray[i].assignmentChecker=0;

            return ;
        }
    }     
 }