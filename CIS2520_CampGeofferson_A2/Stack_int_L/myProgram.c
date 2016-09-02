/*********************************************************************
 * FILE NAME: myProgram.c
 * PURPOSE: Test program for Student List implementations.
 * AUTHOR: P. Matsakis (CIS2520, Assignment 1)
 * DATE: 21/09/2015
 * NOTES: This program uses test data recorded in a text file
 *        (see test.txt). 
 *********************************************************************/

#include "StackInterface.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>			   

int main(void) {
	FILE *test;
	int  number;
        char s1[100];
        int counter;
        int * sum1;
        int * sum2;
        int remain;
        char s2[100];
        int tempTotal;
        int carryOver;
        
	Stack S1,S2,S3; 
        sum1 = malloc(sizeof(int));
        sum2 = malloc(sizeof(int));
	
	Initialize(&S1);
        Initialize(&S2);
        Initialize(&S3);
	
	test=fopen("test.txt","r");
        fgets(s1,100,test);
        counter = 0;

        while (s1[counter] !=  '\0') {
           if (s1[counter] == '0') {
               number = 0;
           } else {
               number = s1[counter] - '0';
           }
           /*printf("|%d--%c|",number,s1[counter]);*/
           Push(number,&S1);
           counter++; 

        }

        fgets(s2,100,test);
        counter = 0;

        while (s2[counter] != '\0') {
            if (s2[counter] == '0') {
                number = 0;
            } else {
                number = s2[counter] - '0';
            }
            Push(number,&S2);
            counter++;
        }

        carryOver = 0;

        Pop(&S1);
        Pop(&S2);
/*
        Top(&S1,sum1);
        Top(&S2,sum2);
        printf("%d look here !! %d",*sum1,*sum2);
*/
        while (Size(&S1) > 0 || Size(&S2) > 0) {

            if (Size(&S1) > 0) {
                Top(&S1,sum1);
                /*printf("%d size is: %d\n",*sum1,Size(&S1));*/
                Pop(&S1);
            } else {
                *sum1 = 0;
            }
            if (Size(&S2) > 0) {
                Top(&S2,sum2);
                /*printf("%d-two size is:%d\n",*sum2,Size(&S2));*/
                Pop(&S2);
            } else {
                *sum2 = 0;
            }

            tempTotal = *sum1+*sum2+carryOver;
             
            if (tempTotal >= 10) {
                carryOver = 1;/*((tempTotal+carryOver)/10)*10;*/
            } else {
                carryOver = 0;
            }
            remain = (tempTotal+carryOver) % 10;
            /*printf("%d is total. %d to be pushed. %d is carryOver\n",tempTotal,remain,carryOver);*/

            Push(remain,&S3);
            Top(&S3,sum2);
            /*printf("%d top test should be %d\n",*sum2,remain);*/
        }

        printf("\n");
        while (Size(&S3) >= 1) {
            Top(&S3,sum1);
            printf("%d",*sum1);
            Pop(&S3);
        }
        printf("\n\n");

	fclose(test);

        free(sum1);
        free(sum2);

	Destroy(&S1);
        Destroy(&S2);
        Destroy(&S3);
	return EXIT_SUCCESS;
}

