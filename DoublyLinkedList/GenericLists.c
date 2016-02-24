/**
 * GenericLists.c
 *  DoublyLinkedList
 *
 *  Created by Mario García on 2/22/16.
 *  Copyright © 2016 Mario García. All rights reserved.
 */

#include <stdio.h>  /* Used for the printf() function */
#include <stdlib.h> /* Used for the malloc() function */
#include <assert.h> /* Used for the assert() function */
#include "GenericLists.h"       /* Header of the file */
#include "HelperFunctions.h" /* Some helper functions */

list_p CreateList(int (*destroy)(const void *data_p), int (*print)(const void *data_p), int (*compare)(const void *source_p, const void *dest_p, int key), void *(* copy)(const void *source_p)){
    list_p linkedList = malloc(sizeof(list));
    
    if (linkedList) {
        /* Initialize the list*/
        linkedList->numItems = 0;
        linkedList->head_p = NULL;
        linkedList->tail_p = NULL;
        
        /* Assign the function references */
        linkedList->destroy = destroy;
        linkedList->print   = print;
        linkedList->compare = compare;
        linkedList->copy    = copy;
        
        return linkedList; /* Return the list if everything is ok */
    }

    return NULL; /* Return NULL if the linked list could not be created */
}

int Insert(list_p myList_p, node_p item_p, const void *data_p){
    assert(myList_p); /* The list points to NULL */
    node_p listNode = malloc(sizeof(node)); /* Allocate memory for the node to be inserted */
    
    if (listNode) {
        listNode->data_p = NULL; /* Initialize its data to NULL */
        
        if (data_p)
            listNode->data_p = (void *)data_p; /* Insert the data into the new node if there is actually some data */
        
        /*** Insert at tail ***/
        if (item_p == NULL) {
            listNode->next_p = NULL; /* The tail next pointer will always be 'landed' */
            /* This is the first element, since there is no head */
            if (ListHead(myList_p) == NULL) {
                listNode->prev_p = NULL; /* The head does not have previous elements */
                ListHead(myList_p) = listNode; /* This node is now the head too */
            } else {
                /* It exists a tail */
                listNode->prev_p = ListTail(myList_p); /* The previous node will be the tail at this moment */
                ListTail(myList_p)->next_p = listNode; /* The previous tail will now point next to the new tail */
            }
            
            ListTail(myList_p) = listNode; /* In both cases the node will be the new tail */
        }
        
        /*** Insert at head ***/
        else if (item_p == ListHead(myList_p)) {
            listNode->prev_p = NULL; /* The head never has a previous node */
            listNode->next_p = ListHead(myList_p); /* The next node for the new head is the previous head */
            ListHead(myList_p)->prev_p = listNode; /* The previous head now has a previous node, which is the new head */
            ListHead(myList_p) = listNode; /* This node is now the head */

        }
        
        /*** Insert at the middle ***/
        else {
            /* Move pointers of the existing item in relation with the the new item */
            item_p->prev_p->next_p = listNode;
            listNode->prev_p = item_p->prev_p;
            item_p->prev_p = listNode;
            listNode->next_p = item_p;
        }
        
        (myList_p->numItems)++; /* Increase the number of items counter in the list by one */
        
        return EXIT_SUCCESS;
        
    }
    
    return EXIT_FAILURE;
}

int PrintList(list_p myList_p){
    
    if (myList_p) {
        node_p current; /* Create a temporal pointer to iterate over the list */
        current = ListHead(myList_p); /* The temporal pointer always start at the head */
        /* Iterate over the list to actually print the information */
        while (current != NULL) {
            myList_p->print(current->data_p); /* Call the print function of the list */
            current = current->next_p; /* Point to the next node */
        }
        
        printf("\n");
        
        return EXIT_SUCCESS;
    }
    
    return EXIT_FAILURE;
}

int Delete(list_p myList_p, node_p item_p, void **data_h){
    
    if (myList_p){
        
        /*** Delete the head ***/
        if (item_p == ListHead(myList_p) || item_p == NULL) {
            /* Is the head the only item on the list? */
            if (ListHead(myList_p)->next_p == NULL)
                ListHead(myList_p) = ListTail(myList_p) = NULL; /* There is nothing left on the list; so everything set it to NULL */
            else {
                ListHead(myList_p) = ListHead(myList_p)->next_p; /* The head is now the next element */
                ListHead(myList_p)->prev_p = NULL; /* The head never points to a previous node */
            }
        }
        
        /*** Delete at the middle and the tail ***/
        else {
            if (item_p != ListTail(myList_p)) /* The tail does not have a next node; while a node at the middle does */
                item_p->next_p->prev_p = item_p->prev_p;
            else
                ListTail(myList_p) = item_p->prev_p;
            
            /* Update the pointers */
            item_p->prev_p->next_p = item_p->next_p;
        }
        
        /* Move the address of the data_p pointer in order to delete it correctly */
        *data_h = (item_p->data_p);
        
        /* Delete the node that points to the user defined structure */
        safeFree(item_p);
        
        
        (myList_p->numItems)--; /* Decrease the number of items counter in the list by one */

        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}

node_p FindInList(list_p myList_p, const void *value_p, int key){
    assert(myList_p); /* The list points to NULL */
    
    if (value_p) {
        node_p current; /* Create a temporal pointer to iterate over the list */
        current = ListHead(myList_p); /* The temporal pointer always start at the head */
        /* Iterate over the nodes of the list to search the specified information in value_p */
        while (current != NULL) {
            int comparisonResult = myList_p->compare(current->data_p, value_p, key); /* Compare the information between nodes */
            if (comparisonResult == 1) /* The node was found; so return it*/
                return current;
            
            current = current->next_p; /* Point to the next node */
        }
        
    }
    
    return NULL; /* The specified value was not found */
}

int DestroyList(list_p myList_p){
    if (myList_p) {
        node_p current; /* Create a temporal pointer to iterate over the list */
        current = ListHead(myList_p); /* The temporal pointer always start at the head */
        
         /* Iterate over the nodes of the list to delete them */
        while (current != NULL) {
            myList_p->destroy(current->data_p); /* Destroy the data node that the temporal pointer is pointing too */
            current = current->next_p; /* Point to the next node */
            
            if (current)
                safeFree(current->prev_p); /* Free the actual node */
            
            (myList_p->numItems)--; /* Decrease the number of items counter in the list by one */
        }
        
        safeFree(ListTail(myList_p)); /* The tail is the only element left */
        /* Destroy the List */
        safeFree(myList_p);
        
        return EXIT_SUCCESS;

    }
    
    return EXIT_FAILURE;
}