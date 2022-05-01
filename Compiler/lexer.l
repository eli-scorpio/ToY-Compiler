%option noyywrap

%{
  ///////////////////////////////////////////////
  // Authors: Mingwei Shi & Eligijus Skersonas //
  ///////////////////////////////////////////////
  
	#include <stdlib.h>
	#include <string.h>
   #include"globals.h"
	extern FILE *yyin;
 
	//extern FILE *yyout;
   #include "parser.tab.h"
	int valid = 1; 
	int lineno = 1; // initialize to 1
	void ret_print(char *token_type);
	void yyerror();

   int lexicalSpeficError=1;
%}



alpha     [a-zA-Z_]
digit     [0-9]
alnum     {alpha}|{digit}
print     [ -~]

ID        {alpha}+{alnum}*
ICONST    "0"|[0-9]{digit}*
WrongString \"[.]*
STRING_CONST    \"{print}*\"
%%


"//".*        //{ printf("Eat up comment at line %d\n", lineno);  } 
"##".*        //{ printf("Eat up comment at line %d\n", lineno); } 





"if"                           { return IF;    }
"then"                         { return THEN;  }
"else"                         { return ELSE;  }
"true"                         {
                                 yylval.str_val = malloc(yyleng * sizeof(char));
                                 strcpy(yylval.str_val, yytext);
                                 return TRUE;  
                               }
"false"                        {
                                 yylval.str_val = malloc(yyleng * sizeof(char));
                                 strcpy(yylval.str_val, yytext);
                                 return FALSE; 
                               }
"int"                          { return INT;   }
"bool"                         { return BOOL;  }
"printf"                       { return PRINTF;}
"void"                         { return VOID;  }
"string"                       { return STRING_TYPE;}
"for"                          { return FOR;   }
"return"                       { return RETURN;}
"struct"                       { return STRUCT;}

"="                            {
   yylval.str_val = malloc(yyleng * sizeof(char));
   strcpy(yylval.str_val, yytext); return EQ; }

"-"                            {
   yylval.str_val = malloc(yyleng * sizeof(char));
   strcpy(yylval.str_val, yytext);return SUB; }

"+"                            {
   yylval.str_val = malloc(yyleng * sizeof(char));
   strcpy(yylval.str_val, yytext);return ADD; }

"*"                            {
   yylval.str_val = malloc(yyleng * sizeof(char));
   strcpy(yylval.str_val, yytext);return MUL; }

"/"                            {
   yylval.str_val = malloc(yyleng * sizeof(char));
   strcpy(yylval.str_val, yytext);return DIV; }

"mod"|"%"                      {
   yylval.str_val = malloc(yyleng * sizeof(char));
   strcpy(yylval.str_val, yytext);return MOD; }

"and"|"&&"                     {
   yylval.str_val = malloc(yyleng * sizeof(char));
   strcpy(yylval.str_val, yytext);return AND; }

"or"|"||"                      {
   yylval.str_val = malloc(yyleng * sizeof(char));
   strcpy(yylval.str_val, yytext);return OR;  }

"not"                          {
   yylval.str_val = malloc(yyleng * sizeof(char));
   strcpy(yylval.str_val, yytext);return NOT; }

"!"                            {
   yylval.str_val = malloc(yyleng * sizeof(char));
   strcpy(yylval.str_val, yytext); return NOT;}

"=="                           {
   yylval.str_val = malloc(yyleng * sizeof(char));
   strcpy(yylval.str_val, yytext);return EQUALITY; }

"!="                           {
   yylval.str_val = malloc(yyleng * sizeof(char));
   strcpy(yylval.str_val, yytext);return NOT_EQUAL; }

">="                           {
   yylval.str_val = malloc(yyleng * sizeof(char));
   strcpy(yylval.str_val, yytext);return GREATER_OR_EQUAL; }

"<="                           {
   yylval.str_val = malloc(yyleng * sizeof(char));
   strcpy(yylval.str_val, yytext);return LESS_OR_EQUAL; }

"<"                            {
   yylval.str_val = malloc(yyleng * sizeof(char));
   strcpy(yylval.str_val, yytext);return LESS_THAN; }
">"                            {
   yylval.str_val = malloc(yyleng * sizeof(char));
   strcpy(yylval.str_val, yytext); return GREATER_THAN; }

"{"                            { return LBRACE; }
"}"                            { return RBRACE; }
"("                            { return LPAREN; }
")"                            { return RPAREN; }

"."                            { return DOT; }
";"                            { return SEMICOLON; }
","                            { return COMMA;}



{ID}    {

      const char *a[17];
      a[0]="bool"; a[1]="true"; a[2]="false"; a[3]="if"; a[4]="then"; a[5]="else";
      a[6]="for"; a[7]="return"; a[8]="struct"; a[9]="int"; a[10]="printf"; a[11]="void";
      a[12]="string"; a[13]="and"; a[14]="or"; a[15]="not"; a[16]="mod";

      int stop=0;

      for(int i = 0; (i < 17)&&(!stop); i++){
         if(strcmp(yytext, a[i]) == 0){
            valid = 0;
            printf("LEXICAL ERROR: Reserved Keyword\n");
            printf("\n                      ❌ FAILED TO COMPILE ❌\n");
            stop =1;
            lexicalSpeficError=0;
         }
      }

      if(lexicalSpeficError==0){
         printf("LEXICAL ERROR: using keyword as ID \n");
         return -1;
      }
      else{
         yylval.str_val = malloc(yyleng * sizeof(char));
         strcpy(yylval.str_val, yytext); 

         return ID;
      }

  
    
}
      
{ICONST}    { 
      char *string = yytext;
      int valueForInt = atoi(yytext);
    //  yylval.int_val = atoi(yytext);

      if(valueForInt >= -32768 && valueForInt <= 32767){
         yylval.str_val = malloc(yyleng * sizeof(char));
         strcpy(yylval.str_val, yytext); 
         
         return ICONST;
      }
     
      else {
        valid = 0;
        printf("LEXICAL ERROR: Integer too large\n");
        printf("\n                     ❌ FAILED TO COMPILE ❌\n");
        exit(0);
        return -1;
      }

 }

{WrongString}  {

            yylval.str_val = malloc(yyleng * sizeof(char));
            strcpy(yylval.str_val, yytext); 
            printf("Wrong string cathing !\n");

            char *copyText = yytext;
            int lengthOfString = strlen(copyText);
            char copyArray[lengthOfString];
            strcpy(copyArray, copyText);
            char quationation =34;

            if ((copyArray[0]!=quationation)||(copyArray[lengthOfString-1]!=quationation)){
               printf("LEXICAL ERROR! \n");
               printf("\n                      ❌ FAILED TO COMPILE ❌\n");
               exit(0);
               return -1;
            }

            char quationString[2] ="\"";
            char *retJudge = strstr(copyArray, quationString);

            if(retJudge){
               printf("LEXICAL ERROR \n");
               printf("\n                      ❌ FAILED TO COMPILE ❌\n");
               exit(0);
               return -1;
            }


}
{STRING_CONST}    {
            yylval.str_val = malloc(yyleng * sizeof(char));
            strcpy(yylval.str_val, yytext); 
            char *copyText = yytext;
            int lengthOfString = strlen(copyText);

            char copyArray[lengthOfString];
            strcpy(copyArray, copyText);

            return STRING_CONSTANT; 
         }


"\n"        { lineno += 1; }
[ \t\r\f]+  /* eat up whitespace */

.       { printf("LEXICAL ERROR: Unrecognized character"); yyerror(); }

%%
/*
int main(int argc, char **argv) {

    yyin = fopen(argv[1], "r");
    yylex();
    fclose(yyin);
    return 0;
    

    if(valid != 0) {
        printf("\n***FAILURE***\n");
        printf("________________________,--.___________,--._______________________\n");
        printf("                        `--'           `--'\n\n");
        return -1;
    } 

    printf("\n***SUCCESS***\n");
    printf("________________________,--.___________,--._______________________\n");
    printf("                        `--'           `--'\n\n");
    return 0;
}
*/

