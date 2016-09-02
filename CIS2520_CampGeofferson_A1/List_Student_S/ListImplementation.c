#include "ListInterface.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* some code here (e.g., #include directives, static functions) */

void Initialize (List *L) {
    /* some code here */
    L->size = 0;

    #ifdef DEBUG 
    if (Empty(L) != 1) {
        printf("List must be empty after initialize\n");
        exit(1);
    } else if (Size(L) != 0) {
        printf("List size must be 0 after initialize\n");
        exit(1);
    }
    #endif
}
void Insert (Student X, int position, List *L) {
    int counter;
    int size = L->size;
    Student debugStu;

    #ifdef DEBUG 
        if (position < 0 || position > Size(L) || Full(L) == 1) {
            printf("The position must be 0 or greater and less than the size of the list. The List cannot be full.\n");
            exit(1);
        }
    #endif 

    for (counter = size; counter > position; counter--) {
        L->items[counter] = L->items[counter-1];
    }
    L->items[position] = X;
    L->size = L->size+1;

    Peek(position,L,&debugStu);
    #ifdef DEBUG 
        if (Empty(L) != 0) {
            printf("The list cannot be empty after an insert\n");
            exit(1);
        } else if (Size(L) != size+1 ) {
            printf("Size must increase by one after an insert\n");
            exit(1);
        } else if (strcmp(debugStu.name,L->items[position].name) != 0 || debugStu.grade != L->items[position].grade) {
            printf("A peek in the specified position must return the same student who was just inserted");
            exit(1);
        }
    #endif
}
void Remove (int position, List *L) {
    /* some code here */
    int counter;
    int size = L->size;

    #ifdef DEBUG 
        if (position < 0 || position > Size(L)) {
            printf("The position must be 0 or greater, and less than the size of the list\n");
            exit(1);
        } else if (Empty(L) == 1) {
            printf("The list cannot be empty when removing\n");
            exit(1);
        }
    #endif

    if (size != 0 && position < 0 && position > size-1) {
        
    } else {

        for (counter=position; counter<size; counter++ ) {
            if (counter == size-1) {
               
            } else {
                L->items[counter]=L->items[counter+1];
            }    
        }
        L->size = size - 1;
    }

    #ifdef DEBUG
        if (Size(L) != size - 1) {
            printf("List size must decrease by one after using remove\n");
            exit(1);
        } else if (Full(L) == 1) {
            printf("The list cannot be full after using remove\n");
            exit(1);
        }
    #endif

}
int Full (List *L) {
    if (L->size == 4) {
        return 1;
    } else {
        return 0;
    }

}
int Empty (List *L) {
    if (L->size == 0) {
        return 1; 
    } else {
        return 0;
    }
}
int Size (List *L) {
    return L->size;
}
void Peek (int position, List *L, Item *X) {
     char * tempName;
     #ifdef DEBUG 
        if (position < 0 || position > Size(L)) {
            printf("The position must be 0 or greater, and less than the size of the list\n");
            exit(1);
        } else if (Empty(L) == 1) {
            printf("The list cannot be empty when using peek\n");
            exit(1);
        }
    #endif

   /* if (!Empty(L) && position < L->size && position >-1 ) 
        strcpy(X->name,L->items[position].name);*/
        tempName = NameOfStudent(L->items[position]);
        strcpy(X->name,tempName);
        free(tempName);
        X->grade = L->items[position].grade;
    
}
void Destroy (List *L) {
    int counter;
    int size = L->size;
    for (counter = 0; counter < size; counter++) {
        /*FreeStudent(&L->items[counter]);*/
    }
    free(L);
}
