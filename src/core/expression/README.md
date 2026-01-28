# Theory

## 1. Lambda Expressions
- In C++11 and later, lambda is a convenient way of defining an anonymous function object right at the location where it's involked or passed as an argument to a function.

- Syntax:
```cpp
[=] () mutable throw() -> int
{
    int n = x + y;
    return n;
}

```
- `[=]`: capture clause a.k.a lambda introducer
- `()`: (O) pararam list a.k.a lambda declarator
- `mutable`: (O)
- `throw()`: (O)
- `-> int`: (O) trailing-return-type
- body

### 1.1 Capture Clause
- It uses to introduce new variables in its body, specifics which vars are captured, and whether the capture is `by value[=]` or `by reference [&]`. 
- An empty capture clause `[]` indicates that the body accesses no vars in the enclosing scope.
- An identifier or `this` cannot appear more than once in a capture scope.
- Since C++14, we can introduce and initialize new vars in the capture scope.
- E.g.
```cpp
int a{};
int b{};

auto f = []{    // no capture
    return 1; 
}

auto f0 = [a]{   // capture by value
    return a+1;
}

auto f1 = [&a]{
    return a+=1;    // capture by reference (a = 1)
}

auto f2 = [=]{
    return a + b; // all capture by value
}

auto f3 = [&]{
    a+=1;
    b+=1;
    return a + b; // all capture by reference
}

auto f4 = [int a{}]{    // no capture
    return a; 
}
```

## 2. Function Pointers
- A function pointer is a pointer variable that stores the address of a function with a specific return type and parameter list.
- Syntax:
```cpp
// Declare
return_type (*FuncPtr) (parameter type, ....);

// Referencing: Assigning a function’s address to the function pointer.
FuncPtr = function_name; 

// 3) Dereferencing: Invoking the function using the pointer. The dereference operator * is optional during function calls.
FuncPtr(10, 20);     // Preferred
(*FuncPtr)(10, 20); // Also valid
```

- e.g.
```cpp
void print(int a){
    std::cout << a;
}

void (*FuncPtr)(int a);
FuncPtr = print;
FuncPtr(1);
```

