
/*
Purpose:

Implementaton of a heap data structure.
a heap is a specialized tree-based data structure 
which is essentially an almost complete tree that satisfies the heap property: 
in a max heap, for any given node C, 
if P is a parent node of C, then the key (the value) of P is greater than or equal to the key of C. 
In a min heap, the key of P is less than or equal to the key of C.
The node at the "top" of the heap (with no parents) is called the root node.

Using:

MakeHeap() Line 49: Creates Heap
GetMax() Line 70: Gets Max element(the first element of the Heap)
Add() Line 91: Adds new element to the Heap and rebuilds it(if it's necessary)

Programmer:
Kozhin Valeriy Alexandrovich, github.com/jeanedit

Date:
10.05.2019
*/


#include <stdio.h>


void swap(int* a, int* b)
{
    int tmp=*b;
    *b=*a;
    *a=tmp;
}

class Heap
{
  public:
    int* HeapArray; // stores non-negative keys
    int HeapSz; //Heap's size

    Heap() 
    { 
        HeapArray = NULL; 
    }
	

    void MakeHeap(int* a, int depth)
    {
        HeapSz=HeapSize(depth);
        HeapArray=new int[HeapSz];

        for(int i=0;i<HeapSz;++i)
            HeapArray[i]=-1;
        
        int i=1;
        HeapArray[0]=a[0];
        
        while(i<HeapSz)
        {
            if(Add(a[i]))
            {
                ++i;
            }
            else return;  
        }
    }
		
    int GetMax() //gets the first element of the HeapArray
    {
        int count=0;
        while(HeapArray[count]>=0&&count<HeapSz)
        {
            count++;
        }
        
        if(count==0) return -1;

        int Max=HeapArray[0];

        swap(&HeapArray[0],&HeapArray[count-1]);

        
        HeapArray[count-1]=-1;
        
        SiftDown(0);
	    return Max; 
    }

    bool Add(int key)
    {
        for(int i=0;i<HeapSz;++i)
        {
            if(HeapArray[i]==-1) 
            {
                HeapArray[i]=key;
                SiftUp(i); 
                return true;
            }
        }
        return false;
    }
  
    private:

        int HeapSize(int depth)
        {
            int Size=1;
            for(int i=0;i<depth+1;++i)
                Size=Size*2;

            return Size-1;
        }


        void SiftDown(int index) 
        {
            while(2*index+1<HeapSz)
            {
              int LeftCh=2*index+1;
              int RightCh=2*index+2;
              int j=LeftCh;

              if(RightCh<HeapSz&&HeapArray[RightCh]>HeapArray[LeftCh])
                j=RightCh;

              if(HeapArray[index]<=HeapArray[j])
                swap(&HeapArray[index],&HeapArray[j]);

                index=j;
            }
        }

        void SiftUp(int index)
        {
            while(HeapArray[index]>HeapArray[(index-1)/2])
            {
                swap(&HeapArray[index],&HeapArray[(index-1)/2]);
                index=(index-1)/2;
            }
        }
};

void test()
{
    int a[15] = {42, 9, 11, 7, 3, 1, 5, 8, 4, 6, 2, 14,21,3,2};

    Heap *heap = new Heap();

    heap->MakeHeap(a, 3);

    for (size_t i = 0; i < heap->HeapSz; i++)
    {
        printf("Heap->Arr:%i\tIndex:%i\t\t2*index+1:%i\t2*index+2:%i\n", heap->HeapArray[i], i, 2 * i + 1, 2 * i + 2);
    }

    printf("Max:%i\n", heap->GetMax());
    for (size_t i = 0; i < heap->HeapSz; i++)
    {
        printf("Heap->Arr:%i\tIndex:%i\t\t2*index+1:%i\t2*index+2:%i\n", heap->HeapArray[i], i, 2 * i + 1, 2 * i + 2);
    }
}
