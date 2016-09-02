#include "StudentInterface.h"
typedef Student Item;

#define MAXQUEUESIZE 4
typedef struct {
	Item items[MAXQUEUESIZE];
        int head;
	int size;
} Queue;
