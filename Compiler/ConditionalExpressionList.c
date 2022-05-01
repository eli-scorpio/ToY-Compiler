//
// Created by Mingwei Shi on 01/04/2022.
//

#include "ConditionalExpressionList.h"

struct ConditionExpressionList *InitilizationAndResetOfConditionSystem()
{
    struct ConditionExpressionList *myNewExpression;
    myNewExpression = (struct ConditionExpressionList *)malloc(sizeof (struct ConditionExpressionList));
    for(int i = 0 ;i<MAX_SIZE;i++)
    {
        strcpy(myNewExpression->myExpressionArray[i].singleElement,"NULL");
    }
    myNewExpression->expressionNumber=0;

    return myNewExpression;
}
void CondtionExpression_tailInsert(struct ConditionExpressionList* myExpressionTypeSystem,char * data)
{

    for(int i = 0 ;i<MAX_SIZE;i++)
    {
        char *emptyString ="NULL";
        if(strcmp(myExpressionTypeSystem->myExpressionArray[i].singleElement,emptyString)==0)
        {
            strcpy(myExpressionTypeSystem->myExpressionArray[i].singleElement,data);
            myExpressionTypeSystem->expressionNumber+=1;
            return;
        }


    }
}

void ConditionExpression_Print(struct ConditionExpressionList *myExpressionTypeSystem)
{
    int iterationTimes = myExpressionTypeSystem->expressionNumber;
    for(int i = 0 ;i<iterationTimes;i++)
    {
        printf("------------------------\n");
        printf("The Index %d in condition System is %s \n",i,myExpressionTypeSystem->myExpressionArray[i].singleElement);
        printf("------------------------\n");
    }
}
/*
 *
 * Key function here
 * Return 1: well define boolean expression for all caluse
 * return 0 non-well define expression
 */
/*
 * 1+3 <= 4+5
 * 1<= 5
 * -1 +3 <=4
 * Previous is not:
 *         not(7+3 < 5)
 *      latter must be digit if current is the last one ,return Invaild:
 *      not true
 *      other case :the latter is true/false
 *                      if the latter is the last one:
 *                          return vaild :not false
 *      else: like not <=
 *              return invaild directly
 *
 * Previsous digit:
        In the left hand side of <= >=
     *      the latter could be +/- * / mod adding_Insert_Integer_ExpressionList()
     *            Edge case: if it is the last one invaild
     *       The latter is <=,>= integer operatiorn:
     *              if it is the last one ,return invaild
     *
     *             other case : set the mark "end of LHS integer expression"
            Else:
                return invaild;
      In the right hand side of >=:
            7+5 《3 and
              the latter could be +/- * / mod adding_Insert_Integer_ExpressionList()
     *            Edge case: if it is the last one invaild
              the latter is and/or:
                    if the last one :return invaild
              else:
                    invaild

 *
 * Preivous is + - * / mod,integer operation :
 *              7+)5<=3+2
 *              if the latter is digit:
 *                      if current string is the last string:
 *                          return invaild
*               other case :
                    return inVAILD
 *
 *
 *
 *
 */
/*
 *
 */


//(1<5) && (not (false and true))
/*(1 <5) and not true
 * 1 < 5 and/or/ not
 * 1< 5 and not true
 *
 *
 */
/*
 * bool type
 * if(true)
 * if(false)
 * if(true and false)
 * if(not true)
 * for(int i = 0;! true; i= i+1)
 *These are case I looked at Prof.github repo for boolean
 * expression in if/For
 * But do i need to consider this case?
 * bool a;
 * a = false;
 * if( not (a and true) || (1 < 5))
 * None of people use write this complex one,but it is vaild in logical
 * But I don't know how to do ?
 */
/*
 * start :  not
 *          true or false
 *          digit
 * Base case
 *
 * Continue case
 *        boolean
 */
int ConditionExpression_JudgeSystem(struct ConditionExpressionList *myExpressionSystem)
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
            int booleanClauseChecker = isBooleanClasueForStringinConditionEXPRESSION(firstString);
            int isDigitCheckerInConditionExpressionfirstIteration = isIntegerTypeOFStringInCondtionExpression(firstString);
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

            int caseTwoDigit = isIntegerTypeOFStringInCondtionExpression(previousStringRecorder);

           int caseThreeChecker = isBooleanClasueForStringinConditionEXPRESSION(previousStringRecorder);

            //VAILD_Integer_boolean_Expression
           int caseFour = belongToIntegerComparationOperationInConditionExpression(previousStringRecorder);

            int caseFive = belongTOBooleanTernaryOperatorInCondtionExpression(previousStringRecorder);


           int caseSeven = belongtoIntegerCalculatedOperation_InConditionExpression(previousStringRecorder);

            if (strcmp(previousStringRecorder, "not") == 0)
            {

                //char * currentString = myExpressionSystem -> myExpressionArray[i].singleElement;

                int digitChekcerinthisCaseO = isIntegerTypeOFStringInCondtionExpression(currentString);
                int booleanClauseChecker = isBooleanClasueForStringinConditionEXPRESSION(currentString);
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
                    int intergerOperation = belongToIntegerComparationOperationInConditionExpression(currentString);
                    int IntegerCaclautedOperator = belongtoIntegerCalculatedOperation_InConditionExpression(currentString);


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
                    int IntegerCalautedOperator = belongtoIntegerCalculatedOperation_InConditionExpression(currentString);
                    int ternaryBoolOperatorChecker = belongTOBooleanTernaryOperatorInCondtionExpression(currentString);
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
            else if (caseThreeChecker == VAILD_BOOLEAN_CLASUE) {

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
                        *    //  int caseThreeChecker = isBooleanClasueForStringinConditionEXPRESSION(previousStringRecorder);

                   */

                int subCaseBooleanTerency = belongTOBooleanTernaryOperatorInCondtionExpression(currentString);
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

                int subJudge = isIntegerTypeOFStringInCondtionExpression(currentString);
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
                int boolCasueChecker = isBooleanClasueForStringinConditionEXPRESSION(currentString);

                if (boolCasueChecker == VAILD_BOOLEAN_CLASUE) {
                    if (i == iterationNumber - 1) {
                        return Vaild_BoolExpression;
                    }
                    strcpy(previousStringRecorder, currentString);
                }
                // digit postive case 3
                int leftHandsideOfDiit = isIntegerTypeOFStringInCondtionExpression(currentString);
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
                int digitChecerkSevenCase = isIntegerTypeOFStringInCondtionExpression(currentString);
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
                int lastCaseDigitcHECK = isIntegerTypeOFStringInCondtionExpression(currentString);
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



/*
 *
 *
 * Utility function
 */
/*
 * Utility function
 */
int isIntegerTypeOFStringInCondtionExpression(char *str)
{
    int len = (int )strlen(str);

    for (int i = 0; i < len; i++) {
        if (!(isdigit(str[i])))
        {

            return NOT_VAILED_INTERGER_TYPE;
        }
    }
    return VAILD_INTERGE_TYPE;
}
int isBooleanClasueForStringinConditionEXPRESSION(char *str)
{
    const char *a[2];
    a[0]="true";a[1] ="false";
    for(int i = 0 ;i<2;i++)
    {
        if(strcmp(str,a[i])==0)
        {
            return VAILD_BOOLEAN_CLASUE;
        }

    }
    return INVAILD_BOOLEAN_CLAUSE;
}


int belongToIntegerComparationOperationInConditionExpression(char *str)
{
    /*
     *  >= <= > < == !=
     */
    const char *a[6];
    a[0] =">=";a[1]="<=";
    a[2] ="<";a[3] =">";
    a[4] ="=="; a[5]="!=";

    for(int i = 0; i < 6; i++){
        if(strcmp(str, a[i]) == 0){
            return VAILD_Integer_boolean_Expression;
        }
    }
    return INVAILD_Integer_boolean_Expression;
}
// and    or
int belongTOBooleanTernaryOperatorInCondtionExpression(char *str)
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
//
int belongtoIntegerCalculatedOperation_InConditionExpression(char *str)
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

int belongtoBooleanBinaryOperatorInConditionExpression(char *str)
{
   if(strcmp(str,"not")==0)
   {
       return Vaild_Bool_Binary_operator;
   }
   else{
       return InVaild_Bool_Binary_operator;
   }
}


