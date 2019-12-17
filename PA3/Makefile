#------------------------------------------------------------------------------
# Makefile for CMPS 101-01 Programming Assignment 3
#
#       make                        makes DigraphProperties
#       make DigaphProperties        
#------------------------------------------------------------------------------


DigraphProperties : DigraphProperties.o List.o Digraph.o
	gcc -o DigraphProperties DigraphProperties.o List.o Digraph.o

Digraph.o : Digraph.c Digraph.h
	gcc -c -g -std=c99 -Wall Digraph.c

List.o : List.c List.h
	gcc -c -g -std=c99 -Wall List.c

DigraphProperties.o : DigraphProperties.c Digraph.h List.h
	gcc -c -g -std=c99 -Wall DigraphProperties.c

clean :
	rm -f DigraphProperties Digraph.o DigraphProperties.o List.o
 
