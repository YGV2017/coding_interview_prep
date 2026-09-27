# Reference Solutions

Spoilers: attempt the matching file in `../exercises/` before reading these files.
Run `make test-solutions` from `c_exam/`, or `make sanitize` for memory and
undefined-behavior checks.

These implementations come from the original practice code, with debug remnants
removed and correctness/portability fixes applied. Full-width bit operations use
unsigned masks, list lookup preserves all nodes, and queues reject zero capacity.

| File | Approach and complexity |
| --- | --- |
| `block1.c` | Linear maximum/string reversal; fixed 32-bit counting; constant-time swap. Stable deduplication scans the retained prefix: O(n²) time, O(1) extra space. |
| `block3.c` | Fixed-width bit scans and unsigned masks: O(1) time and space for 32-bit inputs. |
| `block7.c` | Stable zero compaction: O(n) time, O(1) space. List append/lookup: O(n) time. Queue add/get: O(1) work under a mutex; O(capacity) storage. |

The list functions retain the existing API and do not implement eviction or
recency tracking. Queue operations do not wait for space/data, although acquiring
the mutex may block. The producer/consumer test retries to exercise FIFO behavior.
