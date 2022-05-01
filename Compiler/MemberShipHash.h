//
// Created by Mingwei Shi on 29/03/2022.
//

#ifndef HSSS_MEMBERSHIPHASH_H
#define HSSS_MEMBERSHIPHASH_H
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
 struct membershipNode{
    char *name;
    char *desc;
    struct membershipNode *next;
}node;
#define HASHSIZE 1024
struct memebershipHashTable
{
    struct membershipNode *hashtable[HASHSIZE];
};
//#define HASHSIZE 1024
//static membershipNode* hashtab[HASHSIZE];
struct memebershipHashTable *initilizationOfMemebershipHashtable(struct memebershipHashTable* thisMemebshipHashtable);
struct membershipNode* lookupInMemebershipHashTable(struct memebershipHashTable* thisMemebshipHashtable, char *n);
char* membershipHashtable_strdup(char *o);
char* getValueFromKeyMemebershipHashtable(struct memebershipHashTable* thisMemebshipHashtable,char* name);
int installNewKeyAndValueInMembershipHashTable(struct memebershipHashTable* thisMemebshipHashtable,char* name, char* desc);

void displayMembershipHashtable(struct memebershipHashTable* thisMemebshipHashtable);
void cleanupMembershipHahtable(struct memebershipHashTable* thisMemebshipHashtable);


#endif //HSSS_MEMBERSHIPHASH_H
