#include "TreeInterface.h"
#include "StudentInterface.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int compareValues (void * first, void * second) {
    Student * firstS;
    Student * secondS;
    int firstGrade;
    int secondGrade;

    firstS = (Student*)first;
    secondS = (Student*)second;

    firstGrade = firstS->grade;
    secondGrade = secondS->grade;

    if (firstGrade > secondGrade) {
        return 1;
    } else if (firstGrade == secondGrade) {
        return 0;
    } else {
        return -1;
    }    
}

void destroyValue (void * todestroy) {
    FreeStudent((Student *)todestroy);
}

void * copyValue (void * storage, void * toCopy) {
    Student * toCopyStu;
    Student * storageStu;
  
    toCopyStu = (Student *)toCopy;

    InitializeStudent(toCopyStu->name,toCopyStu->grade,storage);
   
    storageStu = storage;

    return (void *)storage;
}

int main (void) {
    int * grade;
    char s[20];
    FILE * t;
    char balStr[4];
    Student * Stu;
    Tree * T;

    T = malloc(sizeof(Tree));
    Stu = malloc(sizeof(Student));
    grade = malloc(sizeof(int));

    Initialize(T,&copyValue,&destroyValue,&compareValues);
    if (Balanced(T) == 1) {
        strcpy(balStr,"YES");
    } else {
        strcpy(balStr,"NO");
    }
    printf("\nInitialize()\nSize=%d, Height=%d, Balanced=%s\n\n",Size(T),Height(T),balStr);

    t=fopen("test.txt","r");
    while(fscanf(t,"%s %d",s,grade)==2) { 

        InitializeStudent(s,*grade,Stu);

       Insert(T,(void *)Stu);

       if (Balanced(T) == 1) {
            strcpy(balStr,"YES");
        } else {
            strcpy(balStr,"NO");
        } 
        printf("Insert(%s,%d)\nSize=%d,Height=%d,Balanced=%s\n\n",Stu->name,Stu->grade,Size(T),Height(T),balStr);

    }

    Minimum(T,(void *)Stu);
    printf("%s \t %d%%\n",Stu->name,Stu->grade);
    while (Successor(T,(void *)Stu) != 0) {
        printf("%s \t %d%%\n",Stu->name,Stu->grade);

    }

    free(Stu);
    free(grade);
    fclose(t);
    Destroy(T);

    return EXIT_SUCCESS;
}
