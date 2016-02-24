/**
 *  UserDefined.c
 *  DoublyLinkedList
 *
 *  Created by Mario García on 2/22/16.
 *  Copyright © 2016 Mario García. All rights reserved.
 */

#include <stdio.h>  /* Used for the printf() function */
#include <stdlib.h> /* Used for the malloc() function */
#include <string.h> /* Used for the strcmp() function */
#include <assert.h> /* Used for the assert() function */
#include "UserDefined.h"        /* Header of the file */
#include "HelperFunctions.h"       /* The header file */

int PrintItem(const void *data){
    myData * userData = (myData *)data; /* Cast the void pointer */
    
    /* If the data passed is not null continue to print the item */
    if (userData) {
        /* Print the number and the string of the data structure and exit */
        printf("Data element: %d %s\n", userData->number, userData->theString);
        return EXIT_SUCCESS;
    }
    
    return EXIT_FAILURE;
}

int FreeItem(const void *data){
    myData * userData = (myData *)data; /* Cast the void pointer */
    
    /* If the data passed is not null continue to free the item */
    if (userData) {
        safeFree(userData->theString); /* Safe free the String */
        safeFree(userData); /* Avoid Memory Leaks */
        return EXIT_SUCCESS;
    }
    
    return EXIT_FAILURE;
}

int CompareItems(const void *item1_p, const void *item2_p, int key){
    /* The comparation depends on the key specified */
    switch (key) {
        case INT:{
            /* Cast the data pointers */
            myData * userData1 = (myData *)item1_p;
            myData * userData2 = (myData *)item2_p;
            
            /* If the data for void pointers is valid (not null) continue */
            if (userData1 && userData2) {
                if (userData1->number < userData2->number)
                    return 0;
                
                if (userData1->number > userData2->number)
                    return 2;
                
                /* If the numbers are equal return 1 */
                return 1;
            }
            
            break;
        }
            
        case STR:{
            /* Cast the data pointers */
            myData * userData1 = (myData *)item1_p;
            myData * userData2 = (myData *)item2_p;
            
            /* If the data for void pointers is valid (not null) continue */
            if (userData1 && userData2){
                /* Strcmp returns: */
                /* Negative if the string of userData1 appears before the userData2->string in lexicographical order */
                /* Zero if the strings are equal */
                /* Positive if the string of userData2 appears before the userData1->string in lexicographical order */
                int result = strcmp(userData1->theString, userData2->theString);
                
                /* Adjust the result returned to the API specifications */
                if (result < 0) return 0;
                if (result == 0) return 1;
                if (result > 0) return 2;
            }

            
            break;
        }
            
        case SINGLESTR:{
            myData * userData1 = (myData *)item1_p; /* Cast the void data pointer */
            char * theString = (char *)item2_p;    /* Cast to string the second pointer */
            
            if (userData1){
                /* Strcmp returns: */
                /* Negative if the string of userData1 appears before the theString in lexicographical order */
                /* Zero if the strings are equal */
                /* Positive if the theString of userData2 appears before the userData1->string in lexicographical order */
                int result = strcmp(userData1->theString, theString);
                
                /* Adjust the result returned to the API specifications */
                if (result < 0) return 0;
                if (result == 0) return 1;
                if (result > 0) return 2;
            }
            
            break;
        }
    }
    
    return EXIT_FAILURE;
}

void * CopyItems (const void *source_p){
    myData * userData = malloc(sizeof(myData)); /* Allocate memory for the copy structure */
    if (userData) {
        /* Initialize the new structure */
        userData->number = 0;
        userData->theString = NULL;
        
        /* If the source for the copy is valid continue */
        if (source_p) {
            /* Copy the source information */
            userData->number = ((myData *)source_p)->number;
            userData->theString = strdup(((myData *)source_p)->theString); /* theString is a pointer */
        }
        
        /* Return the copy */
        return userData;
    }
    
    /* If the memory could not be allocated return a NULL structure */
    return NULL;
}