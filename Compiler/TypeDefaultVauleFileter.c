//
// Created by Mingwei Shi on 02/04/2022.
//

#include "TypeDefaultVauleFileter.h"


struct TypeDefultValueFilter * initilization_typeDefaultFilter(struct TypeDefultValueFilter * thisOne)
{
    struct TypeDefultValueFilter *thisTypeVauleFileter;
    thisTypeVauleFileter = (struct  TypeDefultValueFilter *)malloc(sizeof (struct  TypeDefultValueFilter));

    strcpy(thisTypeVauleFileter->abstructIDType,"NULL");
    strcpy(thisTypeVauleFileter->defaultValue,"NULL");
    return thisTypeVauleFileter;
}

void adding_abstructureTypeInDefaultFileter(struct TypeDefultValueFilter *thisDefaultFileter,char *thisType)
{
    strcpy(thisDefaultFileter->abstructIDType,thisType);
}
void transferSystem_typeDefaultFilter(struct  TypeDefultValueFilter *thisTypeFileter)
{
        char *copyOfType = thisTypeFileter->abstructIDType;
        if(strcmp(copyOfType,"int")==0)
        {
            strcpy(thisTypeFileter->defaultValue,"11");
        }
        else if(strcmp(copyOfType,"bool")==0)
        {
            strcpy(thisTypeFileter->defaultValue,"true");
        }
        else if(strcmp(copyOfType,"string")==0)
        {
            char filling[6];
            filling[0]=34;
            filling[1]='t';
            filling[2]='o';
            filling[3]='m';
            filling[4]=34;
            filling[5]='\0';
            strcpy(thisTypeFileter->defaultValue,filling);
        }
}
char * acquireFilterVaule(struct  TypeDefultValueFilter *thisTypeFileter)
{
    transferSystem_typeDefaultFilter(thisTypeFileter);
    return thisTypeFileter->defaultValue;
}