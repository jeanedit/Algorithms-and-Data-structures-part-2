
/*
Purpose:

Array representation of a balanced  binary tree

Using:
Functions:
	arr_size Line 25
	log2n    Line 36
	merge_sort Line 42
	merge_procedur Line 90
	BST_creation Line 105
	GenerateBBSTArray Line 118

Programmer:
Kozhin Valeriy Alexandrovich, github.com/jeanedit

Date:
28.04.2019
*/


#include <stdio.h>

//this function counts a number of elements knowing only a depth
int arr_size(int depth)
{
	int count = 1;
	for (int i = 0; i < depth+1; ++i)
		count = 2 * count;

	return count-1;
}

// function that counts a logarithm of n to base 2, it is needed to calculate the depth of a tree 
//knowing only  an array size  
unsigned int log2n(unsigned int n)
{
	return (n > 1) ?1 + log2n(n/2) :0;
}

//MERGE SORT
void merge_sort(int A[], int p, int q, int r) // p is beginning of an array, r is ending and q is the middle 
{
	int n1 = q - p + 1; //size of the left side of an array 
	int n2 = r - q;//size of the right size of an array

	int*L=new int [n1]; //left side
	int*R=new int[n2];//rigth side

	//copying elements to new arrays
	for (int i = 1; i <= n1; ++i)
		L[i - 1] = A[p + i - 1];
	for (int j = 1; j <= n2; ++j)
		R[j - 1] = A[q + j];
	
	int i = 0;
	int j = 0;


	//sortion
	for (int k = p; k <= r; ++k)
	{							
		if (i < n1&&j < n2)
		{
			if (L[i] <= R[j])
			{
				A[k] = L[i];
				++i;
			}
			else {
				A[k] = R[j];
				++j;
			}
		}
		else if (i < n1)
		{
			A[k] = L[i];
			++i;
		}
		else {
			A[k] = R[j];
			++j;
		}
	}
	delete[]L;
	delete[]R;
}

 //merge procedure to sort an array
void merge_procedur(int A[], int p, int r) //p-first index, r-last index
{
	if (p < r)
	{
		int q = (p + r) / 2;
		
		merge_procedur(A, p, q);
		merge_procedur(A, q + 1, r);
		merge_sort(A, p, q, r);
	}
}

//creates an array representation of a binary tree
void BST_creation(int*BST, int a[], int a_len, int Begin, int End, int index)
{
	if (Begin <= End)
	{
		BST[index] = a[(Begin+End)/2]; //Assignment elements to BST from a[]
		BST_creation(BST, a, a_len/2, Begin, (Begin+End)/2-1, 2 * index + 1); //left side of the array a[]
		BST_creation(BST, a, a_len/2,(Begin+End)/2+1,End, 2 * index + 2);//right side of the array a[]
	}
}


// a -- array which consists of keys
// a_len -- array's size
int* GenerateBBSTArray(int a[], int a_len)
{
	//creation of the array BBST with right size
	int*BBST = new int[arr_size(log2n(a_len))];
	
	//sortion of the input array
	merge_procedur(a, 0, a_len-1);
	

	for (int i = 0; i < arr_size(log2n(a_len)); ++i) BBST[i] = -1;

	BST_creation(BBST, a, a_len, 0, a_len - 1, 0);

	return BBST;
}


void test()
{
	const int Size = 1;
	int a[Size];
	//int a[7] = { 5,2,1,55,64,22,72};
	//int a[3] = { 42,70,2 };
	int*b = GenerateBBSTArray(a,Size);
	for (int i = 0; i < arr_size(log2n(Size)); ++i)
		printf("Index:%i\tGenerateBBST:%i\n",i, b[i]);
	//printf("Log2n:%i\n", log2n(1));
}
