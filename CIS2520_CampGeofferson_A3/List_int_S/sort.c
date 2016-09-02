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
        /*printf("%d",k);*/
        Insert(from.items[k],k,into);
    }
    /*printf("size is: %d\n",from.size);*/
}

void timeParse (float * tot, float * best, float * worst, float t1, float t2) {
    float time;

    time = ((t2-t1)/(float)CLOCKS_PER_SEC);
    *tot = *tot + time;
    if (time > *worst) {
        *worst = time;
    }
    if (time < *best) {
        *best = time;
    }
}
		   
int main(int argc, char * argv[]) {
        int counter;
        int innerCounter;
        int numOfLists;
        int sizeOfLists;
        time_t t;
        clock_t t1;
        clock_t t2;
        List L;
        List B1;
        List B2;
        List M;

        float bubble1Tot;
        float bubble1Best;
        float bubble1Worst;
        float bubble2Tot;
        float bubble2Best;
        float bubble2Worst;
        float mergeTot;
        float mergeBest;
        float mergeWorst;

        bubble1Tot = 0;
        bubble1Best = 1;
        bubble1Worst = 0;
        bubble2Tot = 0;
        bubble2Best = 1;
        bubble2Worst = 0;
        mergeTot = 0;
        mergeBest = 1;
        mergeWorst = 0;

        if (argc != 3) {
            printf("Bad command line paramter count.\n");
            exit(EXIT_FAILURE);
        }
        numOfLists = atoi(argv[1]);
        sizeOfLists = atoi(argv[2]);	
	
        srand((unsigned) time(&t));

	for (counter = 1; counter <= numOfLists; counter++) {
             Initialize(&L);
             Initialize(&B1);
             Initialize(&B2);
             Initialize(&M);
	    
            if (counter == 1) {
                for (innerCounter = 1; innerCounter <= sizeOfLists; innerCounter++) {
                    Insert(innerCounter,innerCounter-1,&L);
                }
            } else if (counter == 2)  {
                for (innerCounter = sizeOfLists; innerCounter > 0; innerCounter--) {
                    Insert(innerCounter,sizeOfLists - innerCounter,&L); 
                }
            } else {
                 for (innerCounter = 0; innerCounter < sizeOfLists; innerCounter++) {
                     Insert(rand()%10,innerCounter,&L);
                 }
            }
            copyList(L,&B1);
            copyList(L,&B2);
            copyList(L,&M);           

            t1 = clock();
            BubbleSort1(&B1);
            t2 = clock();

            timeParse(&bubble1Tot,&bubble1Best,&bubble1Worst,t1,t2);

            t1 = clock();
            BubbleSort2(&B2);
            t2 = clock();

            timeParse(&bubble2Tot,&bubble2Best,&bubble2Worst,t1,t2);

            t1 = clock();
            MergeSort(&M,0,M.size-1);
            t2 = clock();
            
            timeParse(&mergeTot,&mergeBest,&mergeWorst,t1,t2);

            Destroy(&L);
            Destroy(&B1);
            Destroy(&B2);
            Destroy(&M); 
	}

        printf("\nBubbleSort1\n");
        printf("Best:%lf seconds\n",bubble1Best);
        printf("Avg:%lf seconds\n",bubble1Tot/numOfLists);
        printf("Worst:%lf seconds\n",bubble1Worst); 

        printf("\nBubbleSort2\n");
        printf("Best:%lf seconds\n",bubble2Best);
        printf("Avg:%lf seconds\n",bubble2Tot/numOfLists);
        printf("Worst:%lf seconds\n",bubble2Worst); 

        printf("\nMergeSort\n");
        printf("Best:%lf seconds\n",mergeBest);
        printf("Avg:%lf seconds\n",mergeTot/numOfLists);
        printf("Worst:%lf seconds\n\n",mergeWorst);
	
	return EXIT_SUCCESS;
}

