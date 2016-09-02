#include "StudentInterface.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* some code here (e.g., #include directives, static functions) */

void InitializeStudent (char *name, int grade, Student *S) {
	/* some code here */
    /*S = malloc(sizeof(Student));*/
    S->name = malloc(sizeof(char)*strlen(name)+1);
    strcpy(S->name,name);
    S->grade = grade;

    #ifdef DEBUG

        if (strcmp(NameOfStudent(*S),name) != 0 || GradeOfStudent(*S) != grade) {
            printf("The correct name and grade of student must be accessible after student initialization\n");
            exit(1);
        }

    #endif

}
char *NameOfStudent (Student S) {
    /*char *name = malloc(sizeof(char)*strlen(S.name)+1);
    strcpy(name,S.name);*/
    /*return name;*/
    return S.name;
}
int GradeOfStudent (Student S) {
    return S.grade;
}
void FreeStudent (Student *S) {
    free(S->name);
    free(S);
}

