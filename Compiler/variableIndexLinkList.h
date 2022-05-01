//
// Created by Mingwei Shi on 30/03/2022.
//

#ifndef VARAIBLESCOPECOLLECTION_VARIABLEINDEXLINKLIST_H
#define VARAIBLESCOPECOLLECTION_VARIABLEINDEXLINKLIST_H

#include <stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct variableIndexNode
{
    int data;
    struct variableIndexNode *next;
} variableLNode;


void headInsertVariableIndexLinklist(variableLNode *h, int data);
void outputVariableIndexLinklist(variableLNode *h);
variableLNode * variableIndexListInitlization(variableLNode* h);
int getLatestIndexVariableIndexLinklist(variableLNode *h);
int checkEmptyVariableIndexLinklist(variableLNode *h);


#endif //VARAIBLESCOPECOLLECTION_VARIABLEINDEXLINKLIST_H
