// ----------------------------------------------------------------------------
//  Jongwoo Park
//  jpark510
//  PA4
//  Digraph.c
//  Implementation file for Digraph ADT
// ----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include "List.h"
#include "Digraph.h"

// structs

typedef struct DigraphObj{
	int numVerticies;
	int numEdges;
	List *adjacencyList;
	int *visited;
} DigraphObj;

 /*** Constructors-Destructors ***/  

 // Returns a Digraph that points to a newly created DigraphObj representing a Digraph which has  
 // n vertices and no edges. 
 Digraph newDigraph(int numVerticies){
 	Digraph G = malloc(sizeof(DigraphObj));
 	G->numVerticies = numVerticies;
 	G->numEdges = 0;
 	G->adjacencyList = malloc((numVerticies + 1) * sizeof(List));
 	for(int i = 0; i < (numVerticies + 1); i++){
 		G->adjacencyList[i] = newList();
 	}
  	G->visited = malloc((numVerticies + 1) * sizeof(int));
 	return(G);
 } 

 // Frees all dynamic memory associated with its Digraph* argument, and sets  
 // *pG to NULL.
 void freeDigraph(Digraph* pG){
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
 int getOrder(Digraph G){
 	return(G->numVerticies);
 }

 // Returns the size of G, the number of edges in G. 
 int getSize(Digraph G){
 	return(G->numEdges);
 }

 // Returns the number of outgoing neighbors that vertex u has in G, the number of vertices v such 
 // that (u, v) is an edge in G.  Returns -1 if v is not a legal vertex. 
 int getOutDegree(Digraph G, int u){
  	if(u <= 0 || u > getOrder(G)){
 		return(-1);
 	}	
 	return(length(getNeighbors(G, u)));
 }


 // Returns a list that has all the vertices that are neighbors of u.  There is no input operation  
 // that corresponds to getNeighbors. 
 List getNeighbors(Digraph G, int v){
 	return(G->adjacencyList[v]);
 }


 /*** Manipulation procedures ***/  

 // Adds v to the adjacency list of u and u to the adjacency list of v, if that edge doesn’t  
 // already exist.  If the edge does already exist, does nothing.  Used when edges are entered.  
 // Returns 0 if u and v are legal vertices, otherwise returns -1. 
 int addEdge(Digraph G, int u, int v){
 	Node current;
  	if(v <= 0 || v > getOrder(G) || u <= 0 || u > getOrder(G)){
 		return 1;
 	}	
 	current = getFront(getNeighbors(G, u));

 	while(current != NULL){
 		if(getValue(current) == v){
 			return 1;
 		}
 		if(getValue(current) > v){
			insertBefore(getNeighbors(G, u), current, v);
			break;
		}
 		current = getNextNode(current);
 	}
 	// Add edge from src to dest
 	if(current == NULL){
  		append(getNeighbors(G, u), v);
 	}
	G->numEdges++;
    return 0;
 }

 int deleteEdge(Digraph G, int u, int v){
   	Node current;
   	if(v <= 0 || v > getOrder(G) || u <= 0 || u > getOrder(G)){
 		return 1;
 	}	
 	current = getFront(getNeighbors(G, u));

 	while(current != NULL){
 		if(getValue(current) == v){
 			break;
 		}
 		current = getNextNode(current);
 	}
 	if(current != NULL){
 		deleteNode(getNeighbors(G, u), current);
 		G->numEdges--;
 		return 0;
 	}
 	return 1;
 }


 /*** Other operations ***/ 
 
 // Prints the Digraph G in the same format as an input line, so all that a client need to do is a single 
 // call to PrintDigraph().  But it should not print out an edge twice.  Achieve this by only printing  
 // the edge for {j, k} when j < k.
 void printDigraph(FILE* out, Digraph G){
 	Node current;

 	if(G != NULL && out != NULL){
 		fprintf(out, "%d", getOrder(G));
 		for(int i = 1; i <= getOrder(G); i++){
 			current = getFront(getNeighbors(G, i));
 			while(current != NULL){
 				fprintf(out, ", %d %d", i, getValue(current));
 				current = getNextNode(current);
 			}
 		}
 		fprintf(out, "\n");
 	}
 }  

// Returns the number of Strongly Connected Components in G. 
int getCountSCC(Digraph G){
	List stack = newList();
	Digraph GT;
	Node current;
	int countSCC = 0;

	for(int i = 0; i < G->numVerticies + 1; i++){
 		G->visited[i] = UNVISITED;
 	}

	for(int i = 1; i < G->numVerticies + 1; i++){
		if(G->visited[i] == UNVISITED){
			buildStackRecursive(G, i, stack);
		}
	}

	GT = transposeGraph(G);

	for(int i = 0; i < G->numVerticies + 1; i++){
 		GT->visited[i] = UNVISITED;
 	}	
	current = getFront(stack);
	while(current != NULL){
 		if(GT->visited[getValue(current)] != VISITED){

 			countSCC++;
 			getCountSCCRecursive(GT, getValue(current));
 		}
 		current = getNextNode(current);
 	}
 	freeDigraph(&GT);
 	freeList(&stack);
	return countSCC;

}

 
// Returns the number of vertices (including u) that are in the same Strongly Connected Component 
// as u in G..  Returns -1 if u is not a legal vertex.  
int getNumSCCVertices(Digraph G, int u){
	List stack = newList();
	Digraph GT;
	Node current;
	int found = 0;
	int numSCC = 0;

	for(int i = 0; i < G->numVerticies + 1; i++){
 		G->visited[i] = UNVISITED;
 	}

	for(int i = 1; i < G->numVerticies + 1; i++){
		if(G->visited[i] == UNVISITED){
			buildStackRecursive(G, i, stack);
		}
	}

	GT = transposeGraph(G);

	for(int i = 0; i < G->numVerticies + 1; i++){
 		GT->visited[i] = UNVISITED;
 	}	
	current = getFront(stack);
	while(current != NULL){
 		if(GT->visited[getValue(current)] != VISITED){
 			getNumSCCVerticesRecursive(GT, getValue(current), &numSCC, u, &found);
 			if(found == 1){
 				break;
 			}
 		}
 		numSCC = 0;
 		current = getNextNode(current);
 	}
 	freeDigraph(&GT);
 	freeList(&stack);
	return numSCC;
}

 

// Returns 1 if u and v are in the same Strongly Connected Component of G, and returns 0 if u and v 
// are not in the same Strongly Connected Component of the current digraph.   
// A vertex is always in the same Strongly Connected Component as itself. 
// Returns -1 if u is not a legal vertex. 
int inSameSCC (Digraph G, int u, int v){

	List stack = newList();
	Digraph GT;
	Node current;
	int found = 0;

	if(v <= 0 || v > getOrder(G) || u <= 0 || u > getOrder(G)){
 		return -1;
 	}
 	if(u == v){
 		return 1;
 	}

	for(int i = 0; i < G->numVerticies + 1; i++){
 		G->visited[i] = UNVISITED;
 	}

	for(int i = 1; i < G->numVerticies + 1; i++){
		if(G->visited[i] == UNVISITED){
			buildStackRecursive(G, i, stack);
		}
	}

	GT = transposeGraph(G);

	for(int i = 0; i < G->numVerticies + 1; i++){
 		GT->visited[i] = UNVISITED;
 	}	

	current = getFront(stack);
	while(current != NULL){
 		if(GT->visited[getValue(current)] != VISITED){
 			inSameSCCRecursive(GT, getValue(current), u, v, &found);
 			if(found == 1){
 				break;
 			}
 		}
 		current = getNextNode(current);
 	}
 	freeDigraph(&GT);
 	freeList(&stack);
	return found;
}

void buildStackRecursive(Digraph G, int v, List stack){
	Node current;

	G->visited[v] = VISITED;

 	current = getFront(G->adjacencyList[v]);

 	while(current != NULL){
 		if(G->visited[getValue(current)] != VISITED){
 			buildStackRecursive(G, getValue(current), stack);
 		}
 		current = getNextNode(current);
 	}
 	prepend(stack, v);

}

Digraph transposeGraph(Digraph G){
	Node current;
	Digraph GT = newDigraph(G->numVerticies);

	for(int i = 0; i < G->numVerticies + 1; i++){
		current = getFront(G->adjacencyList[i]); 
		while(current != NULL){
			addEdge(GT, getValue(current), i);
	 		current = getNextNode(current);
	 	}
 	}	
	return GT;
}

void getCountSCCRecursive(Digraph G, int v){
	Node current;

	G->visited[v] = VISITED;

 	current = getFront(G->adjacencyList[v]);

 	while(current != NULL){
 		if(G->visited[getValue(current)] != VISITED){
 			getCountSCCRecursive(G, getValue(current));
 		}
 		current = getNextNode(current);
 	}
}

void getNumSCCVerticesRecursive(Digraph G, int v, int *pnumSCC, int u, int *found){
	Node current;

	G->visited[v] = VISITED;
	(*pnumSCC)++;

	if(u == v){
		*found = 1;
	}
 	current = getFront(G->adjacencyList[v]);

 	while(current != NULL){
 		if(G->visited[getValue(current)] != VISITED){
 			getNumSCCVerticesRecursive(G, getValue(current), pnumSCC, u, found);
 		}
 		current = getNextNode(current);
 	}
}

void inSameSCCRecursive(Digraph G, int x, int u, int v, int *found){
	Node current;

	G->visited[x] = VISITED;

 	current = getFront(G->adjacencyList[x]);

 	while(current != NULL){
 		if(G->visited[getValue(current)] != VISITED){
 			inSameSCCRecursive(G, getValue(current), u, v, found);
 			if( ((x == u) && (getValue(current) == v)) ||
 			    ((getValue(current) == u) && (x == v))  ){
 				*found = 1;
 				return;
 			}
 		}
 		current = getNextNode(current);
 	}
}
