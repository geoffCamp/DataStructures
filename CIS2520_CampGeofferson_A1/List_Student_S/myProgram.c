#include "ListInterface.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/* some code here (e.g., #include directives, static functions) */

void printList(List * L) {

    Item Stu;
    int counter;    
 
    if (Empty(L) == 1) {
        printf("List is empty; ");
    } else {
        printf("List is not empty; ");
    }
    if (Full(L) == 1) {
        printf("list is full; ");
    } else if (Full(L)==2) {
        printf("");
    } else {
        printf("list is not full; ");
    }
    printf ("list is of size %d:\n",L->size);

    for (counter = 0; counter < L->size; counter++) {
        Peek(counter,L,&Stu);
        printf("%s %d\n",Stu.name,Stu.grade);
    }
    printf("");
}

int main (void) {    

    char lineStr[150];
    char lineStrHolder[150];
    FILE * file;
    char * token;
    int position;
    int grade;
    char name[20];
    Student * Stu;

    List * L;

    /*printf("set variables - path is %s \n",argv[1]);*/

    file = fopen("test.txt","r");
    if (file == NULL) {
        printf("exiting\n");
        exit(1);
    }

    /*printf("opened file path\n");*/

    L = malloc(sizeof(List));
    Initialize(L);

    printList(L);
    while (fgets(lineStr,150,file) != NULL) {
        strcpy(lineStrHolder,lineStr);    

        token = strtok(lineStrHolder," ");

        if (strcmp(lineStrHolder,"\n") == 0) {
            Destroy(L);
            fclose(file);
            exit(1);
        } else if (strcmp(lineStrHolder,"Insert") == 0) {

           token = strtok(NULL," ");
           position = atoi(token);

           token = strtok(NULL," ");
           strcpy(name,token);
           token = strtok(NULL," ");
           grade = atoi(token);

           Stu = malloc(sizeof(Student));

           /*printf("student malloced\n");*/

           InitializeStudent(name,grade,Stu);

           /*printf("student initialized\n");*/

           Insert(*Stu,position,L);

           /*printf("student inserted\n");*/

           printList(L);
           free(Stu);
        } else {

            token = strtok(NULL," ");
            position = atoi(token);
            Remove(position,L);
            printList(L);

        }

    }
    
    fclose(file);
    Destroy(L);    
    
    return EXIT_SUCCESS;
}
