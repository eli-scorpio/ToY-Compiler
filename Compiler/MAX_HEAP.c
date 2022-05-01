//
// Created by Mingwei Shi on 22/03/2022.
//

#include "MAX_HEAP.h"

void swap(int * a,int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void Init_Maxheap(Maxheap* max_heap)
{
    max_heap->data = (int*)malloc( INIT_SIZE * sizeof(int) );
    assert(max_heap->data);
    max_heap->size = 0;
    max_heap->capacity = INIT_SIZE;

}

int Is_Empty(Maxheap max_heap)
{
    return max_heap.size == 0 ? true : false;

}

//这里的循环要理解 曾经写错过
void Insert_Maxheap(Maxheap* max_heap,int e)
{
    //先判断数组空间是否够
    if(max_heap->size +1 > INIT_SIZE)
    {
        //注意 realloc写法
        max_heap->data = (int*)realloc(max_heap->data,
                                       (INIT_SIZE + INCREASE_SIZE) *sizeof(int));
        assert(max_heap->data);
        max_heap->capacity += INCREASE_SIZE;
    }

    //不要忘记改变size的值啊，因为就是通过它来访问堆
    max_heap->size ++;
    int j = max_heap->size;
    max_heap->data[j] = e;

    //将插入的元素上移的过程
    //这里是while 而不是if 有索引就要考虑越界。注意这是一个循环上移的过程
    while( j > 1 && max_heap->data[ j/2 ] < max_heap->data[j]) //注意这里不能写e哦，因为循环每一次这个值都是改变的
    {
        swap(&max_heap->data[j/2],&max_heap->data[j]);
        j = j/2;
    }

}


//这里的循环要理解 曾经写错过。注意这是一个循环下移的过程
int Extract_Maxheap(Maxheap* max_heap)
{

    assert(max_heap->size > 0);
    int ret = max_heap->data[1];

    //这里我们让最后一个元素直接赋值到第一个元素，然后size-- 下一次插入元素的时候就直接将其覆盖即可
    max_heap->data[1] = max_heap->data[max_heap->size];  //可以看出来用c来写有点麻烦啊
    max_heap->size --;

    //然后来从上到下调整堆

    //当它没有孩子的时候就不循环了 由于是从上往下的，每一次父节点值会有所变化，其初始值为1
    int k = 1;
    while(k * 2 <= max_heap->size ) //有左孩子就证明有孩子
    {
        //看它是否有右孩子  并比较左右孩子值的大小
        int exchange = 2 * k;
        if(exchange + 1 <= max_heap->size && max_heap->data[exchange+1] > max_heap->data[exchange])
            exchange += 1;

        //这个思考漏掉了
        if(max_heap->data[k] > max_heap->data[exchange])
            break;

        swap(&max_heap->data[k],&max_heap->data[exchange]);

        k = exchange;  //注意这里要更改变化

    }



    return ret;
}


void Print_Maxheap(Maxheap max_heap)
{
    for(int i = 1; i <= max_heap.size;i++)
    {
        //printf("%d ",max_heap.data[i]);
    }
    //printf("\n");
}

