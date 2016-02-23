//
//  UserDefined.c
//  DoublyLinkedList
//
//  Created by Jacob on 2/22/16.
//  Copyright © 2016 UmbrellaCorp. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "UserDefined.h"
#include "HelperFunctions.h"

int PrintItem(const void *data){
    myData * userData = (myData *)data;
    
    if (userData) {
        printf("\nData element: %d %s", userData->number, userData->theString);
        return EXIT_SUCCESS;
    }
    
    return EXIT_FAILURE;
}

int FreeItem(const void *data){
    myData * userData = (myData *)data;
    
    if (userData) {
        safeFree(userData->theString);
        safeFree(userData); /* Avoid Memory Leaks */
        return EXIT_SUCCESS;
    }
    
    return EXIT_FAILURE;
}

int CompareItems(const void *item1_p, const void *item2_p, int key){
    switch (key) {
        case INT:{
            myData * userData1 = (myData *)item1_p;
            myData * userData2 = (myData *)item2_p;
            
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
            myData * userData1 = (myData *)item1_p;
            myData * userData2 = (myData *)item2_p;
            
            if (userData1 && userData2){
                /* Strcmp returns: */
                /* Negative if the string of userData1 appears before the userData2->string in lexicographical order */
                /* Zero if the strings are equal */
                /* Positive if the string of userData2 appears before the userData1->string in lexicographical order */
                int result = strcmp(userData1->theString, userData2->theString);
                if (result < 0) return 0;
                if (result == 0) return 1;
                if (result > 0) return 2;
            }

            
            break;
        }
            
        case SINGLESTR:{
            myData * userData1 = (myData *)item1_p;
            char * theString = (char *)item2_p;
            
            if (userData1){
                /* Strcmp returns: */
                /* Negative if the string of userData1 appears before the theString in lexicographical order */
                /* Zero if the strings are equal */
                /* Positive if the theString of userData2 appears before the userData1->string in lexicographical order */
                int result = strcmp(userData1->theString, theString);
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
    myData * userData = malloc(sizeof(myData));
    if (userData) {
        userData->number = 0;
        userData->theString = NULL;
        if (source_p) {
            userData->number = ((myData *)source_p)->number;
            userData->theString = ((myData *)source_p)->theString;
        }
        
        return userData;
    }
    
    return NULL;
}