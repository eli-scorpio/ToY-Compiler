%{
  ///////////////////////////////////////////////
  // Authors: Mingwei Shi & Eligijus Skersonas //
  ///////////////////////////////////////////////
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include "banner.h"
  #include "globals.h"
  extern FILE *yyin;
  FILE *yyout;
  extern int lineno;
  extern int yylex();
  void yyerror();
  #define myMalloc  malloc
  #define myCalloc  calloc
  #define myFree    free
  #define myHash    hash
  // extra header here
  #include "CacheNode.h"
  #include "CacheNode.c"
  // function stack
  #include "FunctionStack.h"
  #include "FunctionStack.c"
  // Record type
  #include "StructureRecord.h"
  #include "StructureRecord.c"
  // Stack structure
  #include "Stack.h"
  #include "Stack.c"
  #include "VariableScopeCollection.h"
  #include "VariableScopeCollection.c"
  // Hashmap for type cherk
  #include "hashUtil.h"
  #include "hashMap.h"
  #include "hashUtil.c"
  #include "LexpressionLinkList.h"
  #include "LexpressionLinkList.c"
  #include "ArrayFunctionStack.h"
  #include "ArrayFunctionStack.c"

  #define GLOBAL_UNDEFINED_TYPE 0
  #define GLOBAL_INT_TYPE 1
  #define GLBOAL_BOOLEAN_TYPE 2
  #define GLOBAL_STRING_TYPE 3
  #define GL0BAL_FUNCTION_VOID_RETURN_TYPE 4

  int globalType= GLOBAL_UNDEFINED_TYPE;
  char globalFunctionNameRecord[1024];

  #define GLOBAL_ASSIGNMENT_TRACKER_UNDEFINED 0
  #define GLOBAL_ASSIGNMENT_TRAKER_INVAILD 1
  #define GLOBAL_ASSIGNMENT_TRAKER_VAILD 2

  int assignmentTracker =GLOBAL_ASSIGNMENT_TRACKER_UNDEFINED;

  int grammarError =1;
  int semanticsError =1;
  int lexicalSpeficError;

  #include"ConditionalExpressionList.h"
  #include"ConditionalExpressionList.c"
  // Expressionlist
  #include "ExpressionCollectionList.h"
  #include "ExpressionCollectionList.c"

  #include "TypeDefaultVauleFileter.h"
  #include "TypeDefaultVauleFileter.c"

  struct  TypeDefultValueFilter *myTypeTransder;
  #include"FunctionHeaderInformationCollector.h"
  #include"FunctionHeaderInformationCollector.c"
  struct  FunctionHeaderInformationList *myFunctionInfoHeaderList;

  ///////////////////////////////////////////////////////////////////////////////////////////////////////
  //  1 for left ID we need to scope undelcard checking firstly and tpe checking and prerver the word  //
  //  2 is for right part we need to undeclard checking firstly and then do semantice checking         //
  ///////////////////////////////////////////////////////////////////////////////////////////////////////
  #define LEFT_PART_EQUATION_FOR_LEFT_EXPRESSION 1
  #define RIGHT_PART_EQUATION_FOR_LEFT_EXPRESSION 2

  int globalFunctionParameterNumber = 0;
  int IDPositionSwithcer=LEFT_PART_EQUATION_FOR_LEFT_EXPRESSION;

  //////////////////////////////////////////////////
  // Scope Checking data structures and variables //
  //////////////////////////////////////////////////
  struct VariableScopeArray* myVariableLinklist;
  int globalScope = 0;
  struct FunctionList *myFunctionList;
  struct strucureList *myStructureList;
  struct ArrayFunctionStackList *myArrayFunctionList;
  List* functionNameList;
  List* structureNameList;
  List* functionDeclarationList;
  PNode LexpressionCollectionList;
  PNode LexpressionTypeCollectionList;
  PNode LFunctionParameterCollectionList;

  #define UNDEFINT_LEFTEXPRESSION_TYPE 0
  #define SWITCH_TO_PURE_ID 1
  #define SWITCH_TO_STRUCURE_DOT 2
  int assignmentLexpressionType =UNDEFINT_LEFTEXPRESSION_TYPE;

  // Type checking variable
  int globalVariableAssignmentType;
  int lastTypeOFLexpressionFiled;
  struct ExpressionTypeSystem *myType;

  ///////////////////////////////////
  // Type checking data structures //
  ///////////////////////////////////
  HashMap* functionNameCheckerhashMap;
  HashMap* structureNameCheckerhashMap;
  HashMap* filedBelongWhichStctureCheckerMap;
  HashMap* globalStrucureVaildAssignment;
  //For function call used;
  HashMap *Vaild_DeclrationWithReturnTypeFunctionChecker;
  //for quicly mapping:condition
  HashMap *functionDeclrationTypeChecker;

  //////////////////////////////////////////////////////////////////////////////////
  // First hashing last file -> strucure name eg: first_name->em1 in test1One.txt //
  // Since well-defined strucure only last filed is basic type:                   //
  // Bool int string                                                              //
  // Second hashing em1 -> Assignment                                             //
  //////////////////////////////////////////////////////////////////////////////////

  HashMap* lastFiledMapStructureTypeVariableName;
  HashMap* StrucureTypeNameAassignmentChecker;

  struct stack_t *stackForLexpression;

  //HashMap Function global
  HashMap* CreateHashMap(int n);
  int InsertHashMap(HashMap* hashMap, char* key, char* value);
  char* GetHashMap(HashMap* hashMap, char* key);
  void DeleteHashMap(HashMap* hashMap);
  void PrintHashMap(HashMap* hashMap);
  void functionSizeChecker();
  char globalFunctionCallName[1024];
  char lastStructureDotVariableGlobalRecorder[1024];
  char lastestPureIdGlobalRecorder[1024];

  int globalFunctionParameterNumberForFunctionItself = 0;
%}

/* YYSTYPE union */
%union{
  int int_val;
  char* str_val;
}

/* token declarations */

/*************************************************************************************************
 *                                        Terminals                                              *                                      
 *************************************************************************************************/

%token<int_val>   IF              THEN                    STRING_TYPE              GREATER_THAN
%token<int_val>   INT             BOOL                    PRINTF                   VOID
%token<int_val>   FOR             RETURN                  STRUCT                   LESS_THAN
%token<int_val>   LBRACE          RBRACE                  LPAREN                   RPAREN
%token<int_val>   DOT             SEMICOLON               COMMA                    ELSE
%token<int_val>   NOT_EQUAL                   

%token<str_val>   ID              TRUE                    FALSE                    STRING_CONSTANT
%token<str_val>   EQ              SUB                     ADD                      MUL
%token<str_val>   DIV             MOD                     AND                      OR
%token<str_val>   NOT             EQUALITY                GREATER_OR_EQUAL         LESS_OR_EQUAL
%token<str_val>   ICONST  

/////////////////////////////////////
// Expression Priorities and Rules //
/////////////////////////////////////
%right EQ
%nonassoc EQUALITY NOT_EQUAL GREATER_OR_EQUAL LESS_OR_EQUAL LESS_THAN GREATER_THAN
%left AND OR 
%left MUL DIV MOD
%left ADD SUB
%left UMINUS NOT
%nonassoc DOT

%start toypgm


%%

/*************************************************************************************************
 *                                    Program start                                              *
 *************************************************************************************************/

toypgm: {
        printBanner();
        assignmentLexpressionType=0;
        IDPositionSwithcer=LEFT_PART_EQUATION_FOR_LEFT_EXPRESSION;
        myTypeTransder = initilization_typeDefaultFilter(myTypeTransder);

        stackForLexpression= newStack();
        myFunctionList =init_FunctionList(myFunctionList); // Function linklist initilization;
        myStructureList = init_strucure_list(myStructureList);
        myArrayFunctionList =Arrayinit_FunctionList(myArrayFunctionList);
        functionNameCheckerhashMap = CreateHashMap(1024);
        structureNameCheckerhashMap =CreateHashMap(1024);
        globalStrucureVaildAssignment =CreateHashMap(1024); 

        lastFiledMapStructureTypeVariableName  =CreateHashMap(1024);
        StrucureTypeNameAassignmentChecker= CreateHashMap(1024);

        filedBelongWhichStctureCheckerMap = CreateHashMap(1024);
        Vaild_DeclrationWithReturnTypeFunctionChecker= CreateHashMap(1024);
        functionDeclrationTypeChecker= CreateHashMap(1024);

        functionNameList =(List*)malloc(sizeof(List)); // Linklist initlization
        initList(functionNameList);
        myFunctionInfoHeaderList = initilizaion_functionHeaderinformation(myFunctionInfoHeaderList);

        structureNameList=(List*)malloc(sizeof(List));
        initList(structureNameList);

        functionDeclarationList=(List*)malloc(sizeof(List));
        initList(functionDeclarationList);

        LexpressionList_initilization(&LexpressionCollectionList);
        LexpressionList_initilization(&LexpressionTypeCollectionList);

        LexpressionList_initilization(&LFunctionParameterCollectionList);
        IDPositionSwithcer =LEFT_PART_EQUATION_FOR_LEFT_EXPRESSION;
        myType = InitilizationAndResetOfTypeSystem(myType);
        myVariableLinklist = initilization_And_Reset_variableScopearray(myVariableLinklist);   
      } pgm;


/*************************************************************************************************
 *                                       Overview                                                *
 *************************************************************************************************/
    
pgm:    
  //empty
| proc pgm
| structdecl pgm
;

/*************************************************************************************************
 *                                    Function declaration                                       *
 *************************************************************************************************/
proc:   
  VOID ID {
        char *tempIDname = $2;
        char *functionNameCheckFlag = GetHashMap(functionNameCheckerhashMap,tempIDname);

        if(functionNameCheckFlag){
          printf("GRAMMAR ERROR: procedure %s() already in use\n",$2);
          grammarError = 0;
        } // end if

        if(functionNameCheckFlag == NULL){
          char *tempType = "void";
          insertFuncttionName(myFunctionList,$2,tempType);
          ArrayInsertFunctionName(myArrayFunctionList,$2,tempType);
          addAtHeadCacheNode(functionDeclarationList,"void");
          addAtHeadCacheNode(functionNameList,$2);

          char *temp1 = acquireHeadOfListCache(functionNameList);
          InsertHashMap(functionNameCheckerhashMap,tempIDname, "used"); // We need to insert stackMap here
          myVariableLinklist = initilization_And_Reset_variableScopearray(myVariableLinklist); // Initlize when in the new function
          InsertHashMap(functionDeclrationTypeChecker,tempIDname,tempType);
          // Function header info
          addFunctionDeclartionType_ID_InFunctionHeaderList(myFunctionInfoHeaderList,tempType,tempIDname);
          // For void function we did a special trick            
          InsertHashMap(Vaild_DeclrationWithReturnTypeFunctionChecker,tempIDname,"vaild");
          InsertHashMap(functionDeclrationTypeChecker,tempIDname,"void");
          
        } // end if
  } LPAREN  {
        globalScope += 1; // increase scope
        char *tempName = $2; 
        bracketControlAdd(myFunctionList,tempName);
        ArraybracketControlAdd(myArrayFunctionList,tempName);

  } funcDeclarParameterlist RPAREN LBRACE stmtlist RBRACE {
        // reset globalscope and variablelist
        globalScope = 0;
        myVariableLinklist = initilization_And_Reset_variableScopearray(myVariableLinklist);

  }
| INT ID {
        char *tempIDname = $2;
        char *functionNameCheckFlag = GetHashMap(functionNameCheckerhashMap,tempIDname);

        if(functionNameCheckFlag){
          printf("GRAMMAR ERROR: procedure %s() already in use\n",$2);
          grammarError = 0;
        } // end if

        if(functionNameCheckFlag == NULL){
          char *tempType = "int";
          insertFuncttionName(myFunctionList,$2,tempType);
          ArrayInsertFunctionName(myArrayFunctionList,$2,tempType);
          addAtHeadCacheNode(functionDeclarationList,"int");
          addAtHeadCacheNode(functionNameList,$2);

          char *temp1 = acquireHeadOfListCache(functionNameList);
          InsertHashMap(functionNameCheckerhashMap,tempIDname, "used"); // We need to insert stackMap here
          myVariableLinklist = initilization_And_Reset_variableScopearray(myVariableLinklist);
         
          InsertHashMap(functionDeclrationTypeChecker,tempIDname,tempType);
          addFunctionDeclartionType_ID_InFunctionHeaderList(myFunctionInfoHeaderList,tempType,tempIDname);

        } // end if
  } LPAREN  {
        char *tempName = $2;
        bracketControlAdd(myFunctionList,tempName);
        ArraybracketControlAdd(myArrayFunctionList,tempName);
        globalScope+=1; // increase scope

  } funcDeclarParameterlist RPAREN LBRACE stmtlist RBRACE  {
        // reset globalscope and variablelist
        globalScope=0;
        myVariableLinklist = initilization_And_Reset_variableScopearray(myVariableLinklist);
  }
| BOOL ID {
        char *tempIDname = $2;
        char *functionNameCheckFlag = GetHashMap(functionNameCheckerhashMap,tempIDname);
    
        if(functionNameCheckFlag){
          printf("GRAMMAR ERROR: procedure %s() already in use\n",$2);
          grammarError = 0;
        } // end if

        if(functionNameCheckFlag  == NULL){
          char *tempType = "bool";
          insertFuncttionName(myFunctionList,$2,tempType);
          ArrayInsertFunctionName(myArrayFunctionList,$2,tempType);
          addAtHeadCacheNode(functionDeclarationList,"bool");
          addAtHeadCacheNode(functionNameList,$2);

          char *temp1 = acquireHeadOfListCache(functionNameList);
          InsertHashMap(functionNameCheckerhashMap,tempIDname, "used"); // We need to insert stackMap here
          myVariableLinklist = initilization_And_Reset_variableScopearray(myVariableLinklist);
          addFunctionDeclartionType_ID_InFunctionHeaderList(myFunctionInfoHeaderList,tempType,tempIDname);
          InsertHashMap(functionDeclrationTypeChecker,tempIDname,tempType);
        
        } // end if
  }LPAREN  {
        char *tempName = $2;
        bracketControlAdd(myFunctionList,tempName);
        ArraybracketControlAdd(myArrayFunctionList,tempName);
        globalScope += 1; // increase scope

  } funcDeclarParameterlist RPAREN LBRACE stmtlist RBRACE {
        // reset globalscope and variablelist
        globalScope = 0;
        myVariableLinklist = initilization_And_Reset_variableScopearray(myVariableLinklist);

  }
| STRING_TYPE ID {
        char *tempIDname = $2;
        char *functionNameCheckFlag = GetHashMap(functionNameCheckerhashMap,tempIDname);

        if(functionNameCheckFlag){
          printf("GRAMMAR ERROR: procedure %s() already in use\n",$2);
          grammarError = 0;
        } // end if

        if(functionNameCheckFlag  == NULL){
          char *tempType = "string";
          insertFuncttionName(myFunctionList,$2,tempType);
          ArrayInsertFunctionName(myArrayFunctionList,$2,tempType);
          addAtHeadCacheNode(functionDeclarationList,"string");
          addAtHeadCacheNode(functionNameList,$2);

          char *temp1 = acquireHeadOfListCache(functionNameList);
          InsertHashMap(functionNameCheckerhashMap,tempIDname, "used"); // We need to insert stackMap here
          myVariableLinklist = initilization_And_Reset_variableScopearray(myVariableLinklist);
          addFunctionDeclartionType_ID_InFunctionHeaderList(myFunctionInfoHeaderList,tempType,tempIDname);
          InsertHashMap(functionDeclrationTypeChecker,tempIDname,tempType);
        
        } // end if
  }LPAREN  {
        char *tempName = $2;
        bracketControlAdd(myFunctionList,tempName);
        ArraybracketControlAdd(myArrayFunctionList,tempName);
        globalScope += 1; // increase scope

  } funcDeclarParameterlist RPAREN LBRACE stmtlist RBRACE {
        // reset globalscope and variablelist
        globalScope = 0;
        myVariableLinklist = initilization_And_Reset_variableScopearray(myVariableLinklist);

  }
| ID ID {
        char * structureName = $1;
        char * strctureNameCheckerFlag = GetHashMap(structureNameCheckerhashMap,structureName);

        if(strctureNameCheckerFlag == NULL){
          printf("GRAMMAR ERROR: Structure %s has not been declared\n", structureName);
          grammarError = 0;
        } // end if

        if (structureNameCheckerhashMap) {
          char * tempIDname = $2;
          char * functionNameCheckFlag = GetHashMap(functionNameCheckerhashMap, tempIDname);

          if (functionNameCheckFlag) {
            printf("GRAMMAR ERROR: procedure %s() already in use\n",$2);
            grammarError = 0;
          } // end if

          if (functionNameCheckFlag == NULL) {
            char * tempType = $1;
            insertFuncttionName(myFunctionList, $2, tempType);
            ArrayInsertFunctionName(myArrayFunctionList,$2,tempType);
            addAtHeadCacheNode(functionDeclarationList, tempType);
            addAtHeadCacheNode(functionNameList, $2);

            char * temp1 = acquireHeadOfListCache(functionNameList);
            InsertHashMap(functionNameCheckerhashMap, tempIDname, "used"); // We need to insert stackMap here
            myVariableLinklist = initilization_And_Reset_variableScopearray(myVariableLinklist);
            InsertHashMap(functionDeclrationTypeChecker,tempIDname,structureName);
            addFunctionDeclartionType_ID_InFunctionHeaderList(myFunctionInfoHeaderList,tempType,tempIDname);
          } // end if
        } // end if
}LPAREN  {
        char *tempName = $2;
        bracketControlAdd(myFunctionList,tempName);
        ArraybracketControlAdd(myArrayFunctionList,tempName);
        globalScope += 1; // increase scope

} funcDeclarParameterlist RPAREN LBRACE stmtlist RBRACE {
        globalScope = 0;
        myVariableLinklist = initilization_And_Reset_variableScopearray(myVariableLinklist);
}
;



/*************************************************************************************************
 *                              Parameter of function list                                       *
 *************************************************************************************************/

funcDeclarParameterlist:   
  {/*Empty Parameter List*/} 
| parameterDeclar                
| parameterDeclar COMMA funcDeclarParameterlist
;

/*************************************************************************************************
 *                                         Parameter                                             *
 *************************************************************************************************/
parameterDeclar:   
  INT ID  {
        char *variableName =$2;
        char *variableType = "int";
     
        char *latestFunctionName = acquireHeadOfListCache(functionNameList);
        char *latestFunctionType = acquireHeadOfListCache(functionDeclarationList);

        int redeclatedCheck =checkVariableRecelarationVariableScopeArray(myVariableLinklist,variableName,globalScope);
        if(redeclatedCheck == RECLRATED) { // check if redeclared
          printf("GRAMMAR ERROR: %s is already in use \n", $2);
          grammarError = 0;
        } // end if

        if(redeclatedCheck == NOT_RECLARED){ // if not redeclared
          insertVariableDeclarationforSpecificFunction(myFunctionList,latestFunctionName,latestFunctionType,variableType,variableName);
          inserionOfVaraibelScopeArray(myVariableLinklist,variableType,variableName,globalScope);
          ArrayinsertVariableDeclarationforSpecificFunction(myArrayFunctionList,latestFunctionName,latestFunctionType,variableType,variableName);
          // adding function parameter in the header list
          addFunctionFunctionParameterInFunctionHeaderList(myFunctionInfoHeaderList,latestFunctionName,variableType,variableName);

        } // end if
  }     
| BOOL ID {
        char *variableName =$2;
        char *variableType = "bool";
        char *latestFunctionName = acquireHeadOfListCache(functionNameList);
        char *latestFunctionType = acquireHeadOfListCache(functionDeclarationList);

        int redeclatedCheck = checkVariableRecelarationVariableScopeArray(myVariableLinklist,variableName,globalScope);
        if(redeclatedCheck == RECLRATED){ // check if redeclared
            printf("GRAMMAR ERROR: %s is already in use \n", $2);
            grammarError = 0;
        }

        if(redeclatedCheck == NOT_RECLARED){ // if not redeclared
          inserionOfVaraibelScopeArray(myVariableLinklist,variableType,variableName,globalScope);
          insertVariableDeclarationforSpecificFunction(myFunctionList,latestFunctionName,latestFunctionType,variableType,variableName);
          ArrayinsertVariableDeclarationforSpecificFunction(myArrayFunctionList,latestFunctionName,latestFunctionType,variableType,variableName);
          // adding function parameter in the header list
          addFunctionFunctionParameterInFunctionHeaderList(myFunctionInfoHeaderList,latestFunctionName,variableType,variableName);
        
       }    
  }
| STRING_TYPE ID {
        char * variableName = $2;
        char * variableType = "string";
        char * latestFunctionName = acquireHeadOfListCache(functionNameList);
        char * latestFunctionType = acquireHeadOfListCache(functionDeclarationList);

        int redeclatedCheck =checkVariableRecelarationVariableScopeArray(myVariableLinklist,variableName,globalScope);
        if (redeclatedCheck == RECLRATED) { // check if redeclared
          printf("GRAMMAR ERROR: %s is already in use \n", $2);
          grammarError = 0;
        } // end if

        if (redeclatedCheck == NOT_RECLARED) { // if not redeclared
          insertVariableDeclarationforSpecificFunction(myFunctionList, latestFunctionName, latestFunctionType, variableType, variableName);
          ArrayinsertVariableDeclarationforSpecificFunction(myArrayFunctionList,latestFunctionName,latestFunctionType,variableType,variableName);
          inserionOfVaraibelScopeArray(myVariableLinklist,variableType,variableName,globalScope);
          // adding function parameter in the header list
          addFunctionFunctionParameterInFunctionHeaderList(myFunctionInfoHeaderList,latestFunctionName,variableType,variableName);
        
        } // end if
  }
| ID ID {
        char * structureName = $1;
        char * strctureNameCheckerFlag = GetHashMap(structureNameCheckerhashMap, structureName);

        if (strctureNameCheckerFlag == NULL) {
          printf("GRAMMAR ERROR: Structure %s has not been declared \n", structureName);
          grammarError = 0;
        }

        if(strctureNameCheckerFlag) {           
          char *variableName =$2;
          char *variableType = $1;
          char *latestFunctionName = acquireHeadOfListCache(functionNameList);
          char *latestFunctionType = acquireHeadOfListCache(functionDeclarationList);

          int redeclatedCheck =checkVariableRecelarationVariableScopeArray(myVariableLinklist,variableName,globalScope);
          if(redeclatedCheck == RECLRATED){ // check if redeclared
            printf("GRAMMAR ERROR: %s %s is already in use \n", $1, $2);
            grammarError = 0;
          } // end if

          if(redeclatedCheck == NOT_RECLARED){ // if not redeclared
            insertVariableDeclarationforSpecificFunction(myFunctionList,latestFunctionName,latestFunctionType,variableType,variableName);
            ArrayinsertVariableDeclarationforSpecificFunction(myArrayFunctionList,latestFunctionName,latestFunctionType,variableType,variableName);
            inserionOfVaraibelScopeArray(myVariableLinklist,variableType,variableName,globalScope);
            // adding function parameter in the header list
            addFunctionFunctionParameterInFunctionHeaderList(myFunctionInfoHeaderList,latestFunctionName,variableType,variableName);
        
          } // end if  
        } // end if

  }
;

/**************************************************************************************************
 * Structure DECLARATIONS
 *************************************************************************************************/

structdecl: 
  STRUCT ID {
        char *tempStrctureName = $2;
        char *structureNameChecker =  GetHashMap(structureNameCheckerhashMap,tempStrctureName);
        
        if(structureNameChecker){
          printf("GRAMMAR ERROR: Structure already in use \n");
          grammarError = 0;
        }

        if(structureNameChecker == NULL){
          add_strucure_name(myStructureList,tempStrctureName);
          addAtHeadCacheNode(structureNameList,tempStrctureName);
          InsertHashMap(structureNameCheckerhashMap,tempStrctureName, "used");
        }

} LBRACE strucDeclarationList RBRACE 
;

/*  Structure declaration since we need to add in the stack and that is why we use another one */

strucDeclarationList: 
        singleStructdecl              
|       singleStructdecl COMMA strucDeclarationList
;

singleStructdecl:
  INT ID {
        char *tempFiledID = $2;
        char *latesutStuctureName = acquireHeadOfListCache(structureNameList);

        int filedCheck = checker_structureFiled(myStructureList,latesutStuctureName,tempFiledID);
        if(filedCheck == 1){
          printf("GRAMMAR ERROR: %s is already in use \n", $2);
          grammarError = 0;  
        } // end if

        if(filedCheck == 0){
          char *tempType = "int";
          add_structureFiled(myStructureList,latesutStuctureName,tempType,tempFiledID);
          char *lastStcureNamsssss = acquireHeadOfListCache(structureNameList);
        } // end if
  }     
| BOOL ID {
        char *tempFiledID = $2;
        char *latesutStuctureName = acquireHeadOfListCache(structureNameList);
      
        int filedCheck = checker_structureFiled(myStructureList,latesutStuctureName,tempFiledID);
        if(filedCheck == 1){
          printf("GRAMMAR ERROR: %s is already in use \n", $2);
          grammarError = 0; 
        } // end if

        if(filedCheck == 0){
          char *tempType = "bool"; 
          add_structureFiled(myStructureList,latesutStuctureName,tempType,tempFiledID);
          char *lastStcureNamsssss = acquireHeadOfListCache(structureNameList);
        }        
  }     
| STRING_TYPE ID  {
        char *tempFiledID = $2;
        char *latesutStuctureName = acquireHeadOfListCache(structureNameList);

        int filedCheck = checker_structureFiled(myStructureList,latesutStuctureName,tempFiledID);
        if(filedCheck == 1){
          printf("GRAMMAR ERROR: %s is already in use \n", $2);
          grammarError = 0;
        }

        if(filedCheck ==0){
          char *tempType = "string";
          add_structureFiled(myStructureList,latesutStuctureName,tempType,tempFiledID);
          char *lastStcureNamsssss = acquireHeadOfListCache(structureNameList);
        }        
    }     
| ID ID {
        char * structureName = $1;
        char * strctureNameCheckerFlag = GetHashMap(structureNameCheckerhashMap, structureName);
        if (strctureNameCheckerFlag == NULL) {
          printf("GRAMMAR ERROR: Structure %s has not been declared \n", structureName);
          grammarError = 0;
        }
        if (structureNameCheckerhashMap) {
          char *tempFiledID = $2;
          char *latesutStuctureName = acquireHeadOfListCache(structureNameList);
        
          int filedCheck = checker_structureFiled(myStructureList,latesutStuctureName,tempFiledID);
          if(filedCheck == 1){
            printf("GRAMMAR ERROR: %s is already in use \n", $2);
            grammarError = 0;
          }

          if(filedCheck == 0){
            char *tempType = $1;
            add_structureFiled(myStructureList,latesutStuctureName,tempType,tempFiledID);
            char *lastStcureNamsssss = acquireHeadOfListCache(structureNameList);
          } // end if   
        } // end if
  } 
;


/**************************************************************************************************
 * EXPRESSIONS
 *************************************************************************************************/
/*  Expression */
// expression for typer checking stage 
expr: 
  expr ADD              {typeSystem_tailInsert(myType,"+");}    expr               
| expr SUB              {typeSystem_tailInsert(myType,"-");}    expr              
| expr MUL              {typeSystem_tailInsert(myType,"*");}    expr              
| expr DIV              {typeSystem_tailInsert(myType,"/");}    expr            
| expr MOD              {typeSystem_tailInsert(myType,"mod");}  expr           
| expr AND              {typeSystem_tailInsert(myType,"and");}  expr         
| expr OR               {typeSystem_tailInsert(myType,"or");}   expr               
| expr EQUALITY         {typeSystem_tailInsert(myType,"==");}   expr       
| expr NOT_EQUAL        {typeSystem_tailInsert(myType,"!=");}   expr        
| expr GREATER_OR_EQUAL {typeSystem_tailInsert(myType,">=");}   expr  
| expr LESS_OR_EQUAL    {typeSystem_tailInsert(myType,"<=");}   expr    
| expr GREATER_THAN     {typeSystem_tailInsert(myType,">");}    expr      
| expr LESS_THAN        {typeSystem_tailInsert(myType,"<");}    expr       
| NOT                   {typeSystem_tailInsert(myType,"not");}  expr                   
| SUB  %prec UMINUS     {typeSystem_tailInsert(myType,"-");}    expr        //{$$ = -$2;} 
| ICONST                {typeSystem_tailInsert(myType,$1);}
| STRING_CONSTANT       {typeSystem_tailInsert(myType,$1);}  
| ID   {
        char *latestfUNCTIOnmae = acquireHeadOfListCache(functionNameList);
        char *tempId = $1;
        int undelclaredCheck = checkVariableUndeclarationVariableScopeArray(myVariableLinklist,tempId,globalScope);

        if(undelclaredCheck == UNDELCARED){
          printf("GRAMMAR ERROR: %s is undeclared in variable assignment \n", $1);
          grammarError =0;
          assignmentTracker =GLOBAL_ASSIGNMENT_TRAKER_INVAILD;
        }
        if(undelclaredCheck== NOT_UNCLEATION){
          int AssignmentAlradyChcker = checkAssignedAlreadyVariableInVariabelScopeArray(myVariableLinklist,tempId,globalScope);

          if(AssignmentAlradyChcker == 0){
            semanticsError = 0;
            printf("SEMANTICS ERROR: variable in expression is not initialised \n");
          }
          else{
            char *returnTypeOfThisID = returnTypeOfVaribleInVaribaleScopeArray(myVariableLinklist,tempId,globalScope);
            if (strcmp(returnTypeOfThisID, "int") == 0){
              adding_abstructureTypeInDefaultFileter(myTypeTransder, "int");
              char * returnVaule = acquireFilterVaule(myTypeTransder);
              typeSystem_tailInsert(myType, returnVaule);
              myTypeTransder = initilization_typeDefaultFilter(myTypeTransder);
            } 
            else if (strcmp(returnTypeOfThisID, "bool") == 0){
                adding_abstructureTypeInDefaultFileter(myTypeTransder, "bool");
                char * returnVaule = acquireFilterVaule(myTypeTransder);
                typeSystem_tailInsert(myType, returnVaule);
                myTypeTransder = initilization_typeDefaultFilter(myTypeTransder);
            } 
            else if (strcmp(returnTypeOfThisID, "string") == 0){
                adding_abstructureTypeInDefaultFileter(myTypeTransder, "string");
                char * returnVaule = acquireFilterVaule(myTypeTransder);
                typeSystem_tailInsert(myType, returnVaule);
                myTypeTransder = initilization_typeDefaultFilter(myTypeTransder);
            }
          }
        }  
}
| FALSE         {typeSystem_tailInsert(myType,"false");}
| TRUE          {typeSystem_tailInsert(myType,"true");}
| LPAREN expr RPAREN 
;

/****************************************************************
 * For expression list:
 * Only functio parameter use this rule
 * No matter fun(int para1,int para2,int para 3)
 * the global type of is the defintiokn type
 * when calling fun(1,2,3)
 * Using globalFunctionParameterNumber to count the size of parameterr 
 * For requrienemnt f) in part 3
 * *******************************/

exprlist: 
        //Empty parameter     
| expr {
        globalFunctionParameterNumber+=1;
        int emptyCheck = isEmptyLexpressionList(LFunctionParameterCollectionList);

        if(globalFunctionParameterNumber>globalFunctionParameterNumberForFunctionItself){
            semanticsError=0;
            printf("SEMANTIC ERROR: Expression number > function parameter number \n");
        }
        else{
          char *TopElementType = acquireFirstElementOfLexpressionList(&LFunctionParameterCollectionList);
          if (strcmp(TopElementType, "int") == 0) 
              globalType = GLOBAL_INT_TYPE;
          else if (strcmp(TopElementType, "bool") == 0)
              globalType = GLBOAL_BOOLEAN_TYPE;
          else if (strcmp(TopElementType, "string") == 0) 
            globalType = GLOBAL_STRING_TYPE;

          int temp = globalType;
          modifyEnvironmentTypeSystemInExpressionList(myType, temp);

          // clear expression list here
          typeSystem_Print(myType);
          int result;
          int ExpressionNumber = myType -> expressionNumber;

          result = typeSystemSelectionAndJudgeSystem(myType);

          if (result == 0) {
              semanticsError = 0;
              printf("SEMANTICS ERROR: type checking error occurred \n");
          } 

          // FOR NEXT iteration
          globalType = GLOBAL_UNDEFINED_TYPE;
          myType = InitilizationAndResetOfTypeSystem(myType);

          LexpressionList_headDelete( & LFunctionParameterCollectionList);
       }
}       
| expr {
        globalFunctionParameterNumber += 1;
        if (globalFunctionParameterNumber > globalFunctionParameterNumberForFunctionItself){
          semanticsError = 0;
          printf("SEMANTICS ERROR: Expression number > function parameter number\n");
        } 
        else {
          char * TopElementType = acquireFirstElementOfLexpressionList( & LFunctionParameterCollectionList);

          if (strcmp(TopElementType, "int") == 0)
            globalType = GLOBAL_INT_TYPE;
          else if (strcmp(TopElementType, "bool") == 0)
            globalType = GLBOAL_BOOLEAN_TYPE;
          else if (strcmp(TopElementType, "string") == 0) 
            globalType = GLOBAL_STRING_TYPE;
    
          int temp = globalType;
          modifyEnvironmentTypeSystemInExpressionList(myType, temp);

          // clear expression list here
          typeSystem_Print(myType);
          int result;
          int ExpressionNumber = myType -> expressionNumber;
          result = typeSystemSelectionAndJudgeSystem(myType);

          if (result == 0) {
              semanticsError = 0;
              printf("SEMANTICS ERROR: Type checking error occurred \n");
          } 

          // FOR NEXT iteration
          globalType = GLOBAL_UNDEFINED_TYPE;
          myType = InitilizationAndResetOfTypeSystem(myType);

          LexpressionList_headDelete( & LFunctionParameterCollectionList);

        }

}COMMA exprlist
;

/**************************************************************************************************
 * L Expressions only stucure in the left hand side
 *************************************************************************************************/
// Scope checking
lexprLHS:  
  ID {
        char *latestfUNCTIOnmae = acquireHeadOfListCache(functionNameList);
        char *tempId = $1;
        int undelclaredCheck = checkVariableUndeclarationVariableScopeArray(myVariableLinklist,tempId,globalScope);

        if(undelclaredCheck == UNDELCARED){
          printf("GRAMMAR ERROR: %s is undeclared in variable assignment \n", $1);
          grammarError = 0;
          assignmentTracker = GLOBAL_ASSIGNMENT_TRAKER_INVAILD;
        }
        if(undelclaredCheck == NOT_UNCLEATION){
          char *returnTypeOfThisId = returnTypeOfVaribleInVaribaleScopeArray(myVariableLinklist,tempId,globalScope);

          if(strcmp(returnTypeOfThisId,"int")==0)
            globalType = GLOBAL_INT_TYPE;
          else if(strcmp(returnTypeOfThisId,"bool")==0)
            globalType = GLBOAL_BOOLEAN_TYPE;
          else if(strcmp(returnTypeOfThisId,"string")==0)
            globalType = GLOBAL_STRING_TYPE;

          assignmentCheckerOpenForVariableScopeArray(myVariableLinklist,tempId,globalScope);
          assignmentTracker = GLOBAL_ASSIGNMENT_TRAKER_VAILD;
          strcpy(lastestPureIdGlobalRecorder,tempId);
          assignmentLexpressionType = SWITCH_TO_PURE_ID;
          myType = InitilizationAndResetOfTypeSystem(myType);
          modifyEnvironmentTypeSystemInExpressionList(myType,globalType);
        }    
  }                                  
| Stucture_LHS
;

Stucture_LHS:
  ID DOT{
        char *tempId = $1;
        LexpressionList_tailInsert(&LexpressionCollectionList, tempId);
  } Stucture_LHS
| ID {
        char *tempId =$1;
        LexpressionList_tailInsert(&LexpressionCollectionList, tempId);

        char fullDotName[1024];
        PNode axcuilaryList;
        LexpressionList_initilization(&axcuilaryList);

        char *relativeStrcutureName = acquireFirstElementOfLexpressionList(&LexpressionCollectionList);
        strcpy(fullDotName,relativeStrcutureName);
        char *latestFunctionName = acquireHeadOfListCache(functionNameList);
        int checkID = checkUndeclaratedVaraible(myFunctionList,latestFunctionName,relativeStrcutureName);
    
        
        int checkIDTwo = checkVariableUndeclarationVariableScopeArray(myVariableLinklist,relativeStrcutureName,globalScope);
        int newCheckID = ArraycheckUndeclaratedVaraible(myArrayFunctionList,latestFunctionName,relativeStrcutureName);
        if(checkIDTwo == 0){
          printf("GRAMMAR ERROR: %s has not been declared \n",relativeStrcutureName);
          grammarError = 0;
          assignmentTracker =GLOBAL_ASSIGNMENT_TRAKER_INVAILD;
        }

        if (checkIDTwo == 1){
          char * tempType = ArrayreturnStructureTypeofVariable(myArrayFunctionList, latestFunctionName, relativeStrcutureName);
          //  delete the top one
          char * newType = returnTypeOfVaribleInVaribaleScopeArray(myVariableLinklist, relativeStrcutureName, globalScope);
          LexpressionList_headDelete( & LexpressionCollectionList);
          LexpressionList_headInsert( & LexpressionTypeCollectionList, newType);
          LexpressionList_headInsert( & LexpressionCollectionList, newType);
          LexpressionList_headInsert( & axcuilaryList,newType);
          
         // Lexpression_print(LexpressionCollectionList);

          char lastFiled[MAX_SIZE];
          char RelativeStrucure[1024];
          char relativeFiled[1024];

          int length;
          int counter = 0;
         
          do {
            counter++;
            char * temp1 = acquireFirstElementOfLexpressionList( & LexpressionCollectionList);
            char *temp2_ssss= acquireFirstElementOfLexpressionList( & axcuilaryList);
            strcpy(RelativeStrucure, temp2_ssss);
            LexpressionList_headDelete( & LexpressionCollectionList);
            char * temp2 = acquireFirstElementOfLexpressionList( & LexpressionCollectionList);
            strcpy(relativeFiled, temp2);
            length = Lexpression_length(LexpressionCollectionList);
            
            if (length != 1) {
              int flagCC = checker_structureFiled(myStructureList, RelativeStrucure, relativeFiled);

            
              
              if (flagCC == 0) {
                grammarError = 0;
                printf("GRAMMAR ERROR: The structure field %s does not exist\n", relativeFiled);
              } 
              else {
                // Preseving the type eachly
                char * returnTypeOFfILED = returnFiledTypeForSpecificStrucure(myStructureList, RelativeStrucure, relativeFiled);
               // printf("The return type of file is %s\n",returnTypeOFfILED);
                strcat(fullDotName,".");
                strcat(fullDotName,relativeFiled);
                LexpressionList_headInsert( & LexpressionTypeCollectionList, returnTypeOFfILED);
                LexpressionList_headInsert(& axcuilaryList,returnTypeOFfILED);
              }

              if (length == 2) {
                char * HeadOfTypeLexpression = acquireFirstElementOfLexpressionList( & LexpressionTypeCollectionList);
                LexpressionList_headInsert(&axcuilaryList,HeadOfTypeLexpression);
                Lexpression_print(axcuilaryList);
              }
            }

            if (length == 1) {
          
              
           
              // Preseving the type eachl
              strcat(fullDotName,".");
           
              strcat(fullDotName,relativeFiled);
              char * HeadOfTypeLexpressionLengthOne = acquireFirstElementOfLexpressionList( & LexpressionTypeCollectionList);
            
              char *tempStrcure =RelativeStrucure;
              char *tempFiled =relativeFiled;
            

             
              char *newReturn = returnFiledTypeForSpecificStrucure(myStructureList,tempStrcure,tempFiled);
             


              char * returnTypeOFfILED = returnFiledTypeForSpecificStrucure(myStructureList, RelativeStrucure, relativeFiled);
            
              if(returnTypeOFfILED == NULL){
                  grammarError = 0;
                  printf("GRAMMAR ERROR: structure field is not valid \n");
              }
              else
                LexpressionList_headInsert( & LexpressionTypeCollectionList, returnTypeOFfILED);
            

              
            }
          } while (length > 1 && grammarError != 0);

           
          if(grammarError == 0){
            assignmentTracker = GLOBAL_ASSIGNMENT_TRAKER_INVAILD;
            LexpressionList_initilization( & LexpressionCollectionList);
            LexpressionList_initilization( & LexpressionTypeCollectionList);
          

            myType = InitilizationAndResetOfTypeSystem(myType);
            modifyEnvironmentTypeSystemInExpressionList(myType,BOOL_TYPE);
          }
          else{
            Lexpression_print(LexpressionTypeCollectionList);
            char * TypeOfLastOne = acquireFirstElementOfLexpressionList( & LexpressionTypeCollectionList);
            Lexpression_print(LexpressionTypeCollectionList);

           

            if (strcmp(TypeOfLastOne, "int") == 0)
              globalType = GLOBAL_INT_TYPE;
            else if (strcmp(TypeOfLastOne, "bool") == 0)
              globalType = GLBOAL_BOOLEAN_TYPE;
            else if (strcmp(TypeOfLastOne, "string") == 0)
              globalType = GLOBAL_STRING_TYPE;

            assignmentTracker = GLOBAL_ASSIGNMENT_TRAKER_VAILD;
            assignmentLexpressionType = SWITCH_TO_STRUCURE_DOT;

            // After finishing computer intilization
            strcpy(lastStructureDotVariableGlobalRecorder,fullDotName);
            LexpressionList_initilization( & LexpressionCollectionList);
            LexpressionList_initilization( & LexpressionTypeCollectionList);
          
            myType = InitilizationAndResetOfTypeSystem(myType);
            modifyEnvironmentTypeSystemInExpressionList(myType,globalType);

          }
       }             
};

IFClause : 
  IFCondition THEN stmt
| IFCondition THEN stmt ELSE stmt
;

IFCondition: IF {
        globalType = BOOL_TYPE;
        myType = InitilizationAndResetOfTypeSystem(myType);
        modifyEnvironmentTypeSystemInExpressionList(myType,BOOL_TYPE);
} LPAREN expr RPAREN {
        typeSystem_Print(myType);
        int result = 0;
        int ExpressionNumber = myType -> expressionNumber;
        result = typeSystemSelectionAndJudgeSystem(myType);

        if (result == 0) {
          semanticsError = 0;
          assignmentCheckerCloseForVariableScopeArray(myVariableLinklist, lastestPureIdGlobalRecorder, globalScope);
          printf("SEMANTIC ERROR: Type checking error occurred \n");
        } 

        myType = InitilizationAndResetOfTypeSystem(myType);
  
};


/**************************************************************************************************
 * STATEMENTS
 *************************************************************************************************/

stmt:   
  FOR LPAREN ID{  
        char *latesfFunctioName = acquireHeadOfListCache(functionNameList);
        char *tempId = $3;
        int undelclaredCheck = checkVariableUndeclarationVariableScopeArray(myVariableLinklist,tempId,globalScope);

        if(undelclaredCheck == UNDELCARED){
          grammarError = 0;
          printf("GRAMMAR ERROR: for loop identifier %s\n is not declared\n",tempId);
        }
        else if(undelclaredCheck == NOT_UNCLEATION){
          char *returnTypeOfThisId = returnTypeOfVaribleInVaribaleScopeArray(myVariableLinklist,tempId,globalScope);
          
          if(strcmp(returnTypeOfThisId,"int")==0)
            globalType =GLOBAL_INT_TYPE;
          else if(strcmp(returnTypeOfThisId,"bool")==0)
            globalType =GLBOAL_BOOLEAN_TYPE;
          else if(strcmp(returnTypeOfThisId,"string")==0)
            globalType =GLOBAL_STRING_TYPE;

          assignmentCheckerOpenForVariableScopeArray(myVariableLinklist,tempId,globalScope);
          assignmentTracker = GLOBAL_ASSIGNMENT_TRAKER_VAILD;
          strcpy(lastestPureIdGlobalRecorder,tempId);
          assignmentLexpressionType = SWITCH_TO_PURE_ID;
          myType = InitilizationAndResetOfTypeSystem(myType);
          modifyEnvironmentTypeSystemInExpressionList(myType,globalType);

        }

  } EQ expr{
        if (assignmentTracker == GLOBAL_ASSIGNMENT_TRAKER_VAILD){
          int temp = globalType;
          modifyEnvironmentTypeSystemInExpressionList(myType,temp);

          // clear expression list here
          typeSystem_Print(myType);
          int result=0;
          int ExpressionNumber = myType -> expressionNumber;
          result = typeSystemSelectionAndJudgeSystem(myType);

          if (result == 0){
            semanticsError = 0;
            assignmentCheckerCloseForVariableScopeArray(myVariableLinklist,lastestPureIdGlobalRecorder,globalScope);
            printf("SEMANTICS ERROR: type checking error occurred \n");
          }
          else if(result==1)
            assignmentCheckerOpenForVariableScopeArray(myVariableLinklist,lastestPureIdGlobalRecorder,globalScope);
        }
        else if (assignmentTracker == GLOBAL_ASSIGNMENT_TRAKER_INVAILD) {
          grammarError = 0;
          printf("GRAMMAR ERROR: cannot assign to an undeclared variable \n");
        }

        assignmentTracker = GLOBAL_ASSIGNMENT_TRACKER_UNDEFINED;
        myType = InitilizationAndResetOfTypeSystem(myType);

        // Clearing the type system 
        globalType = GLOBAL_UNDEFINED_TYPE;
        assignmentLexpressionType=UNDEFINT_LEFTEXPRESSION_TYPE;

        // Cleaning for next boolean expression
        myType = InitilizationAndResetOfTypeSystem(myType);
        globalType= BOOL_TYPE;
        modifyEnvironmentTypeSystemInExpressionList(myType,globalType);

  } SEMICOLON expr SEMICOLON {

        int temp = globalType;
        modifyEnvironmentTypeSystemInExpressionList(myType, temp);

        // clear expression list here
        typeSystem_Print(myType);
        int result = 0;
        int ExpressionNumber = myType -> expressionNumber;
        result = typeSystemSelectionAndJudgeSystem(myType);
        if (result == 0) {
          semanticsError = 0;
          assignmentCheckerCloseForVariableScopeArray(myVariableLinklist, lastestPureIdGlobalRecorder, globalScope);
        } 
        else if (result == 1)
          assignmentCheckerOpenForVariableScopeArray(myVariableLinklist, lastestPureIdGlobalRecorder, globalScope);

        assignmentTracker = GLOBAL_ASSIGNMENT_TRACKER_UNDEFINED;
        myType = InitilizationAndResetOfTypeSystem(myType);

        // Clearing the type system agsi
        globalType = GLOBAL_UNDEFINED_TYPE;
        assignmentLexpressionType=UNDEFINT_LEFTEXPRESSION_TYPE;

  }stmt RPAREN 

| IFClause                     
| PRINTF LPAREN STRING_CONSTANT RPAREN SEMICOLON                          
| RETURN {
        char * tempFunctionDeclrationType = acquireHeadOfListCache(functionDeclarationList);
        char * trueFunctionName = acquireHeadOfListCache(functionNameList);
        if (strcmp(tempFunctionDeclrationType, "int") == 0)
          globalType = GLOBAL_INT_TYPE;
        else if (strcmp(tempFunctionDeclrationType, "bool") == 0)
          globalType = GLBOAL_BOOLEAN_TYPE;
        else if (strcmp(tempFunctionDeclrationType, "string") == 0)
          globalType = GLOBAL_STRING_TYPE;
        else if(strcmp(tempFunctionDeclrationType, "void")==0)
          globalType = GL0BAL_FUNCTION_VOID_RETURN_TYPE;

        if(globalType == GL0BAL_FUNCTION_VOID_RETURN_TYPE){
          myType=InitilizationAndResetOfTypeSystem(myType);
          // Selecting random one ;
          modifyEnvironmentTypeSystemInExpressionList(myType,STRING_TYPE);
        }
        else{
            myType = InitilizationAndResetOfTypeSystem(myType);
            modifyEnvironmentTypeSystemInExpressionList(myType, globalType);
        }

} expr SEMICOLON  {

        char *trueFunctionName = acquireHeadOfListCache(functionNameList);
        int temp =globalType;

        if(globalType== GL0BAL_FUNCTION_VOID_RETURN_TYPE){
          // clear expression list here
          typeSystem_Print(myType);
          int result;
          int ExpressionNumberForVoidFunction =myType->expressionNumber;

          if(ExpressionNumberForVoidFunction==0){
            InsertHashMap(Vaild_DeclrationWithReturnTypeFunctionChecker,trueFunctionName,"vaild");
            InsertHashMap(functionDeclrationTypeChecker,trueFunctionName,"void");
          }
          else
              semanticsError=0;

          globalType = GLOBAL_UNDEFINED_TYPE;
          myType=InitilizationAndResetOfTypeSystem(myType);
        }
        else{
          // clear expression list here
          typeSystem_Print(myType);
          int result;
          int ExpressionNumber =myType->expressionNumber;
          result = typeSystemSelectionAndJudgeSystem(myType);

          if(result == 0)
            semanticsError = 0;
          else if(result == 1){
            char *tempFunctionName = acquireHeadOfListCache(functionNameList);
            InsertHashMap(Vaild_DeclrationWithReturnTypeFunctionChecker,tempFunctionName,"vaild");
            char gloablTypeMapping[1024];

            if(globalType==INT_TYPE)
              strcpy(gloablTypeMapping,"int");
            else if(globalType==BOOL_TYPE)
              strcpy(gloablTypeMapping,"bool");
            else if(globalType==STRING_TYPE)
              strcpy(gloablTypeMapping,"string");
                    
            InsertHashMap(Vaild_DeclrationWithReturnTypeFunctionChecker,tempFunctionName,"vaild");
            InsertHashMap(functionDeclrationTypeChecker,tempFunctionName,gloablTypeMapping);
          }

          globalType = GLOBAL_UNDEFINED_TYPE;
          myType=InitilizationAndResetOfTypeSystem(myType);

      }
}                                         
| LBRACE{
        globalScope += 1; // increase scope
        char *lastesfFunctionName = acquireHeadOfListCache(functionNameList);
        bracketControlAdd(myFunctionList,lastesfFunctionName);
        ArraybracketControlAdd(myArrayFunctionList,lastesfFunctionName);
  } stmtlist RBRACE {
        char *lastesfFunctionName = acquireHeadOfListCache(functionNameList);
        ArraycloseScopeOfVariable(myArrayFunctionList,lastesfFunctionName);
        closeScopeOfVariable(myFunctionList,lastesfFunctionName);
        bracketControlSub(myFunctionList,lastesfFunctionName);
        ArraybracketControlSub(myArrayFunctionList,lastesfFunctionName);      
        globalScope-=1; // decrease scope

  }
| decl SEMICOLON                                                                                      
| lexprLHS  EQ expr SEMICOLON {
        if(assignmentLexpressionType == SWITCH_TO_PURE_ID){
          if (assignmentTracker == GLOBAL_ASSIGNMENT_TRAKER_VAILD) {
            int temp = globalType;
            modifyEnvironmentTypeSystemInExpressionList(myType,temp);

            // clear expression list here
            typeSystem_Print(myType);
            int result=0;
            int ExpressionNumber = myType -> expressionNumber;
            result = typeSystemSelectionAndJudgeSystem(myType);

            if (result == 0) {
              semanticsError = 0;
              assignmentCheckerCloseForVariableScopeArray(myVariableLinklist,lastestPureIdGlobalRecorder,globalScope);
              printf("SEMANTIC ERROR: Type checking error occurred \n");
            }
            else if(result==1)
              assignmentCheckerOpenForVariableScopeArray(myVariableLinklist,lastestPureIdGlobalRecorder,globalScope);

          }
          else if (assignmentTracker == GLOBAL_ASSIGNMENT_TRAKER_INVAILD) {
            grammarError = 0;
            printf("GRAMMAR ERROR: cannot assign to an undeclared variable \n");
          }

          assignmentTracker = GLOBAL_ASSIGNMENT_TRACKER_UNDEFINED;
          myType = InitilizationAndResetOfTypeSystem(myType);
          // Clearing the type system agsi
          globalType = GLOBAL_UNDEFINED_TYPE;
          assignmentLexpressionType=UNDEFINT_LEFTEXPRESSION_TYPE;

        } //end if

        if(assignmentLexpressionType== SWITCH_TO_STRUCURE_DOT){
          if (assignmentTracker == GLOBAL_ASSIGNMENT_TRAKER_VAILD) {
            int temp = globalType;
            // clear expression list here
            typeSystem_Print(myType);
            int result=0;
            int ExpressionNumber = myType -> expressionNumber;
            result = typeSystemSelectionAndJudgeSystem(myType);

            if (result == 0) {
              semanticsError = 0;
              assignmentCheckerCloseForVariableScopeArray(myVariableLinklist,lastestPureIdGlobalRecorder,globalScope);
              printf("SEMANTIC ERROR: Type checking error occurred \n");
            }
            else if(result==1)
                InsertHashMap(globalStrucureVaildAssignment,lastStructureDotVariableGlobalRecorder,"vaild");
          }
          else if (assignmentTracker == GLOBAL_ASSIGNMENT_TRAKER_INVAILD) {
            grammarError = 0;
            printf("GRAMMAR ERROR: cannot assign to an undeclared variable \n");
          }

          assignmentTracker = GLOBAL_ASSIGNMENT_TRACKER_UNDEFINED;
          myType = InitilizationAndResetOfTypeSystem(myType);
          // Clearing the type system agsi
          globalType = GLOBAL_UNDEFINED_TYPE;
          assignmentLexpressionType=UNDEFINT_LEFTEXPRESSION_TYPE;
        } //end if

        assignmentTracker = GLOBAL_ASSIGNMENT_TRACKER_UNDEFINED;
        myType = InitilizationAndResetOfTypeSystem(myType);
        // Clearing the type system agsi
        globalType = GLOBAL_UNDEFINED_TYPE;
        assignmentLexpressionType=UNDEFINT_LEFTEXPRESSION_TYPE;
}                                    
| ID {
        strcpy(globalFunctionCallName,$1);
        char *tempFunctionName = $1;
        char* flagWellDefinedFunctionChekcker = GetHashMap(Vaild_DeclrationWithReturnTypeFunctionChecker,tempFunctionName);

        if(flagWellDefinedFunctionChekcker == NULL){
          semanticsError = 0;
          printf("SEMANTICS ERROR: function is not well defined and could not be called\n");
        }
        else{
          struct functionHeaderParameterNode * myNode = getFunctionParameterList(myFunctionInfoHeaderList, tempFunctionName);
          int parameterIteratiion = getSpecifificFunctionParameterCount(myFunctionInfoHeaderList, tempFunctionName);
          struct functionHeaderParameterNode * indexFunctionParamet;
          
          globalFunctionParameterNumberForFunctionItself=0;
          for (indexFunctionParamet = myNode; indexFunctionParamet < myNode + parameterIteratiion; indexFunctionParamet++){
            char * Type = indexFunctionParamet -> parameterType;
            globalFunctionParameterNumberForFunctionItself+=1;
            LexpressionList_tailInsert( & LFunctionParameterCollectionList, Type);
          }

          // reseting for functionlist
          myType =InitilizationAndResetOfTypeSystem(myType);
        }
} LPAREN exprlist RPAREN SEMICOLON {
        char *tempFucntionName = $1;   
        int checkFlagMatching = checkingFunctionParameterSizeCounter(myFunctionInfoHeaderList,tempFucntionName,globalFunctionParameterNumber);
        
        if(checkFlagMatching == Missing_Match_function_Parameter_count){
          semanticsError = 0;
          printf("SEMANTICS ERROR: number of arguments passed does not match function signature \n");
        }

        globalFunctionParameterNumber=0;
        globalFunctionParameterNumberForFunctionItself=0;
        LexpressionList_initilization(&LFunctionParameterCollectionList);
        myType = InitilizationAndResetOfTypeSystem(myType);
}                          
| decl EQ expr  SEMICOLON {
        semanticsError =0;
        printf("SEMANTICS ERROR: declaration and assignment is on the same line\n");
  }
| lexprLHS EQ ID {
        strcpy(globalFunctionCallName,$3);

        //Checking well defined function here 
        char *tempFunctionName = $3;
        char* flagWellDefinedFunctionChekcker = GetHashMap(Vaild_DeclrationWithReturnTypeFunctionChecker,tempFunctionName);

        if(flagWellDefinedFunctionChekcker == NULL){
          semanticsError = 0;
          printf("SEMANTICS ERROR: function is not well defined and could not be called\n");
        }
        else{
          char *functionReturnType =GetHashMap(functionDeclrationTypeChecker,tempFunctionName);
          if(strcmp(functionReturnType,"void") == 0){
              semanticsError = 0;
              printf("SEMANTIC ERROR: void function cannot be assigned to a variable \n");
          }
          else{
            char gloablTypeMapping[1024];

            if(globalType==INT_TYPE)
                strcpy(gloablTypeMapping,"int");
            else if(globalType==BOOL_TYPE)
              strcpy(gloablTypeMapping,"bool");
            else if(globalType==STRING_TYPE)
                strcpy(gloablTypeMapping,"string");

            if(strcmp(functionReturnType,gloablTypeMapping)==0){
              // doing function list here
              struct functionHeaderParameterNode * myNode = getFunctionParameterList(myFunctionInfoHeaderList, tempFunctionName);
              int parameterIteratiion = getSpecifificFunctionParameterCount(myFunctionInfoHeaderList, tempFunctionName);

              struct functionHeaderParameterNode * indexFunctionParamet;
              globalFunctionParameterNumberForFunctionItself=0;
              for (indexFunctionParamet = myNode; indexFunctionParamet < myNode + parameterIteratiion; indexFunctionParamet++){
                char * Type = indexFunctionParamet -> parameterType;
                globalFunctionParameterNumberForFunctionItself+=1;
                LexpressionList_tailInsert( & LFunctionParameterCollectionList, Type);
              }

              // reseting for functionlist
              myType =InitilizationAndResetOfTypeSystem(myType);
            }
            else{
              semanticsError=0;
              char * idd = $3;
              printf("SEMANTICS ERROR: The  type is not equal to fucntin declation type \n");
            }
          } // end if

        }// end if
} LPAREN exprlist RPAREN SEMICOLON{
        int checkFlagMatching = checkingFunctionParameterSizeCounter(myFunctionInfoHeaderList,$3,globalFunctionParameterNumber);

        if(checkFlagMatching == Missing_Match_function_Parameter_count){
          semanticsError = 0;
          printf("SEMANTICS ERROR: number of arguments passed does not match function signature \n");
        }

      
        if((semanticsError != 0)&&(grammarError != 0))
        {
          //printf("assign this function to a varaible!\n");
           assignmentCheckerOpenForVariableScopeArray(myVariableLinklist, lastestPureIdGlobalRecorder, globalScope); 
        }
        

        globalFunctionParameterNumber=0;
        myType=InitilizationAndResetOfTypeSystem(myType);
        LexpressionList_initilization(&LFunctionParameterCollectionList);

}                
;

stmtlist: /*empty list*/
|          stmt stmtlist 
;

/**************************************************************************************************
 * Variable Declaration 
 *************************************************************************************************/

decl:  
  INT ID {
        char *variableName = $2;
        char *variableType = "int";
        char *latestFunctionName = acquireHeadOfListCache(functionNameList);
        char *latestFunctionType = acquireHeadOfListCache(functionDeclarationList);

        int redeclatedCheck =checkVariableRecelarationVariableScopeArray(myVariableLinklist,variableName,globalScope);
        
        if(redeclatedCheck == RECLRATED){ // check if redeclared
            printf("GRAMMAR ERROR: %s is already in use \n", $2);
            grammarError = 0;
        } // end if

        if(redeclatedCheck == NOT_RECLARED){ // if not redeclared
          insertVariableDeclarationforSpecificFunction(myFunctionList,latestFunctionName,latestFunctionType,variableType,variableName);  
          inserionOfVaraibelScopeArray(myVariableLinklist,variableType,variableName,globalScope);
         
          ArrayinsertVariableDeclarationforSpecificFunction(myArrayFunctionList,latestFunctionName,latestFunctionType,variableType,variableName);
        } // end if
}     
| BOOL ID {
        char *variableName = $2;
        char *variableType = "bool";
        char *latestFunctionName = acquireHeadOfListCache(functionNameList);
        char *latestFunctionType = acquireHeadOfListCache(functionDeclarationList);

        int redeclatedCheck =checkVariableRecelarationVariableScopeArray(myVariableLinklist,variableName,globalScope);
       
        if(redeclatedCheck == RECLRATED){ // check if redeclared
            printf("GRAMMAR ERROR: %s is already in use \n", $2);
            grammarError = 0;
        } // end if

        if(redeclatedCheck == NOT_RECLARED){ // if not redeclared
          inserionOfVaraibelScopeArray(myVariableLinklist,variableType,variableName,globalScope);
          insertVariableDeclarationforSpecificFunction(myFunctionList,latestFunctionName,latestFunctionType,variableType,variableName);
          ArrayinsertVariableDeclarationforSpecificFunction(myArrayFunctionList,latestFunctionName,latestFunctionType,variableType,variableName);
        } // end if
  }
| STRING_TYPE ID {
        char * variableName = $2;
        char * variableType = "string";
        char * latestFunctionName = acquireHeadOfListCache(functionNameList);
        char * latestFunctionType = acquireHeadOfListCache(functionDeclarationList);

        int redeclatedCheck =checkVariableRecelarationVariableScopeArray(myVariableLinklist,variableName,globalScope);
        if (redeclatedCheck == RECLRATED) { // check if redeclared
          printf("GRAMMAR ERROR: %s is already in use \n", $2);
          grammarError = 0;
        } // end if

        if (redeclatedCheck == NOT_RECLARED) { // if not redeclared
          insertVariableDeclarationforSpecificFunction(myFunctionList,latestFunctionName,latestFunctionType,variableType,variableName);
          insertVariableDeclarationforSpecificFunction(myFunctionList, latestFunctionName, latestFunctionType, variableType, variableName);
          ArrayinsertVariableDeclarationforSpecificFunction(myArrayFunctionList,latestFunctionName,latestFunctionType,variableType,variableName);
        } // end if
  }
| ID ID {
          char * structureName = $1;
          char * strctureNameCheckerFlag = GetHashMap(structureNameCheckerhashMap, structureName);
          if (strctureNameCheckerFlag == NULL) {
            printf("GRAMMAR ERROR: Structure %s has not been declared\n", structureName);
            grammarError = 0;
          }

          if (strctureNameCheckerFlag) {
            char * variableName = $2;
            char * variableType = $1;
            char * latestFunctionName = acquireHeadOfListCache(functionNameList);
            char * latestFunctionType = acquireHeadOfListCache(functionDeclarationList);

            int redeclatedCheck =checkVariableRecelarationVariableScopeArray(myVariableLinklist,variableName,globalScope);
            if(redeclatedCheck == RECLRATED) { // check if redeclared
              printf("GRAMMAR ERROR: %s is already in use \n", $2);
              grammarError = 0;
            } // end if
            
            if (redeclatedCheck == NOT_RECLARED ) { // if not redeclared
              ArrayinsertVariableDeclarationforSpecificFunction(myArrayFunctionList,latestFunctionName,latestFunctionType,variableType,variableName);
              insertVariableDeclarationforSpecificFunction(myFunctionList,latestFunctionName,latestFunctionType,variableType,variableName);
              inserionOfVaraibelScopeArray(myVariableLinklist,variableType,variableName,globalScope);
            } // end if
          }
      }




%%

void yyerror (){
   printf("Exception Thrown! \n");
}

HashMap* CreateHashMap(int n){
    HashMap* hashMap = (HashMap*)myCalloc(1, sizeof(HashMap));
    hashMap->hashArr = (HashNode**)myCalloc(n, sizeof(HashNode*));
    if (hashMap == NULL || hashMap->hashArr == NULL)
        return NULL;

    hashMap->size = n;
    return hashMap;
};

int InsertHashMap(HashMap* hashMap, char* key, char* value){
    HashNode* node = (HashNode*)myCalloc(1, sizeof(HashNode));
    if (node == NULL)
        return 0;

    node->key = strdup(key);
    node->value = strdup(value);
    node->next = NULL;

    int index = myHash(key) % hashMap->size;
    if (hashMap->hashArr[index] == NULL)
        hashMap->hashArr[index] = node;
    else {
        HashNode *temp = hashMap->hashArr[index];
        HashNode *prev = temp;

        while (temp != NULL) {
          if (strcmp(temp->key, node->key) == 0) {
              myFree(temp->value);
              temp->value = strdup(node->value);
              return 1;
          }
          prev = temp;
          temp = temp->next;
        }
        prev->next = node;
    }
    return 1;
}

char* GetHashMap(HashMap* hashMap, char* key){
    int index = myHash(key) % hashMap->size;
    HashNode *temp = hashMap->hashArr[index];

    while (temp != NULL) {
        if (strcmp(temp->key, key) == 0) 
            return temp->value;

        temp = temp->next;
    }
    return NULL;
}

void DeleteHashMap(HashMap* hashMap){
    for (int i = 0; i < hashMap->size; i++){
        HashNode *temp = hashMap->hashArr[i];
        HashNode *prev = temp;

        while (temp != NULL) {
            prev = temp;
            temp = temp->next;
            myFree(prev->key);
            myFree(prev->value);
            myFree(prev);
        }
    }
    myFree(hashMap->hashArr);
    myFree(hashMap);
    hashMap->hashArr = NULL;
    hashMap = NULL;
}

void PrintHashMap(HashMap* hashMap){
    HashNode* node = NULL;
    for (int i = 0; i < hashMap->size; i++){
        node = hashMap->hashArr[i];
        if (node != NULL) {
            HashNode* temp = node;
            while (temp != NULL) {
                temp = temp->next;
            }
            fprintf(yyout,"\n");
        }
    }
}

// Semantics function 
 void functionSizeChecker()
 {
        int lengthOfFunction = lengthOfCacheNodeForFunctionLengthChecking(functionNameList);
        if(lengthOfFunction ==0)
        {
           semanticsError = 0;
           printf("Semantics error ,function number is zero \n");
        }
 }
int main (int argc, char *argv[]){
  // parsing
	int flag;
	yyin = fopen(argv[1], "r");
	flag = yyparse();
	fclose(yyin);
  functionSizeChecker();
    
    if((flag != 0) || (grammarError == 0) || (semanticsError == 0)){
        if(flag !=0)
          printf("LEXICAL ERROR!\n");

        if(grammarError ==0) 
          printf("GRAMMAR ERROR!\n");

        if(semanticsError==0)
          printf("SEMANTIC ERROR!\n");

        printf("\n                      ❌ FAILED TO COMPILE ❌\n");
    }
    else
      printf("\n                    ✅ COMPILED SUCCESSFULLY ✅\n");

    printf("________________________,--.___________,--._______________________\n");
    printf("                        `--'           `--'\n\n");

	return flag;
}
