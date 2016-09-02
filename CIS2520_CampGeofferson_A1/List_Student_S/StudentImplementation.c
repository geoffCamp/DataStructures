#include "StudentInterface.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* some code here (e.g., #include directives, static functions) */

void InitializeStudent (char *name, int grade, Student *S) {
	/* some code here */
    char * tempName;
    strcpy(S->name,name);
    S->grade = grade;
  
    tempName = NameOfStudent(*S);
    #ifdef DEBUG
  
        if (strcmp(tempName,name) != 0 || GradeOfStudent(*S) != grade) {
            printf("The correct name and grade of student must be accessible after student initialization\n");
            exit(1);
        }
  
    #endif 

    free(tempName);
}
char *NameOfStudent (Student S) {
    char *name = malloc(sizeof(char)*20);
    
    strcpy(name,S.name);
    return name;
}
int GradeOfStudent (Student S) {
    return S.grade;
}
void FreeStudent (Student *S) {
    free(S);
}

