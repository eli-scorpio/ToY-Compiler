//
// Created by Mingwei Shi on 31/03/2022.
//

#include "ExpressionCollectionList.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
// Done
struct ExpressionTypeSystem *InitilizationAndResetOfTypeSystem(struct ExpressionTypeSystem * thisType){
    struct  ExpressionTypeSystem *myNewExpression;
    myNewExpression = (struct ExpressionTypeSystem *)malloc(sizeof(struct ExpressionTypeSystem));
    myNewExpression->environmentType = UN_DEFINED_TYPE;
   // myNewExpression->expressionType = UN_DEFINED_TYPE;
    // in baison set -1 but normal case 0
    myNewExpression->expressionNumber=0;
    for(int i = 0 ;i<MAX_SIZE;i++)
    {
        strcpy(myNewExpression->myExpressionArray[i].singleElement,"NULL");
    }


    return myNewExpression;
    //ExpressionList_initilization(&myExpressionTypeSystem->pHeadOfExpressionlist);
}
// Done
void modifyEnvironmentTypeSystemInExpressionList(struct ExpressionTypeSystem *myExpressionTypeSystem, int type)
{
    myExpressionTypeSystem->environmentType=type;
}

void typeSystem_tailInsert(struct ExpressionTypeSystem* myExpressionTypeSystem,ExpressionElement data)
{
   for(int i = 0 ;i<MAX_SIZE;i++)
   {
       char *emptyString= "NULL";
       if(strcmp(myExpressionTypeSystem->myExpressionArray[i].singleElement,emptyString)==0)
       {
           strcpy(myExpressionTypeSystem->myExpressionArray[i].singleElement,data);
           myExpressionTypeSystem->expressionNumber+=1;
           return;
       }
   }

}

void typeSystem_Print(struct ExpressionTypeSystem *myExpressionTypeSystem)
{
    int countS = myExpressionTypeSystem->expressionNumber;
    for(int i = 0;i<countS;i++)
    {
        //printf("%s ->\n",myExpressionTypeSystem->myExpressionArray[i].singleElement);
    }

}

int typeSystem_Expression_length(struct ExpressionTypeSystem *myExpressionTypeSystem)
{
    int countS = myExpressionTypeSystem->expressionNumber;
    int count =0;
    for(int i = 0;i<countS;i++)
    {
        count +=1;
       // printf("%s ->\n",myExpressionTypeSystem->myExpressionArray[i].singleElement);
    }
    return count;
}
int typeSystemSelectionAndJudgeSystem(struct ExpressionTypeSystem *myExpressionSystem) {
    int valueofEnvrionmentType = myExpressionSystem->environmentType;
    int isVaildMatchingType ;
    switch (valueofEnvrionmentType) {
        case INT_TYPE:
            //printf("Integer judge system \n");
            isVaildMatchingType = INT_TYPE_ExpressionTypeDuduction(myExpressionSystem);
            break;
        case BOOL_TYPE:
            //printf("Boolean judge system \n");
            isVaildMatchingType = BOOL_TYPE_ExpressionTypeDuciton(myExpressionSystem);
            break;
        case STRING_TYPE_IN_TYPESYSTEM:
            //printf("String judge system \n");
            isVaildMatchingType = STRING_TYPE_ExpressionTypeDuciton(myExpressionSystem);
            break;
        default:
            break;

    }
    return isVaildMatchingType;
}

int STRING_TYPE_ExpressionTypeDuciton(struct ExpressionTypeSystem *myExpressionSystem)
{
    int theLengthOfExpression =myExpressionSystem->expressionNumber;
    
    
 

    char *copyString = myExpressionSystem->myExpressionArray[0].singleElement;
    int lengthOfString = strlen(copyString);
    char myCopy[lengthOfString];
    strcpy(myCopy,copyString);
    /*printf("______________________________________________\n");
    printf("########################################################################\n");
    printf("The length of string is %s\n",copyString);
    printf("The copy in the judge system is %s\n",copyString);*/

    strcpy(myCopy,copyString);
    /*printf("The first character in the charter is %c\n",myCopy[0]);
    printf("Asci value is this one is %d\n",myCopy[0]);
    printf("The last character of this string is %c\n ",myCopy[lengthOfString-1]);
    printf("Asci value is this one is %d\n",myCopy[lengthOfString-1]);
    printf("########################################################################\n");
       
    printf("########################################################################\n");*/
    

    
    if(theLengthOfExpression ==1)
    {
        if((myCopy[0] ==34)&&(myCopy[lengthOfString-1] ==34))
        {
            return VAILD_EXPRESSION_TYPE;
        }
        else{
            return INVAILD_EXPRESSION_TYPE;
        }
    }
    else{

       

    

        
        return INVAILD_EXPRESSION_TYPE;
    }
}
// --5

int  BOOL_TYPE_ExpressionTypeDuciton(struct ExpressionTypeSystem *myExpressionSystem)
{
    int iterationNumber = myExpressionSystem -> expressionNumber;
    char firstString[MAX_SIZE];
    int digitPosition;
    //int NotSignal=0;
    char previousStringRecorder[MAX_SIZE];
    for (int i = 0; i < iterationNumber; i++) {
        /*
         * Base case
         *  not
         *          true or false
         *          digit
         *          minus
         */
        if (i == 0) {
            strcpy(firstString, myExpressionSystem -> myExpressionArray[i].singleElement);
            int booleanClauseChecker = isBooleanClasueForStringinExpressionTypeSystem(firstString);
            int isDigitCheckerInConditionExpressionfirstIteration = isIntegerTypeOFStringInTypeExpression(firstString);
            // subcase 1:true or false
            if (booleanClauseChecker == VAILD_BOOLEAN_CLASUE) {
                if (iterationNumber == 1) {
                    // the length of expression is 1 ,we could return
                    // think this is  vaild one directly
                    return Vaild_BoolExpression;
                }
                // transfer
                strcpy(previousStringRecorder, firstString);

            } //Subcase w
            else if (strcmp(firstString, "not") == 0)
            {
                if (iterationNumber == 1) {
                    return InVaild_Bool_expression;
                }
                //  NotSignal =Not_SWITCH_OFF;
                strcpy(previousStringRecorder, firstString);
            } // subcase 3
            else if (isDigitCheckerInConditionExpressionfirstIteration == VAILD_INTERGE_TYPE)
            {
                // other case is noot invail
                // 7 /  or /and -
                if (iterationNumber == 1) {
                    return InVaild_Bool_expression;
                }
                strcpy(previousStringRecorder, firstString);
                digitPosition = Left_Part_OF_interger_opeator;

            }
            else if(strcmp(firstString,"-")==0)
            {
                //-
                if(iterationNumber==1)
                {
                    return InVaild_Bool_expression;
                }
                strcpy(previousStringRecorder,firstString);
            }
            else {
                //other case :and /or/</> appear first one all
                //regard as invaid
                return InVaild_Bool_expression;
            }

        }

        if (i != 0) {
            char * currentString = myExpressionSystem -> myExpressionArray[i].singleElement;

            int caseTwoDigit = isIntegerTypeOFStringInTypeExpression(previousStringRecorder);

            int caseThreeChecker = isBooleanClasueForStringinExpressionTypeSystem(previousStringRecorder);

            //VAILD_Integer_boolean_Expression
            int caseFour = belongToInteger_ComparationOperationInExpressionTypeSystem(previousStringRecorder);

            int caseFive = belongTOBooleanTernaryOperatorInTypeSystem(previousStringRecorder);


            int caseSeven = belongtoIntegerCalculatedOperation_InTypeSystem(previousStringRecorder);

            if (strcmp(previousStringRecorder, "not") == 0)
            {

                //char * currentString = myExpressionSystem -> myExpressionArray[i].singleElement;

                int digitChekcerinthisCaseO = isIntegerTypeOFStringInTypeExpression(currentString);
                int booleanClauseChecker = isBooleanClasueForStringinExpressionTypeSystem(currentString);
                // pOSTIVE
                if (digitChekcerinthisCaseO == VAILD_INTERGE_TYPE)
                {
                    if (i == iterationNumber - 1)
                    {
                        return InVaild_Bool_expression;
                    }
                    digitPosition = Left_Part_OF_interger_opeator;
                    strcpy(previousStringRecorder, currentString);
                }
                else if (booleanClauseChecker == VAILD_BOOLEAN_CLASUE)
                {
                    if (i == iterationNumber - 1) {
                        return Vaild_BoolExpression;
                    }
                    strcpy(previousStringRecorder, currentString);
                }
                else if(strcmp(currentString,"-")==0)
                {
                    if(i ==iterationNumber-1)
                    {
                        return InVaild_Bool_expression;
                    }
                    digitPosition =Left_Part_OF_interger_opeator;
                    strcpy(previousStringRecorder,currentString);
                }
                else {
                    return InVaild_Bool_expression;
                }
            }
            else if (caseTwoDigit == VAILD_INTERGE_TYPE) {

                int tempDigitRecord = digitPosition;
                if (tempDigitRecord == Left_Part_OF_interger_opeator) {
                    int intergerOperation = belongToInteger_ComparationOperationInExpressionTypeSystem(currentString);
                    int IntegerCaclautedOperator = belongtoIntegerCalculatedOperation_InTypeSystem(currentString);


                    if (intergerOperation == VAILD_Integer_boolean_Expression) {
                        if (i == iterationNumber - 1) {
                            return InVaild_Bool_expression;
                        }
                        //other
                        strcpy(previousStringRecorder, currentString);
                        digitPosition = Right_part_of_Intger_operator;
                    }
                    else if(IntegerCaclautedOperator==Vaild_Integer_Calculated_Operator)
                    {
                        //Invaild;
                        if(i == iterationNumber-1)
                        {
                            return InVaild_Bool_expression;
                        }
                        digitPosition=Left_Part_OF_interger_opeator;
                        strcpy(previousStringRecorder,currentString);

                    }
                    else {
                        return InVaild_Bool_expression;
                    }
                }
                else if (digitPosition == Right_part_of_Intger_operator) {
                    // 7 > 7 //->AND OR
                    // 6+7 <4+)3 AND
                    int IntegerCalautedOperator = belongtoIntegerCalculatedOperation_InTypeSystem(currentString);
                    int ternaryBoolOperatorChecker = belongTOBooleanTernaryOperatorInTypeSystem(currentString);
                    if (ternaryBoolOperatorChecker == VAILD_Bool_Ternary_operator) {
                        if (i == iterationNumber - 1) {
                            return InVaild_Bool_expression;
                        }
                        strcpy(previousStringRecorder, currentString);
                    }
                    else if(IntegerCalautedOperator==Vaild_Integer_Calculated_Operator)
                    {
                        if(i ==iterationNumber-1)
                        {
                            return InVaild_Bool_expression;
                        }
                        strcpy(previousStringRecorder,currentString);
                        digitPosition=Right_part_of_Intger_operator;

                    }
                    else {
                        return InVaild_Bool_expression;
                    }
                }

            }
            else if (caseThreeChecker == VAILD_BOOLEAN_CLASUE)
            {

                /*
                   * case 3:preivous is boolean caluse true false
                   * true and/or if the last one
                   * other is invaild
                   * Current :
                   * True
                   *  True: and/or
                   *
                   *  True and false :
                        *
                        *    //  int caseThreeChecker = isBooleanClasueForStringinExpressionTypeSystem(previousStringRecorder);

                   */

                int subCaseBooleanTerency = belongTOBooleanTernaryOperatorInTypeSystem(currentString);
                if (subCaseBooleanTerency == VAILD_Bool_Ternary_operator) {
                    if (i == iterationNumber - 1) {
                        return InVaild_Bool_expression;
                    }
                    strcpy(previousStringRecorder, currentString);
                } else {
                    return InVaild_Bool_expression;
                }
            }
            else if (caseFour == VAILD_Integer_boolean_Expression) {

                /*
                 *   * case4: previous is interger operation // > <
                 *   Current one:must be digit if current is the last
                 *   not -
                 *
                 */
                //VAILD_Integer_boolean_Expression
                // int caseFour = belongToIntegerComparationOperationInConditionExpression(previousStringRecorder);

                int subJudge = isIntegerTypeOFStringInTypeExpression(currentString);
                if (subJudge == VAILD_INTERGE_TYPE) {
                    if (i == iterationNumber - 1) {
                        // 7 < 5 WELL define;
                        return Vaild_BoolExpression;
                    }
                    // MARK
                    digitPosition = Right_part_of_Intger_operator;
                    strcpy(previousStringRecorder, currentString);
                }
                else if(strcmp(currentString,"-")==0)
                {
                    if(i ==iterationNumber-1)
                    {
                        return InVaild_Bool_expression;
                    }
                    digitPosition =Right_part_of_Intger_operator;
                    strcpy(previousStringRecorder,currentString);
                }
                else {
                    return InVaild_Bool_expression;
                }
            }
            else if (caseFive == VAILD_Bool_Ternary_operator) {

                /*
                 * case 5: previous is boolean Tenerary operator and or
                 *
                 * subcase 1:
                 * True and )false/true directly vaild finished
                 *
                 * 7 <5 and/or) not ;if current is the last one ,invaild,other finish
                 * continue
                 *
                 * 7 < 5 and 7 :if digit is the last invaild;other mark the
                 * left hand sice
                 * subcase two :
                 * 7 < 5 and )true/false/not
                 * the latter one could only be true
                 */
                // int caseFive = belongTOBooleanTernaryOperatorInCondtionExpression(previousStringRecorder);

                // CASE 1 noot for current string
                if (strcmp(currentString, "not") == 0) {
                    if (i == iterationNumber - 1) {
                        return InVaild_Bool_expression;
                    }
                    strcpy(previousStringRecorder, currentString);
                }
                // CASE 2:TRUW
                int boolCasueChecker = isBooleanClasueForStringinExpressionTypeSystem(currentString);

                if (boolCasueChecker == VAILD_BOOLEAN_CLASUE) {
                    if (i == iterationNumber - 1) {
                        return Vaild_BoolExpression;
                    }
                    strcpy(previousStringRecorder, currentString);
                }
                // digit postive case 3
                int leftHandsideOfDiit = isIntegerTypeOFStringInTypeExpression(currentString);
                if (leftHandsideOfDiit == VAILD_INTERGE_TYPE) {
                    if (i == iterationNumber - 1) {
                        return InVaild_Bool_expression;
                    }
                    strcpy(previousStringRecorder, currentString);
                    digitPosition = Left_Part_OF_interger_opeator;
                }
                if(strcmp(currentString,"-")==0)
                {
                    if(i ==iterationNumber-1)
                    {
                        return InVaild_Bool_expression;
                    }
                    digitPosition=Left_Part_OF_interger_opeator;
                    strcpy(previousStringRecorder,currentString);
                }

            }
            else if(strcmp(previousStringRecorder,"-")==0)
            {
                int digitChecerkSevenCase = isIntegerTypeOFStringInTypeExpression(currentString);
                if(strcmp(currentString,"-")==0)
                {
                    if(i ==iterationNumber-1)
                    {
                        return InVaild_Bool_expression;
                    }
                    strcpy(previousStringRecorder,currentString);
                }
                else if(digitChecerkSevenCase==VAILD_INTERGE_TYPE)
                {
                    if(i ==iterationNumber-1)
                    {
                        return InVaild_Bool_expression;
                    }
                    strcpy(previousStringRecorder,currentString);
                }

            }
            else if(caseSeven ==Vaild_Integer_Calculated_Operator)
            {
                // Previous is +/-/* mod / \
                // the latter must be digit
                int lastCaseDigitcHECK = isIntegerTypeOFStringInTypeExpression(currentString);
                if(lastCaseDigitcHECK ==VAILD_INTERGE_TYPE)
                {
                    // case study
                    if(digitPosition==Left_Part_OF_interger_opeator)
                    {
                        if(i ==iterationNumber-1)
                        {
                            return InVaild_Bool_expression;
                        }
                        strcpy(previousStringRecorder,currentString);
                    }
                    else if(digitPosition ==Right_part_of_Intger_operator)
                    {
                        if(i ==iterationNumber-1)
                        {
                            return Vaild_BoolExpression;
                        }
                        strcpy(previousStringRecorder,currentString);
                    }

                }
                else{
                    return InVaild_Bool_expression;
                }

            }
            else {
                return InVaild_Bool_expression;
            }


        }

    }
    return InVaild_Bool_expression;
}


int INT_TYPE_ExpressionTypeDuduction(struct ExpressionTypeSystem *myExpressionSystem)
{
    int iterationNumber = myExpressionSystem->expressionNumber;
    char firstString[MAX_SIZE];
    char previousStringRecorder[MAX_SIZE];
    //int numberODD_EVENCounter;
    for(int i = 0;i<iterationNumber;i++)
    {

        if(i == 0)
        {
            // the first element
            // only only - or digit
            strcpy(firstString,myExpressionSystem->myExpressionArray[i].singleElement);
            int isDigitStringChecker = isIntegerTypeOFStringInTypeExpression(firstString);
            if(strcmp(firstString,"-")==0)
            {
               // strcpy(previousStringRecorder,myExpressionSystem->myExpressionArray[i].singleElement);
                if(iterationNumber ==1)
                {
                   // int a;
                    // foR CASE a = -
                    return NOT_VAILED_INTERGER_TYPE;
                }
                // other case transfer
                strcpy(previousStringRecorder,firstString);

            }
            else if(isDigitStringChecker ==VAILD_INTERGE_TYPE)
            {
                //strcpy(previousStringRecorder,myExpressionSystem->myExpressionArray[i].singleElement);
                if(iterationNumber==1)
                {
                    return VAILD_INTERGE_TYPE;
                }
                // other case
                strcpy(previousStringRecorder,firstString);

            }
            else{
                return INVAILD_EXPRESSION_TYPE;
            }
        }

        if(i !=0)
        {
            // Case 1;
            // if previous one is "-",the latter one is only for digit or -
            // other is not vaild
            // -5 --5 vaild ; -*
            // Case 2:
            // if previous one is digit ,the latter one could be any integer operator
            //  7 -  7 + 7 *
            // 7 -
            // Case3
            // if previous one is opertor excpet "-" ,the latter only could be - or digit
            //  mod - 6
            char *currentString = myExpressionSystem->myExpressionArray[i].singleElement;

            int caseDigitChecker = isIntegerTypeOFStringInTypeExpression(previousStringRecorder);
            int otherOpeatorChecker = belongToIntegerOpeatorExceptMinus(previousStringRecorder);

            if(strcmp(previousStringRecorder,"-")==0)
            {
                // Case 1
                // if previous one is "-",
                // the latter one is only for digit or -
                // other is not vaild
                char *currentStringPointer =myExpressionSystem->myExpressionArray[i].singleElement;

                if(isIntegerTypeOFStringInTypeExpression(currentString)==VAILD_INTERGE_TYPE)
                {
                    // copy this fone
                    if(i == iterationNumber-1)
                    {
                        // -2
                        return VAILD_INTERGE_TYPE;
                    }
                    strcpy(previousStringRecorder,currentStringPointer);
                }
                else if(strcmp(currentStringPointer,"-")==0)
                {
                    // update previous one
                    // ---- not vaild ---4 vaild
                    if(i ==(iterationNumber-1))
                    {
                        return NOT_VAILED_INTERGER_TYPE;
                    }
                    strcpy(previousStringRecorder,currentStringPointer);
                }
                else {
                    // - +mod
                    return NOT_VAILED_INTERGER_TYPE;

                }
            }
            else if(caseDigitChecker == VAILD_INTERGE_TYPE) {
                // if previous one is digit ,
                // the latter one could be any interg opeator
                //  87 -  87  87 * 74 + 47
                // 7 7 not vaild
                // 7
                // other case is invaild
                char *currentStringPointer =myExpressionSystem->myExpressionArray[i].singleElement;


                int operatorIntegerChecker = belongToIntegerOperation(currentStringPointer);

                if(operatorIntegerChecker == VAILD_INTERGER_Operator)
                {
                    // UPDATE
                    // Previous is digit,but current i+ is the last one
                    if( i== iterationNumber-1)
                    {
                        return NOT_VAILED_INTERGER_TYPE;
                    }
                    strcpy(previousStringRecorder,currentStringPointer);
                }
                else{
                    // LIKE preiovus 7 ,the next one is 77 or and
                    return NOT_VAILED_INTERGER_TYPE;
                }

            }
            else if(otherOpeatorChecker ==VAILD_INTERGER_OPERATOR_EXCEPT_MINUS)
            {
                // mod 7
                // if previous one is opertor excpet "-" ,the latter only could be - or digit
                //  mod
                // other is invaild
                char *currentStringPointer =myExpressionSystem->myExpressionArray[i].singleElement;
                int caseThreeDigitChecker = isIntegerTypeOFStringInTypeExpression(currentStringPointer);
                if(strcmp(currentStringPointer,"-")==0)
                {
                    // edge case
                    if(i ==iterationNumber-1)
                    {
                        return NOT_VAILED_INTERGER_TYPE;
                    }
                    // update 7 mod - not vaild
                    //other transfer
                    strcpy(previousStringRecorder,currentStringPointer);
                }
                else if(caseThreeDigitChecker==VAILD_INTERGE_TYPE)
                {
                    // update mod
                    if(i ==(iterationNumber-1))
                    {
                        return VAILD_INTERGE_TYPE;
                    }
                    strcpy(previousStringRecorder,currentStringPointer);
                }
                else{
                    return NOT_VAILED_INTERGER_TYPE;
                }


            }
            else{
                return NOT_VAILED_INTERGER_TYPE;
            }
        }


    }
    return NOT_VAILED_INTERGER_TYPE;
}

/*
 *
 * The most complext one
 */




/*
 *
 * Utility Function Here
 */


int isIntegerTypeOFStringInTypeExpression(char *str)
{
    int len = strlen(str);

    for (int i = 0; i < len; i++) {
        if (!(isdigit(str[i])))
        {

            return NOT_VAILED_INTERGER_TYPE;
        }
    }
    return VAILD_INTERGE_TYPE;
}

int isBooleanClasueForStringinExpressionTypeSystem(char *str)
{
    const char *a[2];
    a[0]="true";a[1] ="false";
    if((strcmp(str,"true")==0)||(strcmp(str,"false")==0))
    {
        return VAILD_BOOLEAN_CLASUE;
    }
    return INVAILD_BOOLEAN_CLAUSE;
}
// mod | and | or   | == | > | < |  >= | <= | != | not
int belongTOBooleanOperation(char *str)
{
    const char *a[9];
    a[0] ="and";a[1]="or";a[2]="==";
    a[3]=">";a[4]="<";a[5]=">=";
    a[6]="<=";a[7]="!=";a[8]="not";
    for(int i = 0; i < 9; i++){
        if(strcmp(str, a[i]) == 0){
           return VAILD_BOOLEAN_OPERATOR;
        }
    }
    return NOT_VAILD_BOOLEAN_OPERATOR;
}

int belongToIntegerOperation(char *str)
{
  //  + | - | * | / | mod
    const char *a[5];
    a[0] ="+";a[1]="-";a[2]="*";
    a[3]="/";a[4]="mod";

    for(int i = 0; i < 5; i++){
        if(strcmp(str, a[i]) == 0){
            return VAILD_INTERGER_Operator;
        }
    }
    return INVAILD_INTERGER_Operator;
}

int belongToIntegerOpeatorExceptMinus(char *str)
{
    //  + | - | * | / | mod
    const char *a[4];
    a[0] ="+";
    a[1]="*";
    a[2]="/";a[3]="mod";

    for(int i = 0; i < 4; i++){
        if(strcmp(str, a[i]) == 0){
            return VAILD_INTERGER_OPERATOR_EXCEPT_MINUS;
        }
    }
    return INVAILD_INTEGER_OPERATOR_EXCEPT_MINUS;
}
int belongtoBooleanOperatorExcpetNot(char *str)
{
    const char *a[8];
    a[0] ="and";a[1]="or";a[2]="==";
    a[3]=">";a[4]="<";a[5]=">=";
    a[6]="<=";a[7]="!=";


    for(int i = 0; i < 8; i++){
        if(strcmp(str, a[i]) == 0){
            return VAILD_BOOLEAN_OPERATOR_EXCEPT_NOT;
        }
    }
    return INVAILD_BOOLEAN_OPERATOR_EXCEPT_NOT;
}

/*
 * Utlity
 */
int belongToIntegerComparationOperationInTypeSystemUtility(char *str)
{
    /*
 *  >= <= > < == !=
 */
    const char *a[6];
    a[0] =">=";a[1]="<=";
    a[2] ="<";a[3] =">";
    a[4] ="==";
    a[5]="!=";

    for(int i = 0; i < 6; i++){
        if(strcmp(str, a[i]) == 0){
            return VAILD_Integer_boolean_Expression;
        }
    }
    return INVAILD_Integer_boolean_Expression;
}

// and    or
int belongTOBooleanTernaryOperatorInTypeSystemUtility(char *str)
{
    const char *a[2];
    a[0] ="and";
    a[1]="or";
    for(int i = 0; i < 2; i++){
        if(strcmp(str, a[i]) == 0){
            return VAILD_Bool_Ternary_operator;
        }
    }
    return InVaild_Bool_Ternary_operator;
}
// not
int belongtoBooleanBinaryOperatorInTypeSystemUtility(char *str)
{
    if(strcmp(str,"not")==0)
    {
        return Vaild_Bool_Binary_operator;
    }
    else{
        return InVaild_Bool_Binary_operator;
    }
}
int belongtoIntegerCalculatedOperation_InTypeSystem(char *str)
{
    const char *a[5];
    a[0] ="+";a[1]="-";a[2]="*";
    a[3]="/";a[4]="mod";

    for(int i = 0; i < 5; i++){
        if(strcmp(str, a[i]) == 0){
            return Vaild_Integer_Calculated_Operator;
        }
    }
    return Invaild_Integer_Calculated_Operator;

}
int belongToInteger_ComparationOperationInExpressionTypeSystem(char *str) {
    /*
   *  >= <= > < == !=
   */
    const char *a[6];
    a[0] = ">=";
    a[1] = "<=";
    a[2] = "<";
    a[3] = ">";
    a[4] = "==";
    a[5] = "!=";

    for (int i = 0; i < 6; i++) {
        if (strcmp(str, a[i]) == 0) {
            return VAILD_Integer_boolean_Expression;
        }
    }
    return INVAILD_Integer_boolean_Expression;
}


int belongTOBooleanTernaryOperatorInTypeSystem(char *str)
{
    const char *a[2];
    a[0] ="and";
    a[1]="or";
    for(int i = 0; i < 2; i++){
        if(strcmp(str, a[i]) == 0){
            return VAILD_Bool_Ternary_operator;
        }
    }
    return InVaild_Bool_Ternary_operator;

}

int belongtoBooleanBinaryOperatorInTypeSystem(char *str)
{
    if(strcmp(str,"not")==0)
    {
        return Vaild_Bool_Binary_operator;
    }
    else{
        return InVaild_Bool_Binary_operator;
    }
}
