
/*
Purpose:

Implementation of a balanced binary tree
Tree's building is carrying out through functions ,which I've implemented in the 
private section for an array representation of a balanced binary tree 

Using of a balanced binary tree class:

	CreateFromArray() Line 160
	 
	GenerateTree() Line 172

	bool IsBalanced() Line 177
	
	GenerateBBST() Line 195

	TreeTraversal Line 214


Programmer:
Kozhin Valeriy Alexandrovich, github.com/jeanedit

Date:
03.05.2019
*/


#include <stdio.h>

#define MAX_LEN 100



//this function counts a number of elements knowing only a depth
int arr_size(int depth)
{
	int count = 1;
	for (int i = 0; i < depth + 1; ++i)
		count = 2 * count;

	return count - 1;
}

// function that counts a logarithm of n to base 2, it is needed to calculate the depth of a tree 
//knowing only  an array size  
unsigned int log2n(unsigned int n)
{
	return (n > 1) ? 1 + log2n(n / 2) : 0;
}

//MERGE SORT
void merge_sort(int A[], int p, int q, int r) // p is beginning of an array, r is ending and q is the middle 
{
	int n1 = q - p + 1; //size of the left side of an array 
	int n2 = r - q;//size of the right size of an array

	int*L = new int[n1]; //left side
	int*R = new int[n2];//rigth side

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
		BST[index] = a[(Begin + End) / 2]; //Assignment elements to BST from the a[]
		BST_creation(BST, a, a_len / 2, Begin, (Begin + End) / 2 - 1, 2 * index + 1); //left side of the array a[]
		BST_creation(BST, a, a_len / 2, (Begin + End) / 2 + 1, End, 2 * index + 2);//right side of the array a[]
	}
}


class BSTNode
{
public:
	int      NodeKey;
	BSTNode* Parent; // NULL for root
	BSTNode* LeftChild; 
	BSTNode* RightChild; 	
	int      Level; // node's depth

	BSTNode(int key, BSTNode* parent)
	{
		NodeKey = key;
		Parent = parent;
		LeftChild = NULL;
		RightChild = NULL;
	}
};


class BalancedBST
{
public:
	BSTNode* Root;

	int BSTArray[MAX_LEN]; // temporary array for keys
	int ArrActPart; //is used to highlight necessary part of the BSTArray

	BalancedBST()
	{
		Root = NULL;
	}

	void CreateFromArray(int* a, int a_len) // Creates array representation of a balanced binary tree
	{
		ArrActPart = arr_size(log2n(a_len));

		for (int i = 0; i < ArrActPart; ++i)
			BSTArray[i] = -1;

		merge_procedur(a, 0, a_len - 1);
		
		BST_creation(BSTArray, a, a_len, 0, a_len - 1, 0);
	}

	void GenerateTree() //generates balanced binary tree
	{
		Root = GenerateBBST(Root, 0,1);
	}

	bool IsBalanced(BSTNode* root_node)// if left and right subtrees nodes depth difference is less or equal than 1
		//tree is balanced
	{

		BSTNode*left_subtree=TreeTraversal(root_node->LeftChild);
		BSTNode*right_subtree = TreeTraversal(root_node->RightChild);


		int comp = left_subtree->Level - right_subtree->Level;

		if (comp <= 1 && comp >= -1) return true;

		return false; 
	}

	
private:

	BSTNode* GenerateBBST(BSTNode*node, int index, int level)
	{
		if (index < arr_size(log2n(ArrActPart)))
		{

			if (BSTArray[index] == -1) return NULL;

			BSTNode*curr = new BSTNode(BSTArray[index], node);

			curr->Level = level;

			curr->LeftChild = GenerateBBST(curr, 2 * index + 1, level + 1); //2*index+1 left child's index
			curr->RightChild = GenerateBBST(curr, 2 * index + 2, level + 1);//2*index+2 right child's index
			return curr;
		}
		return NULL;
	}

	//recursive tree's traversal, returns the last node of a tree
	BSTNode*TreeTraversal(BSTNode*node)
	{
		if (node != NULL)
		{
			if (node->LeftChild == NULL && node->RightChild == NULL) return node;

			TreeTraversal(node->LeftChild);
			TreeTraversal(node->RightChild);
		}
	}
};


void test()
{
	BalancedBST*BBST = new BalancedBST();
	int a[19] = {54,7,18,17,16,15,14, 13, 12, 11, 10, 9, 8,6, 5, 4, 3, 2, 1 };
	//int a[4] = { 4,15,10,12};

	BBST->CreateFromArray(a, 19);


	for (int i = 0; i < BBST->ArrActPart; ++i)
		printf("Index:%i\tBBST:%i\n",i,BBST->BSTArray[i]);

	BBST->GenerateTree();
	printf("\nGENE:%i\n\n", BBST->Root->NodeKey);
	
	printf("Balanced:%i\n", BBST->IsBalanced(BBST->Root->RightChild));
}
