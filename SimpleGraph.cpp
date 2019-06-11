
/*
Purpose:
   Simple graph implementation
   Universal data sturcture
   Graph is a set of nodes(called vertices) which can be connected.

   This implementation contains Breadth search 

Using:
  AddVertex Line 45
  RemoveVertex Line 58
  IsEdge Line 74
  AddEdge Line 86
  RemoveEdge Line 96
  DepthFirstSearch Line 190
 Programmer: Kozhin Valery Alexandrovich

 Date: May,29 2019
*/

#include <stdio.h>



class Vertex
{
public:
  int Value;
  bool Hit;
  Vertex() { Value = 0; }
  Vertex(int val) { Value = val; }
};


Vertex**reverse(Vertex**vert,int size)
{
  Vertex**reverse1=new Vertex*[size];
  for(int i=0;i<size;++i)
    reverse1[size]=NULL;
  
  int count=0;
  int i=size-1;
  while(vert[count]!=NULL)
  {
    reverse1[i]=vert[count];
    --i;
    ++count;
  }
  return reverse1;
}

struct Node //Struct Node for class List with val and pointer on the previous element
{
  Vertex* val;
  Node *next;
  Node(Vertex* value)
  {
    val = value;
    next = NULL;
  }
};

class List //Class List with the two pointers: on the head and on the tail;
{
public:
  Node *head;
  Node *tail;
  List()
  {
    head = NULL;
    tail = NULL;
  }
};

class Queue
{
public:
	List*list;
	int queuesize;
	Queue()
	{
		list = new List();
		queuesize = 0;
	}

	void enqueue(Vertex* item)
	{
		Node*node = new Node(item);
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

	Vertex* dequeue()
	{
		Node*node = list->head;
		if (list->head == NULL) return NULL;
		list->head = node->next;
		--queuesize;
		return node->val;
	}

	int size()
	{
		return queuesize;
	}
	void rotate(int N)
	{
		for (int i = 0; i < N; ++i)
		{
			enqueue(dequeue());
		}
	}
};

class SimpleGraph
{
public:
  Vertex *vertex;
  int **m_adjacency; //adjacency matrix
  //The elements of the matrix indicate whether pairs of vertices are adjacent or not in the graph.
  int max_vertex;
  int vert_num; //current number of vertices

  SimpleGraph(int size)
  {
    max_vertex = size;
    m_adjacency = new int *[size];
    for (int i = 0; i < size; i++)
      m_adjacency[i] = new int[size];
    vertex = new Vertex[size];
    vert_num = 0;
  }

  void AddVertex(int value)
  {
    if (vert_num > max_vertex)
      return;

    vertex[vert_num] = Vertex(value);

    for (int i = 0; i < max_vertex; ++i)
      m_adjacency[vert_num][i] = 0;

    ++vert_num;
  }

  //v is a vertex index
  void RemoveVertex(int v)
  {
    if (v < 0 || v >= max_vertex)
      return;
    vertex[v] = Vertex();

    for (int i = 0; i < max_vertex; ++i)
      m_adjacency[v][i] = 0;

    for (int i = 0; i < max_vertex; ++i)
      m_adjacency[i][v] = 0;

    --vert_num;
  }

  bool IsEdge(int v1, int v2)
  {
    if (v1 < 0 || v2 < 0 || v1 >= max_vertex || v2 >= max_vertex)
      return false;

    if (m_adjacency[v1][v2] == 1 && m_adjacency[v2][v1] == 1)
      return true;
    else
      return false;
  }


  //v1 and v2 vertices index
  void AddEdge(int v1, int v2)
  {
    if (v1 < 0 || v2 < 0 || v1 >= max_vertex || v2 >= max_vertex)
      return;

    m_adjacency[v1][v2] = 1;
    m_adjacency[v2][v1] = 1;
  }


  void RemoveEdge(int v1, int v2)
  {
    if (v1 < 0 || v2 < 0 || v1 >= max_vertex || v2 >= max_vertex)
      return;

    m_adjacency[v1][v2] = 0;
    m_adjacency[v2][v1] = 0;
  }

   Vertex** BreadthFirstSearch(int VFrom, int VTo) //VFrom index of the first vertex and 
                                                //VTo index of the last vertex perspective                                        
  {
      Vertex**path_arr=new Vertex*[vert_num]; //path from VFrom to VTo
      for(int i=0;i<vert_num;++i)
        path_arr[i]=NULL;
      
      int pred[vert_num];

      Queue queue;
      int count=0;
      int index=0;
      int sec=VFrom;
      vertex[VFrom].Hit=true;
      queue.enqueue(new Vertex(vertex[VFrom]));

      while(queue.size()!=0)
      {
          count=queue.size();
          if(IsEdge(VTo,sec))
          {
             pred[VTo]=sec;
             sec=VTo;
             Vertex*h_vertex=new Vertex(vertex[sec]);
             count=0;
             while(sec!=VFrom)
             {
               path_arr[count]=h_vertex;
               
               sec=pred[sec];
               h_vertex=new Vertex(vertex[sec]);
               ++count;               
             }
             h_vertex=new Vertex(vertex[VFrom]);
             path_arr[count]=h_vertex;       
            return reverse(path_arr,count+1);
          }
          
          for(int i=0;i<vert_num;++i)
          {
            if(IsEdge(sec,i)&&!vertex[i].Hit)
                {
                  pred[i]=sec;
                  //printf("Pred:%i Index:%i\n",pred[i],vertex[i]);
                  index=i;
                  vertex[i].Hit=true;
                  queue.enqueue(new Vertex(vertex[i]));
                }
          }
          
          sec=index;

          if(queue.size()==count)
          {    
            Vertex*del_elem=queue.dequeue();
            for(int i=0;i<vert_num;++i)
            {
              if(del_elem->Value==vertex[i].Value)
                  sec=i;
            }
             
          }
      }
    return path_arr;
  }
};

// //int main()
// void test()
// {
//   Vertex vertex = Vertex();
//   SimpleGraph *graph = new SimpleGraph(5);
//   for (int i = 1; i < 6; ++i)
//     graph->AddVertex(i);

//   for (int i = 0; i < 5; ++i)
//     printf("Vertices:%i\n", graph->vertex[i]);

//   graph->AddEdge(1, 4);
//   graph->AddEdge(3, 2);

//   printf("Edge 1-4,4-1:%i\n", graph->IsEdge(1, 4), graph->IsEdge(4, 1));

//   graph->RemoveVertex(4);
//   printf("\nAfter RemoveVertex(4):\n");

//   printf("Edge 1-4,4-1:%i\t%i\n", graph->IsEdge(1, 4), graph->IsEdge(4, 1));

//   graph->AddVertex(10);
//   graph->AddEdge(4, 2);
//   printf("Edge 4-2:%i\t%i\n", graph->IsEdge(2, 4), graph->IsEdge(4, 2));
//   graph->RemoveEdge(2, 4);
//   printf("Edge 4-2:%i\t%i\n", graph->IsEdge(2, 4), graph->IsEdge(4, 2));
// }

// void test1()
// {
//   SimpleGraph graph(5);
//   for(int i=1;i<=5;++i)
//     graph.AddVertex(i);

//   graph.AddEdge(3,2);
//   graph.AddEdge(0,4);
//   graph.AddEdge(4,2);
//   graph.AddEdge(4,3);

//   Vertex**test=graph.BreadthFirstSearch(0,2);
//   for(int i=0;i<3;++i)
//     printf("Test:%i\n",test[i]); 
// }

void test()
{
  SimpleGraph graph(8);
  for(int i=1;i<=8;++i)
    graph.AddVertex(2*i*i-i);

  graph.AddEdge(0,1);
  graph.AddEdge(0,3);
  graph.AddEdge(1,2);
  graph.AddEdge(3,7);
  graph.AddEdge(3,4);
  graph.AddEdge(4,6);
  graph.AddEdge(4,5);
  graph.AddEdge(4,7);
  graph.AddEdge(7,6);
  graph.AddEdge(6,5);

  Vertex**kek=graph.BreadthFirstSearch(2,6);
  for(int i=0;kek[i]!=NULL;++i)
    printf("FFFF:%i\n",kek[i]->Value);

  printf("FFFF:%i\n",kek[6]);
}