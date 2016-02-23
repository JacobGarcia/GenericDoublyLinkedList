//
//  HelperFunctions.c
//  DoublyLinkedList
//
//  Created by Jacob on 2/22/16.
//  Copyright © 2016 UmbrellaCorp. All rights reserved.
//

#include "HelperFunctions.h"
#include <stdlib.h>

void saferFree(void **h) {
    if (h != NULL && *h != NULL) {
        free(*h);
        *h = NULL;
    }
}