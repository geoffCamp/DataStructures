/*********************************************************************
 * FILE NAME: myProgram.c
 * PURPOSE: Test program for Student List implementations.
 * AUTHOR: P. Matsakis (CIS2520, Assignment 1)
 * DATE: 21/09/2015
 * NOTES: This program uses test data recorded in a text file
 *        (see test.txt). 
 *********************************************************************/


#include "QueueInterface.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


static void showListSize (Queue *Q) {
	if(Empty(Q)) printf("queue is empty; ");
	else printf("queue is not empty; ");
	if(Full(Q)) printf("queue is full; ");
	else printf("queue is not full; ");
	printf("queue is of size %d:\n",Size(Q));
}
	
	
static void showListContent (Queue *Q) {
	int i;
	Student S; 

        for (i=0;i<Size(Q);i++) {
            Head(Q,&S);
            Dequeue(Q);
            Enqueue(S,Q);
            printf("\t%s %d%%\n",NameOfStudent(S),GradeOfStudent(S));
            FreeStudent(&S);
        }

}
			   

int main(void) {
	FILE *test;
	char s[20];
	int grade;
	
	Student S;
	Queue Q; 
	
	Initialize(&Q);
	showListSize(&Q);
	showListContent(&Q);
	
	test=fopen("test.txt","r");
	while(fscanf(test,"%s",s)==1) {
/*printf("in main loop\n");*/
		if(strcmp(s,"Enqueue")==0) {
			fscanf(test,"%s %d",s,&grade);
			InitializeStudent(s,grade,&S);
			Enqueue(S,&Q);
			FreeStudent(&S);
		}
		if(strcmp(s,"Dequeue")==0)
			Dequeue(&Q);
		showListSize(&Q);
		showListContent(&Q);
	}
	
	fclose(test);
	Destroy(&Q);
	return EXIT_SUCCESS;
}

