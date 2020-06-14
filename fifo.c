/*
 * File:   fifo.c
 * Author: Sherwin Tiongson
 *
 */
/******************************************************************************
 * Software License Agreement
 *
 * Copyright © 2011 Microchip Technology Inc.  All rights reserved.
 * Microchip licenses to you the right to use, modify, copy and distribute
 * Software only when embedded on a Microchip microcontroller or digital
 * signal controller, which is integrated into your product or third party
 * product (pursuant to the sublicense terms in the accompanying license
 * agreement).
 *
 * You should refer to the license agreement accompanying this Software
 * for additional information regarding your rights and obligations.
 *
 * SOFTWARE AND DOCUMENTATION ARE PROVIDED Ã¬AS ISÃ® WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY
 * OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR
 * PURPOSE. IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR
 * OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION,
 * BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT
 * DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL,
 * INDIRECT, PUNITIVE OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA,
 * COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY
 * CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF),
 * OR OTHER SIMILAR COSTS.
 *
 *****************************************************************************/
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "fifo.h"

/*! This module implements a simple FIFO class that can be
  used for asynchronous byte buffering at any point. */

hFifo fifo_create(unsigned short size) {
    hFifo ptr = malloc(sizeof(fifo));
    if (ptr == NULL) return NULL;
    ptr->array = calloc(1, size);
    if (ptr->array == NULL) return NULL;
    ptr->size = size;
    ptr->count = ptr->in = ptr->out = 0;
    return ptr;
}

short fifo_is_empty(hFifo ptr) {
    if (ptr == NULL) return FIFO_ENULLHANDLE;
    return (ptr->count == 0);
}

short fifo_is_full(hFifo ptr) {
    if (ptr == NULL) return FIFO_ENULLHANDLE;
    return (ptr->count == ptr->size);
}

short fifo_count(hFifo ptr) {
    if (ptr == NULL) return FIFO_ENULLHANDLE;
    return ptr->count;
}

short fifo_get(hFifo ptr, unsigned char *buffer, unsigned short size) {
    unsigned short i;
    if (ptr == NULL) return FIFO_ENULLHANDLE;
    if (buffer == NULL) return FIFO_ENULLBUFFER;
    if (ptr->size < size) return FIFO_EILLEGALSIZE;
    if (ptr->count == 0) return FIFO_EEMPTY;
    if (ptr->count < size) return FIFO_UNDERFLOW;
    for (i = 0; i < size; i++) {
        buffer[i] = ptr->array[(ptr->out + i) % ptr->size];
    }
    ptr->out = (ptr->out + size) % ptr->size;
    ptr->count -= size;
    return FIFO_EOK;
}

short fifo_peek(hFifo ptr, unsigned char *buffer, unsigned short size) {
    unsigned short i;
    if (ptr == NULL) return FIFO_ENULLHANDLE;
    if (buffer == NULL) return FIFO_ENULLBUFFER;
    if (ptr->size < size) return FIFO_EILLEGALSIZE;
    if (ptr->count == 0) return FIFO_EEMPTY;
    if (ptr->count < size) return FIFO_UNDERFLOW;
    for (i = 0; i < size; i++) {
        buffer[i] = ptr->array[(ptr->out + i) % ptr->size];
    }
    return FIFO_EOK;
}

short fifo_put(hFifo ptr, unsigned char *buffer, unsigned short size) {
    unsigned short i, n;
    if (ptr == NULL) return FIFO_ENULLHANDLE;
    if (buffer == NULL) return FIFO_ENULLBUFFER;
    if (ptr->size < size) return FIFO_EILLEGALSIZE;
    if (ptr->count == ptr->size) return FIFO_EFULL;
    if ((ptr->size - ptr->count) < size) return FIFO_OVERFLOW;
    n = ((ptr->size - ptr->count) < size) ? (ptr->size - ptr->count) : size;
    for (i = 0; i < n; i++) {
        ptr->array[(ptr->in + i) % ptr->size] = buffer[i];
    }
    ptr->in = (ptr->in + n) % ptr->size;
    ptr->count += n;
    return FIFO_EOK;
}

void fifo_destroy(hFifo ptr) {
    if (ptr != NULL) {
        free(ptr->array);
        free(ptr);
    }
}

void fifo_flush(hFifo ptr) {
    if (ptr != NULL) {
        memset(ptr->array, 0, ptr->size);
        ptr->count = ptr->in = ptr->out = 0;
    }
}

/* End of file. */
