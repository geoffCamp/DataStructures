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


#include "QueueInterface.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#define DEBUG


static void copyItem (Item *Y, Item X) {
	InitializeStudent(NameOfStudent(X),GradeOfStudent(X),Y);
}


static void destroyItem (Item *X) {
	FreeStudent(X);
}


#ifdef DEBUG
static int equalItems (Item X, Item Y) {
	/* Why couldn't we write the following?
	   if(strcmp(NameOfStudent(X),NameOfStudent(Y))!=0 ||
	      GradeOfStudent(X)!=GradeOfStudent(Y)) return 0;
	   else return 1; */
	int i;
	char *s;
	s=(char *)malloc(strlen(NameOfStudent(X))+1);
	strcpy(s,NameOfStudent(X));
	i=strcmp(s,NameOfStudent(Y));
	free(s);
	if(i!=0 || GradeOfStudent(X)!=GradeOfStudent(Y)) return 0;
	else return 1;
}
#endif


void Initialize (Queue *Q) {
	Q->size=0;
        Q->head=0;
#ifdef DEBUG
	if(!Empty(Q) || Full(Q) || Size(Q)!=0) {
		printf("Violated postcondition for Initialize!\n");
		exit(EXIT_FAILURE);
	}
#endif
}


void Enqueue (Item I, Queue *Q) {
  	int i;
#ifdef DEBUG
  	Item Y;
	int oldSize=Size(Q);
	if(Full(Q)) {
		printf("Violated precondition for Enqueue!\n");
		exit(EXIT_FAILURE);
	}
#endif
        i = Q->head+(Q->size); 
        if (i > MAXQUEUESIZE-1) {
            i = i-MAXQUEUESIZE;
        }
	copyItem(&Q->items[i],I);
	Q->size++;
#ifdef DEBUG
	Tail(Q,&Y);
	if(Empty(Q) || Size(Q)!=oldSize+1 || !equalItems(I,Y)) {
		printf("Violated postcondition for Enqueue!\n");
		exit(EXIT_FAILURE);
	}
#endif
}


void Dequeue (Queue *Q) {
#ifdef DEBUG
	int oldSize=Size(Q);
	if(Empty(Q)) {
		printf("Violated precondition for Remove!\n");
		exit(EXIT_FAILURE);
	}
#endif
	Q->size--;
	Q->head = Q->head+1;
        if (Q->head > MAXQUEUESIZE-1) {
            Q->head = Q->head-MAXQUEUESIZE;
        }
	destroyItem(&Q->items[Q->size]);
#ifdef DEBUG
	if(Full(Q) || Size(Q)!=oldSize-1) {
		printf("Violated postcondition for Remove!\n");
		exit(EXIT_FAILURE);
	}
#endif
}


int Full (Queue *Q) {
	return Q->size==MAXQUEUESIZE;
}


int Empty (Queue *Q) {
	return Q->size==0;
}


int Size (Queue *Q) {
	return Q->size;
}


void Head (Queue *Q, Item *I) {
#ifdef DEBUG
	if(Empty(Q)) {
		printf("Violated precondition for Head!\n");
		exit(EXIT_FAILURE);
	}
#endif
	copyItem(I,Q->items[Q->head]);
}

void Tail (Queue *Q, Item *I) {
    int newTail;
#ifdef DEBUG
    if (Empty(Q)) {
        printf("Violated precondition for Tail\n");
        exit(EXIT_FAILURE);
    }
#endif
    newTail = Q->head+(Q->size-1);

    if (newTail > MAXQUEUESIZE-1) {
        newTail = newTail - MAXQUEUESIZE;
    }

    copyItem(I,Q->items[newTail]);
}

void Destroy (Queue *Q) {
	int i;
	for(i=0;i<Q->size;i++)
		destroyItem(&Q->items[i]);
}

