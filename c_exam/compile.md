# Building and Testing C Exercises

## Environment

Use Linux or WSL with a C11 compiler, GNU Make, GNU coreutils (`timeout`),
and POSIX threads. On Ubuntu/Debian, install prerequisites if needed:

```sh
sudo apt update
sudo apt install build-essential coreutils
```

On Windows, open a WSL shell and navigate to the checkout. For example,
`C:\work\interview_prep` is `/mnt/c/work/interview_prep` in WSL.
The commands below use a POSIX shell, not PowerShell or native MSVC.
All commands below start in **`c_exam/`**.

## Make targets

```sh
make all                 # Compile learner code only
make test-block1         # Run learner warm-up tests
make test-block3         # Run learner bit tests
make test-block7         # Run learner list/queue tests
make test                # Run all learner suites
make test-solutions      # Run all references against the same tests
make sanitize            # Reference tests with address/undefined sanitizers
make clean               # Remove generated files under build/
```

The default implementation is `exercises/`. Fill in its TODO bodies; the starter
functions exit unsuccessfully with a message. An assertion failure, nonzero
exit, or timeout makes Make fail. Compilation failure also stops the command.
Tests have a 15-second timeout. Override the compiler or timeout as needed:

```sh
make CC=clang test-solutions
make TIMEOUT='timeout 60s' test-block7
make BUILD_DIR=build/learner-sanitize \
    CFLAGS='-std=c11 -Wall -Wextra -Wpedantic -g -fsanitize=address,undefined -fno-omit-frame-pointer' test
```

## Direct compiler commands

```sh
mkdir -p build/exercises
gcc -std=c11 -Wall -Wextra -Wpedantic -g -UNDEBUG -Iinclude \
    exercises/block1.c tests/test_block1.c -o build/exercises/test_block1 && \
    timeout 15s ./build/exercises/test_block1

gcc -std=c11 -Wall -Wextra -Wpedantic -g -UNDEBUG -Iinclude \
    exercises/block3.c tests/test_block3.c -o build/exercises/test_block3 && \
    timeout 15s ./build/exercises/test_block3

gcc -std=c11 -Wall -Wextra -Wpedantic -g -UNDEBUG -Iinclude \
    exercises/block7.c tests/test_block7.c -pthread -o build/exercises/test_block7 && \
    timeout 15s ./build/exercises/test_block7
```

For reference builds, replace `exercises/blockN.c` with `solutions/blockN.c`
and write the executable under `build/solutions/` (create that directory first).
Keep the same test source and `-Iinclude`. Assertions must remain enabled;
the commands enforce that with `-UNDEBUG`.

Make rebuilds on every invocation to pick up flag changes, keeping learner and
reference outputs separate. Pre-refactor local executables have been moved
directly into ignored `build/` and are never used by these targets.
