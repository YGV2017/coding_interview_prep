/* Existing block 7 harness: arrays, linked lists, and a POSIX FIFO queue. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include <pthread.h>

#include "block7.h"

/* ----------------------------------------------------------------------- */
/* Small test framework                                                    */
/* ----------------------------------------------------------------------- */

static int g_tests_run = 0;
static int g_tests_failed = 0;

#define CHECK(cond)                                                       \
    do {                                                                  \
        g_tests_run++;                                                    \
        if (!(cond)) {                                                    \
            g_tests_failed++;                                             \
            printf("  FAIL: %s (line %d)\n", #cond, __LINE__);            \
        }                                                                 \
    } while (0)

#define CHECK_MSG(cond, msg)                                              \
    do {                                                                  \
        g_tests_run++;                                                    \
        if (!(cond)) {                                                    \
            g_tests_failed++;                                             \
            printf("  FAIL: %s -> %s (line %d)\n", #cond, (msg),          \
                   __LINE__);                                             \
        }                                                                 \
    } while (0)

/* ----------------------------------------------------------------------- */
/* Q1: zero_sort tests                                                     */
/* ----------------------------------------------------------------------- */

static void print_arr(const uint32_t *a, uint32_t n)
{
    uint32_t i;
    printf("    [");
    for (i = 0; i < n; i++)
        printf("%u%s", a[i], (i + 1 < n) ? ", " : "");
    printf("]\n");
}

/* Helper: verify that non-zero elements are in their original relative order
 * and that all zeros are at the tail. */
static int verify_zero_sort(const uint32_t *before,
                            const uint32_t *after,
                            uint32_t n)
{
    uint32_t i, j = 0;

    /* non-zero prefix must match original non-zero sequence */
    for (i = 0; i < n; i++) {
        if (before[i] == 0)
            continue;
        /* find it as the next non-zero in `after` */
        if (j >= n || after[j] != before[i])
            return 0;
        j++;
    }
    /* everything after the last non-zero must be zero */
    while (j < n) {
        if (after[j] != 0)
            return 0;
        j++;
    }
    return 1;
}

static void test_zero_sort(void)
{
    printf("Testing zero_sort...\n");

    {
        uint32_t a[] = {0, 1, 0, 3, 12};
        uint32_t orig[] = {0, 1, 0, 3, 12};
        uint32_t n = 5;
        zero_sort(a, n);
        print_arr(a, n);
        CHECK_MSG(memcmp(a, (uint32_t[]){1, 3, 12, 0, 0},
                         sizeof(a)) == 0,
                  "expected [1,3,12,0,0]");
        CHECK(verify_zero_sort(orig, a, n));
    }

    {
        /* no zeros -> unchanged */
        uint32_t a[] = {1, 2, 3, 4};
        uint32_t orig[] = {1, 2, 3, 4};
        uint32_t n = 4;
        zero_sort(a, n);
        print_arr(a, n);
        CHECK_MSG(memcmp(a, orig, sizeof(a)) == 0, "no-op expected");
    }

    {
        /* all zeros -> unchanged */
        uint32_t a[] = {0, 0, 0};
        uint32_t n = 3;
        zero_sort(a, n);
        print_arr(a, n);
        CHECK(memcmp(a, (uint32_t[]){0, 0, 0}, sizeof(a)) == 0);
    }

    {
        /* trailing zeros stay, leading run collapses */
        uint32_t a[] = {0, 0, 5, 0, 6, 0};
        uint32_t orig[] = {0, 0, 5, 0, 6, 0};
        uint32_t n = 6;
        zero_sort(a, n);
        print_arr(a, n);
        CHECK_MSG(memcmp(a, (uint32_t[]){5, 6, 0, 0, 0, 0},
                         sizeof(a)) == 0,
                  "expected [5,6,0,0,0,0]");
        CHECK(verify_zero_sort(orig, a, n));
    }

    {
        /* single element */
        uint32_t a[] = {0};
        zero_sort(a, 1);
        CHECK(a[0] == 0);
    }

    /* Degenerate inputs must not crash: */
    zero_sort(NULL, 0);
    {
        uint32_t a[] = {1, 2, 3};
        zero_sort(a, 0);   /* n == 0 -> no-op */
        CHECK(memcmp(a, (uint32_t[]){1, 2, 3}, sizeof(a)) == 0);
    }

    printf("zero_sort tests done.\n");
}

/* ----------------------------------------------------------------------- */
/* Q2: LRU linked-list tests                                               */
/* ----------------------------------------------------------------------- */

static struct llist *make_node(uint32_t key, uint32_t val)
{
    struct llist *n = malloc(sizeof(struct llist));
    assert(n != NULL);
    n->key = key;
    n->val = val;
    n->next = NULL;
    return n;
}

static void free_list(struct llist *head)
{
    while (head) {
        struct llist *n = head->next;
        free(head);
        head = n;
    }
}

static uint32_t list_len(struct llist *head)
{
    uint32_t c = 0;
    while (head) {
        c++;
        head = head->next;
    }
    return c;
}

static void test_lru(void)
{
    printf("Testing lru_buffer_add / lru_buffer_get...\n");

    /* build a list 1 -> 2 -> 3 */
    struct llist *head = make_node(1, 100);
    lru_buffer_add(head, make_node(2, 200));
    lru_buffer_add(head, make_node(3, 300));

    CHECK(list_len(head) == 3);
    CHECK(head->key == 1);          /* add appends to the tail */
    CHECK(head->next->key == 2);
    CHECK(head->next->next->key == 3);

    struct llist *tail = head->next->next;

    /* find the tail node */
    {
        struct llist *found = lru_buffer_get(head, 3);
        CHECK(found != NULL);
        CHECK(found == tail);
        CHECK(found->val == 300);
    }

    /* find the middle node */
    {
        struct llist *found = lru_buffer_get(head, 2);
        CHECK(found != NULL);
        CHECK(found->val == 200);
    }

    /* miss returns NULL */
    CHECK(lru_buffer_get(head, 999) == NULL);

    CHECK(lru_buffer_get(NULL, 1) == NULL);
    CHECK(list_len(head) == 3);
    CHECK(head->next->next == tail);
    free_list(head);
    printf("lru tests done.\n");
}

/* ----------------------------------------------------------------------- */
/* Q3: thread-safe packet queue tests                                      */
/* ----------------------------------------------------------------------- */

static void test_queue_basic(void)
{
    printf("Testing packet queue (single-threaded)...\n");

    CHECK(build_q(0) == NULL);
    CHECK(queue_add(NULL, 1) == -1);
    CHECK(queue_get(NULL, NULL) == -1);
    struct packet_q *q = build_q(4);
    assert(q != NULL);
    CHECK(queue_get(q, NULL) == -1);
    uint32_t v = 0;

    /* empty queue: get fails */
    CHECK(queue_get(q, &v) != 0);

    /* add/get preserves FIFO order */
    CHECK(queue_add(q, 10) == 0);
    CHECK(queue_add(q, 20) == 0);
    CHECK(queue_add(q, 30) == 0);

    CHECK(queue_get(q, &v) == 0);
    CHECK(v == 10);
    CHECK(queue_get(q, &v) == 0);
    CHECK(v == 20);
    CHECK(queue_get(q, &v) == 0);
    CHECK(v == 30);

    /* drained -> empty again */
    CHECK(queue_get(q, &v) != 0);

    q_destory(q);
    printf("queue basic tests done.\n");
}

static void test_queue_wraparound(void)
{
    printf("Testing packet queue wraparound...\n");

    struct packet_q *q = build_q(3);
    assert(q != NULL);

    /* fill, drain, refill to force head/tail wraparound */
    CHECK(queue_add(q, 1) == 0);
    CHECK(queue_add(q, 2) == 0);
    CHECK(queue_add(q, 3) == 0);
    CHECK(queue_add(q, 99) == -2);

    uint32_t v;
    CHECK(queue_get(q, &v) == 0 && v == 1);
    CHECK(queue_get(q, &v) == 0 && v == 2);

    /* insert more to wrap */
    CHECK(queue_add(q, 4) == 0);
    CHECK(queue_add(q, 5) == 0);

    CHECK(queue_get(q, &v) == 0 && v == 3);
    CHECK(queue_get(q, &v) == 0 && v == 4);
    CHECK(queue_get(q, &v) == 0 && v == 5);
    CHECK(queue_get(q, &v) != 0);

    q_destory(q);
    printf("queue wraparound tests done.\n");
}

/* --- Producer/consumer concurrency test --- */

#define PC_ITEMS  100000
#define PC_QCAP   128

static struct packet_q *g_pc_q;

static uint32_t       g_produced = 0;
static int            g_cons_err = 0;

static void *producer(void *arg)
{
    uint32_t i;
    (void)arg;
    for (i = 0; i < PC_ITEMS; i++) {
        /* retry until there is space */
        while (queue_add(g_pc_q, i) != 0) {
            /* busy-wait; a real impl would use a condvar */
        }
    }
    return NULL;
}

static void *consumer(void *arg)
{
    uint32_t v;
    (void)arg;
    while (g_produced < PC_ITEMS) {
        if (queue_get(g_pc_q, &v) == 0) {
            if (v != g_produced) {
                g_cons_err = 1;

            }
            g_produced++;
        }

    }
    return NULL;
}

static void test_queue_threaded(void)
{

    printf("Testing packet queue (producer/consumer)...\n");

    g_pc_q = build_q(PC_QCAP);
    assert(g_pc_q != NULL);
    g_produced = 0;
    g_cons_err = 0;
    pthread_t tp, tc;
    if (pthread_create(&tp, NULL, producer, NULL) != 0) exit(EXIT_FAILURE);
    if (pthread_create(&tc, NULL, consumer, NULL) != 0) exit(EXIT_FAILURE);
    pthread_join(tp, NULL);
    pthread_join(tc, NULL);

    CHECK_MSG(g_cons_err == 0, "FIFO order violated across threads");
    CHECK_MSG(g_produced == PC_ITEMS, "lost or duplicated items");

    q_destory(g_pc_q);
    printf("queue threaded tests done.\n");
}

/* ----------------------------------------------------------------------- */

int main(void)
{
    printf("=== Running block7 tests ===\n\n");

    test_zero_sort();
    printf("\n");
    test_lru();
    printf("\n");
    test_queue_basic();
    printf("\n");
    test_queue_wraparound();
    printf("\n");
    test_queue_threaded();

    printf("\n=== Summary: %d checks, %d failed ===\n",
           g_tests_run, g_tests_failed);
    return g_tests_failed == 0 ? 0 : 1;
}
