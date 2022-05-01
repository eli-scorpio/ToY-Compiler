//
// Created by Mingwei Shi on 31/03/2022.
//

#ifndef EXPRESSION_COLLECTION_LIST_H
#define EXPRESSION_COLLECTION_LIST_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
typedef char* ExpressionElement;


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
/*
 * Define
 * int
 */
#define VAILD_INTERGER_OPERATOR_EXCEPT_MINUS 1
#define INVAILD_INTEGER_OPERATOR_EXCEPT_MINUS 0

#define VAILD_BOOLEAN_OPERATOR_EXCEPT_NOT 1
#define INVAILD_BOOLEAN_OPERATOR_EXCEPT_NOT 0
#define VAILD_INTERGER_Operator 1
#define INVAILD_INTERGER_Operator 0
#define VAILD_BOOLEAN_OPERATOR 1
#define NOT_VAILD_BOOLEAN_OPERATOR 0

#define VAILD_BOOLEAN_CLASUE 1
#define INVAILD_BOOELAN_CALSE 0
#define VAILD_INTERGE_TYPE 1
#define NOT_VAILED_INTERGER_TYPE 0

#define VAILD_BOOLEAN_TYPE 1
#define NOT_VAILD_BOOELEAN_TYPE 0
#define VAILD_BOOLEAN_TYPE 1
#define INVAILD_BOOLEAN_TYPE 0
#define VAILD_BOOLEAN_CLASUE 1
#define INVAILD_BOOLEAN_CLAUSE 0

#define VAILD_EXPRESSION_TYPE 1
#define INVAILD_EXPRESSION_TYPE 0
#define  MAX_SIZE 1024

/*
 *
 * Type System
 */
#define UN_DEFINED_TYPE 0
#define INT_TYPE 1
#define BOOL_TYPE 2
#define STRING_TYPE_IN_TYPESYSTEM 3
struct ExpressionNode{
    char singleElement[MAX_SIZE];
};
struct ExpressionTypeSystem
{
    int environmentType;
    //int expressionType;
    int expressionNumber;
    struct ExpressionNode myExpressionArray[MAX_SIZE];


};
// Construction
struct ExpressionTypeSystem *InitilizationAndResetOfTypeSystem(struct ExpressionTypeSystem * thisType);
void modifyEnvironmentTypeSystemInExpressionList(struct ExpressionTypeSystem *myExpressionTypeSystem, int type);

void typeSystem_tailInsert(struct ExpressionTypeSystem* myExpressionTypeSystem,ExpressionElement data);
int typeSystem_Expression_length(struct ExpressionTypeSystem *myExpressionTypeSystem);

void typeSystem_Print(struct ExpressionTypeSystem *myExpressionTypeSystem);

int isIntegerTypeOFStringInTypeExpression(char *str);

int isBooleanClasueForStringinExpressionTypeSystem(char *str);

int belongTOBooleanOperation(char *str);
int belongToIntegerOperation(char *str);
int belongToIntegerOpeatorExceptMinus(char *str);
int belongtoBooleanOperatorExcpetNot(char *str);

int belongToInteger_ComparationOperationInExpressionTypeSystem(char *str);
int belongTOBooleanTernaryOperatorInTypeSystem(char *str);
int belongtoIntegerCalculatedOperation_InTypeSystem(char *str);
int belongtoBooleanBinaryOperatorInTypeSystem(char *str);
int belongToInteger_ComparationOperationInExpressionTypeSystem(char *str);
/*
 *
 */


// Switch case

int typeSystemSelectionAndJudgeSystem(struct ExpressionTypeSystem *myExpressionSystem);
//
int INT_TYPE_ExpressionTypeDuduction(struct ExpressionTypeSystem *myExpressionSystem);

int  BOOL_TYPE_ExpressionTypeDuciton(struct ExpressionTypeSystem *myExpressionSystem);

int STRING_TYPE_ExpressionTypeDuciton(struct ExpressionTypeSystem *myExpressionSystem);


/*
 *
 * Utility
 */
int belongToIntegerComparationOperationInTypeSystemUtility(char *str);

// and    or
int belongTOBooleanTernaryOperatorInTypeSystemUtility(char *str);
// not
int belongtoBooleanBinaryOperatorInTypeSystemUtility(char *str);



#endif
