// ----------------------------------------------------------------------------
//  Jongwoo Park
//  jpark510
//  PA1
//  List.h
//  Header file for List ADT
// ----------------------------------------------------------------------------

#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

// Exported Type --------------------------------------------------------------
typedef struct ListObj* List;

typedef struct NodeObj* Node;

// Constructors-Destructors ---------------------------------------------------

// newList()
// Returns reference to new empty List object.
List newList(void);

// freeStack()
// Frees all heap memory associated with Stack *pS, and sets *pS to NULL.
void freeList(List* pL);


// Access functions -----------------------------------------------------------

// Returns the number of nodes in this List.
int length(List L);

// Returns the integer in the front Node. // Precondition:  L has at least one Node on it.
int frontValue(List L); 

// Returns the integer in the back Node. 
// Precondition:  L has at least one Node on it.
int backValue(List L); 

// Returns the integer in Node N. // Precondition:  N is not NULL
int getValue(Node N); 

// Returns 1 if if List A and List B are the same integer 
// sequence, otherwise returns 0.
int equals(List A, List B); 

// Manipulation Procedures -----------------------------------

// Resets this List to the empty state.
void clear(List L);  

// If List is non-empty, returns the front Node, without  
// changing the List.  Otherwise, does nothing.
Node getFront(List L);   

// If List is non-empty, returns the back Node, without 
// changing the List.  Otherwise, does nothing.
Node getBack(List L);  

// Without changing the List that N is on, returns the  
// Node that is previous to Node N on its List.  If  
// there is no previous Node, returns NULL.
Node getPrevNode(Node N);  

// Without changing the List that N is on, returns the  
// Node that is next after Node N on its List.  If  
// there is no next Node, returns NULL.
Node getNextNode(Node N);  

// Inserts a new Node into List L before the front 
// Node that has data as its value. If List is empty, 
// makes that new Node the only Node on the list.
void prepend(List L, int data);  

// Inserts a new Node into List L after the back 
// Node that has data as its value. If List is empty, 
// makes that new Node the only Node on the list.
void append(List L, int data);  

// Insert a new Node into Node N’s list 
// before Node N that has data as its value. 
// Assume that Node N is on List L.  If Node N is 
// the front of List L, then N becomes the new front. 
// Precondition:  Node N is not NULL
void insertBefore(List L, Node N, int data);  

// Insert a new Node into Node N’s list  
// after Node N that has data as its value. 
// Assume that Node N is on List L.  If Node N is 
// the back of List L, then N becomes the new back. 
// Precondition:  Node N is not NULL
void insertAfter(List L, Node N, int data);  

// Deletes the front Node in List L.
// Precondition:  L has at least one Node on it.
void deleteFront(List L);  

// Deletes the back Node in List L. 
// Precondition:  L has at least one Node on it.
void deleteBack(List L);  

// Detaches the Node and frees it.
void deleteNode(List L, Node N);

//  Other Operations -------------------------------------------------------

// Prints the values in List L from front to back
// to the file pointed to by out, formatted as a
// space-separated string.
// For those familiar with Java, this is similar
// to toString()in Java.
void printList(FILE* out, List L); 



#endif // LIST_H_INCLUDED
