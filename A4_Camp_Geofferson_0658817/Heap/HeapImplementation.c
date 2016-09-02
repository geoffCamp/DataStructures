#include "HeapInterface.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static int leftRightUp (int start) {
    int toReturn;

    if (start % 2 == 0) {
        toReturn = start/2;
    } else {
        toReturn = (start-1)/2;
    }
 
    if (toReturn == 0) {
        toReturn = 1;
    }
    return toReturn;
}

int Initialize (Heap *H, int capacity,
                        void * (*copyValue) (void *, void *),
                        void (*destroyValue) (void *),
                        int (*compareValues) (void *, void *)) {
    
    if (H == NULL || copyValue == NULL || destroyValue == NULL || compareValues == NULL) {
        return 0;
    }

    H->heap = malloc(sizeof(void*)*((capacity*2)+1));
    H->capacity = capacity;
    H->numberOfValues = 0;
    H->copyValue = copyValue;
    H->destroyValue = destroyValue;
    H->compareValues = compareValues;

    return 1;

}

int Insert (Heap *H, void *I) {
    int position;
    int toCompareTo;
    void * holder;

    if (H->numberOfValues == H->capacity) {
        return 0;
    } 

    position = H->numberOfValues+1;
 
    toCompareTo = leftRightUp(position); 

    H->heap[position] = I;
    H->numberOfValues = H->numberOfValues+1;

    while (H->compareValues(H->heap[position],H->heap[toCompareTo]) == 1) {
        /* the swap */
        holder = H->heap[toCompareTo];
        H->heap[toCompareTo] = I; 
        H->heap[position] = holder;
        
        position = toCompareTo;
        toCompareTo = leftRightUp(position);
     
    }

    return 1;
}

void Remove (Heap * H) {
    int root;
    int toCompareLeft;
    int toCompareRight;
    int theSwapper;
    void * holder;

    H->heap[1] = H->heap[H->numberOfValues];
    H->heap[H->numberOfValues] = NULL;
    H->numberOfValues = H->numberOfValues - 1; 

    root = 1;
    toCompareLeft = root*2;
    toCompareRight = root*2 + 1;

    while (H->compareValues(H->heap[root],H->heap[toCompareLeft]) == -1 || H->compareValues(H->heap[root],H->heap[toCompareRight]) == -1) {

        /* the swap */
        if (H->compareValues(H->heap[toCompareLeft],H->heap[toCompareRight]) == 1) {
            theSwapper = toCompareLeft;
        } else if (H->compareValues(H->heap[toCompareLeft],H->heap[toCompareRight]) == -1){
            theSwapper = toCompareRight;
        } else if (H->compareValues(H->heap[toCompareLeft],H->heap[toCompareRight]) == 0) {
            theSwapper = toCompareRight;
        } else {
            if (toCompareLeft > H->capacity) {
                theSwapper = toCompareRight;
            } else {
                theSwapper = toCompareLeft;
            }
        }

        holder = H->heap[root];
        H->heap[root] = H->heap[theSwapper];
        H->heap[theSwapper] = holder;

        root = theSwapper;
        toCompareLeft = root*2;
        toCompareRight = (root*2)+1;
        if (toCompareLeft > H->capacity && toCompareRight > H->capacity) {
            root = 44;
        }
        
    }        

}

void Top (Heap * H, void * I) {
    
    H->copyValue(I,H->heap[1]);

}

int Full (Heap * H) {
    if (H->numberOfValues == H->capacity) {
        return 1;
    } else {
        return 0;
    }
}

int Empty (Heap * H) {
    if (H->numberOfValues == 0) { 
        return 1;
    } else {
        return 0;
    }
}

void Destroy (Heap * H) {
    int i;

    for (i = 1; i <= H->numberOfValues; i++ ) {
        free(H->heap[i]);
    }
    free(H->heap);
}
