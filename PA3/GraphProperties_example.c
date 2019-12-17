/**
 * Author: Abhishek Alfred Singh
 * Email:  abasingh@ucsc.edu
 */

#include "Graph.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

char *parseVertex(char *buffer, int *numOfVertices);

void parseEdges(char *buf, Graph g);

void getIntsBetween(char *buf, char *tmp, int *u, int *v);

char *getNumber(const char *buffer, int *numOfVertices, char **found);

FILE *openFileOrExitOnFailure(char *filename, char *mode);


int main(int argc, char **argv) {
    Graph g;
    if (argc != 3) {
        exit(EXIT_FAILURE);
    }
    char *infileName = argv[1];
    char *outfileName = argv[2];
    FILE *in = openFileOrExitOnFailure(infileName, "r");
    FILE *out = stdout;//openFileOrExitOnFailure(outfileName, "w");

    int n = 10000; // large graph. You may even allocate 1000000 bytes to read a line. But for PA3, line length will be restricted to 1000 bytes.
    char *buffer = calloc(n, 1);  
    fgets(buffer,n,in); // Alternatively, instead of fgets() you can use getline() on Linux machines only as: char *buffer; int n; getline(&buffer, &n, in);

    // Setup graph data.
    int vcount=0;
    char* restOfTheBuffer = parseVertex(buffer, &vcount);
    g=newGraph(vcount);
    parseEdges(restOfTheBuffer+1,g);

    printGraph(stdout,g);

    // Read next set of lines and perform actions
    while(fgets(buffer,n,in)!=NULL) {
        fprintf(out,"%s",buffer);
    }

    // Free all allocated data.
    fclose(in);
    freeGraph(&g);
    free(g);
    free(buffer);
    return 0;
}

FILE *openFileOrExitOnFailure(char *filename, char *mode) {
    FILE *in = fopen(filename, mode);
    if (in == NULL) {
        fprintf(stderr, "unable to open file %s\n", filename);
        exit(EXIT_FAILURE);
    }
    return in;
}

void parseEdges(char *buf, Graph g) {
    char* tmp=buf;
    char* start=buf;
    int u,v;
    while (tmp!=NULL) {
        tmp = strchr(start, ',');
        getIntsBetween(start,tmp,&u,&v);
        addEdge(g,u,v);
        start=tmp+1;
    }

}

void getIntsBetween(char *buf, char *tmp, int *u, int *v) {
    while (*buf == ' ')
        buf++;
    char* found = strchr(buf,' ');
    getNumber(buf,u,&found);
    getNumber(found,v,&tmp);
}

char *parseVertex(char *buffer, int *numOfVertices) {
    char* found = strchr(buffer,',');
    return getNumber(buffer, numOfVertices, &found);
}

char *getNumber(const char *buffer, int *numOfVertices, char **found) {
    errno =0;
    *numOfVertices = (int) strtol(buffer, found, 10);
    if (errno == ERANGE) {
        *numOfVertices=-1;
        (*found) =NULL;
        fprintf(stderr,"Error occurred while parsing vertex.");
        exit(EXIT_FAILURE);
    }
    return (*found);
}