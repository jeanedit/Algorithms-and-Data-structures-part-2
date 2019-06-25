
/*
Purpose:
   Simple graph implementation
   Universal data sturcture
   Graph is a set of nodes(called vertices) which can be connected.

   This implementation contains Breadth search 

Using:
  Same functions as in the SimpleGraph.cpp
  WeakVertices Line 133
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
  
  Vertex**WeakVertices()
  {
    Vertex**vert_set=new Vertex*[vert_num+1];
    for(int i=0;i<vert_num+1;++i)
      vert_set[i]=NULL;

    Vertex*sm_vert=new Vertex(0);
    int count=0;
    bool weak_vert=true;

  for(int k=0;k<vert_num;++k)
  {
    for(int i=0;i<vert_num;++i)
    {
      for(int j=0;j<vert_num;++j)
      {
        if(IsEdge(i,j)==true&&IsEdge(k,i)==true&&IsEdge(k,j)==true)
        {
          weak_vert=false;
        }  
      }
    }
    if(weak_vert==true&&vertex[k].Hit==false) {
        sm_vert=new Vertex(vertex[k].Value);
        vert_set[count]=sm_vert;
        vertex[k].Hit=true;
        ++count;
    }
    weak_vert=true;
  }
  return vert_set;
  }
  
};

void test1()
{
   SimpleGraph graph(5);
  for(int i=1;i<=5;++i)
    graph.AddVertex(i);

  graph.AddEdge(0,1);
  graph.AddEdge(1,2);
  graph.AddEdge(2,3);
  graph.AddEdge(3,4);
  graph.AddEdge(1,3);

  Vertex**vert=graph.WeakVertices();

   for(int i=0;vert[i]!=NULL;++i)
     printf("Vert:%i\n",vert[i]->Value);
}

void test()
{
  SimpleGraph graph(8);
  for(int i=1;i<=8;++i)
    graph.AddVertex(i);

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

  Vertex**vert=graph.WeakVertices();

   for(int i=0;vert[i]!=NULL;++i)
     printf("Vert:%i\n",vert[i]->Value);
  
  printf("EDge:%i\n",graph.IsEdge(7,4));
}

