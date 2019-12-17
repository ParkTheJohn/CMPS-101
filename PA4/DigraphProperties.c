// ----------------------------------------------------------------------------
//  Jongwoo Park
//  jpark510
//  PA4
//  DigraphProperties.c
//  Reads the first line of the input file, and uses newDigraph() and addEdge() to create a digraph
//  that corresponds to that line and tests functions implemented in Digraph.c
// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"
#include "Digraph.h"

#define MAX_LEN 1500


int main(int argc, char* argv[]){
	
	char line[MAX_LEN];

	int n = -1;
	int i, v, w;
	char* token;
	FILE *in, *out;
	Digraph G = NULL;


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
				G = newDigraph(n);				
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
		if(strcmp(token, "PrintDigraph") == 0) {
			token = strtok(NULL, " \n\r");
			if(token == NULL){
				printDigraph(out, G);
			}else{
				fprintf(out, "ERROR\n");
			}		
		} else if(strcmp(token, "GetOrder") == 0) {
			token = strtok(NULL, " \n\r");
			if(token == NULL){
				fprintf(out, "%d\n", getOrder(G));
			}else{
				fprintf(out, "ERROR\n");
			}
		} else if(strcmp(token, "GetCountSCC") == 0) {
			token = strtok(NULL, " \n\r");
			if(token == NULL){
				fprintf(out, "%d\n", getCountSCC(G));
			}else{
				fprintf(out, "ERROR\n");
			}
		} else if(strcmp(token, "GetNumSCCVertices") == 0) {
			token = strtok(NULL, " \n\r");
			if(token == NULL){
				fprintf(out, "ERROR\n");
			}else{
				n = atoi(token);
				token = strtok(NULL, " \n\r");
				if(token == NULL){
					fprintf(out, "%d\n", getNumSCCVertices(G, n));
				}else{
					fprintf(out, "ERROR\n");
				}
			}
		} else if(strcmp(token, "InSameSCC") == 0) {
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
					token = strtok(NULL, " \n\r");
					if(token == NULL){
						int inSame = inSameSCC(G, v, w);
						if(inSame == 0){
							fprintf(out, "NO\n");
						}else if(inSame == 1){
							fprintf(out, "YES\n");
						}else{
							fprintf(out, "ERROR\n");
						}
					}else{
						fprintf(out, "ERROR\n");
					}
				}		
			}
		} else if(strcmp(token, "GetSize") == 0) {
			
			token = strtok(NULL, " \n\r");
			if(token == NULL){
				fprintf(out, "%d\n", getSize(G));
			}else{
				fprintf(out, "ERROR\n");
			}
		} else if(strcmp(token, "GetOutDegree") == 0) {
			token = strtok(NULL, " \n\r");
			if(token == NULL){
				fprintf(out, "ERROR\n");
			}else{
				n = atoi(token);
				token = strtok(NULL, " \n\r");
				if(token == NULL){
					int outDegree = getOutDegree(G, n);
					if(outDegree < 0){
						fprintf(out, "ERROR\n");
					}else{
						fprintf(out, "%d\n", outDegree);
					}	
				}else{
					fprintf(out, "ERROR\n");
				}
			}
		} else if(strcmp(token, "AddEdge") == 0) {
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
					token = strtok(NULL, " \n\r");
					if(token == NULL){
						fprintf(out, "%d\n", addEdge(G, v, w));
					}else{
						fprintf(out, "ERROR\n");
					}
				}		
			}
		} else if(strcmp(token, "DeleteEdge") == 0) {
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
					token = strtok(NULL, " \n\r");
					if(token == NULL){
						fprintf(out, "%d\n", deleteEdge(G, v, w));
					}else{
						fprintf(out, "ERROR\n");
					}
				}
			}
		} else{
			fprintf(out, "ERROR\n");
		}
	}

	if(G != NULL){
		freeDigraph(&G);
	}
	fclose(in);
	fclose(out);
	
	return 0;
}