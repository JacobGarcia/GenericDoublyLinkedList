//
//  HelperFunctions.h
//  DoublyLinkedList
//
//  Created by Jacob on 2/22/16.
//  Copyright © 2016 UmbrellaCorp. All rights reserved.
//

#ifndef HelperFunctions_h
#define HelperFunctions_h

#include <stdio.h>

#endif /* HelperFunctions_h */


/*************************************************************************
 *                    Helper Functions and MACROS                        *
 ************************************************************************/
#define safeFree(p) saferFree((void**)&(p))
void saferFree(void **h);