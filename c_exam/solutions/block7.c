#include <stdlib.h>
#include "block7.h"


void zero_sort(uint32_t *a, size_t n)
{
    if (a == NULL) return;
    size_t write_ptr = 0;
    for (size_t i = 0; i < n; ++i)
        if (a[i] != 0) a[write_ptr++] = a[i];
    while (write_ptr < n) a[write_ptr++] = 0;
}

void lru_buffer_add(struct llist *head, struct llist *node)
{
    if (head == NULL || node == NULL) return;
    while (head->next != NULL) head = head->next;
    head->next = node;
    node->next = NULL;
}

struct llist *lru_buffer_get(struct llist *head, uint32_t key)
{
    while (head != NULL && head->key != key) head = head->next;
    return head;
}

struct packet_q *build_q(uint32_t q_len)
{
    if (q_len == 0) return NULL;
    struct packet_q *pq = malloc(sizeof(struct packet_q));
    if (pq == NULL)
        return NULL;

    pq->q_data = calloc(q_len, sizeof(uint32_t));
    if (pq->q_data == NULL) {
        free(pq);
        return NULL;
    }
    if (pthread_mutex_init(&pq->lock, NULL) != 0) {
        free(pq->q_data);
        free(pq);
        return NULL;
    }

    
    pq->empty = 1;
    pq->head = 0;
    pq->tail=0;
    pq->q_len=q_len;
    return pq;
}

int queue_add(struct packet_q *q, uint32_t data)
{
    int ret_val=0;
    if (q == NULL)
        return -1;
    pthread_mutex_lock(&q->lock);
    if(q->empty == 1) {
        q->q_data[q->tail++]=data;
        q->empty = 0;
    } else {
        if(q->tail == q->head) // List full
            ret_val = -2;
        else
            q->q_data[q->tail++]=data;
    }
    if (q->tail == q->q_len){
        q->tail = 0;
    }
    pthread_mutex_unlock(&q->lock);
    return ret_val;
   
}

int queue_get(struct packet_q *q, uint32_t *data)
{
    int ret_val=0;
    if (q == NULL || data == NULL)
        return -1;
    pthread_mutex_lock(&q->lock);
    if(q->empty == 1) {
        ret_val = -3;

    } else {
        *data = q->q_data[q->head];
        q->head++;
        if (q->head == q->q_len){
            q->head = 0;
        }
        if(q->tail == q->head) // List empty
            q->empty = 1;
    }

    pthread_mutex_unlock(&q->lock);
    return ret_val;
   
}

void q_destory(struct packet_q *q)
{
    if (q == NULL)
        return;
    if(q->q_data != NULL)
        free(q->q_data);
    pthread_mutex_destroy(&q->lock);
    free(q);
}
