/*
 *	First In First Out Buffer (FIFO)
 *	
 *	John E Maddox
 */

#ifndef __fifoBuffer
#define __fifoBuffer

#include <stdint.h> // uint8_t

typedef struct Node {
	uint8_t data;
	struct Node *next; // couldn't use typedef, VS bug?
} node_t;

typedef struct {
	node_t *head;
	node_t *tail;
	int curSize;
	int maxSize;
} fifo_t;

void fifoInit(fifo_t *f, int maxSize);

int fifoWrite(fifo_t *f, uint8_t *input, int nBytes);

int fifoRead(fifo_t *f, uint8_t *output, int nBytes);

void fifoReset(fifo_t *f);

#endif /* __fifoBuffer */
