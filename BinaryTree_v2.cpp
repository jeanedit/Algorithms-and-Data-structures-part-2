
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

WideAllNodes: breadth traversal algorithm(2 implementation)

DeepAllNodes: depth traversal algorithm(in-order,pre-order and post-order)

Programmer:
Kozhin Valeriy Alexandrovich, github.com/jeanedit

Date:
21.04.2019
*/


#include <stdio.h>

const int MAX_LIST = 100;





class BSTNode
{
public:

	int NodeKey; // Node's key
	int NodeValue; // Node's value
	BSTNode* Parent; // Parent or NULL for root
	BSTNode* LeftChild;
	BSTNode* RightChild;
	BSTNode*next;
	
	BSTNode(int key, int val, BSTNode* parent)
	{
		NodeKey = key;
		NodeValue = val;
		Parent = parent;
		LeftChild = NULL;
		RightChild = NULL;
		next = NULL; //this pointer will be use inside the queue class
	}
};


//========need Queue to implement Breadth Travers========//
class List
{
public:

	BSTNode*head;
	BSTNode*tail;

	List()
	{
		head = NULL;
		tail = NULL;
	}
};


class Queue
{
public:
	List * list;
	int queuesize;
	Queue()
	{
		list = new List();
		queuesize = 0;
	}

	void enqueue(BSTNode*item)
	{
		BSTNode*node = item;
		if (list->head == NULL)
		{
			list->head = node;
		}
		else
		{
			list->tail->next = node;
		}
		list->tail = node;
		list->tail->next = NULL;
		++queuesize;
	}

	BSTNode*dequeue()
	{
		BSTNode*node = list->head;
		if (list->head == NULL) return NULL;
		list->head = node->next;
		--queuesize;
		return node;
	}

	int size()
	{
		return queuesize;
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
	BSTNode*AllNodes[MAX_LIST];


	BST(BSTNode* node)
	{
		Root = node;
		for (int i = 0; i < MAX_LIST; ++i) AllNodes[i] = NULL;
	}


	//FindOp

	BSTFind* FindNodeByKey(int key)
	{	
		BSTFind*find = new BSTFind();
		
		find->Node = Root;

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


	//AddOp

	bool AddKeyValue(int key, int val)
	{
		BSTFind*find = FindNodeByKey(key);
		BSTNode*node = new BSTNode(key, val, NULL);
		if (Root==NULL)
		{
			Root = node;
			return true;
		}
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


	//FINDMinMax op

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
		else //traverse from root to left MIN key
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

	//==========================================================
	//DeleteOp

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

		else // if a node doesn't have any children just remove this node
		{
			if (!find->ToLeft)
				find->Node->Parent->RightChild = NULL;
			else
				find->Node->Parent->LeftChild = NULL;
		
			delete find->Node;
			
			return true;
		}
	}
	//==========================================================================

	int Count()
	{
		return Nodes(Root); // Number of nodes in a tree
	}


	BSTNode**WideAllNodes_v2() //Implementation without Queue, just adds Root and his children in the array
	{
		ResetList();

		int i = 0;

		AllNodes[i] = Root;

		while (i < Count()&&AllNodes[i]!=NULL)
		{
			if (AllNodes[i]->LeftChild) AddNode(AllNodes[i]->LeftChild);
			
			if(AllNodes[i]->RightChild) AddNode(AllNodes[i]->RightChild);
			++i;
		}
		return AllNodes;
	}

	BSTNode**WideAllNodes() //breadth traversal
	{
		ResetList();

		Queue*queue = new Queue();

		queue->enqueue(Root);

		while(queue->size()!=0)  //handle nodes which removes from Queue
		{
			BSTNode*node = queue->dequeue();
			AddNode(node);
			
			if (node->LeftChild)
				queue->enqueue(node->LeftChild);
			if (node->RightChild)
				queue->enqueue(node->RightChild);
		
		}
		return AllNodes;
	}

	BSTNode**DeepAllNodes(int order) // depth traversal
	{
		ResetList();
		switch (order)
		{
		case 0:  //LeftSubtree-Root->RighSubtree
			InOrder(Root);
			break;
		case 1:
			PostOrder(Root); //Root Last
			break;
		case 2:
			PreOrder(Root); //Root first
			break;
		default:
			return AllNodes;
		}
		return AllNodes;
	}

 private:

	 void ResetList()
	 {
		 int i = 0;
		 while (AllNodes[i] != NULL)
		 {
			 AllNodes[i] = NULL;
			 ++i;
		 }
	 }


	 void AddNode(BSTNode*node)
	 {
		 int i = 0;
		 while (AllNodes[i] != NULL)
		 {
			 ++i;
		 }
		 AllNodes[i] = node;
	 }

	 //LeftSubTree-Root-RightSubTree
	void InOrder(BSTNode*node)
	{
		if (node)
		{
			InOrder(node->LeftChild);

			AddNode(node);

			InOrder(node->RightChild);
		}
	}


	//Root First
	void PreOrder(BSTNode*node)
	{
		if (node)
		{

			AddNode(node);

			PreOrder(node->LeftChild);
			PreOrder(node->RightChild);
		}
	}

	//Root Last
	void PostOrder(BSTNode*node)
	{
		if (node)
		{
			PostOrder(node->LeftChild);
			PostOrder(node->RightChild);
			AddNode(node);
		
		}
	}

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



void test()
{
	BST*bst_tree = new BST(NULL);
	bst_tree->AddKeyValue(12, 12);
	bst_tree->AddKeyValue(10, 10);
	bst_tree->AddKeyValue(11, 11);
	bst_tree->AddKeyValue(9, 9);
	bst_tree->AddKeyValue(6, 6);
	bst_tree->AddKeyValue(8, 8);
	bst_tree->AddKeyValue(15, 15);
	bst_tree->AddKeyValue(20, 20);
	bst_tree->AddKeyValue(17, 17);
	bst_tree->AddKeyValue(7, 7);
	bst_tree->AddKeyValue(14, 14);
	bst_tree->AddKeyValue(3, 3);


	bst_tree->FindNodeByKey(100);

	printf("\nBST_size():%i\n", bst_tree->Count());


	bst_tree->WideAllNodes_v2();
	for(int i=0;i<bst_tree->Count();++i)
		printf("WideAllNode:%i\n", bst_tree->AllNodes[i]->NodeKey);

	printf("\nWideAllNode\n");
	bst_tree->WideAllNodes();
	for (int i = 0; i<bst_tree->Count(); ++i)
		printf("WideAllNode:%i\n", bst_tree->AllNodes[i]->NodeKey);

	printf("\nIn-Order\n");
	bst_tree->DeepAllNodes(0);
	for (int i = 0; i<bst_tree->Count(); ++i)
		printf("DeepAllNode In-Order:%i\n", bst_tree->AllNodes[i]->NodeKey);

	printf("\nPre-Order\n");
	bst_tree->DeepAllNodes(1);
	for (int i = 0; i<bst_tree->Count(); ++i)
		printf("DeepAllNode Pre-Order:%i\n", bst_tree->AllNodes[i]->NodeKey);

	printf("\nPost-Order\n");
	bst_tree->DeepAllNodes(2);
	for (int i = 0; i<bst_tree->Count(); ++i)
		printf("DeepAllNode Post-Order:%i\n", bst_tree->AllNodes[i]->NodeKey);
}
