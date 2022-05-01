//
// Created by Mingwei Shi on 14/03/2022.
//
#ifndef STRUCTURE_RECORD_H
#define STRUCTURE_RECORD_H
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<string.h>

// ArrayList in java
/*
 * Node is for strucure name
 */

#define MAX_SIZE 1024
/*
 * Strucure name
 * fildlist
 */
struct stuctureFiledNode
{
    char declarationType[MAX_SIZE];
    char identificationName[MAX_SIZE];
    // 1 for decleation  0 for not

};
typedef struct structureNode
{
    char structureName[MAX_SIZE];
    // the maxfile is 1024 for ELEMENT
    /*
     * For example
     * struture Name{
     *      int age;
     *      char * name;
     * }
     */
    struct stuctureFiledNode filedList[MAX_SIZE];
}StructuerNode;

 struct strucureList
{
    StructuerNode arrayStucure[MAX_SIZE];
};
struct strucureList * init_strucure_list( struct strucureList *thisStructureList);
void add_strucure_name( struct strucureList *thisStructureList,char *strucreuName);
void add_structureFiled( struct strucureList *thisStructureList,char * structureName,char *filedType,char * filedName);

/*
 * Return 1 true
 * Return 0 false
 */
int structureNameExistChecker( struct strucureList *thisStructureList,char *  structureName);
/*
 * Return 1 declrated alrea
 * Return 0 false
 */

int checker_structureFiled( struct strucureList *thisStructureList,char * stuName,char * fieldName);

char *returnFiledTypeForSpecificStrucure( struct strucureList *thisStructureList,char * stuName,char * fieldName);

void print_strucureInfo(struct strucureList *thisStructureList,char *structureName);
#endif