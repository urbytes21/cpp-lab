# Exception handling
- We prefer using exceptions with the following reasons:
 - Forces the caller to recognize an error condition and handle it rather than stopping program.
 - Let exceptions propagate in the call stack where they can be handled probably (e.g destroys all the objects in scope error )
 - TBD
- The exception mechanism has a minimal performance cost if no exception is thrown. If an exception is thrown, the cost of the stack traversal and unwinding is roughly comparable to the cost of a function call.

- Design for exception safe:
 - Low/ middle layers: catch and rethrow an exception  if they do not have enough context to handle.  This way, the exceptions will propagate up the call stack.
 - Highest layers: let an unhandled exception terminate a program. (`exit(-1)`)

- Resource Acquisition Is Initialization (RAII) 

