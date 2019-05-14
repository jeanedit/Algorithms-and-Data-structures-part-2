
/*
Purpose:
   Simple graph implementation
   Universal data sturcture
   Graph is a set of nodes(called vertices) which can be connected.

Using:
  AddVertex Line 45
  RemoveVertex Line 58
  IsEdge Line 74
  AddEdge Line 86
  RemoveEdge Line 96
 
 Programmer: Kozhin Valery Alexandrovich

 Date: May,14 2019
*/




#include<stdio.h>

class Vertex
{
    public:
      int Value;
      Vertex() { Value = 0; }
      Vertex(int val) { Value = val; }
};
  
class SimpleGraph
{
    public:
      Vertex * vertex;
      int ** m_adjacency; //adjacency matrix 
      //The elements of the matrix indicate whether pairs of vertices are adjacent or not in the graph.
      int max_vertex; 
      int vert_num; //current number of vertices
	
      SimpleGraph(int size)
      {
        max_vertex = size;
        m_adjacency = new int*[size];
        for(int i = 0; i < size; i++)
          m_adjacency[i] = new int[size];
        vertex = new Vertex [size];
        vert_num=0;
      }
	
      void AddVertex(int value)
      {
        if(vert_num>max_vertex) return;

        vertex[vert_num]=Vertex(value);

        for(int i=0;i<max_vertex;++i)
          m_adjacency[vert_num][i]=0;

          ++vert_num;
      }

     //v is a vertex index
      void RemoveVertex(int v)
      {
        if(v<0||v>=max_vertex) return;
        vertex[v]=Vertex();

        for(int i=0;i<max_vertex;++i)
            m_adjacency[v][i]=0;
        
        for(int i=0;i<max_vertex;++i)
          m_adjacency[i][v]=0;

        --vert_num;
      }
	
      bool IsEdge(int v1, int v2)
      {
        if(v1<0||v2<0||v1>=max_vertex||v2>=max_vertex) 
        return false;

        if(m_adjacency[v1][v2]==1
        &&m_adjacency[v2][v1]==1) return true;
        else return false;
      }
  
      //v1 and v2 vertices index
      void AddEdge(int v1, int v2)
      {
        if(v1<0||v2<0||v1>=max_vertex||v2>=max_vertex) 
        return;

        m_adjacency[v1][v2]=1;
        m_adjacency[v2][v1]=1;
      }
	
      void RemoveEdge(int v1, int v2)
      {
        if(v1<0||v2<0||v1>=max_vertex||v2>=max_vertex) 
        return;

        m_adjacency[v1][v2]=0;
        m_adjacency[v2][v1]=0;
      }
};

//int main()
void test()
{
  Vertex vertex=Vertex();
  SimpleGraph*graph=new SimpleGraph(5);
  for(int i=1;i<6;++i)
    graph->AddVertex(i);
  
  for(int i=0;i<5;++i)
    printf("Vertices:%i\n",graph->vertex[i]);

  graph->AddEdge(1,4);
  graph->AddEdge(3,2);

  printf("Edge 1-4,4-1:%i\n",graph->IsEdge(1,4),graph->IsEdge(4,1));

  graph->RemoveVertex(4);
  printf("\nAfter RemoveVertex(4):\n");

  printf("Edge 1-4,4-1:%i\t%i\n",graph->IsEdge(1,4),graph->IsEdge(4,1));

  graph->AddVertex(10);
  graph->AddEdge(4,2);
  printf("Edge 4-2:%i\t%i\n",graph->IsEdge(2,4),graph->IsEdge(4,2));
  graph->RemoveEdge(2,4);
  printf("Edge 4-2:%i\t%i\n",graph->IsEdge(2,4),graph->IsEdge(4,2));  
  }      