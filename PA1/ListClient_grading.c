//
//  ListClient.c
//  Created by Jayanth Yetukuri on 1/21/19.
//  Email me(jyetukur@ucsc.edu) if you have any concerns on this file
//

#include<stdio.h>
#include<stdlib.h>
#include"List.h"

void publicListClient();
void privateListClient();

int main(int argc, char* argv[]){
    
    publicListClient();
    privateListClient();
    return(0);
}

void publicListClient(){
    List A = newList();
    List A_A = newList();
    List B = newList();
    List C = newList();
    
    int a[]={1,2,3,4,5,6,7,8,9};
    int a_a[]={1,2,3,4,5,6,7,8,9};
    int b[]={8,9,10,11,12,13,14};
    
    int i;
    
    for(i=0; i<9;  i++) append(A, a[i]);
    for(i=0; i<9; i++) append(A_A, a_a[i]);
    for(i=0; i<7;  i++) prepend(B, b[i]);
    
    for(i=0;i<15; i++){
        append(C, i);
        prepend(C, i);
    }
    
    printf("Length of A: %d\n", length(A));
    printf("Front element of A: %d\n", getValue(getFront(A)));
    printf("Second element of A: %d\n", getValue(getNextNode(getFront(A))));
    insertBefore(A, getFront(A), -1);
    insertAfter(A, getFront(A), -2);
    printf("New front element of A: %d\n", frontValue(A));
    
    printf("Length of A: %d\n", length(A));
    printf("Last element of A: %d\n", getValue(getBack(A)));
    printf("Second to last element of A: %d\n", getValue(getPrevNode(getBack(A))));
    insertBefore(A, getBack(A), -3);
    insertAfter(A, getBack(A), -4);
    printf("New Last element of A: %d\n", backValue(A));
    
    printf("Length of A: %d\n", length(A));
    printf("A compared to A: %d\n", equals(A, A));
    printf("A compared to B: %d\n", equals(A, B));
    
    printList(stdout,A);
    
    freeList(&A);
    freeList(&A_A);
    freeList(&B);
    freeList(&C);
}


void privateListClient(){
    List A = newList();
    List A_A = newList();
    List B = newList();
    List C = newList();
    List D = newList();
    
    
    int a[]={-1,2,0,-34,55,-666,7,800,9};
    int a_a[]={1,2,3,4,5,6,7,8,9};
    int b[]={8,9,10,11,12,13,14};
    
    int i;
    
    for(i=0; i<9;  i++) append(A, a[i]);
    for(i=0; i<9; i++) append(A_A, a_a[i]);
    for(i=0; i<7;  i++) prepend(B, b[i]);
    
    for(i=0;i<5; i++){
        append(C, i+2);
        prepend(C, i-3);
        append(C, i-3);
    }
    
    for(i=0;i<7; i++){
        prepend(D, i-3);
        append(D, i-3);
        append(D, i+2);
    }
    
    printf("Length of A: %d\n", length(A));
    printf("Front element of A: %d\n", frontValue(A));
    printf("Back element of A: %d\n", backValue(A));
    append(A, getValue(getFront(A)));
    prepend(A, getValue(getNextNode(getFront(A))));
    append(A, getValue(getFront(A)));
    prepend(A, getValue(getPrevNode(getBack(A))));
    printf("New Front element of A: %d\n", frontValue(A));
    printf("New Back element of A: %d\n", backValue(A));
    
    insertBefore(A, getNextNode(getNextNode(getFront(A))), -111);
    insertBefore(A, getNextNode(getFront(A)), -111);
    insertBefore(A, getNextNode(getNextNode(getNextNode(getFront(A)))), -111);
    insertAfter(A, getPrevNode(getBack(A)), -222);
    insertAfter(A, getPrevNode(getPrevNode(getBack(A))), -222);
    printf("Length of A: %d\n", length(A));
    
    deleteFront(A);
    deleteBack(A);
    deleteFront(A);
    printf("New Front element of A: %d\n", frontValue(A));
    
    deleteBack(A);
    deleteFront(A);
    deleteBack(A);
    deleteBack(A);
    printf("New Back element of A: %d\n", backValue(A));
    
    printf("Length of A: %d\n", length(A));
    append(A, 0);
    printf("Front element of A: %d\n", frontValue(A));
    printf("Front element of A: %d\n", getValue(getFront(A)));
    
    prepend(A, 0);
    printf("Back element of A: %d\n", backValue(A));
    printf("Back element of A: %d\n", getValue(getBack(A)));
    
    printf("Second to last element of A: %d\n", getValue(getPrevNode(getBack(A))));
    printf("New Last element of A: %d\n", backValue(A));
    insertBefore(A, getBack(A), -3);
    insertAfter(A, getBack(A), -4);
    printf("New Last element of A: %d\n", backValue(A));
    
    printf("Length of A: %d\n", length(A));
    printf("A compared to A: %d\n", equals(A, A));
    printf("A compared to B: %d\n", equals(A, B));
    
    printList(stdout,A);
    
    freeList(&A);
    freeList(&A_A);
    freeList(&B);
    freeList(&C);
    freeList(&D);
}


//Expected Output:

/*
 
 Length of A: 9
 Front element of A: 1
 Second element of A: 2
 New front element of A: -1
 Length of A: 11
 Last element of A: 9
 Second to last element of A: 8
 New Last element of A: -4
 Length of A: 13
 A compared to A: 1
 A compared to B: 0
 -1 -2 1 2 3 4 5 6 7 8 -3 9 -4
 Length of A: 9
 Front element of A: -1
 Back element of A: 9
 New Front element of A: -1
 New Back element of A: 2
 Length of A: 18
 New Front element of A: 2
 New Back element of A: 9
 Length of A: 11
 Front element of A: -111
 Front element of A: -111
 Back element of A: 0
 Back element of A: 0
 Second to last element of A: 9
 New Last element of A: 0
 New Last element of A: -4
 Length of A: 15
 A compared to A: 1
 A compared to B: 0
 0 -111 -111 -1 2 0 -34 55 -666 7 800 9 -3 0 -4

 */
