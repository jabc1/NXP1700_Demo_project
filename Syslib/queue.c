/**
******************************************************************************
* @file    queue.c
* @author  Jason
* @date    2018/10/29
* @brief   实现fifo功能
******************************************************************************
*/
#include "queue.h"


static u32 fifo_surplusSize(struct fifo_data *head); //队列剩余空间判断
static u8 fifo_full(struct fifo_data *head);         //队满判断

/*******************************************************************************
函 数 名：  fifo_Init
功能说明：  队列初始化
参    数：  *head:  队列头
            *data:  数据存储首地址
            len:    数据存储区域长度
返 回 值：  初始化结果 TRUE/FALSE
*******************************************************************************/
u8 fifo_Init(struct fifo_data *head, u8 *buf, u32 len)
{
    ERRR(head == NULL, return FALSE);
    head->data = buf;
    head->size = len;
    head->front = head->rear = 0;

    return TRUE;
}

/*******************************************************************************
函 数 名：  fifo_Clr
功能说明：  队列清空
参    数：  *head:  队列头
返 回 值：  无
*******************************************************************************/
void fifo_Rst(struct fifo_data *head)
{
    ERRR(head == NULL, return);
    head->front = 0;
    head->rear = 0;
}
/*******************************************************************************
函 数 名：  fifo_empty
功能说明：  判断队列是否为空
参    数：  *head:  队列头
返 回 值：  TRUE(队列为空)/FALSE
*******************************************************************************/
u8 fifo_empty(struct fifo_data *head)
{
    
    return ((head->front == head->rear) ? TRUE : FALSE);
}

/*******************************************************************************
函 数 名：  fifo_full
功能说明：  判断队列是否已满
参    数：  *head:  队列头
返 回 值：  TRUE(队列已满)/FALSE
*******************************************************************************/
static u8 fifo_full(struct fifo_data *head)
{
    
    return ((head->front == ((head->rear+1)%head->size)) ? TRUE : FALSE);
}

/*******************************************************************************
函 数 名：  fifo_surplusSize
功能说明：  判断队列剩余空间大小 
参    数：  *head:  队列头
返 回 值：  剩余空间大小(字符为单位)
*******************************************************************************/
static u32 fifo_surplusSize(struct fifo_data *head)
{

    return ((head->front > head->rear)
            ? (head->front - head->rear - 1)
            : (head->size + head->front - head->rear - 1));

}

/*******************************************************************************
函 数 名：  fifo_validSize
功能说明：  查询队列有效空间大小
参    数：  *head:  队列头
返 回 值：  剩余空间大小(字符为单位)
*******************************************************************************/
u32 fifo_validSize(struct fifo_data *head)
{

    return ((head->rear < head->front)
            ? (head->rear + head->size - head->front)
            : (head->rear - head->front));
}

/*******************************************************************************
函 数 名：  kfifo_puts
功能说明：  入队
参    数：  *head:  队列头
            *data:  入队数据
            len:    数据长度
返 回 值：  入队结果 TRUE/FALSE
*******************************************************************************/
u8 fifo_puts(struct fifo_data *head, u8 *data, u32 len)
{  
    u32 size;

    ERRR(head == NULL, return FALSE);
    ERRR(len > fifo_surplusSize(head), return FALSE); //判断队列中是否还有存储空间
    
    size = MIN(len, head->size - head->rear);
    memcpy(head->data + head->rear, data, size);
    memcpy(head->data, data + size, len - size);

    head->rear = (head->rear + len)%head->size;

    return TRUE;   
}

/*******************************************************************************
函 数 名：  kfifo_gets
功能说明：  出队
参    数：  *head:  队列头
            *data:  出队数据
            len:    出队数据长度
返 回 值：  出队结果 TRUE/FALSE
*******************************************************************************/
u8 fifo_gets(struct fifo_data *head, u8 *data, u32 len)
{
    u32 size;

    ERRR(head == NULL, return FALSE);
    ERRR(fifo_empty(head) == TRUE, return FALSE); //队列为空
    ERRR(len > fifo_validSize(head), return FALSE); //存储总数小于要读取的数

    size = MIN(len, head->size - head->front);
    memcpy(data, head->data + head->front, size);
    memcpy(data+size, head->data, len - size);

    head->front = (head->front + len)%head->size;

    return TRUE;   
}

/*******************************************************************************
函 数 名：  fifo_putc
功能说明：  入队一个字符
参    数：  *head:  队列头
            data:   要入队的数据
返 回 值：  入队结果 TRUE/FALSE
*******************************************************************************/
u8 fifo_putc(struct fifo_data *head, u8 data)
{
    ERRR(head == NULL, return FALSE);
    ERRR(fifo_full(head) == TRUE, return FALSE); //判断队列中是否还有存储空间

    head->data[head->rear] = data;

    head->rear = (++head->rear)%head->size;

    return TRUE;   
}

/*******************************************************************************
函 数 名：  kfifo_getc
功能说明：  出队一个字符
参    数：  *head:  队列头
            data:  出队数据
返 回 值：  出队结果 TRUE/FALSE
*******************************************************************************/
u8 fifo_getc(struct fifo_data *head, u8 *data)
{
    ERRR(head == NULL, return FALSE);
    ERRR(fifo_empty(head) == TRUE, return FALSE); //队列为空

    *data = head->data[head->front];
    head->front = (++head->front)%head->size;

    return TRUE;   
}





