
/*
Purpose:
In computer science, a tree is a widely used abstract data type (ADT)
—or data structure implementing this ADT—that simulates a hierarchical tree structure, 
with a root value and subtrees of children with a parent node, 
represented as a set of linked nodes.

In this cpp file I have implemented simple tree;

Using:

AddChild: adds new child to the parent
DeleteNode: deletes node from tree with with its subtree (if exist)
GetAllNodes: Represents all nodes as an array 
FindNodesByValue: Finds all nodes by value and represents them as an array
MoveNode:Moves node with its subtree to the new parent
Count: Counts number of nodes in the tree
LeafCount: Counts number of leaves(nodes that haven't children) in the tree

Programmer:
Kozhin Valeriy Alexandrovich, github.com/jeanedit

Date:
03.04.2019
*/



#include <stdio.h>

const int MAX_CHILD = 10; //max number of children

class SimpleTreeNode
{
public:
	int NodeValue; // value in node
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
		return list;
	}

	SimpleTreeNode** FindNodesByValue(int val)
	{
		SimpleTreeNode**list = new SimpleTreeNode*[10 * levels];
		count = 0;
		NodeFind(list, Root,val); //in private section
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

private:
	int count;

	void NodeRecord(SimpleTreeNode**list,SimpleTreeNode*element) // recursive function for record elements into the array of TreeNOdes
	{
		
		if (element == NULL) return;

		list[count] = element;
		count++;
		

		for (int j = 0; (element->Children[j])&&(j < MAX_CHILD); ++j)
			NodeRecord(list, element->Children[j]);
		
	}

	void NodeFind(SimpleTreeNode**list, SimpleTreeNode*element,int val) //Recursive function for record appropriate nodes into the array  
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

	int LeavesNumber(SimpleTreeNode*elem) //Recursive function for the computation number of leaves into the tree
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
	SimpleTree*empty_tree = new SimpleTree(NULL);
	SimpleTreeNode**list1 = empty_tree->GetAllNodes();
	SimpleTreeNode**findlist1 = empty_tree->FindNodesByValue(1);
	printf("list1:%i\n", list1[0]);
	printf("list1:%i\n", findlist1[0]);
	printf("empty_tree:%i\n", empty_tree->Count());

	SimpleTree one_el_tree(new SimpleTreeNode(1,NULL));

	printf("one_element_tree:%i\n", one_el_tree.LeafCount());
	SimpleTreeNode**list = one_el_tree.GetAllNodes();
	SimpleTreeNode**findlist = one_el_tree.FindNodesByValue(1);
	printf("list1:%i\n", *list[0]);
	printf("findlist1:%i\n", *findlist[0]);

	SimpleTree tree(new SimpleTreeNode(12, NULL));
	tree.AddChild(tree.Root, new SimpleTreeNode(53, NULL));
	tree.AddChild(tree.Root, new SimpleTreeNode(8, NULL));
	
	tree.AddChild(tree.Root->Children[0], new SimpleTreeNode(2, NULL));
	tree.AddChild(tree.Root->Children[0], new SimpleTreeNode(17, NULL));
	tree.AddChild(tree.Root->Children[0], new SimpleTreeNode(46, NULL));


	tree.AddChild(tree.Root->Children[1], new SimpleTreeNode(23, NULL));
	tree.AddChild(tree.Root->Children[1], new SimpleTreeNode(45, NULL));

	tree.AddChild(tree.Root->Children[0]->Children[0], new SimpleTreeNode(11, NULL));
	tree.AddChild(tree.Root->Children[1]->Children[0], new SimpleTreeNode(12, NULL));
	
	

	printf("VALUE:%i\n", tree.Root->Children[0]->Children[1]->Parent->NodeValue);

	printf("COUNT:%i\n", tree.Count());

	printf("LEAF:%i\n", tree.LeafCount());

	tree.MoveNode(tree.Root->Children[0], tree.Root->Children[1]);
	
	printf("COUNT:%i\n", tree.Count());

	printf("LEAF:%i\n", tree.LeafCount());


	printf("AFTER MOVENODE:%i\n", tree.Root->Children[0]->Children[2]->Parent->NodeValue);

	for (int i = 0; (tree.Root->Children[0]->Children[i])&&i < MAX_CHILD; ++i)
		printf("AFTER MOVENODE:%i\n", tree.Root->Children[0]->Children[i]->NodeValue);

	for (int i = 0; (tree.Root->Children[0]->Children[2]->Children[i]) && i < MAX_CHILD; ++i)
		printf("53 CHILDREN:%i\n", tree.Root->Children[0]->Children[2]->Children[i]->NodeValue);

	printf("2 CHILDREN:%i\n", tree.Root->Children[0]->Children[2]->Children[0]->Children[0]->NodeValue);

	tree.DeleteNode(tree.Root->Children[0]->Children[2]);

	printf("2 CHILDREN:%i\n", tree.Root->Children[0]->Children[0]->NodeValue);

	printf("COUNT:%i\n", tree.Count());

	printf("LEAF:%i\n", tree.LeafCount());

}
