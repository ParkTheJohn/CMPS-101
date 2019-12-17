// ----------------------------------------------------------------------------
//  Jongwoo Park
//  jpark510
//  PA1
//  List.c
//  Implementation file for List ADT
// ----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj{
   int data;
   struct NodeObj* next;
   struct NodeObj* prev;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj{
   Node head;
   Node tail;
   int length;
} ListObj;

// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
// Private.
Node newNode(int node_data){
   Node N = malloc(sizeof(NodeObj));
   N->data = node_data;
   N->next = NULL;
   N->prev = NULL;
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

// newList()
// Returns reference to new empty List object.
List newList(void){
   List L;
   L = malloc(sizeof(ListObj));
   L->length = 0;
   return(L);
}

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
// not done
void freeList(List* pL){
   if(pL!=NULL && *pL!=NULL){
      clear(*pL);
      free(*pL);
      *pL = NULL;
   }
}

// length()
// returns the length of the list L
int length(List L){
    return(L->length);
}

// frontValue()
// returns the head(front) value of the list L
int frontValue(List L){
    if(L->length > 0){
        return(L->head->data);
    }else{
        return 0;
    }
}

// backValue()
// returns the back(tail) value of the list L
int backValue(List L){
    if(L->length > 0){
        return(L->tail->data);
    }else{
        return 0;
    }
}

// getValue()
// returns the value(data) of the node N
int getValue(Node N){
    if(N != NULL){
        return(N->data);
    }else{
        return 0;
    }
}

// equals()
// returns 0 if the list A and B are not equal,
// returns 1 if they are equal
int equals(List A, List B){
    if(A->length != B->length){
    	return 0;
    }else{
    	Node node1 = NULL;
    	Node node2 = NULL;
    	node1 = A->head;
    	node2 = B->head;
    	while(node1 != NULL && node2 != NULL){
    		if(node1->data != node2->data){
    			return 0;
    		}
    		node1 = node1->next;
    		node2 = node2->next;
    	}
    	return 1;
    }
}

// clear()
// deletes all nodes in list L
void clear(List L){
    while(length(L) != 0) {
        deleteFront(L);
    }
}

// getFront()
// returns the front node(head) of the list L
Node getFront(List L){
    if(L->length > 0){
        return(L->head);
    }else{
        return NULL;
    }
}

// getBack()
// returns the back node(tail) of the list L
Node getBack(List L){
    if(L->length > 0){
        return(L->tail);
    }else{
        return NULL;
    }
}

// getPrevNode()
// returns the prev node of node N
Node getPrevNode(Node N){
    if(N == NULL || N->prev == NULL){
        return NULL;
    }else{
        return(N->prev);
    }
}

// getNextNode()
// returns the next node of the node N
Node getNextNode(Node N){
    if(N == NULL || N->next == NULL){
        return NULL;
    }else{
        return(N->next);
    }
}

// prepend()
// attaches a node to the front of the list L with value data
void prepend(List L, int data){
    Node N = newNode(data);
    N->next = L->head;
    if(L->head != NULL){
        L->head->prev = N;
    }
    L->head = N;
    if(L->length == 0){
        L->tail = N;
    }
    L->length++;
    return;
}

// append()
// attaches a node to the back of the list L with value data
void append(List L, int data){
    Node N = newNode(data);
    if(L->length == 0){
        L->head = N;
        L->tail = N;
        N->next = NULL;
        N->prev = NULL;
    }else{
        N->prev = L->tail;
        L->tail->next = N;
        L->tail = N;
    }
    L->length++;
    return;
}

// insertBefore()
// inserts a node with data before node N in list L
void insertBefore(List L, Node N, int data){
    if(N != NULL){
        Node Node = newNode(data);
        if(N == L->head){
        	Node->next = L->head;
        	Node->prev = NULL;
            L->head = Node;
            N->prev = Node;
        }else{
        	Node->next = N;
        	Node->prev = N->prev;
            N->prev->next = Node;
            N->prev = Node;
        }
        L->length++;
    }

}

// insertAfter()
// inserts a node with data after node N in list L
void insertAfter(List L, Node N, int data){
    if(N != NULL){
        Node Node = newNode(data);
        if(N == L->tail){
        	Node->next = NULL;
        	Node->prev = L->tail;
            L->tail = Node;
            N->next = Node;
        }else{
        	Node->prev = N;
        	Node->next = N->next;
            N->next->prev = Node;
            N->next = Node;
        }
        L->length++;
    }
}

// deleteNode()
// deletes node N in list L
void deleteNode(List L, Node N){
    if(N == NULL || L == NULL){
        return;
    }
	if(N == L->head){
		L->head = N->next;
		if(L->head != NULL){
            L->head->prev = NULL;
		}
	}else if(N == L->tail){
		L->tail = N->prev;
		L->tail->next = NULL;
	}else{
		N->prev->next = N->next;
		N->next->prev = N->prev;
	}
    L->length--;
    freeNode(&N);
}

// deleteFront()
// delete the front node in list L
void deleteFront(List L){
    if(L->length != 0){
        deleteNode(L, L->head);
    }
}

// deleteBack()
// delete the back node in list L
void deleteBack(List L){
    if(L->length != 0){
        deleteNode(L, L->tail);
    }
}

// Other operations ---------------------------------------

// printList()
// print all values of the list L in a single line to file out
void printList(FILE* out, List L){
    Node node = getFront(L);
    for(int i = 0; i < L->length; i++){
        if(i > 0){
            fprintf(out, " ");
        }
        fprintf(out, "%d", getValue(node));
        node = getNextNode(node);
    }
    fprintf(out, "\n");
}





