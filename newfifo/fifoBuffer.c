#include "fifoBuffer.h"
#include <stdlib.h> // malloc, free

static int i;

/*
 *	initialize a fifo buffer
 *	- The buffer is created externally to allow for memory allocation
 *	- Size is the size of the buffer
 */
void fifoInit(fifo_t *f, int maxSize) {
	f->head = f->tail = NULL;
	f->curSize = 0;
	f->maxSize = maxSize;
}

/*
 *	write a record the head of fifo buffer
 *	- returns -1 when buffer is full
 *	- if input exceeds buffer size, input will enter memory
 */
int fifoWrite(fifo_t *f, uint8_t *input, int nBytes) {
	
	// return -1 if buffer is full
	if (f->curSize >= f->maxSize) { return -1; }
	
	// add data to buffer
	for (i=0; i < nBytes; i++) {

		// create data node
		node_t *tmp = (node_t*)malloc(sizeof(node_t));
		tmp->data = *input++;
		tmp->next = NULL;

		if (f->head == NULL) {
			// first node, create head and tail structure with data
			f->head = f->tail = tmp;
		} else {
			// add link to new node
			f->tail->next = tmp;

			// add new node to tail
			f->tail = tmp;
		}

		// update curSize
		f->curSize++;
 	}
	return i;
}

/*
 *	read a record from the tail of fifo buffer
 *	- if buffer runs out before requested bytes are returned, \0 fills empty values
 */
int fifoRead(fifo_t *f, uint8_t *output, int nBytes) {

	node_t *tmp;

	for (i=0; i < nBytes; i++) {
		// check for empty buffer
		if (f->curSize != 0) {
			
			// output head
			output[i] = f->head->data;

			// increment head
			tmp = f->head;
			f->head = f->head->next;

			// destroy previous head
			free(tmp);

			// update curSize
			f->curSize--;

		} else {
			// fill remaining bytes with \0
			output[i] = '\0';
		}
	}
	return i;
}

/*
 *	removes all nodes, frees memory 
 */
void fifoReset(fifo_t *f) {
	node_t *current = f->head;
	node_t *next;

	while (current != NULL) {
		next = current->next;
		free(current);
		current = next;
	}
	f->head = f->tail = NULL;
}
