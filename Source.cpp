

/*
Purpose:
Implementaton of a binary tree data structure.

A tree whose elements have at most 2 children is called a binary tree. 
Since each element in a binary tree can have only 2 children, we typically name them the left and right child.

Using:

FindNodebyKey: Finds a node with this key in a binary tree or a node to which we need to add
               node with the given key as a right or left child

AddKeyValue: adds new child to the parent

FinMinMax:Finds a biggest or smallest key in a binary tree

DeleteNodebyKey:removes node with this key

Count: Counts number of nodes in a binary tree


Programmer:
Kozhin Valeriy Alexandrovich, github.com/jeanedit

Date:
15.04.2019
*/


#include <stdio.h>


class BSTNode
{
public:

	int NodeKey; // Node's key
	int NodeValue; // Node's value
	BSTNode* Parent; // Parent or NULL for root
	BSTNode* LeftChild;
	BSTNode* RightChild;

	BSTNode(int key, int val, BSTNode* parent)
	{
		NodeKey = key;
		NodeValue = val;
		Parent = parent;
		LeftChild = NULL;
		RightChild = NULL;
	}
};

// transitional search result 
class BSTFind
{
	// NULL if a key didn't find and if a tree has only root
public:
	BSTNode* Node;

	// true if node has found;
	bool NodeHasKey;

	// true, if we should to add new key as a LeftChild 
	bool ToLeft;

	BSTFind() { Node = NULL; }

	~BSTFind()
	{
		delete Node;
	}
};



class BST
{
public:
	BSTNode * Root; // Tree's root or NULL

	BST(BSTNode* node)
	{
		Root = node;
	}

	BSTFind* FindNodeByKey(int key)
	{	
		BSTFind*find = new BSTFind();
		
		find->Node = this->Root;

		while (find->Node != NULL)
		{
			if (find->Node->NodeKey == key)
			{
				find->NodeHasKey = true;
				return find;
			}
			else if (find->Node->NodeKey > key)
			{
				find->ToLeft = true;

				if (find->Node->LeftChild == NULL)
				{
					return find;
				}
				find->Node = find->Node->LeftChild;

			}
			else
			{
				find->ToLeft = false;

				if (find->Node->RightChild == NULL)
				{
					return find;
				}
					find->Node = find->Node->RightChild;
			}
			
		}

		return find;
	}

	bool AddKeyValue(int key, int val)
	{
		BSTFind*find = FindNodeByKey(key);
		BSTNode*node = new BSTNode(key, val, NULL);
		if (find->NodeHasKey == true) return false;
		
		if (find->ToLeft == true)
		{
			find->Node->LeftChild = node;
			find->Node->LeftChild->Parent = find->Node;
			return true;
		}
		
		if (find->ToLeft == false)
		{
			find->Node->RightChild = node;
			find->Node->RightChild->Parent = find->Node;
			return true;
		}

	}

	BSTNode* FinMinMax(BSTNode* FromNode, bool FindMax)
	{
		if (FromNode == NULL) return NULL;

		if (FindMax) //traverse from root to right MAX key
		{
			BSTNode*max = FromNode->RightChild;
			if (max == NULL) return FromNode;
			while (max->RightChild!= NULL)
			{
				max = max->RightChild;
			}
			return max;
		}
		else //traverse from root to LEFT MIN key
		{
			BSTNode*min= FromNode->LeftChild;
			if (min == NULL) return FromNode;
			while (min->LeftChild != NULL)
			{
				min = min->LeftChild;
			}
			return min;
		}
	}

	bool DeleteNodeByKey(int key)
	{
		BSTFind*find = FindNodeByKey(key);

		if (find->NodeHasKey == false) return false;

		//if Node has left and right children we look for the smallest key that greater than given and put it instead of the node
		//which we want to delete
		if (find->Node->LeftChild!=NULL&&find->Node->RightChild != NULL)
		{
			
			BSTNode*node = find->Node->RightChild; 

			while (node->LeftChild!= NULL) // traverse from node to left
			{
				node = node->LeftChild;
			}

			if (node->RightChild != NULL) // if last left child has right child we put it instead of this left child
			{
				node->RightChild->Parent = node->Parent;
				node->Parent->LeftChild = node->RightChild;
			}
			else
				node->Parent->LeftChild = NULL;

			//put  removed node's  children to the node that we put instead of it.
			node->LeftChild = find->Node->LeftChild;
			node->RightChild = find->Node->RightChild;
			node->Parent = find->Node->Parent;
			

			// assignment new node to the removed node's parent
			if (find->Node == Root)
				this->Root = node;
			else
			{
				if (!find->ToLeft)
					find->Node->Parent->RightChild = node;
				else
					find->Node->Parent->LeftChild = node;
			}
			delete find->Node;
			return true;
		}
		else if (find->Node->RightChild != NULL) //if a node has only right child just put right child instead of removed node
		{
			if (find->Node == Root)
				this->Root = find->Node->RightChild;
			else
			{
				if (!find->ToLeft)
					find->Node->Parent->RightChild = find->Node->RightChild;
				else
					find->Node->Parent->LeftChild = find->Node->RightChild;
			}

			find->Node->RightChild->Parent = find->Node->Parent;
			
			delete find->Node;
			return true;
		}

		else if (find->Node->LeftChild != NULL) //if a node has only left child just put left child instead of removed node
		{
			if (find->Node == Root)
				this->Root = find->Node->LeftChild;
			else
			{
				if (!find->ToLeft)
					find->Node->Parent->RightChild = find->Node->LeftChild;
				else
					find->Node->Parent->LeftChild = find->Node->LeftChild;
			}

			find->Node->LeftChild->Parent = find->Node->Parent;

			delete find->Node;
			return true;
		}
		else // if node doesn't have any children just remove this node
		{
			if (!find->ToLeft)
				find->Node->Parent->RightChild = NULL;
			else
				find->Node->Parent->LeftChild = NULL;
		
			delete find->Node;
			
			return true;
		}
	}

	int Count()
	{
		return Nodes(Root); // Number of nodes in a tree
	}


	private:
		int Nodes(BSTNode*node)
		{
			int count = 0;

			if (node == NULL)  return 0;

			count += Nodes(node->RightChild);
			count += Nodes(node->LeftChild);

			++count;

			return count;
		}
};
