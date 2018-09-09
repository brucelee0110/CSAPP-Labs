/* 
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q =  malloc(sizeof(queue_t)); 
    // will return null if no sapce available
    /* What if malloc returned NULL? */
    if (q != NULL){
      q->head = NULL;
      q->tail = NULL;
      q->size = 0;
    }
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements? */
    if (q != NULL){
        list_ele_t *next_element;
        for(int i=0;i<q->size;i++){
            list_ele_t *element;
            // get the element to free
            if (i == 0){
                element = q->head;
            }else {
                element = next_element;
            }
            // update for the next element
            int last = q->size -1;
            if (i != last){ // except the last one
                next_element = element->next;
            }
            free(element);
        }
        /* Free queue structure */
        free(q);
    }
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_head(queue_t *q, int v)
{
    /* What should you do if the q is NULL? */
    if (q == NULL){
        return false;
    }
    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));
    /* What if malloc returned NULL? */
    if (newh == NULL){
        return false;
    }
    newh->value = v;
    newh->next = q->head;
    q->head = newh;
    q->size++;
    if(q->tail == NULL){// check empty queue case
        q->tail=newh;
    }
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_tail(queue_t *q, int v)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    if (q == NULL){
        return false;
    }
    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));
    if (newh == NULL){
        return false;
    }
    newh->value = v;
    newh->next = NULL;
    if (q->size != 0){// only update when there is an element
        q->tail->next = newh;
    }
    q->tail = newh;
    q->size++;
    if(q->head == NULL){// check empty queue case
        q->head=newh;
    }
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If vp non-NULL and element removed, store removed value at *vp.
  Any unused storage should be freed
*/
bool q_remove_head(queue_t *q, int *vp)
{
    /* You need to fix up this code. */
    if(q == NULL || q->size == 0){
        return false;
    }
    list_ele_t *rm_element = q->head;
    if (vp !=NULL){ // store value only when vp non-NULL
        *vp = rm_element->value;
    }
    if (q->size == 1){// only one element left
        q->head = NULL;
        q->tail = NULL;
    }else{
        q->head = rm_element->next;
    }
    free(rm_element);
    q->size--;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if (q == NULL){
        return 0;
    }
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    return q->size;
}

/*
  Reverse elements in queue.

  Your implementation must not allocate or free any elements (e.g., by
  calling q_insert_head or q_remove_head).  Instead, it should modify
  the pointers in the existing data structure.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
    if (q !=NULL && q->size != 0) {
        q->tail = q->head;
        list_ele_t *newq;
        list_ele_t *curr_element;
        list_ele_t *next_element;
        // update the param
        newq = q->head;
        curr_element = q->head;
        next_element = q->head->next;
        // make last null
        curr_element->next=NULL;
        for (int i=1;i<q->size;i++){
            newq=next_element;
            if (i+1 != q->size){
                next_element = next_element->next;
            }
            newq->next=curr_element;
            curr_element=newq;
        }
        q->head=newq;
    }
}

