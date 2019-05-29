
/*
Purpose:
   Simple graph implementation
   Universal data sturcture
   Graph is a set of nodes(called vertices) which can be connected.

   This implementation contains Depth search 

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

struct Node //Struct Node for class List with val and pointer on the previous element
{
   Vertex* val;
   Node *prev;
   Node(Vertex* value)
   {
      val = value;
      prev = NULL;
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

class Stack
{
   public:
      List *list;
      int stacksize; //numbers of elements in the stack

      Stack()
      {
         list = new List();
         stacksize = 0;
      }

      int size()
      {
         return stacksize;
      }

  Vertex* pop() //deleting top element from the stack
  {
    if (list->head == NULL)
      return NULL;
    Vertex* value = list->head->val;
    list->head = list->head->prev;
    --stacksize;
    return value;
  }

  void push(Vertex* val) // adding element on  top of the stack
  {
    Node *node = new Node(val);
    if (list->head == NULL)
    {
      list->head = node;
      node->prev = NULL;
    }
    else
    {
      node->prev = list->head;
      list->head = node;
    }
    ++stacksize;
  }

  Vertex* peek() // returning value of the stack's top element
  {
    if (list->head != NULL)
    {
      return list->head->val;
    }
    else
      return NULL;
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

   Vertex** DepthFirstSearch(int VFrom, int VTo) //VFrom index of the first vertex and 
                                                //VTo index of the last vertex perspective                                        
  {
      Vertex**path_arr=new Vertex*[vert_num]; //path from VFrom to VTo
      for(int i=0;i<vert_num;++i)
        path_arr[i]=NULL;
      
      int count=VFrom;
      Stack stack; // Stack which store Vertex* type
      stack.push(new Vertex(vertex[VFrom]));
      vertex[VFrom].Hit=true;
     
      while(stack.size()!=0)
      {
        bool flag=false; //need to check for untouched vertex
        if(IsEdge(count,VTo)) // if we found the last vertex return array of vertices which we need to pass to reach the last vertex
           {
              stack.push(new Vertex(vertex[VTo]));
              int i=stack.size()-1;
              for(;i>=0;--i)
                path_arr[i]=stack.pop();

              break;
           }

        int i=0;

        while(i<vert_num) //looking for an appropriate vertex for the current vertex
        {
          if(IsEdge(count,i)&&vertex[i].Hit==false)
            {
              flag=true;
              vertex[i].Hit=true;
              count=i;
              break;
            }
            ++i;
        }

        if(flag)
          stack.push(new Vertex(vertex[i]));
        else
          stack.pop(); //delete when we don't have any untouched vertex for last hitted vertex
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

void test1()
{
  SimpleGraph graph(5);
  for(int i=1;i<=5;++i)
    graph.AddVertex(i);

  graph.AddEdge(3,2);
  graph.AddEdge(0,4);
  graph.AddEdge(4,2);
  graph.AddEdge(4,3);

  Vertex**test=graph.DepthFirstSearch(0,2);
  for(int i=0;i<3;++i)
    printf("Test:%i\n",test[i]); 

}
