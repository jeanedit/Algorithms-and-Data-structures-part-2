/*
Purpose:

Array representation of a binary tree

Using:

FindKeyIndex Line 42: Finds a node with this key in a binary tree or a node to which we need to add
node with the given key as a right or left child
AddKeyValue: adds new child to the parent
FinMinMax:Finds a biggest or smallest key in a binary tree
DeleteNodebyKey:removes node with this key
Count: Counts number of nodes in a binary tree
WideAllNodes: breadth traversal algorithm(2 implementation)
DeepAllNodes: depth traversal algorithm(in-order,pre-order and post-order)

Programmer:

Kozhin Valeriy Alexandrovich, github.com/jeanedit

Date:

25.04.2019
*/


#include <stdio.h>


//Index of a left child is (2*index+1) and of a right child is (2*index+2)
//Parent's index is (index-1)/2

class aBST
{
public:
	int* Tree; // Array which consists of positive keys
	int ArrSize; //Size of an array

	aBST(int depth)
	{
		ArrSize = ArrSizeCount(depth);
		Tree = new int[ArrSize];
		for (int i = 0; i < ArrSize; i++) Tree[i] = -1;
	}

	int FindKeyIndex(int key) //Finds index of a key in an array or returns -1 if an array doens't have a key
	{
		int i = 0;
		while (i < ArrSize)
		{
			if (key == Tree[i]) return i;
			else if (key < Tree[i]) i = 2 * i + 1;
			else i = 2 * i + 2;
		}
		return -1; 
	}

	int FindFreeCell(int key) //Finds appropriate index for a key or returns -1 if an array doesn't have a free slot
	{
		if (FindKeyIndex(key) != -1) return -1;
	
		int i = 0;

		while (i < ArrSize)
		{
			if (Tree[i] == -1) return i;

			else if (key < Tree[i]) i = 2 * i + 1;

			else i = 2 * i + 2;
		}
		return -1; 
	}

	int AddKey(int key) //Adds a key to the appropriate position 
	{
		int index = FindFreeCell(key);
		if (index == -1) return -1;
		
		Tree[index] = key;
		return -index;
	}

private:

	int ArrSizeCount(int depth) //Counts array's size depending on a tree's depth
	{
		//Expression: ArraySize=(2^depth-1)
		int count = 1;  
		for (int i = 0; i < depth; ++i)
		{
			count = count * 2;
		}
		return count - 1;
	}
};


void test()
{
	aBST*arr_tree = new aBST(3);

	arr_tree->AddKey(50);
	arr_tree->AddKey(75);
	arr_tree->AddKey(25);
	arr_tree->AddKey(37);
	arr_tree->AddKey(84);
	arr_tree->AddKey(62);
	arr_tree->AddKey(92);
	arr_tree->AddKey(55);
	arr_tree->AddKey(43);
	arr_tree->AddKey(31);


	//printf("FindKeyIndex:%i\n", arr_tree->FindKeyIndex(84));

	for(int i=0;i<arr_tree->ArrSize;++i)
	 printf("Tree:%i\tIndex:%i\n", arr_tree->Tree[i],i);

}
