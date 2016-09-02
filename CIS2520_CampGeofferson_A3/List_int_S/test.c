/*********************************************************************
 * FILE NAME: myProgram.c
 * PURPOSE: Test program for Student List implementations.
 * AUTHOR: P. Matsakis (CIS2520, Assignment 1)
 * DATE: 21/09/2015
 * NOTES: This program uses test data recorded in a text file
 *        (see test.txt). 
 *********************************************************************/


#include "ListInterface.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
	
void printList (List L) {
    int k;
    for (k=0; k<L.size; k++) {
        printf("%d ",L.items[k]);
    }
}

void copyList (List from, List * into) {
    int k;
    for (k=0; k<from.size; k++) {
        /*printf("in copy for");*/
        Insert(from.items[k],k,into);
    }
}

void sortList (List L, List * toSort, char name[20]) {
    
    clock_t t1;
    clock_t t2;

    copyList(L,toSort);
    if (strcmp(name,"BubbleSort1")==0) {
        t1 = clock();
        BubbleSort1(toSort);
        t2 = clock();
    } else if (strcmp(name,"BubbleSort2")==0) {
        t1 = clock();
        BubbleSort2(toSort);
        t2 = clock();
    } else {
        t1 = clock();
        MergeSort(toSort,0,toSort->size-1);
        t2 = clock();
    }
    printList(*toSort);
    printf(" %s in %lf seconds\n",name,(t2-t1)/(float)CLOCKS_PER_SEC);
}
		   
int main(void) {
	FILE *test;
        char c;
        int counter;

        List L;
        List B1;
        List B2;
        List M;

        counter = 0; 
	
	Initialize(&L);
        Initialize(&B1);
        Initialize(&B2);
        Initialize(&M);
	
	test=fopen("test.txt","r");
	while((c = fgetc(test)) != '\n' && c != '\0' && c != '\r') {
	    /*printf("-%d*",c-'0');*/ 
            Insert(c-'0',counter,&L);
            counter++; 
	}

        printList(L);
        printf(" to sort\n");
/*
        copyList(L,&B1);
        BubbleSort1(&B1);
        printList(B1);
        printf(" BubbleSort1\n");
*/      
        sortList(L,&B1,"BubbleSort1");
        sortList(L,&B2,"BubbleSort2");
        sortList(L,&M,"MergeSort");      
/*
        copyList(L,&B2);
        BubbleSort2(&B2);
        printList(B2);
        printf(" BubbleSort2\n");

        copyList(L,&M);
        MergeSort(&M,M.items[0],M.items[M.size-1]);
        printList(M);
        printf(" MergeSort\n");
*/	
	fclose(test);
	Destroy(&L);
	return EXIT_SUCCESS;
}

