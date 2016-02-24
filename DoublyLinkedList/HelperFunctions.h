/*
 * Copyright (c) 2016 Mario Jacob García Navarro
 *
 * File name: HelperFunctions..h
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



/*************************************************************************
 *                    Helper Functions and MACROS                        *
 ************************************************************************/
/* Create a MACRO so the user can call the function without sending the 
 address of the pointer to be freed */
#define safeFree(p) saferFree((void**)&(p))
void saferFree(void **h);