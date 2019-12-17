// ----------------------------------------------------------------------------
//  Jongwoo Park
//  jpark510
//  PA2
//  Graph.c
//  Implementation file for Graph ADT
// ----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include "List.h"
#include "Graph.h"

// structs

typedef struct GraphObj{
	int numVerticies;
	int numEdges;
	List *adjacencyList;
	int *visited;
} GraphObj;

 /*** Constructors-Destructors ***/  

 // Returns a Graph that points to a newly created GraphObj representing a graph which has  
 // n vertices and no edges. 
 Graph newGraph(int numVerticies){
 	Graph G = malloc(sizeof(GraphObj));
 	G->numVerticies = numVerticies;
 	G->numEdges = 0;
 	G->adjacencyList = malloc((numVerticies + 1) * sizeof(List));
 	for(int i = 0; i < (numVerticies + 1); i++){
 		G->adjacencyList[i] = newList();
 	}
  	G->visited = malloc((numVerticies + 1) * sizeof(int));
 	return(G);
 } 

 // Frees all dynamic memory associated with its Graph* argument, and sets  
 // *pG to NULL.
 void freeGraph(Graph* pG){
 	if(pG!=NULL && *pG!=NULL){
 		free((*pG)->visited);
 		for(int i = 0; i < ((*pG)->numVerticies + 1); i++){
 			freeList(&((*pG)->adjacencyList[i]));
 		}
 		free((*pG)->adjacencyList);
 		free(*pG);
 		*pG = NULL;
    }
}

 /*** Access functions ***/ 

 // Returns the order of G, the number of vertices in G. 
 int getOrder(Graph G){
 	return(G->numVerticies);
 }

 // Returns the size of G, the number of edges in G. 
 int getSize(Graph G){
 	return(G->numEdges);
 }

 // Returns the number of neighbors that vertex v has in G.  Returns -1 if v is not a legal vertex. 
 int getNeighborCount(Graph G, int v){
 	if(v <= 0 || v > getOrder(G)){
 		return(-1);
 	}
 	return(length(G->adjacencyList[v]));
 }
 // Returns a list that has all the vertices that are neighbors of u.  There is no input operation  
 // that corresponds to getNeighbors. 
 List getNeighbors(Graph G, int v){
 	return(G->adjacencyList[v]);
 }


 /*** Manipulation procedures ***/  

 // Adds v to the adjacency list of u and u to the adjacency list of v, if that edge doesn’t  
 // already exist.  If the edge does already exist, does nothing.  Used when edges are entered.  
 // Returns 0 if u and v are legal vertices, otherwise returns -1. 
 int addEdge(Graph G, int u, int v){
 	Node current;
  	if(v <= 0 || v > getOrder(G) || u <= 0 || u > getOrder(G)){
 		return -1;
 	}	
 	current = getFront(getNeighbors(G, u));

 	while(current != NULL){
 		if(getValue(current) == v){
 			return 0;
 		}
 		current = getNextNode(current);
 	}
 	// Add edge from src to dest
 	append(getNeighbors(G, u), v);
 	// Add edge from dest to src
	append(getNeighbors(G, v), u); 
	G->numEdges++;
    return 0;
 }

 // Marks all vertices of the graph as UNVISITED. 
 void unvisitAll(Graph G){
 	for(int i = 0; i < (G->numVerticies + 1); i++){
 		G->visited[i] = UNVISITED;
 	}
 	return;
 }

 // Returns the mark for vertex u, which will be UNVISITED, INPROGRESS or ALLDONE. 
 int getMark(Graph G, int u){
 	if(u <= 0 || u > getOrder(G)){
 		return NOTFOUND;
 	}
 	return G->visited[u];
 }

 // Sets the mark for vertex u to be theMark. 
 // theMark must be UNVISITED, INPROGRESS or ALLDONE.
 void setMark(Graph G, int u, int theMark){
 	if(u <= 0 || u > getOrder(G)){
 		return;
 	}
 	G->visited[u] = theMark;
 	return;
 }
 
 // Described below; returns FOUND or NOTFOUND, which are (different) constants. 
 int PathExistsRecursive(Graph G, int w, int v){
 	int theMark;
 	int x;
 	int theFoundValue = NOTFOUND;
 	Node current;

 	if(v <= 0 || v > getOrder(G) || w <= 0 || w > getOrder(G)){
 		return NOTFOUND;
 	}

 	if(w == v){
 		return FOUND;
 	}

 	setMark(G, w, INPROGRESS);

 	current = getFront(getNeighbors(G, w));
 	while(current != NULL){
 		x = getValue(current);
		theMark = getMark(G, x);

 		if(theMark == UNVISITED){
 			theFoundValue = PathExistsRecursive(G, x, v);
 		}
 		if(theFoundValue == FOUND){
 			return FOUND;
 		}
 		current = getNextNode(current);
 	}
 	setMark(G, w, ALLDONE);
 	return NOTFOUND;
 }

 /*** Other operations ***/ 
 
 // Prints the Graph G in the same format as an input line, so all that a client need to do is a single 
 // call to PrintGraph().  But it should not print out an edge twice.  Achieve this by only printing  
 // the edge for {j, k} when j < k.
 void printGraph(FILE* out, Graph G){
 	Node current;

 	if(G != NULL && out != NULL){
 		fprintf(out, "%d", getOrder(G));
 		for(int i = 1; i <= getOrder(G); i++){
 			current = getFront(getNeighbors(G, i));
 			while(current != NULL){
 				if(getValue(current) > i){
 					fprintf(out, ", %d %d", i, getValue(current));
 				}
 				current = getNextNode(current);
 			}
 		}
 		fprintf(out, "\n");
 	}
 }  

