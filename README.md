# Bratan: C Utility Library Collection

A curated collection of **header-only C utility libraries** designed to simplify common programming tasks. These libraries provide clean, self-contained implementations that do not require manual compilation or linking of separate source files.

## Content

* `headers/data_structures/linkedlist_t.h` – Generic singly linked list implementation.
* `headers/data_structures/queue_t.h` – Generic queue implementation based on a singly linked list.
* `headers/threadpool_t.h` – Threadpool implementation. **Depends on `queue_t.h`**.

### Tests

* `tests` – Contains tests written using the `Unity` test framework.
* `unity` – Unity testing library to run all tests. [GitHub Repository of Unity](https://github.com/ThrowTheSwitch/Unity)
* `run_tests.sh` – Script to run all tests sequentially.

## To Do

* [ ] Implement proper shutdown logic for `threadpool_t.h` inside `_threadroutine`.
