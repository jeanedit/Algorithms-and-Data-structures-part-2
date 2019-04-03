#include <stdio.h>

const int MAX_CHILD = 10; //max number of children

class SimpleTreeNode
{
public:
	int NodeValue; // значение в узле
	SimpleTreeNode* Parent; // родитель или NULL для корня
	SimpleTreeNode* Children[MAX_CHILD]; // список дочерних узлов

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
	SimpleTreeNode * Root; // корень, может быть NULL
	int levels;
	

	SimpleTree(SimpleTreeNode* root)
	{
		Root = root;
		levels = 1;
	}

	void AddChild(SimpleTreeNode* ParentNode, SimpleTreeNode* NewChild)
	{
		if (ParentNode == NULL || NewChild == NULL)  return;

		for (int i=0; i < MAX_CHILD; ++i)
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
					NodeToDelete->Parent->Children[j] = NodeToDelete->Parent->Children[j+1];
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
		NodeRecord(list, Root);
		return list;
	}

	SimpleTreeNode** FindNodesByValue(int val)
	{
		SimpleTreeNode**list = new SimpleTreeNode*[10 * levels];
		count = 0;
		NodeFind(list, Root,val);
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
		NodeRecord(list, Root);
		return count;
	}

	int LeafCount()
	{
		count = 0;
		return LeavesNumber(Root);
	}

	/*int NodeLevel()
	{
		count = 0;
		Levels(Root);
		return count;
	}*/

private:
	int count;

	void NodeRecord(SimpleTreeNode**list,SimpleTreeNode*element)
	{
		
		list[count] = element;
		count++;
		
		if (element == NULL) return;

		for (int j = 0; (element->Children[j])&&(j < MAX_CHILD); ++j)
			NodeRecord(list, element->Children[j]);
		
	}

	void NodeFind(SimpleTreeNode**list, SimpleTreeNode*element,int val)
	{
		
		if (element->NodeValue == val)
		{
			list[count] = element;
			count++;
		}


		if (element == NULL) return;

		for (int j = 0; (element->Children[j]) && (j < MAX_CHILD); ++j)
			 NodeFind(list, element->Children[j], val);
		
	}

	int LeavesNumber(SimpleTreeNode*elem)
	{

		//printf("Elem->Children[0]:%i\n", elem->Children[0]);
		if (elem->Children[0] == NULL) count++;

		for (int i = 0; (elem->Children[i]) && (i < MAX_CHILD); ++i)
			LeavesNumber(elem->Children[i]);
		return count;
	}

	/*int Levels(SimpleTreeNode*elem)
	{

		for (int i = 0;(elem->Children[i])&& i < MAX_CHILD; ++i)
		{
			
		}

		for (int i = 0; (elem->Children[i]) && (i < MAX_CHILD); ++i)
			Levels(elem->Children[i]);
		return count;
	}*/
};



int main()
{
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