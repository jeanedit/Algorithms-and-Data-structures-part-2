

// Purpose:
// In computer science, a tree is a widely used abstract data type (ADT)
// —or data structure implementing this ADT—that simulates a hierarchical tree structure, 
// with a root value and subtrees of children with a parent node, 
// represented as a set of linked nodes.
// In this cpp file I have implemented simple tree;

//Also in this implementation was written function that tell us how many edge we need to remove to get forest which consists of even tree.

// Using:

// AddChild: adds new child to the parent
// DeleteNode: deletes node from tree with with its subtree (if exist)
// GetAllNodes: Represents all nodes as an array 
// FindNodesByValue: Finds all nodes by value and represents them as an array
// MoveNode:Moves node with its subtree to the new parent
// Count: Counts number of nodes in the tree
// LeafCount: Counts number of leaves(nodes that haven't children) in the tree
//EvenTree: Finds min forest which consists from even trees

// Programmer:

// Kozhin Valeriy Alexandrovich, github.com/jeanedit

// Date:

// 19.05.2019




#include <stdio.h>

const int MAX_CHILD = 10; //max number of children
const int ArrSize=50; //Size of the array which consists of max number of pairs parent-child 
//that we need to remove to get forest

class SimpleTreeNode
{
public:
	int NodeValue; // Node's Value
	SimpleTreeNode* Parent; // Parent or NULL for Root
	SimpleTreeNode* Children[MAX_CHILD]; // List of children

	SimpleTreeNode(int val, SimpleTreeNode* parent)
	{
		NodeValue = val;
		Parent = parent;
		for (int i = 0; i<MAX_CHILD; i++) Children[i] = NULL;
	}
};

class SimpleTree
{
public:
	SimpleTreeNode * Root; // root, maybe NULL;
	int levels;
	

	SimpleTree(SimpleTreeNode* root)
	{
		Root = root;
		levels = 1;
	}

	void AddChild(SimpleTreeNode* ParentNode, SimpleTreeNode* NewChild)
	{
		if (ParentNode == NULL || NewChild == NULL)  return;

		for (int i=0; i < MAX_CHILD; ++i) //checking for free slots for new child
		{
			if (ParentNode->Children[i] == NULL)
			{
				ParentNode->Children[i] = NewChild;
				if(i==0) levels++;
				NewChild->Parent = ParentNode;
				return;
			}
		}
	}

	void DeleteNode(SimpleTreeNode* NodeToDelete)
	{
		if (NodeToDelete == NULL) return;
		if (NodeToDelete == Root) return;

		for (int i = 0; i < MAX_CHILD; ++i)
		{
			if (NodeToDelete->Parent->Children[i] == NodeToDelete)
			{
				for (int j = i; j < MAX_CHILD; ++j)
				{
					NodeToDelete->Parent->Children[j] = NodeToDelete->Parent->Children[j+1]; //move elements on one slots left
				}
				
				NodeToDelete->Parent->Children[MAX_CHILD - 1] = NULL;
				return;
			}
		}
	}

	SimpleTreeNode** GetAllNodes()
	{
		SimpleTreeNode**list = new SimpleTreeNode* [10 * levels]; 
		count = 0;
		NodeRecord(list, Root); //in private section
		list[count] = NULL;
		return list;
	}

	SimpleTreeNode** FindNodesByValue(int val)
	{
		SimpleTreeNode**list = new SimpleTreeNode*[10 * levels];
		count = 0;
		NodeFind(list, Root,val); //in private section
		list[count] = NULL;
		return list;
	}

	void MoveNode(SimpleTreeNode* OriginalNode, SimpleTreeNode* NewParent)
	{
		SimpleTreeNode*node = OriginalNode;
		DeleteNode(OriginalNode);
		AddChild(NewParent, node);
	}

	int Count()
	{
		SimpleTreeNode**list = new SimpleTreeNode*[10 * levels];
		count = 0;
		NodeRecord(list, Root); //in private section
		return count;
	}

	int LeafCount()
	{
		count = 0;
		return LeavesNumber(Root); //in private section
	}
	
	int LevelCount(SimpleTreeNode*elem)
	{
		int level = 0;
		while (elem != NULL)
		{
			elem = elem->Parent;
			if (elem != NULL) printf("Elem:%i\n", elem->NodeValue);
			++level;
		}
		return level;
	}


 SimpleTreeNode** EvenTrees()
    {
		SimpleTreeNode**nodes=new SimpleTreeNode*[ArrSize];
		for(int i=0;i<ArrSize;++i)
			nodes[i]=NULL;

		EvenFind(nodes,Root);
      	return nodes;
    }



	void EvenFind(SimpleTreeNode**even,SimpleTreeNode*root)
	{
		for(int i=0;(root->Children[i])&&i<MAX_CHILD;++i)
		{
			count=0;
			SbTrNodes(root->Children[i]);
			if(count%2==0) //if number is even add parent and child in the even array
			{
				AddNode(even,root);
				AddNode(even,root->Children[i]);
			} 
			else //else call this function for children of the root
			{
				EvenFind(even,root->Children[i]);
			}
		}
	}


	inline int NodesNum() //returns number of nodes;
	{
		return count;
	}

private:
	int count;

	 void SbTrNodes(SimpleTreeNode*Root) //Number of nodes in the subtree or whole tree
    {
        if(Root==NULL) return;
		++count;
		for(int i=0;i<MAX_CHILD&&Root->Children[i];++i)
			SbTrNodes(Root->Children[i]);
    }

	void AddNode(SimpleTreeNode**arr,SimpleTreeNode* node) //Adds nodes in the array
	{
		for(int i=0;i<ArrSize;++i)
		{
			if(arr[i]==NULL)
			{
				arr[i]=node;
				break;
			}
		}
	}
	void NodeRecord(SimpleTreeNode**list,SimpleTreeNode*element) // recursive function to record elements at the array of TreeNOdes
	{
		
		if (element == NULL) return;

		list[count] = element;
		count++;
		

		for (int j = 0; (element->Children[j])&&(j < MAX_CHILD); ++j)
			NodeRecord(list, element->Children[j]);
		
	}

	void NodeFind(SimpleTreeNode**list, SimpleTreeNode*element,int val) //Recursive function to  record appropriate nodes at the array  
	{
		if (element == NULL) return;

		if (element->NodeValue == val)
		{
			list[count] = element;
			count++;
		}


		

		for (int j = 0; (element->Children[j]) && (j < MAX_CHILD); ++j)
			 NodeFind(list, element->Children[j], val);
		
	}

	int LeavesNumber(SimpleTreeNode*elem) //Recursive function  computes number of leaves at the tree
	{
		if (elem == NULL) return count;
		if (elem->Children[0] == NULL) count++;

		for (int i = 0; (elem->Children[i]) && (i < MAX_CHILD); ++i)
			LeavesNumber(elem->Children[i]);
		return count;
	}
	 
};



void test()
{
    SimpleTree tree(new SimpleTreeNode(1,NULL));
    tree.AddChild(tree.Root,new SimpleTreeNode(2,tree.Root));
    tree.AddChild(tree.Root,new SimpleTreeNode(3,tree.Root));
	tree.AddChild(tree.Root,new SimpleTreeNode(6,tree.Root));

    tree.AddChild(tree.Root->Children[0],
	new SimpleTreeNode(5,tree.Root->Children[0]));
	tree.AddChild(tree.Root->Children[0],
	new SimpleTreeNode(7,tree.Root->Children[0]));
    tree.AddChild(tree.Root->Children[1],
	new SimpleTreeNode(4,NULL));
	tree.AddChild(tree.Root->Children[2],
	new SimpleTreeNode(8,tree.Root->Children[0]));
	tree.AddChild(tree.Root->Children[2]->Children[0],
	new SimpleTreeNode(9,NULL));
	tree.AddChild(tree.Root->Children[2]->Children[0],
	new SimpleTreeNode(10,NULL));
	tree.AddChild(tree.Root->Children[0]->Children[0],
	new SimpleTreeNode(12,NULL));
	tree.AddChild(tree.Root->Children[0]->Children[1],
	new SimpleTreeNode(13,NULL));

	SimpleTreeNode**tr=tree.EvenTrees();
    	printf("Number:%i\n",tr[3]->NodeValue);
}
