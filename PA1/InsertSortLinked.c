// ----------------------------------------------------------------------------
//  Jongwoo Park
//  jpark510
//  PA1
//  InsertSortLinked.c
//  Insert sort implementation using linked list ADT
// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#include "List.h"
#define MAX_LEN 160


int main(int argc, char* argv[]){
	char line[MAX_LEN];
	int n;
	char* token;
	FILE *in, *out;
	Node current, next, prev;
	List A = newList();

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

	while( fgets(line, MAX_LEN, in) != NULL)  {
		clear(A);
		token = strtok(line, " \n");

     	 // appending integer to list from file per line
		while( token!=NULL ){
			n = atoi(token);
			append(A, n);
			token = strtok(NULL, " \n");
		}

     	 // sort
		current = getFront(A);
		while(current != NULL){
			prev = getPrevNode(current);
			next = getNextNode(current);
			while(prev != NULL){
				if(getValue(prev) > getValue(current)){
					prev = getPrevNode(prev);
					// Found head of the list to prepend
					if(prev == NULL){
						prepend(A, getValue(current));
						deleteNode(A, current);
					}
				}else{
					// Found lower value of current to insert after
					insertAfter(A, prev, getValue(current));
					deleteNode(A, current);
					break;
				}
			}
			current = next;
		}

      	// print list to output
		printList(out, A);
	}

	fclose(in);
	fclose(out);
	freeList(&A);
	return 0;
}

