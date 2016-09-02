/********************************************
Geofferson Camp - CIS2520 A4
myProgram.c
*********************************************/

#include "HeapInterface.h"
#include "StudentInterface.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void * copyValue (void * storage, void * toCopy) {
    Student * toCopyStu;
    Student * storageStu;

    if (toCopy == NULL || storage == NULL) {
        return NULL;
    }
  
    toCopyStu = (Student *)toCopy;

    InitializeStudent(toCopyStu->name,toCopyStu->grade,storage);
   
    storageStu = storage;

    return (void *)storage;
}

void destroyValue (void * toDestroy) {
    free(toDestroy);
}

int compareValues (void * first, void * second) {
    Student * first2;
    Student * second2;
    int firstGrade;
    int secondGrade;
    int toReturn;

    if (first == NULL || second == NULL) {
        return 2;
    } 

    first2 = (Student *)first;
    second2 = (Student *)second;
 
    firstGrade = first2->grade;
    secondGrade = second2->grade;

    if (firstGrade < secondGrade) {
        toReturn = -1;
    } else if (firstGrade == secondGrade) {
        toReturn = 0;
    } else {
        toReturn = 1;
    }

    return toReturn;
}

void freeStudents(Heap * H) {
    int i;
    Student * S;

    for (i = 1; i<=H->numberOfValues; i++) {
        S=(Student *)H->heap[i];
        FreeStudent(S);
    }
    
}

void printHeap (Heap * H,int numberShown) { 
    int i;
    Student * stu;
    for (i=1; i <= H->numberOfValues; i++) {
        stu = (Student *)H->heap[i];
        printf("%s %d\n",stu->name,stu->grade);
    }
    printf("\n");
}

int main(int argc, char * argv[]) {
    Heap * H;
    char s[20];
    int * grade;
    FILE * t;
    Student * Stu;
    Student Stu2;
    int numberShown;
    int i;

    if (argc != 2) {
        printf("Bad command line paramter count.\n");
        exit(EXIT_FAILURE);
    }
    numberShown = atoi(argv[1]);

    if (numberShown > 20) {
        printf("Input parameter can not be greater than 20.\n");
        exit(EXIT_FAILURE);
    }

    grade = malloc(sizeof(int));
    H = malloc(sizeof(Heap)); 

    Initialize(H,20,&copyValue,&destroyValue,&compareValues);    
  
    t=fopen("test.txt","r");
    while(fscanf(t,"%s %d",s,grade)==2) {
        Stu = malloc(sizeof(Student));
        InitializeStudent(s,*grade,Stu);

        Insert(H,(void *)Stu);       
    }

    fclose(t);
    
    for (i=1; i<=numberShown; i++) {
        Top(H,&Stu2);
        Remove(H);
        printf("%s %d\n",Stu2.name,Stu2.grade);
    } 


    FreeStudent(&Stu2);
    free(grade);
    Destroy(H);

    return EXIT_SUCCESS;
}
