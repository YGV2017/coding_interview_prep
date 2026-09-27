# C Coding Interview Practice Guide

A focused practice repository for experienced software engineers preparing for a **C programming interview**, especially for systems, embedded, firmware, low-level software, and hands-on software architecture roles.

This guide is designed for engineers who already know how to program but may not have written C recently.

The emphasis is on:

- restoring C fluency quickly
- writing correct code under interview pressure
- pointers and memory
- bit manipulation
- core data structures
- systems-oriented coding
- concurrency basics
- defensive coding
- explaining design decisions like a senior engineer

---

## Recommended Practice Method

For each exercise:

1. Read the problem.
2. Clarify assumptions before coding.
3. State expected time and space complexity.
4. Implement it in C.
5. Compile with warnings enabled.
6. Test edge cases.
7. Explain the design as if speaking to an interviewer.
8. Consider how the solution changes for embedded or concurrent systems.

Recommended compile command:

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic -g solution.c -o solution
```

Recommended sanitizer build:

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic \
    -fsanitize=address,undefined -g solution.c -o solution
```

For POSIX thread exercises:

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic \
    -fsanitize=address,undefined -g solution.c -pthread -o solution
```

---

# Part 1 â€” C Warm-Up

These problems are intended to restore coding muscle memory.

## 1. Second Largest Distinct Value

```c
int find_second_largest(const int *arr, size_t n);
```

Requirements:

- return the second-largest **distinct** value
- do not sort
- do not modify the input
- aim for `O(n)` time and `O(1)` extra space
- decide how the API should report that no second distinct value exists

Example:

```text
Input:  [7, 3, 9, 9, 5, 7]
Output: 7
```

Interview follow-ups:

- What should happen for `{5, 5, 5}`?
- What if the array contains `INT_MIN`?
- Would you redesign the API?

---

## 2. Reverse a String In Place

```c
void reverse_string(char *str);
```

Requirements:

- reverse a null-terminated string in place
- use `O(1)` additional memory
- handle the empty string

Examples:

```text
"hello" -> "olleh"
""      -> ""
"a"     -> "a"
```

Follow-ups:

- What happens if `str == NULL`?
- What is the time complexity?
- How would this differ for UTF-8 text?

---

## 3. Swap Two Integers

```c
void swap_int(int *a, int *b);
```

Requirements:

- swap the values using pointers
- define behavior for null pointers

Follow-ups:

- Is XOR swap a good idea?
- What happens if `a == b`?

---

## 4. Maximum Value in an Array

```c
int max_array(const int *arr, size_t n);
```

Requirements:

- return the maximum value
- do not modify the input
- decide how to handle `n == 0`

Follow-ups:

- Is returning a sentinel safe?
- Would an output parameter be better?

---

## 5. Remove Duplicates from a Sorted Array

```c
size_t remove_duplicates(int *arr, size_t n);
```

Requirements:

- modify the array in place
- preserve order
- return the new logical length
- use `O(1)` extra memory

Example:

```text
Input:  [1, 1, 2, 2, 2, 5, 7, 7]
Output: [1, 2, 5, 7]
Length: 4
```

---

# Part 2 â€” Pointers, Memory, and Strings

## 6. Implement `strdup`

```c
char *my_strdup(const char *src);
```

Requirements:

- allocate enough memory
- copy the complete string
- include the null terminator
- return `NULL` on allocation failure

Follow-ups:

- Who owns the returned memory?
- How would you avoid integer overflow in allocation-size calculations?

---

## 7. Implement `strlen`

```c
size_t my_strlen(const char *str);
```

Requirements:

- do not use the standard library `strlen`
- implement once using indexing
- implement again using pointer arithmetic

---

## 8. Implement `memcpy`

```c
void *my_memcpy(void *dst, const void *src, size_t n);
```

Requirements:

- copy exactly `n` bytes
- return `dst`

Follow-ups:

- What happens if memory regions overlap?
- When should `memmove` be used instead?
- What alignment optimizations could a production implementation use?

---

## 9. Implement `memmove`

```c
void *my_memmove(void *dst, const void *src, size_t n);
```

Requirements:

- correctly handle overlapping buffers

Test:

```text
buffer = "abcdef"
move bytes [0..3] to [2..5]
```

Be prepared to explain why copy direction matters.

---

## 10. Reverse a Singly Linked List

```c
typedef struct node {
    int value;
    struct node *next;
} node_t;

node_t *reverse_list(node_t *head);
```

Requirements:

- iterative implementation
- `O(n)` time
- `O(1)` extra space

Follow-ups:

- Write a recursive version.
- What is the stack-space cost?
- How would you detect a cycle first?

---

# Part 3 â€” Bit Manipulation and Low-Level C

Create a header such as:

```c
#ifndef BIT_EXERCISES_H
#define BIT_EXERCISES_H

#include <stdbool.h>
#include <stdint.h>

bool is_power_of_two(uint32_t x);

unsigned count_set_bits(uint32_t x);

uint32_t reverse_bits(uint32_t x);

uint32_t extract_bits(
    uint32_t x,
    unsigned start,
    unsigned width);

uint32_t set_bit_field(
    uint32_t x,
    unsigned start,
    unsigned width,
    uint32_t value);

#endif
```

---

## 11. Power of Two

```c
bool is_power_of_two(uint32_t x);
```

Examples:

```text
0  -> false
1  -> true
2  -> true
8  -> true
10 -> false
```

Try to solve it without looping over all 32 bits.

---

## 12. Count Set Bits

```c
unsigned count_set_bits(uint32_t x);
```

Examples:

```text
0x00000000 -> 0
0x00000001 -> 1
0x0000000F -> 4
0xFFFFFFFF -> 32
```

Try at least two implementations.

---

## 13. Reverse 32 Bits

```c
uint32_t reverse_bits(uint32_t x);
```

Example:

```text
0x00000001 -> 0x80000000
```

Bit 0 becomes bit 31, bit 1 becomes bit 30, and so on.

---

## 14. Extract a Bit Field

```c
uint32_t extract_bits(
    uint32_t x,
    unsigned start,
    unsigned width);
```

The extracted value must be right-aligned.

Example:

```text
x     = 0b11010110
start = 2
width = 3

result = 0b101
```

Assume:

```text
start < 32
width >= 1
start + width <= 32
```

Then consider what additional checks a production API should make.

---

## 15. Replace a Bit Field

```c
uint32_t set_bit_field(
    uint32_t x,
    unsigned start,
    unsigned width,
    uint32_t value);
```

Requirements:

- modify only the selected bit field
- preserve all other bits
- use only the lowest `width` bits of `value`

This models modification of fields inside hardware registers.

Follow-ups:

- How would you support `width == 32` safely?
- What shifting expressions could cause undefined behavior?

---

## Low-Level Topics to Explain

Be able to explain:

- signed vs unsigned integers
- integer promotion
- fixed-width integer types
- left and right shifts
- overflow behavior
- endian order
- alignment
- structure padding
- memory-mapped I/O
- why `1U << n` is often preferable to `1 << n`

---

# Part 4 â€” Core Interview Algorithms

## 16. Binary Search

```c
int binary_search(
    const int *arr,
    size_t n,
    int target);
```

Requirements:

- sorted ascending input
- `O(log n)` time

Avoid midpoint overflow.

Prefer:

```c
mid = low + (high - low) / 2;
```

rather than:

```c
mid = (low + high) / 2;
```

Follow-ups:

- Why can the second expression overflow?
- How would you find the first occurrence of a duplicate value?
- How would you return an insertion position?

---

## 17. Move Zeros to the End

```c
void move_zeros(int *arr, size_t n);
```

Requirements:

- preserve the relative order of non-zero values
- operate in place
- aim for `O(n)` time

Example:

```text
[0, 3, 0, 4, 5, 0, 2]

->

[3, 4, 5, 2, 0, 0, 0]
```

---

## 18. Detect a Linked-List Cycle

```c
bool has_cycle(const node_t *head);
```

Requirements:

- `O(n)` time
- `O(1)` additional memory

Follow-ups:

- How would you find the cycle entry point?
- Why does Floyd's algorithm work?

---

## 19. Palindrome Check

```c
bool is_palindrome(const char *str);
```

Start with a simple ASCII version.

Then discuss:

- case sensitivity
- spaces
- punctuation
- UTF-8

---

# Part 5 â€” Systems Coding Problems

These problems are especially useful for embedded, platform, firmware, networking, driver, and systems software interviews.

---

## 20. Ring Buffer

Design:

```c
#define RB_SIZE 128

typedef struct {
    uint32_t data[RB_SIZE];
    size_t head;
    size_t tail;
} ring_buffer_t;
```

Implement:

```c
void rb_init(ring_buffer_t *rb);

bool rb_empty(const ring_buffer_t *rb);

bool rb_full(const ring_buffer_t *rb);

bool rb_push(ring_buffer_t *rb, uint32_t value);

bool rb_pop(ring_buffer_t *rb, uint32_t *value);
```

Requirements:

- `O(1)` push and pop
- no dynamic memory allocation

Design questions:

- How will you distinguish full from empty?
- Will you waste one slot?
- Would you add a `count` field?
- What happens when indices wrap?
- What if `RB_SIZE` is a power of two?
- Can modulo be replaced with masking?

Possible optimization:

```c
next = (index + 1) & (RB_SIZE - 1);
```

This works only when the size is a power of two.

---

## 21. Binary Packet Parser

Assume this packet format:

```text
+------+--------+----------+------+
| TYPE | LENGTH | PAYLOAD  | CRC  |
+------+--------+----------+------+
| 1 B  | 2 B    | N bytes  | 2 B  |
+------+--------+----------+------+
```

Length is encoded in network byte order.

Design:

```c
typedef struct {
    uint8_t type;
    uint16_t length;
    const uint8_t *payload;
    uint16_t crc;
} packet_t;

int parse_packet(
    const uint8_t *buffer,
    size_t buffer_len,
    packet_t *packet);
```

Requirements:

- validate all lengths before dereferencing
- reject truncated packets
- avoid unaligned integer reads
- handle endian conversion
- clearly define payload ownership

Questions to ask yourself:

- What is the minimum packet length?
- Can `length + header_size` overflow?
- Should payload point into the original buffer or be copied?
- What happens if the caller frees the source buffer?
- Should trailing bytes be allowed?

---

## 22. Fixed-Size Memory Pool

Design a pool for fixed-size objects.

```c
#define BLOCK_SIZE  128
#define BLOCK_COUNT 32
```

Implement:

```c
void pool_init(memory_pool_t *pool);

void *pool_alloc(memory_pool_t *pool);

void pool_free(memory_pool_t *pool, void *ptr);
```

Consider:

- free-list design
- alignment
- deterministic allocation
- invalid free
- double free
- thread safety
- fragmentation

Interview discussion:

Why might an embedded system prefer a memory pool over `malloc`?

---

## 23. State Machine

```c
typedef enum {
    STATE_OFF,
    STATE_STARTING,
    STATE_RUNNING,
    STATE_ERROR
} state_t;

typedef enum {
    EVENT_START,
    EVENT_STARTED,
    EVENT_FAILURE,
    EVENT_RESET
} event_t;
```

Implement:

```c
int handle_event(
    system_context_t *ctx,
    event_t event);
```

Requirements:

- clearly define valid transitions
- reject invalid transitions
- avoid hidden global state

Follow-ups:

- switch statement or transition table?
- where should transition side effects happen?
- how would you test every transition?

---

## 24. Reference Counting

```c
typedef struct {
    unsigned ref_count;
    /* object data */
} object_t;
```

Implement:

```c
void object_get(object_t *obj);

void object_put(object_t *obj);
```

Assume the object should be destroyed when the reference count reaches zero.

Follow-ups:

- What happens if two threads update the reference count?
- How could atomics help?
- What problem remains if references form cycles?
- What happens on underflow?

---

# Part 6 â€” Concurrency

## Core Concepts

A race condition occurs when multiple execution contexts access shared state concurrently and the correctness depends on timing.

Example:

```c
counter++;
```

Conceptually, this can involve:

```text
load
increment
store
```

Two threads can interleave those operations and lose an increment.

---

## Mutex

Use a mutex when several operations must execute as one protected critical section.

```c
pthread_mutex_lock(&mutex);

/* access shared state */

pthread_mutex_unlock(&mutex);
```

Typical use:

- queues
- linked data structures
- multiple related shared fields
- maintaining invariants

Keep critical sections as short as possible.

---

## Semaphore

Semaphores are often useful for counting resources or events.

Typical producer/consumer queue:

```text
free_slots = capacity
items      = 0
```

Producer:

```text
wait(free slot)
lock queue
insert item
unlock queue
signal(item available)
```

Consumer:

```text
wait(item available)
lock queue
remove item
unlock queue
signal(free slot)
```

---

## Condition Variable

Use a condition variable when a thread should sleep until protected state changes.

Conceptually:

```c
pthread_mutex_lock(&mutex);

while (!condition)
    pthread_cond_wait(&cond, &mutex);

/* condition is true */

pthread_mutex_unlock(&mutex);
```

Use a `while`, not an `if`, because wakeups do not guarantee that the condition remains true.

---

## Atomics

C11 atomics:

```c
#include <stdatomic.h>

atomic_int counter = 0;

atomic_fetch_add(&counter, 1);
```

Useful operations include:

```c
atomic_load(&value);
atomic_store(&value, new_value);
atomic_fetch_add(&value, 1);
atomic_fetch_sub(&value, 1);
atomic_exchange(&value, new_value);
```

Also understand compare-and-exchange:

```c
atomic_compare_exchange_strong(
    &value,
    &expected,
    desired);
```

High-level rule:

- use atomics for simple shared state when appropriate
- use a mutex when several operations must preserve a larger invariant

---

## Acquire / Release

Know the basic concept.

Producer:

```c
data = 42;

atomic_store_explicit(
    &ready,
    true,
    memory_order_release);
```

Consumer:

```c
if (atomic_load_explicit(
        &ready,
        memory_order_acquire)) {

    use(data);
}
```

Acquire/release ordering is used to establish visibility and ordering between threads.

You do not need to implement sophisticated lock-free structures to understand this concept.

---

## `volatile`

`volatile` does **not** make normal shared variables thread-safe.

Example:

```c
volatile int counter;
counter++;
```

This can still race.

`volatile` is commonly important for:

- memory-mapped hardware registers
- hardware state that can change outside normal code execution
- certain ISR/shared-state patterns

Remember:

> `volatile` controls compiler treatment of accesses. It does not provide atomicity, mutual exclusion, or thread synchronization.

---

# Part 7 â€” Thread-Safe Ring Buffer

Take the ring-buffer exercise and make it safe for multiple producers and consumers.

Possible structure:

```c
typedef struct {
    uint32_t data[RB_SIZE];

    size_t head;
    size_t tail;

    pthread_mutex_t mutex;

    sem_t free_slots;
    sem_t available_items;
} thread_safe_queue_t;
```

Implement:

```c
int queue_init(thread_safe_queue_t *q);

int queue_push(
    thread_safe_queue_t *q,
    uint32_t value);

int queue_pop(
    thread_safe_queue_t *q,
    uint32_t *value);

void queue_destroy(thread_safe_queue_t *q);
```

Be prepared to explain:

- what the mutex protects
- what each semaphore represents
- why semaphore wait should occur before acquiring the mutex
- what could deadlock
- what happens if a thread exits while holding the lock
- whether a single-producer/single-consumer queue could avoid the mutex

---

# Part 8 â€” Debugging and C Traps

For each snippet, explain the problem before compiling it.

---

## Returning Stack Memory

```c
int *get_value(void)
{
    int value = 10;
    return &value;
}
```

What is wrong?

---

## Modifying a String Literal

```c
char *text = "hello";
text[0] = 'H';
```

What is wrong?

---

## Use After Free

```c
char *p = malloc(100);

free(p);

p[0] = 'A';
```

What is wrong?

---

## Double Free

```c
free(ptr);
free(ptr);
```

What can happen?

---

## Incorrect `sizeof`

```c
void clear_buffer(int *buffer)
{
    memset(buffer, 0, sizeof(buffer));
}
```

Why is this probably wrong?

---

## Macro Side Effects

```c
#define SQUARE(x) ((x) * (x))

int y = SQUARE(i++);
```

Why is this unsafe?

---

## Signed / Unsigned Comparison

```c
int index = -1;
size_t length = 10;

if (index < length) {
    /* ... */
}
```

What conversion occurs?

---

## Shift Edge Cases

Discuss these:

```c
1 << 31
1U << 31
1U << 32
```

Which expressions are safe or unsafe for common 32-bit integer types, and why?

---

# Part 9 â€” Mock Interview

Run this section under time pressure.

Do not search online while solving.

---

## Interview Problem 1 â€” Warm-Up

Implement:

```c
void move_zeros(int *arr, size_t n);
```

Target time:

**10â€“15 minutes**

After coding, explain:

- complexity
- edge cases
- whether order is preserved

---

## Interview Problem 2 â€” Data Structure

Implement a fixed-size ring buffer.

Target time:

**20â€“25 minutes**

After coding, answer:

- empty/full representation
- wrap-around
- API error handling
- complexity

---

## Interview Problem 3 â€” Systems Problem

Make the queue safe for a producer and consumer running concurrently.

Target time:

**30â€“40 minutes**

Discuss:

- mutex
- semaphore
- condition variable
- atomics
- shutdown behavior
- blocking vs non-blocking APIs

---

## Interview Problem 4 â€” Packet Parsing

Implement a defensive binary packet parser.

Target time:

**25â€“30 minutes**

The interviewer should deliberately provide:

- truncated packet
- invalid length
- maximum length
- empty payload
- endian mismatch
- unaligned buffer address

---

# Part 10 â€” Senior-Level Follow-Up Questions

After every coding problem, practice answering questions such as:

### Correctness

- What are the edge cases?
- What assumptions are you making?
- How do you represent an error?
- What happens on null input?

### Complexity

- What is the time complexity?
- What is the memory complexity?
- Can either be improved?

### Memory

- Who owns this memory?
- Who frees it?
- Can the pointer outlive its backing storage?
- What alignment assumptions exist?

### Concurrency

- What happens if two threads call this simultaneously?
- What exactly is protected by the lock?
- Could you reduce lock contention?
- Would an atomic operation be enough?
- What memory ordering is needed?

### Embedded Systems

- Can this allocate dynamically?
- Can it block?
- Can it execute from an ISR?
- Is execution time deterministic?
- Are hardware registers involved?
- Is endian conversion required?

### API Design

- Is the contract obvious?
- Are invalid states representable?
- Should errors use return codes, enums, or output parameters?
- Can the API be misused easily?

---

# Part 11 â€” C Interview Checklist

Before submitting code, check:

## Input

- [ ] null pointers handled or documented
- [ ] length validated
- [ ] empty input considered
- [ ] integer ranges considered

## Memory

- [ ] allocation checked
- [ ] ownership clear
- [ ] no out-of-bounds access
- [ ] no dangling pointers
- [ ] no double free
- [ ] overlap handled where relevant

## Arithmetic

- [ ] no obvious integer overflow
- [ ] signed/unsigned conversion considered
- [ ] shift ranges valid
- [ ] no unsafe mask construction

## Concurrency

- [ ] shared state identified
- [ ] race conditions considered
- [ ] lock scope minimized
- [ ] deadlock risk considered
- [ ] `volatile` not used as a synchronization substitute

## Code Quality

- [ ] meaningful names
- [ ] clear control flow
- [ ] no unnecessary cleverness
- [ ] complexity can be explained
- [ ] behavior under failure is defined

---

# Suggested One-Day Preparation Order

For engineers preparing under significant time pressure:

| Block | Focus |
|---|---|
| 1 | C warm-up |
| 2 | pointers, strings, memory |
| 3 | bit manipulation and low-level C |
| 4 | arrays, linked lists, binary search |
| 5 | ring buffer and packet parser |
| 6 | C traps and debugging |
| 7 | concurrency, mutexes, semaphores, atomics |
| 8 | full mock interview |

A good target is roughly:

```text
25% review
75% writing and compiling code
```

Do not spend the entire preparation session reading.

Write code.

Compile it.

Break it.

Fix it.

Explain it.

---

# Repository Practice Files

The runnable exercises are documented in [the C README](README.md), with
learner files in `exercises/`, shared contracts in `include/`, reusable tests in
`tests/`, and reference answers in `solutions/`. See [compile.md](compile.md)
for commands that build these files together. The single-file commands earlier
in this guide are for standalone programs with their own `main` function.

Only blocks 1, 3, and 7 currently have implementations and tests. Other prompts
in this guide are additional practice ideas. The schedule above is a study plan;
its block numbering does not map directly to the existing filenames.

---

# Final Advice

In a senior C interview, producing the correct answer is only part of the evaluation.

Strong candidates also communicate:

- assumptions
- ownership
- invariants
- failure behavior
- edge cases
- complexity
- concurrency implications
- hardware and portability concerns

Avoid clever code unless it improves the design.

Simple, correct, explainable C is usually better interview code than a compact trick that is difficult to reason about.
