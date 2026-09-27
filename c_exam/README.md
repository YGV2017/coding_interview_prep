# C Interview Practice

Practice C with learner starter files, shared interfaces, and an existing test
harness. Reference implementations live separately in [`solutions/`](solutions/).

## Exercises

| Block | Tasks | Contract | Starter |
| --- | --- | --- | --- |
| 1 | Array maximum, string reversal, count bits, swap, stable deduplication | [block1.h](include/block1.h) | [block1.c](exercises/block1.c) |
| 3 | Power of two, population count, reverse bits, extract/replace bit fields | [block3.h](include/block3.h) | [block3.c](exercises/block3.c) |
| 7 | Move zeros, linked-list append/lookup, thread-safe bounded FIFO queue | [block7.h](include/block7.h) | [block7.c](exercises/block7.c) |

Original block filenames are retained. The [practice guide](C_Coding_Interview_Practice_Guide.md)
contains additional prompts and a study schedule; only these three blocks have
starter files, tests, and solutions. The guide's schedule numbering is independent
of the filenames.

## Workflow

Use Linux or WSL with GCC, GNU Make, and GNU `timeout`; block 7 uses POSIX
threads. See [compile.md](compile.md) for setup and direct compiler commands.
Run these commands from `c_exam/`:

```sh
make test-solutions   # Check the reference implementations
make all             # Compile all learner files without running tests
# Edit exercises/block1.c, then:
make test-block1
make test-block3
make test-block7
make test            # Run all learner suites; stop on the first failure
make sanitize        # Reference suites with AddressSanitizer and UBSan
```

Every starter function exits with a TODO message until implemented. Initial test
failures are expected. Keep signatures consistent with `include/` and use the
existing files in `tests/` to check your work. These tests are not exhaustive;
consider additional edge cases. Compile exactly one implementation per executable.

Builds go under ignored `build/exercises/`, `build/solutions/`, and
`build/sanitize/` directories. Each suite has a 15-second timeout to catch hanging
queue implementations. Use `make TIMEOUT='timeout 60s' test-block7` if needed.

## Contracts and limitations

- Block 1 preserves first-occurrence order when removing duplicates from unsorted
  arrays; only the returned prefix is meaningful. `max_array` returns `-1` for
  empty/NULL input, an ambiguous sentinel if the maximum itself is `-1`.
- Block 3 uses 32-bit values. Valid fields satisfy `start < 32`, `width >= 1`,
  and `width <= 32 - start`, including full-width fields.
- The historical `lru_buffer_*` names in block 7 describe append and lookup on a
  caller-owned linked list. Lookup preserves the list. A full LRU cache with
  move-to-front behavior needs an API that can update the caller's head.
- The queue uses all allocated slots and returns immediately when full or empty;
  acquiring its mutex may block. Stop/join all users before `q_destory` (original
  spelling retained). The concurrency test transfers 100,000 values between one
  producer and one consumer.

## Files

- `exercises/`: learner starter files to edit.
- `include/`: shared declarations and behavior contracts.
- `tests/`: suites reused for both learners and reference implementations.
- `solutions/`: implementations and [solution notes](solutions/README.md).
- `compile.md`: build, test, and sanitizer commands.
- `C_Coding_Interview_Practice_Guide.md`: broader preparation material.
