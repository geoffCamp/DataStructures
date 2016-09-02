 /*********************************************************************
 * FILE NAME: ListInterface.h
 * PURPOSE: Interface of the Student List ADT
 * AUTHOR: P. Matsakis (CIS2520, Assignment 1)
 * DATE: 21/09/2015
 * NOTES: . If the user includes QueueInterface.h in a source file,
 *          they should not include StudentInterface.h. Including 
 *          both header files in the same source file would cause 
 *          a compilation error, because ListInterface.h indirectly 
 *          includes StudentInterface.h, and the type Student would 
 *          therefore be defined twice. (As we will see, however,  
 *          there is a way to go around this.)
 *        . Peek calls InitializeStudent, and it is the user's
 *          responsibility to call FreeStudent when appropriate
 *          (see StudentInterface.h).
 *        . In the following,
 *          the word Item may be replaced by the word Student.
 *********************************************************************/
#include "QueueType.h"

/*********************************************************************
 * FUNCTION NAME: Initialize
 * PURPOSE: Sets a Queue variable to the empty Queue.
 * ARGUMENTS: The address of the Queue variable to be initialized 
 *            (Queue *) 
 * ENSURES (postconditions):
 *          . Empty will return true (a nonzero integer).
 *          . Size will return 0.
 * NOTES: Initialize is the only function that may be used right
 *        after the declaration of the List variable or a call
 *        to Destroy, and it should not be used otherwise.
 *********************************************************************/
extern void Initialize (Queue *Q);

/*********************************************************************
 * FUNCTION NAME: Enqueue
 * PURPOSE: Inserts an Item into a Queue.
 * ARGUMENTS: . The Item to be inserted (Item) 
 *            . The address of the List (Queue *Q)
 * REQUIRES (preconditions):
 *              not greater than the size of the Queue.
 *            . The Queue should not be full.
 * ENSURES: . Empty will return false (0).
 *          . Size will return the first integer greater
 *            than the size of the List before the call.
 *          . Top will find
 *            the Item that was inserted.
 *********************************************************************/
extern void Enqueue (Item I, Queue *Q);

/*********************************************************************
 * FUNCTION NAME: Dequeue
 * PURPOSE: Removes an Item from the front of the queue.
 * ARGUMENTS: . The address of the Queue (Queue *Q)
 * REQUIRES:. The List should not be empty.
 * ENSURES: . Full will return false (0).
 *          . Size will return the first integer lower
 *            than the size of the Queue before the call.
 *********************************************************************/
extern void Dequeue (Queue *Q);

/*********************************************************************
 * FUNCTION NAME: Full
 * PURPOSE: Determines whether a Queue is full.
 * ARGUMENTS: The address of the Queue (Queue *) 
 * RETURNS: True (a nonzero integer) if the Queue is full,
 *          false (0) otherwise
 *********************************************************************/
extern int Full (Queue *Q);

/*********************************************************************
 * FUNCTION NAME: Empty
 * PURPOSE: Determines whether a Queue is empty.
 * ARGUMENTS: The address of the Queue (Queue *) 
 * RETURNS: True (a nonzero integer) if the Queue is empty,
 *          false (0) otherwise
 *********************************************************************/
extern int Empty (Queue *Q);

/*********************************************************************
 * FUNCTION NAME: Size
 * PURPOSE: Finds the size of a Queue.
 * ARGUMENTS: The address of the Queue (Queue *) 
 * RETURNS: The size of the Queue (int)
 *********************************************************************/
extern int Size (Queue *Q);

/*********************************************************************
 * FUNCTION NAME: Head
 * PURPOSE: Finds the Item at the top of the Queue.
 * ARGUMENTS: . The address of the Queue (Queue *Q)
 *            . The address of the Item
 *              the Item found should be copied to
 * REQUIRES: . The List should not be empty.
 *********************************************************************/
extern void Head (Queue *Q, Item *I);


/*********************************************************************
 * FUNCTION NAME: Tail
 * PURPOSE: Finds the Item at the tail of the Queue.
 * ARGUMENTS: . The address of the Queue (Queue *Q)
 *            . The address of the Item
 *              the Item found should be copied to
 * REQUIRES: . The List should not be empty.
 *********************************************************************/
extern void Tail (Queue *Q, Item *I);

/*********************************************************************
 * FUNCTION NAME: Destroy
 * PURPOSE: Frees memory that may have been allocated
 *          by InitializeStudent.
 * ARGUMENTS: The address of the Queue to be destroyed (Queue *) 
 * NOTES: The last function to be called should always be Destroy. 
 *********************************************************************/
extern void Destroy (Queue *Q);


