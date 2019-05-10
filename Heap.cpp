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
    int HeapSz;

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
		
    int GetMax()
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

int main()
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