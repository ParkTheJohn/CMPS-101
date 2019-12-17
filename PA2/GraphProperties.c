// ----------------------------------------------------------------------------
//  Jongwoo Park
//  jpark510
//  PA2
//  GraphProperties.c
//  Reads the first line of the input file, and uses newGraph() and addEdge() to create a graph
//  that corresponds to that line and tests functions implemented in Graph.c
// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"
#include "Graph.h"

#define MAX_LEN 999


int pathExists(Graph G, int u, int v){
	if(G == NULL){
		return 0;
	}
	unvisitAll(G);
	if(PathExistsRecursive(G, u, v) == FOUND){
		return 1;
	}
	return 0;
}


int main(int argc, char* argv[]){
	
	char line[MAX_LEN];

	int n = -1;
	int i, v, w;
	char* token;
	FILE *in, *out;
	Graph G = NULL;

  	// check command line for correct number of arguments
	if( argc != 3 ){
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}

   // open files for reading and writing 
	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");
	if( in==NULL ){
		printf("Unable to open file %s for reading\n", argv[1]);
		exit(1);
	}
	if( out==NULL ){
		printf("Unable to open file %s for writing\n", argv[2]);
		fclose(in);
		exit(1);
	}
	// read first line as input
	if(fgets(line, MAX_LEN, in) == NULL)  {
		fprintf(out, "ERROR\n");
		fclose(in);
		fclose(out);
		exit(1);
	}
	// parsing input line
	token = strtok(line, ",\n\r");
	i = 0;
	while(token != NULL){
		if(i == 0){
			n = atoi(token);
			if(n > 0){
				G = newGraph(n);				
			}
		}else{
			if(G != NULL){
				sscanf(token, "%d %d", &v, &w);
				addEdge(G, v, w);
			}else{
				printf("ERROR: Graph is NULL\n");
				fclose(in);
				fclose(out);
				exit(1);
			}
		}

		token = strtok(NULL, ",\n\r");
		i++;
	}

	// loop for each commands
	while(fgets(line, MAX_LEN, in) != NULL)  {
		token = strtok(line, "\n\r");
		if(token == NULL){
			continue;
		}
		fprintf(out, "%s\n", line);

		token = strtok(line, " ");


		if(strcmp(token, "PrintGraph") == 0) {
			printGraph(out, G);
		} else if(strcmp(token, "GetOrder") == 0) {
			fprintf(out, "%d\n", getOrder(G));
		} else if(strcmp(token, "GetSize") == 0) {
			fprintf(out, "%d\n", getSize(G));
		} else if(strcmp(token, "GetNeighborCount") == 0) {
			token = strtok(NULL, " \n\r");
			if(token == NULL){
				fprintf(out, "ERROR\n");
			}else{
				n = atoi(token);
				fprintf(out, "%d\n", getNeighborCount(G, n));
			}
		} else if(strcmp(token, "PathExists") == 0) {
			token = strtok(NULL, " \n\r");
			if(token == NULL){
				fprintf(out, "ERROR\n");
			}else{
				v = atoi(token);
				token = strtok(NULL, " \n\r");
				if(token == NULL){
					fprintf(out, "ERROR\n");
				}else{
					w = atoi(token);
					if(pathExists(G, v, w) == 0){
						fprintf(out, "NO\n");
					}else{
						fprintf(out, "YES\n");
					}
				}
			}
		}else{
			fprintf(out, "ERROR\n");
		}
	}

	if(G != NULL){
		freeGraph(&G);
	}
	fclose(in);
	fclose(out);
	
	return 0;
}