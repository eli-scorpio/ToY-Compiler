//
// Created by Mingwei Shi on 29/03/2022.
//

#include "MemberShipHash.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct memebershipHashTable *initilizationOfMemebershipHashtable(struct memebershipHashTable* thisMemebshipHashtable)
{
    thisMemebshipHashtable = malloc(sizeof( struct memebershipHashTable));
    int i;
    for(i=0;i<HASHSIZE;i++) {
        thisMemebshipHashtable->hashtable[i] = NULL;
    }
    return thisMemebshipHashtable;

}

unsigned int hashingFunctionForMembership(char *s){
    unsigned int h=0;
    for(;*s;s++)
        h=*s+h*31;
    return h%HASHSIZE;
}

struct membershipNode* lookupInMemebershipHashTable(struct memebershipHashTable* thisMemebshipHashtable, char *n)
{
    unsigned int hi= hashingFunctionForMembership(n);
    struct membershipNode* np=thisMemebshipHashtable->hashtable[hi];
    for(;np!=NULL;np=np->next){
        if(!strcmp(np->name,n))
            return np;
    }
    return NULL;
}

char* membershipHashtable_strdup(char *o){
    int l=strlen(o)+1;
    char *ns=(char*)malloc(l*sizeof(char));
    strcpy(ns,o);
    if(ns==NULL)
        return NULL;
    else
        return ns;
}

char* getValueFromKeyMemebershipHashtable(struct memebershipHashTable* thisMemebshipHashtable,char* name)
{
    struct membershipNode* n= lookupInMemebershipHashTable(thisMemebshipHashtable, name);
    if(n==NULL){
        return NULL;
    }
    else{
        return n->desc;
    }

}

int installNewKeyAndValueInMembershipHashTable(struct memebershipHashTable* thisMemebshipHashtable,char* name, char* desc)
{
    unsigned int hi;
    struct membershipNode* np;
    if((np= lookupInMemebershipHashTable(thisMemebshipHashtable,name)) == NULL)
    {
        hi= hashingFunctionForMembership(name);
        np=(struct membershipNode*)malloc(sizeof(struct membershipNode));
        if(np==NULL)
        {
            return 0;
        }


        np->name= membershipHashtable_strdup(name);
        if(np->name==NULL) return 0;
        np->next=thisMemebshipHashtable->hashtable[hi];
        thisMemebshipHashtable->hashtable[hi]=np;
     //   hashtab[hi]=np;
    }
    else
    {
       free(np->desc);
    }

    np->desc= membershipHashtable_strdup(desc);
    if(np->desc==NULL)
    {
        return 0;
    }
    return 1;
}

/* A pretty useless but good debugging function,
which simply displays the hashtable in (key.value) pairs
*/

void displayMembershipHashtable(struct memebershipHashTable* thisMemebshipHashtable)
{
    int i;
    struct membershipNode *t;
    for(i=0;i<HASHSIZE;i++){
        if(thisMemebshipHashtable->hashtable[i]==NULL) {
            printf("()");
        }
        else{
            t=thisMemebshipHashtable->hashtable[i];
            printf("(");
            for(;t!=NULL;t=t->next)
                printf("(%s.%s) ",t->name,t->desc);
            printf(".)\n");
        }
    }
}

void cleanupMembershipHahtable(struct memebershipHashTable* thisMemebshipHashtable)
{
    int i;
    struct membershipNode *np,*t;
    for(i=0;i<HASHSIZE;i++){
        if(thisMemebshipHashtable->hashtable[i]!=NULL){
            np=thisMemebshipHashtable->hashtable[i];
            while(np!=NULL){
                t=np->next;
                free(np->name);
                free(np->desc);
                free(np);
                np=t;
            }
        }
    }
}