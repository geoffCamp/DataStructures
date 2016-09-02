/*********************************************************************
 * FILE NAME: ListImplementation.c
 * PURPOSE: Sequential implementation of the Student List ADT.
 * AUTHOR: P. Matsakis (CIS2520, Assignment 1)
 * DATE: 21/09/2015
 * NOTES: . Some functions are static (they are auxiliary functions
 *          with local scope; they are not visible outside the file).
 *        . Only these static functions will need to be modified
 *          if the type of the list items (here, Student) changes. 
 *        . Only the other functions will need to be modified if
 *          the implementation of the List ADT changes.
 *        . As we will see, there is a better way to check whether
 *          the preconditions and postconditions are met.
 *********************************************************************/


#include "ListInterface.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>


#define DEBUG


static void copyItem (Item *Y, Item X) {
    *Y = X; 
}


static void destroyItem (Item *X) {
	/*FreeStudent(X);*/
}


#ifdef DEBUG
static int equalItems (Item X, Item Y) {
	/* Why couldn't we write the following?
	   if(strcmp(NameOfStudent(X),NameOfStudent(Y))!=0 ||
	      GradeOfStudent(X)!=GradeOfStudent(Y)) return 0;
	   else return 1; */

    if (X == Y) {
        return 1;
    } else {
        return 0;
    } 
   
}
#endif

void BubbleSort1 (List * L) {
    int j;
    int i;
    int holder;

    for (j=1; j<L->size; j++) {
        for (i=1; i<=L->size-j; i++) {
            if (L->items[i-1]>L->items[i]) {
                holder = L->items[i];
                L->items[i] = L->items[i-1];
                L->items[i-1] = holder; 
            }
        }
    }
}

void BubbleSort2 (List * A) {
    int k;
    int i;
    int swapped;
    int holder;

    swapped = 1;

    k = A->size;
    while (swapped == 1) {
        swapped = 0;
        for (i=1; i<k; i++) {
            if (A->items[i-1] > A->items[i]) {
                holder = A->items[i];
                A->items[i] = A->items[i-1];
                A->items[i-1] = holder;
                swapped = 1;
            }
        }
    }
}

void MergeSort (List * A, int first, int last) {
    int middle;

    if (first < last) {
        middle = floor((first+last)/2);
        MergeSort(A,first,middle);
        MergeSort(A,middle+1,last);
        Merge(A,first,middle,last);
    }
}

void Merge (List * A, int first, int middle, int last) {
    int i;
    int j;
    int k;
    int L[10000];
    int R[10000];

    for (i=0; i<=middle-first; i++) {
        L[i] = A->items[first+i];        
    }
    L[middle-first+1]= 9999999;

    for (j=0; j<=last-middle-1; j++) {
        R[j] = A->items[middle+j+1];
    }
    R[last-middle] = 9999999;

    i=0;
    j=0;
    for (k=first; k<=last; k++) {
        if (L[i] <= R[j]) {
            A->items[k]=L[i];
            i = i+1;
        } else {
            A->items[k]=R[j];
            j=j+1;
        }
    } 
}

void Initialize (List *L) {
	L->size=0;
#ifdef DEBUG
	if(!Empty(L) || Full(L) || Size(L)!=0) {
		printf("Violated postcondition for Initialize!\n");
		exit(EXIT_FAILURE);
	}
#endif
}


void Insert (Item X, int position, List *L) {
  	int i;
#ifdef DEBUG
  	Item Y;
	int oldSize=Size(L);
	if(position<0 || position>oldSize || Full(L)) {
		printf("Violated precondition for Insert! %d %d\n",position,oldSize);
		exit(EXIT_FAILURE);
	}
#endif
/*printf("%d-",X);*/
	for (i=L->size; i>position; i--) { 
		/*copyItem(&L->items[i],L->items[i-1]);
		destroyItem(&L->items[i-1]);*/
                L->items[i] = L->items[i-1];
	}
	/*copyItem(&L->items[position],X);*/
        L->items[position] = X;
	L->size++;
#ifdef DEBUG
	Peek(position,L,&Y);
	if(Empty(L) || Size(L)!=oldSize+1 || !equalItems(X,Y)) {
		printf("Violated postcondition for Insert!\n");
		exit(EXIT_FAILURE);
	}
#endif
}


void Remove (int position, List *L) {
	int i;
#ifdef DEBUG
	int oldSize=Size(L);
	if(position<0 || position>=oldSize || Empty(L)) {
		printf("Violated precondition for Remove!\n");
		exit(EXIT_FAILURE);
	}
#endif
	L->size--;
	for (i=position; i<L->size; i++) {
		destroyItem(&L->items[i]);
		copyItem(&L->items[i],L->items[i+1]);
	}
	destroyItem(&L->items[L->size]);
#ifdef DEBUG
	if(Full(L) || Size(L)!=oldSize-1) {
		printf("Violated postcondition for Remove!\n");
		exit(EXIT_FAILURE);
	}
#endif
}


int Full (List *L) {
	return L->size==MAXLISTSIZE;
}


int Empty (List *L) {
	return L->size==0;
}


int Size (List *L) {
	return L->size;
}


void Peek (int position, List *L, Item *X) {
#ifdef DEBUG
	if(position<0 || position>=Size(L) || Empty(L)) {
		printf("Violated precondition for Peek!\n");
		exit(EXIT_FAILURE);
	}
#endif
	copyItem(X,L->items[position]);
}


void Destroy (List *L) {
	int i;
	for(i=0;i<L->size;i++)
		destroyItem(&L->items[i]);
}

