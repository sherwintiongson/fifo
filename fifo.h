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
#ifndef _FIFO_H_
#define _FIFO_H_

/*! \file */

#define FIFO_EOK 0
#define FIFO_EEMPTY -1
#define FIFO_EFULL -2
#define FIFO_ENOMEM -3
#define FIFO_ENULLHANDLE -4
#define FIFO_ENULLBUFFER -5
#define FIFO_EILLEGALSIZE -6
#define FIFO_UNDERFLOW -7
#define FIFO_OVERFLOW -8

typedef struct _fifo {
    unsigned short in;
    unsigned short out;
    unsigned char *array;
    unsigned short size;
    unsigned short count;
} fifo, *hFifo;

hFifo fifo_create(unsigned short size);
short fifo_is_empty(hFifo ptr);
short fifo_is_full(hFifo ptr);
short fifo_count(hFifo ptr);
short fifo_get(hFifo ptr, unsigned char *buffer, unsigned short size);
short fifo_put(hFifo ptr, unsigned char *buffer, unsigned short size);
void fifo_destroy(hFifo ptr);
void fifo_flush(hFifo ptr);
short fifo_peek(hFifo ptr, unsigned char *buffer, unsigned short size);

#endif /* _FIFO_H_ */

/* End of file. */
