// ----------------------------------------------------------------------------
//  Jongwoo Park
//  jpark510
//  PA3
//  Digraph.h
//  Header file for Graph ADT
// ----------------------------------------------------------------------------

#ifndef DIGRAPH_H_INCLUDED
#define DIGRAPH_H_INCLUDED

#define UNVISITED 0
#define VISITED 1
#define CYCLIC 1
#define ACYCLIC 0
/*
#define ALLDONE 2
#define FOUND 3
#define NOTFOUND 4
*/

// exported type
typedef struct DigraphObj* Digraph;


 /*** Constructors-Destructors ***/  
 Digraph newDigraph(int numVertices);  
 // Returns a Digraph that points to a newly created DigraphObj representing a digraph which has  
 // n vertices and no edges. 

 void freeDigraph(Digraph* pG); 
 // Frees all dynamic memory associated with its Digraph* argument, and sets  
 // *pG to NULL. 

 /*** Access functions ***/ 
 int getOrder(Digraph G);  
 // Returns the order of G, the number of vertices in G. 

 int getSize(Digraph G);  
 // Returns the size of G, the number of edges in G. 

 int getOutDegree(Digraph G, int u);  
 // Returns the number of outgoing neighbors that vertex u has in G, the number of vertices v such 
 // that (u, v) is an edge in G.  Returns -1 if v is not a legal vertex. 

 List getNeighbors(Digraph G, int u);  
 // Returns a list that has all the vertices that are outgoing neighbors of vertex u, i.e.,  
 // a list that has all the vertices v such that (u, v) is an edge in G.  
 // There is no input operation that corresponds to getNeighbors. 

 /*** Manipulation procedures ***/  
 int addEdge(Digraph G, int u, int v);  
 // Adds v to the adjacency list of u, if that edge doesn’t already exist.  
 // If the edge does already exist, does nothing.  Used when edges are entered or added.  
 // Returns 0 if (u, v) is a legal edge, and the edge didn’t already exist. 
 // Returns 1 if (u, v) is a legal edge and the edge did already exist. 
 // Returns -1 if (u, v) is not a legal edge. 

 int deleteEdge(Digraph G, int u, int v);  
 // Deletes v from the adjacency list of u, if that edge exists.  
 // If the edge doesn’t exist, does nothing.  Used when edges are deleted.  
 // Returns 0 if (u, v) is a legal edge, and the edge did already exist. 
 // Returns 1 if (u, v) is a legal edge and the edge didn’t already exist. 
 // Returns -1 if (u, v) is not a legal edge. 
 
 /*** Other operations ***/ 
 void printDigraph(FILE* out, Digraph G);  
 // Outputs the digraph G in the same format as an input line, including the number of vertices 
 // and the edges.  The edges should be in sorted order, as described above. 

 void distance(FILE* out, Digraph G, int u, int v);  
 // Outputs the distance between vertices u and v if there is a directed path between them in the 
 // digraph.  Otherwise, outputs INF 

 int isCyclicRecursve(Digraph G, int v, int *recStack);

 int isCyclic(Digraph G);

 void acyclic(FILE* out, Digraph G);  
 // Outputs YES if the digraph is acyclic.  Otherwise, outputs NO.

 void topoSortRecursive(Digraph G, int v, List stack); 

 void topoSort(FILE* out, Digraph G);  
 // Outputs a topological sort of the digraph.  If the digraph is not acyclic, outputs IMPOSSIBLE. 

 #endif //DIGRAPH_H_INCLUDED