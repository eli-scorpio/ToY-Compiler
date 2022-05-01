//
// Created by Mingwei Shi on 22/03/2022.
//

#ifndef MAXHEADP_MAX_HEAP_H
#define MAXHEADP_MAX_HEAP_H

#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>

#define INIT_SIZE 100
#define INCREASE_SIZE 10
#define true 1
#define false 0

typedef struct
{
    int* data; //实现一个可以动态扩展容量的堆
    int size;  //堆内元素的个数
    int capacity;

}Maxheap;

void swap(int * a,int *b);
void Init_Maxheap(Maxheap* max_heap);
int Is_Empty(Maxheap max_heap);
void Insert_Maxheap(Maxheap* max_heap,int e);
int Extract_Maxheap(Maxheap* max_heap);

void Print_Maxheap(Maxheap max_heap);
#endif //MAXHEADP_MAX_HEAP_H
