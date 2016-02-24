/*
 * Copyright (c) 2016 Mario Jacob García Navarro
 *
 * File name: HelperFunctions.c
 *
 * Author:  Mario Jacob García Navarro
 *
 * Purpose: Support routine that handle some problems with the 
 *          free() function
 *
 * References:
 *          Understanding and Using C Pointers - Richard Reese
 *          O'Reilly (2013)
 *
 * Revision history:
 *          Feb 22 14:52 2016 - File created
 *
 * Error handling:
 *          None
 *
 */

#include "HelperFunctions.h" /* The header file */
#include <stdlib.h>          /* Used for the free() function */

/*
 *
 *  Function: saferFree
 *
 *  Purpose: The free function does not check the pointer passed 
 *           to see whether it is NULL and does not set the pointer 
 *           to NULL before it returns. The purpose of this
 *           function is address this problems of free().
 *
 *  Parameters:
 *            Input:  A handle that points to the pointer that
 *                    is desired to free
 *
 *            Output: A clean and safe pointer to NULL. Waiting 
 *                    to be destroyed by the end of the scope
 *                    of a function
 */
void saferFree(void **h) {
    /* If the handle or the pointer points to null, do nothing */
    if (h != NULL && *h != NULL) {
        free(*h);         /* Free the pointer */
        *h = NULL; /* Set the pointer to null */
    }
}