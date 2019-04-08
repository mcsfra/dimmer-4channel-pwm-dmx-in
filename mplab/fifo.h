#ifndef __FIFO_H__
#define __FIFO_H__


#define FIFO_SIZE   16
#define FIFO_MASK 0x0F

/*
** Prototypes
*/


extern void          fifoInit  ( void );
extern unsigned char fifoGet   ( void );
extern void          fifoPut   ( unsigned char in );
extern unsigned char fifoEmpty ( void );


#endif
