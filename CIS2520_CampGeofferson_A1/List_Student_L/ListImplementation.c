#include "ListInterface.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
/* some code here (e.g., #include directives, static functions) */

void Initialize (List *L) {
    L->size = 0;
    L->first = NULL;

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
    int size;
    ListNode * new;
    ListNode * active;
    ListNode * holder;
    Student debugStu;

     #ifdef DEBUG 
        if (position < 0 || position > Size(L)) {
            printf("The position must be 0 or greater and less than the size of the list\n");
            exit(1);
        }
    #endif

    new = malloc(sizeof(ListNode));
    new->item = X;
    new->next = NULL;   
    active = L->first;
    size = L->size;

    if (L->first == NULL) {
        L->first = new;
        /*printf("first set %s \n",new->item.name);*/ 
    } else if (position == 0) { 
        holder = L->first;
        L->first = new;
        new->next = holder;
    
    } else {
        for (counter = 0; counter < position-1; counter++) {
            /*printf("%s\n",active->item.name);*/
            active = active->next;
        }       
        /*printf("for loop done about to set holder active is: %s\n",active->item.name);*/ 
        holder = active->next;
        
        active->next = new;
       
        new->next = holder;
    }
    
    L->size = L->size+1;

    Peek(position,L,&debugStu);
    #ifdef DEBUG 
        if (Empty(L) != 0) {
            printf("The list cannot be empty after an insert\n");
            exit(1);
        } else if (Size(L) != size+1 ) {
            printf("Size must increase by one after an insert\n");
            exit(1);
        } else if (strcmp(debugStu.name,new->item.name) != 0 || debugStu.grade != new->item.grade) {
            printf("A peek in the specified position must return the same student who was just inserted");
            exit(1);
        }
    #endif
    
}
void Remove (int position, List *L) {    
    int counter;
    int size;
    ListNode * active;
    ListNode * toFree;

     #ifdef DEBUG 
        if (position < 0 || position > Size(L)) {
            printf("The position must be 0 or greater, and less than the size of the list\n");
            exit(1);
        } else if (Empty(L) == 1) {
            printf("The list cannot be empty when removing\n");
            exit(1);
        }
    #endif

    size = L->size;

    active = L->first;

    if (position == 0) {
        toFree = L->first;
        L->first = L->first->next;
    } else {

        for (counter = 0; counter < position-1; counter++) {
            active = active->next;
        }
        toFree = active->next;
        active->next = active->next->next;
    }
    FreeStudent(&toFree->item);
    /*free(toFree);*/
    L->size = L->size-1;

    #ifdef DEBUG
        if (Size(L) != size - 1) {
            printf("List size must decrease by one after a remove");
            exit(1);
        }
    #endif

}
int Full (List *L) {

    return 2;
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
    ListNode * active;
    int counter;

     #ifdef DEBUG 
        if (position < 0 || position > Size(L)) {
            printf("The position must be 0 or greater and less than the size of the list\n");
            exit(1);
        } else if (Empty(L) == 1) {
            printf("The list cannot be empty when using peek\n");
            exit(1);
        }
    #endif

    /*printf("inside peek position is:%d\n",position);*/

    active = L->first;
 
    for (counter = 0; counter < position; counter++) {
        active = active->next;
    }
    /*printf("after peek for loop| active name: %s\n",active->item.name);*/
    /*X->name = malloc(sizeof(char)*strlen(active->item.name)+1);*/
    /*strcpy(X->name,active->item.name);*/
    X->name = NameOfStudent(active->item);
    X->grade = active->item.grade;

}
void Destroy (List *L) {
    ListNode * active;
    ListNode * holder;

    active = L->first;

    if (!Empty(L)) {
        while (active->next != NULL) {
            holder = active->next;
            FreeStudent(&active->item);
            /*free(active);*/
            active = holder;
        }
        FreeStudent(&active->item);
        /*free(active);*/
    }
    free(L);

    /*FreeStudent(&active->item);*/

}
