# Bratan: C Utility Library Collection

A collection of **header-only C utility libraries** designed to streamline common programming tasks. These libraries offer clean, self-contained implementations without the need for manual compilation or linking of separate source files.

## Content

* `./headers/data_structures/linkedlist_t.h` – this is a generic singly linked list implementation.
* `./headers/data_structures/queue_t.h` – This is a generic, singly linked list-based queue implementation.
* `./headers/threadpool_t.h` – implementation of a threadpool. **Requires a `queue_t.h`**

# To Do
- [ ] Add proper shutdown logic for ``threadpool_t.h`` inside ``_threadroutine``.