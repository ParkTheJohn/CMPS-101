#------------------------------------------------------------------------------
# Makefile for CMPS 101-01 Programming Assignment 2
#
#       make                        makes GraphProperties
#       make GraphProperties        
#------------------------------------------------------------------------------


GraphProperties : GraphProperties.o List.o Graph.o
	gcc -o GraphProperties GraphProperties.o List.o Graph.o

Graph.o : Graph.c Graph.h
	gcc -c -g -std=c99 -Wall Graph.c

List.o : List.c List.h
	gcc -c -g -std=c99 -Wall List.c

GraphProperties.o : GraphProperties.c Graph.h List.h
	gcc -c -g -std=c99 -Wall GraphProperties.c

clean :
	rm -f GraphProperties Graph.o GraphProperties.o List.o
 
