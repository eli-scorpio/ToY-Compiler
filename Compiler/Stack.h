#ifndef STACK_H
#define STACK_H
#include <stdio.h>
#include<string.h>
#include<stdlib.h>

#include <stdlib.h>
#include <string.h>
#include<stdlib.h>
#include<stdio.h>
/**
 * Type for individual stack entry
 */
struct stack_entry{
    char *data;
    struct stack_entry *next;
};

/**
 * Type for stack instance
 */
struct stack_t
{
    struct stack_entry *head;
    size_t stackSize;  // not strictly necessary, but
    // useful for logging
};
struct stack_t *newStack(void);
char *copyString(char *str);
void push(struct stack_t *theStack, char *value);
char *top(struct stack_t *theStack);
// empty 1 ,not 0
int isEmptyStack(struct stack_t *theStack);
void pop(struct stack_t *theStack);
void destroyStack(struct stack_t **theStack);

void clear (struct stack_t *theStack);
#endif