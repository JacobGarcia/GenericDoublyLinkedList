//
//  GenericLists.c
//  DoublyLinkedList
//
//  Created by Jacob on 2/22/16.
//  Copyright © 2016 UmbrellaCorp. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "GenericLists.h"
#include "HelperFunctions.h"

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
        
        return linkedList;
    }

    return NULL;
}

int Insert(list_p myList_p, node_p item_p, const void *data_p){
    assert(myList_p);
    node_p listNode = malloc(sizeof(node));
    
    if (listNode) {
        listNode->data_p = NULL;
        
        if (data_p)
            listNode->data_p = (void *)data_p; /* Insert the data into the new node if its not null */
        
        /*** Insert at tail ***/
        if (item_p == NULL) {
            listNode->next_p = NULL; /* The tail will always be 'landed' */
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
            /* It exists a head */
            listNode->next_p = ListHead(myList_p); /* The next node for the new head is the previous head */
            ListHead(myList_p)->prev_p = listNode; /* The previous head now has a previous node, which is the new head */
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
    node_p current = malloc(sizeof(node));
    
    if (current) {
        current = ListHead(myList_p);
        /* Iterate over the list to actually print the information */
        while (current != NULL) {
            myList_p->print(current->data_p);
            current = current->next_p;
        }
        
        safeFree(current);
        
        return EXIT_SUCCESS;
    }
    
    return EXIT_FAILURE;
}