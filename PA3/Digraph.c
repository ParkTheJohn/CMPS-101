// ----------------------------------------------------------------------------
//  Jongwoo Park
//  jpark510
//  PA3
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
 	// Add edge from dest to src
	//append(getNeighbors(G, v), u); 
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
 		return 0;
 	}
 	return 1;
 }

/*

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


*/

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


// Outputs the distance between vertices u and v if there is a directed path between them in the 
// digraph.  Otherwise, outputs INF 
void distance(FILE* out, Digraph G, int u, int v){
	Node current;
	List queue;
	int *distance = malloc((G->numVerticies + 1) * sizeof(int));
 	queue = newList();
 	for(int i = 0; i < G->numVerticies + 1; i++){
 		G->visited[i] = UNVISITED;
 		distance[i] = 0;
 	}

 	prepend(queue, u);
 	while(length(queue) > 0){
 		int x = getValue(getFront(queue));
 		//printList(stdout, queue);
 		//printf("length = %d    x = %d\n", length(queue), x);

 		deleteFront(queue);
 		//printf("length = %d\n", length(queue));
 		G->visited[x] = VISITED;
 		current = getFront(G->adjacencyList[x]);

 		while(current != NULL){
 			if(G->visited[getValue(current)] == VISITED){
 				current = getNextNode(current);
 				continue;
 			}


 			distance[getValue(current)] = distance[x] + 1;
 			append(queue, getValue(current));
 			//printf("value = %d\n", getValue(current));
 			G->visited[getValue(current)] = VISITED;
 			if(getValue(current) == v){
 				//printf("sadfasdfasdfsdf\n");
 				fprintf(out, "%d\n", distance[v]);
 				freeList(&queue);
 				free(distance);
 				return;
 			}
 			current = getNextNode(current);
 		}
 		//printList(stdout, queue);
 		//printf("......\n");
 		//sleep(1);
 	}
 	freeList(&queue);
	free(distance);
	fprintf(out, "INF\n");
}


int isCyclicRecursive(Digraph G, int v, int *recStack) {
	Node current; 
    if(G->visited[v] == 0) { 
        // Mark the current node as visited and part of recursion stack 
        G->visited[v] = VISITED; 
        recStack[v] = VISITED; 
  		current = getFront(G->adjacencyList[v]);
        // Recur for all the vertices adjacent to this vertex 
        while(current != NULL){
 			if((G->visited[getValue(current)] == UNVISITED) && (isCyclicRecursive(G, getValue(current), recStack) == VISITED)){
 				return CYCLIC;
 			}else if(recStack[getValue(current)] == VISITED){
 				return CYCLIC;
 			}
 			current = getNextNode(current);
		}

    } 
    recStack[v] = UNVISITED;  // remove the vertex from recursion stack 
    return ACYCLIC;
}
 int isCyclic(Digraph G){
	int *recStack = malloc((G->numVerticies + 1) * sizeof(int));

	for(int i = 0; i < G->numVerticies + 1; i++){
		 G->visited[i] = UNVISITED;
		 recStack[i] = UNVISITED;
	}

	for(int i = 1; i < G->numVerticies + 1; i++){
		if(isCyclicRecursive(G, i, recStack) == CYCLIC){
			free(recStack);
			return CYCLIC;
		}
	}
	free(recStack);
	return ACYCLIC;
 } 

// Outputs YES if the digraph is acyclic.  Otherwise, outputs NO. 
void acyclic(FILE* out, Digraph G){
	if(isCyclic(G) == CYCLIC){
		fprintf(out, "NO\n");
	}else{
		fprintf(out, "YES\n");
	}
}

void topoSortRecursive(Digraph G, int v, List stack){
	Node current;
	G->visited[v] = VISITED;

	current = getFront(G->adjacencyList[v]);

	while(current != NULL){
		if(G->visited[getValue(current)] == UNVISITED){
			topoSortRecursive(G, getValue(current), stack); 
		}
		current = getNextNode(current);
	}

	prepend(stack, v); 
}

// Outputs a topological sort of the digraph.  If the digraph is not acyclic, outputs IMPOSSIBLE. 
void topoSort(FILE* out, Digraph G){
	List stack;

	if(isCyclic(G) == CYCLIC){
		fprintf(out, "IMPOSSIBLE\n");
		return;
	}
	stack = newList();
	for(int i = 0; i < G->numVerticies + 1; i++){
		 G->visited[i] = UNVISITED;
	}

	for(int i = 1; i < G->numVerticies + 1; i++){
		if(G->visited[i] == UNVISITED){
			topoSortRecursive(G, i, stack);
		}
	}
	printList(out, stack);
	freeList(&stack);


}

