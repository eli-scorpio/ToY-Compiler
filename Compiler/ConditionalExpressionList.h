//
// Created by Mingwei Shi on 01/04/2022.
//

#ifndef CONDITIONEXPRESSION_CONDITIONALEXPRESSIONLIST_H
#define CONDITIONEXPRESSION_CONDITIONALEXPRESSIONLIST_H


#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<ctype.h>

#define Not_SWITCH_ON 1
#define Not_SWITCH_OFF 0
#define Vaild_Integer_Calculated_Operator 1
#define Invaild_Integer_Calculated_Operator 0

#define Left_Part_OF_interger_opeator 1
#define Right_part_of_Intger_operator 2
#define VAILD_Bool_Ternary_operator 1
#define InVaild_Bool_Ternary_operator 0

#define Vaild_Bool_Binary_operator 1
#define InVaild_Bool_Binary_operator 0

#define VAILD_Integer_boolean_Expression 1
#define INVAILD_Integer_boolean_Expression 0


#define VAILD_BOOLEAN_CLASUE 1

#define VAILD_INTERGE_TYPE 1
#define NOT_VAILED_INTERGER_TYPE 0


#define VAILD_BOOLEAN_CLASUE 1
#define INVAILD_BOOLEAN_CLAUSE 0


#define  MAX_SIZE 1024
// General marco
#define Vaild_BoolExpression 1
#define InVaild_Bool_expression 0
#define MAX_SIZE 1024
/*
 *
 * We don't need to do the type duduction here
 */
struct conditionExpressionNode
{
    char singleElement[MAX_SIZE];
};
/*
 *
 *  not  7 < 7
 */
struct ConditionExpressionList
{

    int expressionNumber;
    struct conditionExpressionNode myExpressionArray[MAX_SIZE];

};



struct ConditionExpressionList *InitilizationAndResetOfConditionSystem();
void CondtionExpression_tailInsert(struct ConditionExpressionList* myExpressionTypeSystem,char * data);
void ConditionExpression_Print(struct ConditionExpressionList *myExpressionTypeSystem);


//
int ConditionExpression_JudgeSystem(struct ConditionExpressionList *myExpressionSystem);

/*Check length is 3
 * a < b
 * a>5
 *
 */
int isIntegerTypeOFStringInCondtionExpression(char *str);
//void ConditionExpression_Intgercomparison();
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
 *
 * Utility function for Condition boolean expression
 */
// Atom
//int isIntegerTypeOFStringInCondtionExpression(char *str);
int isBooleanClasueForStringinConditionEXPRESSION(char *str);

// we need to split interge boolean operator
// and Boolean type bool operator
//
// >= <= > < == !=

int belongtoIntegerCalculatedOperation_InConditionExpression(char *str);


int belongToIntegerComparationOperationInConditionExpression(char *str);


// and    or
int belongTOBooleanTernaryOperatorInCondtionExpression(char *str);
// not
int belongtoBooleanBinaryOperatorInConditionExpression(char *str);




#endif //CONDITIONEXPRESSION_CONDITIONALEXPRESSIONLIST_H
