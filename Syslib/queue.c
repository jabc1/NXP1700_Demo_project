/**
******************************************************************************
* @file    queue.c
* @author  Jason
* @date    2018/10/29
* @brief   ʵ��fifo����
******************************************************************************
*/
#include "queue.h"


static u32 fifo_surplusSize(struct fifo_data *head); //����ʣ��ռ��ж�
static u8 fifo_full(struct fifo_data *head);         //�����ж�

/*******************************************************************************
�� �� ����  fifo_Init
����˵����  ���г�ʼ��
��    ����  *head:  ����ͷ
            *data:  ���ݴ洢�׵�ַ
            len:    ���ݴ洢���򳤶�
�� �� ֵ��  ��ʼ����� TRUE/FALSE
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
�� �� ����  fifo_Clr
����˵����  �������
��    ����  *head:  ����ͷ
�� �� ֵ��  ��
*******************************************************************************/
void fifo_Rst(struct fifo_data *head)
{
    ERRR(head == NULL, return);
    head->front = 0;
    head->rear = 0;
}
/*******************************************************************************
�� �� ����  fifo_empty
����˵����  �ж϶����Ƿ�Ϊ��
��    ����  *head:  ����ͷ
�� �� ֵ��  TRUE(����Ϊ��)/FALSE
*******************************************************************************/
u8 fifo_empty(struct fifo_data *head)
{
    
    return ((head->front == head->rear) ? TRUE : FALSE);
}

/*******************************************************************************
�� �� ����  fifo_full
����˵����  �ж϶����Ƿ�����
��    ����  *head:  ����ͷ
�� �� ֵ��  TRUE(��������)/FALSE
*******************************************************************************/
static u8 fifo_full(struct fifo_data *head)
{
    
    return ((head->front == ((head->rear+1)%head->size)) ? TRUE : FALSE);
}

/*******************************************************************************
�� �� ����  fifo_surplusSize
����˵����  �ж϶���ʣ��ռ��С 
��    ����  *head:  ����ͷ
�� �� ֵ��  ʣ��ռ��С(�ַ�Ϊ��λ)
*******************************************************************************/
static u32 fifo_surplusSize(struct fifo_data *head)
{

    return ((head->front > head->rear)
            ? (head->front - head->rear - 1)
            : (head->size + head->front - head->rear - 1));

}

/*******************************************************************************
�� �� ����  fifo_validSize
����˵����  ��ѯ������Ч�ռ��С
��    ����  *head:  ����ͷ
�� �� ֵ��  ʣ��ռ��С(�ַ�Ϊ��λ)
*******************************************************************************/
u32 fifo_validSize(struct fifo_data *head)
{

    return ((head->rear < head->front)
            ? (head->rear + head->size - head->front)
            : (head->rear - head->front));
}

/*******************************************************************************
�� �� ����  kfifo_puts
����˵����  ���
��    ����  *head:  ����ͷ
            *data:  �������
            len:    ���ݳ���
�� �� ֵ��  ��ӽ�� TRUE/FALSE
*******************************************************************************/
u8 fifo_puts(struct fifo_data *head, u8 *data, u32 len)
{  
    u32 size;

    ERRR(head == NULL, return FALSE);
    ERRR(len > fifo_surplusSize(head), return FALSE); //�ж϶������Ƿ��д洢�ռ�
    
    size = MIN(len, head->size - head->rear);
    memcpy(head->data + head->rear, data, size);
    memcpy(head->data, data + size, len - size);

    head->rear = (head->rear + len)%head->size;

    return TRUE;   
}

/*******************************************************************************
�� �� ����  kfifo_gets
����˵����  ����
��    ����  *head:  ����ͷ
            *data:  ��������
            len:    �������ݳ���
�� �� ֵ��  ���ӽ�� TRUE/FALSE
*******************************************************************************/
u8 fifo_gets(struct fifo_data *head, u8 *data, u32 len)
{
    u32 size;

    ERRR(head == NULL, return FALSE);
    ERRR(fifo_empty(head) == TRUE, return FALSE); //����Ϊ��
    ERRR(len > fifo_validSize(head), return FALSE); //�洢����С��Ҫ��ȡ����

    size = MIN(len, head->size - head->front);
    memcpy(data, head->data + head->front, size);
    memcpy(data+size, head->data, len - size);

    head->front = (head->front + len)%head->size;

    return TRUE;   
}

/*******************************************************************************
�� �� ����  fifo_putc
����˵����  ���һ���ַ�
��    ����  *head:  ����ͷ
            data:   Ҫ��ӵ�����
�� �� ֵ��  ��ӽ�� TRUE/FALSE
*******************************************************************************/
u8 fifo_putc(struct fifo_data *head, u8 data)
{
    ERRR(head == NULL, return FALSE);
    ERRR(fifo_full(head) == TRUE, return FALSE); //�ж϶������Ƿ��д洢�ռ�

    head->data[head->rear] = data;

    head->rear = (++head->rear)%head->size;

    return TRUE;   
}

/*******************************************************************************
�� �� ����  kfifo_getc
����˵����  ����һ���ַ�
��    ����  *head:  ����ͷ
            data:  ��������
�� �� ֵ��  ���ӽ�� TRUE/FALSE
*******************************************************************************/
u8 fifo_getc(struct fifo_data *head, u8 *data)
{
    ERRR(head == NULL, return FALSE);
    ERRR(fifo_empty(head) == TRUE, return FALSE); //����Ϊ��

    *data = head->data[head->front];
    head->front = (++head->front)%head->size;

    return TRUE;   
}





