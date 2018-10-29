#ifndef _queue_h
#define _queue_h
#include "base.h"
#include <stdio.h>
#include <stdlib.h>  

/*容错宏*/
#define ERRR(conf, ret)      do              \
                            {                \
                                if (conf)    \
                                {            \
                                    ret;     \
                                }            \
                            } while(0) 
							
#define ABS(i, j)       (((i) > (j)) ? ((i) - (j)) : ((j) - (i)))       //获取绝对值

struct fifo_data
{
    u8   *data;
    u32   size;
    u32   front;
    u32   rear;
};
u8 fifo_Init(struct fifo_data *head, u8 *buf, u32 len); 
void fifo_Rst(struct fifo_data *head);
u32 fifo_validSize(struct fifo_data *head);
u8 fifo_empty(struct fifo_data *head);
u8 fifo_puts(struct fifo_data *head, u8 *data, u32 len);
u8 fifo_gets(struct fifo_data *head, u8 *data, u32 len);
u8 fifo_putc(struct fifo_data *head, u8 data);
u8 fifo_getc(struct fifo_data *head, u8 *data);

#endif

