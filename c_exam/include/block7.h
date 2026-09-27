#ifndef BLOCK7_H
#define BLOCK7_H
#include <stddef.h>
#include <stdint.h>
#include <pthread.h>

/* Move zeros to the end in place, preserving nonzero order. NULL is a no-op. */
void zero_sort(uint32_t *a, size_t n);

struct llist {
    uint32_t key;
    uint32_t val;
    struct llist *next;
};
/* Append a detached node to a nonempty list. NULL arguments are no-ops.
 * The caller owns all nodes and initializes the first node itself. */
void lru_buffer_add(struct llist *head, struct llist *node);
/* Return the first matching node, or NULL. Do not change the list.
 * Historical names retained: this API is a list exercise, not a full LRU cache.
 * Moving a node to the front would require returning/updating the caller's head. */
struct llist *lru_buffer_get(struct llist *head, uint32_t key);

struct packet_q {
    uint32_t *q_data;
    uint32_t q_len;
    uint32_t head;
    uint32_t tail;
    uint32_t empty;
    pthread_mutex_t lock;
};
/* Allocate a queue with q_len usable slots. Zero capacity or failure -> NULL. */
struct packet_q *build_q(uint32_t q_len);
/* Thread-safe, nonblocking FIFO operations:
 * 0 = success, -1 = invalid pointer, -2 = full (add), -3 = empty (get).
 * A failed get leaves *data unchanged. */
int queue_add(struct packet_q *q, uint32_t data);
int queue_get(struct packet_q *q, uint32_t *data);
/* Free after all threads stop using the queue. NULL is a no-op.
 * Original spelling retained for compatibility with the exercise. */
void q_destory(struct packet_q *q);
#endif
