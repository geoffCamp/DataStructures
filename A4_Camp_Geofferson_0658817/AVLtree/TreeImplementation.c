#include "TreeInterface.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int BalancedRec(TreeNode *, int, int);

TreeNode * InorderBal (TreeNode *);

void InorderAssign (TreeNode *, TreeNode **);

void reBalance (Tree *, TreeNode *, TreeNode *, TreeNode *);

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
    TreeNode * balNode;
    TreeNode * nodeA;
    TreeNode * nodeB;
    TreeNode * nodeC;
    TreeNode ** array;

    new = malloc(sizeof(void *));
    node = malloc(sizeof(TreeNode));

    array = malloc(sizeof(TreeNode *)*3);

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

    balNode = InorderBal(T->root);
    if (balNode != NULL) {
        InorderAssign(balNode,array);
        nodeA = array[0];
        nodeB = array[1];
        nodeC = array[2];
        reBalance(T,nodeA,nodeB,nodeC);    
    } 

    free(array);

}

void InorderAssign (TreeNode * node, TreeNode ** array) {
   
    if (node->left != NULL) {
        InorderAssign(node->left,array);
    }

    if (array[0] == NULL) {
        array[0] = node;
    } else if (array[1] == NULL) {
        array[1] = node;
    } else {
        array[2] = node;
    }

    if (node->right != NULL) {
        InorderAssign(node->right,array);
    }
}

void reBalance (Tree * T, TreeNode * nodeA, TreeNode * nodeB, TreeNode * nodeC) {
    TreeNode * p;
    TreeNode * holder1;
    TreeNode * holder2;
    TreeNode * holder3;
    TreeNode * holder4;

    if (nodeA->left == NULL && nodeA->right == NULL) {
        p = nodeA;
        holder1 = nodeA->left;
        holder2 = nodeA->right;
        holder3 = nodeB->right;
        holder4 = nodeC->right;

    } else if (nodeC->left == NULL && nodeC->right == NULL) {
        p = nodeC;
        holder1 = nodeA->left;
        holder2 = nodeB->left;
        holder3 = nodeC->left;
        holder4 = nodeC->right;

    } else if (nodeB->left == NULL && nodeB->right == NULL && nodeB->parent == nodeA) {
        p = nodeA;
        holder1 = nodeA->left;
        holder2 = nodeB->left;
        holder3 = nodeB->right;
        holder4 = nodeC->right;
    } else {
        p = nodeC;
        holder1 = nodeA->left;
        holder2 = nodeB->left;
        holder3 = nodeB->right;
        holder4 = nodeC->right;
    }


    if (p->parent != NULL) {

        if (p->parent->left != NULL) {

            if (p->parent->left == p) {

                p->parent->left = nodeB;
            } else {
                p->parent->right = nodeB;
            }
        } else {
            p->parent->right = nodeB;
        }
    } else {
        T->root = nodeB;
    }

    nodeA->left = NULL;
    nodeA->right = NULL;
    nodeB->left = NULL;
    nodeB->right = NULL;
    nodeC->right = NULL;
    nodeC->left = NULL;
   
    nodeB->left = nodeA;
    nodeB->right = nodeC;

    nodeA->left = holder1;
    nodeA->right = holder2;
    nodeC->left = holder3;
    nodeC->right = holder4;
 
}

TreeNode * InorderBal (TreeNode * node) {
    
    if (node->left != NULL) {
        InorderBal(node->left);
    }
    if (BalancedRec(node,0,0) == 893467) {
        return node;
    } else {
        return NULL;
    }
    if (node->right != NULL) {
        InorderBal(node->right);
    }
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

