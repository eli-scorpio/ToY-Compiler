
#include"CacheNode.h"

#include<string.h>

//Initialize List
void initList(List* lp)
{
    lp->head = NULL;
    lp->tail = NULL;
}

struct CacheLinklist* createNode(char * item){

    struct CacheLinklist*  nNode;

    nNode = (struct CacheLinklist* )malloc(sizeof(struct CacheLinklist));

    nNode->data = item;
    nNode->next = NULL;

    return nNode;


}

void addAtHeadCacheNode(List* lp, char* item)
{
    struct CacheLinklist* node;
    node = createNode(item);

    //if list is empty.
    if (lp->head == NULL) {
        lp->head = node;
        lp->tail = node;
    }
    else {
        node->next = lp->head;
        lp->head = node;
    }
}

char* acquireHeadOfListCache(List *lp)
{
    char *temp = NULL;
    struct CacheLinklist* node;
    if (lp->head == NULL) {
        //printf("\nEmpty List");
        return temp;
    }
    node = lp->head;

   //printf("The first element of cache list \n");
    temp = node->data;
    //printf("%s",temp);
    return temp;
}

int exsitingInCachenode(List *lp,char *item)
{
    struct CacheLinklist* node;
    node = lp->head;
    while(node !=NULL)
    {
        char *temp = node->data;
        if(strcmp(temp,item)==0)
        {
            return 1;
        }
        node=node->next;
    }
    return 0;
}

int lengthOfCacheNodeForFunctionLengthChecking(List *lp)
{
    struct CacheLinklist *node;
    node = lp->head;
    int count =0;
    while (node != NULL) {
        count+=1;
        node = node->next;
    }
    return count;
}