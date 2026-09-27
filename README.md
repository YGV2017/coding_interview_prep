# Interview Prep

Hands-on coding interview exercises with reusable tests and reference solutions.
Write your own implementation, check it against the tests, and compare your
approach with the solution after your attempt.

Each language has its own folder and build instructions. C is the first set;
more languages can be added in separate top-level folders.

| Language | Topics | Start here |
| --- | --- | --- |
| C | Arrays, strings, bits, linked lists, and a thread-safe queue | [C practice](c_exam/README.md) |

## Quick start

Use a Linux or WSL shell with GCC, GNU Make, and GNU `timeout`:

```sh
cd c_exam
make test-solutions
# Implement exercises/block1.c, then run:
make test-block1
```

Starter files intentionally fail with a TODO message until implemented.
See the [C instructions](c_exam/README.md) and [build guide](c_exam/compile.md)
for prerequisites, exercise contracts, and compiler commands.

## Layout

```text
interview_prep/
├── README.md
└── c_exam/
    ├── README.md
    ├── C_Coding_Interview_Practice_Guide.md
    ├── compile.md
    ├── Makefile
    ├── include/      # Shared interfaces and requirements
    ├── exercises/    # Learner starter files
    ├── tests/        # Reusable test infrastructure
    └── solutions/    # Reference implementations (spoilers)
```

## Practicing and contributing

1. Read the exercise contract and tests.
2. Implement the corresponding file in `exercises/`, keeping the public interface.
3. Run its tests, consider additional edge cases, and explain the complexity.
4. Compare your approach with `solutions/` after your attempt.

For a new language, add a separate top-level folder with a README, exercise
starters, tests, reference solutions, and reproducible build/run instructions.
Add it to the language table above. Keep prompts and tests separate from answers,
and exclude generated binaries from version control.
