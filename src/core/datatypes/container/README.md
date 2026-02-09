# Containers library
- The Containers library is a generic collection of class templates and algorithms that allow programmers to easilly implement common data structures.
- All container functions can be called concurrently by different threads on different containers
## 1. Sequence Containers
Sequence containers implement data structures which can be accessed sequentially.

|name|description|
|---|---|
|array|fixed-sized inplace contiguous array|
|vector|resizeable contiguous array|
|dequeue|double-ended queue|
|forward_list|singly-linked list|
|list|doubly-linked list|

## 2. Unordered Containers
Unordered associative containers implement unsorted (hashed) data structures that can be quickly searched (O(1) average, O(n) worst-case complexity).
|name|description|
|---|---|
|unordered_map|collection of key-value pairs, hashed by keys, keys are unique|
|unordered_set|collection of unique keys, hashed by keys|

## 3. Adapter Container
**Container adaptors** provide a different interface for **sequential containers**.
|name|description|
|---|---|
|queue|apdapts a container to provide queue (FIFO data structure)|

TBD