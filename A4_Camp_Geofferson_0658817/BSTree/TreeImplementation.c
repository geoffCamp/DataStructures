#include "TreeInterface.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void Initialize (Tree *T,
                 void * (*copyValue) (void *, void *),
                 void (*destroyValue) (void *),
                 int (*compareValues) (void *, void *)) {
    T->copyValue = copyValue;
    T->destroyValue = destroyValue;
    T->compareValues = compareValues;
    T->size = 0;
    T->root = malloc(sizeof(void *));
    T->root->value = NULL;
    T->current = malloc(sizeof(void *));
}

void Insert (Tree *T, void *I) {
    int compVal;
    void * new;
    int breaker;
    TreeNode * node;

    new = malloc(sizeof(void *));
    node = malloc(sizeof(TreeNode));

    T->copyValue(new,I);
    node->value = new;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;

    breaker = 0;

    if (T->root->value == NULL) {
        node->parent = NULL;
        T->root = node;
        T->size = T->size + 1;
        return;
    } else {
        T->current = T->root;
    }
    while (breaker == 0 && T->current != NULL) {
       
         node->parent = T->current;

        compVal = T->compareValues(T->current->value,new);
        
        if (compVal == 1) { 
            if (T->current->left != NULL) {
                T->current = T->current->left;
            } else {
                T->current->left = node;
                breaker = 1;
            }

        } else if (compVal == 0) {
 
            if (T->current->right != NULL) {
                T->current = T->current->right;
            } else {
                T->current->right = node;
                breaker = 1;
            }
    
        } else {
            if (T->current->right != NULL) {
                T->current = T->current->right;
             } else {
                 T->current->right = node;
                 breaker = 1;
             }
        }
    }

    T->size = T->size + 1; 

}

int Minimum (Tree *T, void *I) {
    int breaker;

    breaker = 0;    

    if (Size(T) == 0) {
        return 0;
    }
    
    T->current = T->root;
    
    while (breaker == 0 && T->current != NULL) {
        
        if (T->current->left == NULL) {
            breaker = 1;
        } else {
            T->current = T->current->left;
        }
    }

    T->copyValue(I,T->current->value);
    
    return 1;    

}

int Successor (Tree *T, void *I) {
    TreeNode *  checker;
    TreeNode * original;

    if (T->current == NULL || Size(T) == 0) {
        printf("Successor call must be preceeded by a call to minimum or successor. Tree can not be empty.\n");
        return 0;
    }
    
    checker = T->root;
    while (checker->right != NULL) {
        checker=checker->right;
    }
    if (T->compareValues(checker->value,T->current->value) == 0) {
        return 0;
    }

    original = T->current;
    if (T->current ->right != NULL) {
        T->current = T->current->right;
        while (T->current->left != NULL) {
            T->current = T->current->left;
        }
        T->copyValue(I,T->current->value);
        return 1;
    }

    while (T->compareValues(T->current->value,original->value) != 1) {
        T->current = T->current->parent;
    }
    T->copyValue(I,T->current->value);
    return 1;
    
}

int Size (Tree *T) {

   return T->size;

}

int HeightRec(TreeNode * node, int left, int right) {

    if (node == NULL) {
        return right;
    }    

    left = HeightRec(node->left,left+1,right+1); 
    right = HeightRec(node->right,left+1,right+1);

    if (left > right) {
        return left;
    } else { 
        return right;
    }
}


int Height (Tree *T) {

    if (Size(T) == 0) {
        return -1;
    } else { 
        return HeightRec(T->root,0,0)-1;
    }

}

int BalancedRec (TreeNode * node, int left, int right) {

    if (node == NULL) {
        return right;
    }  

    left = BalancedRec(node->left,left+1,right+1);
    right = BalancedRec(node->right,left+1,right+1);

    if (left-right > 1 || right-left > 1) {
        return 893467;
    }

    if (left > right) {
         return left;
     } else {
         return right;
     }
}

int Balanced (Tree *T) {

    if (Size(T) == 0) {
        return 1;
    }

    if (BalancedRec(T->root,0,0) == 893467) {
       return 0;
    } else {
        return 1;
    }

}

void DestroyRec (Tree * T, TreeNode * node) {

    if (node == NULL) {
        return;
    }

    DestroyRec(T,node->left);
    DestroyRec(T,node->right);

   T->destroyValue(node->value);

}

void Destroy (Tree *T) {
    
    DestroyRec(T, T->root);

    free(T->current);
    
    if (Size(T) == 0) {
        free(T);
        return;
    }
}
