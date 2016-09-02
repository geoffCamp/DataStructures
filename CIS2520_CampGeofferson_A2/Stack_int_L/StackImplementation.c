/*********************************************************************
 * FILE NAME: ListImplementation.c
 * PURPOSE: One-way linked implementation of the Student List ADT.
 * AUTHOR: P. Matsakis (CIS2520, Assignment 1)
 * DATE: 21/09/2015
 * NOTES: . Some functions are static (they are auxiliary functions
 *          with local scope; they are not visible outside the file).
 *        . Only the first two functions will need to be modified
 *          if the type of the list items (here, Student) changes. 
 *        . Only the other functions will need to be modified if
 *          the implementation of the List ADT changes.
 *        . For preconditions and postconditions,
 *          see the sequential implementation (no changes).
 *********************************************************************/

#include <assert.h>
#include "StackInterface.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void Initialize (Stack *S) {
	S->size=0;
	S->first=NULL;
  
        assert(Empty(S));
        assert(Size(S) == 0);   
}


void Push (Item X, Stack *S) {
	ListNode *p, *q;
        int testNum;

	S->size++;
	q=(ListNode *)malloc(sizeof(ListNode));
			 
	q->item = X;
        q->next = NULL;
        /*printf("%d^^%d",q->item,X);*/
        p = S->first;        

        if (p == NULL) {
            S->first = q;
            /*printf("%c from first",S->first->item);*/
        } else {
            while (p->next != NULL) {
                /*printf("|%c in push|",p->item);*/
                p = p->next;

            } 

            p->next = q;
            /*printf("&%d&",p->next->item);*/
       
        }
        Top(S,&testNum);
        assert(Empty(S) == 0);
        assert(Size(S) == S->size);
        assert(testNum == X);
        
}

void Pop (Stack *S) {
        int size;
        ListNode *p, *q;

        size = S->size;

        assert(Empty(S) == 0);
	
        p = S->first;
        q = p;
	while (p->next != NULL) {
            q = p;
            p = p->next;

        }
        /*printf("%d\n",p->item);*/
	
        q->next = NULL;

	free(p);
	S->size = S->size-1;

        assert(Size(S) == size-1);
}


int Full (Stack *S) {
	return 0;
}


int Empty (Stack *S) {
	return S->size==0;
}


int Size (Stack *S) {
	return S->size;
}


void Top (Stack *S, Item *X) {
	ListNode *p, *q;

        assert(Empty(S) == 0);

        p = S->first;
       
	while (p->next != NULL) {
            q = p;
            p = p->next;
        }

/*printf("%d in top. this is p: %d \n",q->item,p->item);*/
      
        *X = p->item;
}


void Destroy (Stack *S) {
	int i;
	ListNode *p, *q;
	
	p=S->first;
	for(i=0;i<S->size;i++) {
		q=p;
		p=p->next;
		free(q);
	}         
}

