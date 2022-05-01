//
// Created by Mingwei Shi on 02/04/2022.
//

#ifndef TYPEDEFAULTVAULEFITER_TYPEDEFAULTVAULEFILETER_H
#define TYPEDEFAULTVAULEFITER_TYPEDEFAULTVAULEFILETER_H
#define MAX_SIZE 1024

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct TypeDefultValueFilter
{
    char abstructIDType[MAX_SIZE];
    char defaultValue[MAX_SIZE];

};
/*
 *
 * String type : "defaultString"
 * Boolean type default value fill : "true"
 * Integer type defulat value : "1"
 */

//function
//Initilze
// getting abstruct Type
// Transfer system
// return default fill vaule

struct TypeDefultValueFilter * initilization_typeDefaultFilter();

void adding_abstructureTypeInDefaultFileter(struct TypeDefultValueFilter *thisDefaultFileter,char *thisType);

void transferSystem_typeDefaultFilter(struct  TypeDefultValueFilter *thisTypeFileter);

char * acquireFilterVaule(struct  TypeDefultValueFilter *thisTypeFileter);

#endif //TYPEDEFAULTVAULEFITER_TYPEDEFAULTVAULEFILETER_H
