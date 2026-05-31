
---
# Functions
Functions are self-contained blocks of code designed to perform specific tasks. They promote code reusability, modularity, and abstraction.
Functions can participate in polymorphism through:
- **Compile-time polymorphism (Static Polymorphism)**
  - Function overloading
  - Operator overloading
  - Function templates
- **Runtime polymorphism**
  - Virtual functions

---
## 1. Function Overloading
- `function overloading` allows us to create multiple functions with the same name, so long as each identically named function has different parameter types/numbers.  Return types are not considered for 
- `function delete` using `delete` keyword. delete means "I forbid this", not "this doesn’t exist". 
- `default-arguments`: is a default value provided for a function parameter. Parameters with default arguments must always be the rightmost parameters, and they are not used to differentiate functions when resolving overloaded functions.
```cpp
void printInt(int x)
{
    std::cout << x << '\n';
}

void printIntOrDefault(int x, int y = 2)
{
    std::cout << x << ", " << y << '\n';
}

template <typename T>
void printInt(T) = delete;

int main()
{
    printInt(97);             // okay

    // printInt('a');         // compile error
    // printInt(true);        // compile error

    printIntOrDefault(5);     // prints: 5, 2
    printIntOrDefault(5, 10); // prints: 5, 10

    return 0;
}
```

---
## 2. Operator Overloading

- **Operator overloading** allows C++ operators to be customized for user-defined types.
- An overloaded operator is implemented as a special function called an **operator function**.

- Operator Function Names:
    ```cpp
    operator op

    operator new
    operator new[]
    operator delete
    operator delete[]

    operator co_await // C++20
    ```

- Operator Syntax:
    | Expression | Member Function      | Non-member Function | Example                                             |
    | ---------- | -------------------- | ------------------- | --------------------------------------------------- |
    | `@a`       | `a.operator@()`      | `operator@(a)`      | `!a` calls `a.operator!()`                          |
    | `a@b`      | `a.operator@(b)`     | `operator@(a, b)`   | `std::cout << 42` calls  `std::cout.operator<<(42)` |
    | `a=b`      | `a.operator=(b)`     | N/A                 | `s = "abc"` calls `s.operator=("abc")`              |
    | `a(b...)`  | `a.operator()(b...)` | N/A                 | `r(1)` calls `r.operator()(1)`                      |
    | `a[b]`     | `a.operator[](b)`    | N/A                 | `m[1]` calls `m.operator[](1)`                      |
    | `a->`      | `a.operator->()`     | N/A                 | `p->do()` calls `p.operator->()`                    |
    | `a@`       | `a.operator@(0)`     | `operator@(a, 0)`   | `i++` calls `i.operator++(0)`                       |

- Restrictions:
    The following operators **cannot be overloaded**:
        ```cpp
        ::   // scope resolution
        .    // member access
        .*   // member access through pointer-to-member
        ?:   // conditional operator
        ```
    - New operators cannot be created.
    - Operators such as `**`, `<>`, or `&|` are invalid.
    - At least one operand must be a user-defined type.
    - Overloading does not change an operator's precedence, associativity, or number of operands.


#### Assignment Operator (`=`)
- Return the lhs by reference
```cpp
// copy assignment
T& operator=(const T& other)
{
    // Guard self assignment
    if (this == &other)
        return *this;
    
    // 
    
    return *this;
}

// move assignment
T& operator=(T&& other) noexcept
{
    // Guard self assignment
    if (this == &other)
        return *this; // delete[]/size=0 would also be ok
    
    //

    return *this;
}
```

#### Stream Extraction and Insertion (`>>`, `<<`)
- Must be implemented as non-members cause that take a `std::istream&` or `std::ostream&` as the left hand argument `std::cout << a; std::cout.operator << (a)`
```cpp
std::ostream& operator<<(std::ostream& os, const T& obj)
{
    // write obj to stream
    return os;
}

std::istream& operator>>(std::istream& is, T& obj)
{
    // read obj from stream
    if (/* T could not be constructed */)
        is.setstate(std::ios::failbit);
    return is;
}
```

#### Function Call Operator (`()`)

#### Increment and Decrement (`++`, `--`)

#### Binary Arithmetic Operators (`+`, `-`, `*`, `/`)

#### Comparison Operators (`==`, `!=`, `<`, `>`, `<=`, `>=`)

#### Array Subscript Operator (`[]`)

#### Bitwise Operators (`&`, `|`, `^`, `~`, `<<`, `>>`)

#### Boolean Negation Operator (`!`)

---
## 3. Lambda
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
  - `()`: *(Optional)* pararam list a.k.a lambda declarator
  - `mutable`: *(Optional)*
  - `throw()`: *(Optional)*
  - `-> int`: *(Optional)* trailing-return-type
  - `[](){ ... }` defines a lambda
  - `[](){ ... }()` defines and immediately CALLS it

### Capture Clause
- It uses to introduce new variables in its body, specifics which vars are captured, and whether the capture is `by value[=]` or `by reference [&]`. 
- An empty capture clause `[]` indicates that the body accesses no vars in the enclosing scope.
- An identifier or `this` cannot appear more than once in a capture scope.
- Since C++14, we can introduce and initialize new vars in the capture scope.
- e.g.
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

---
## 4. Function Pointers
- A function pointer is a pointer variable that stores the address of a function with a specific return type and parameter list.
- Syntax: `return_type (*FuncPtr) (parameter type, ....);`
```cpp
// @brief Declaration
rtype (*FuncPtr) (atype..);

// @brief Referencing: Assigning a function’s address to the function pointer.
FuncPtr = function_name; 

// @brief Dereferencing: Invoking the function using the pointer. The dereference operator * is optional during function calls.
FuncPtr(10, 20);     // Preferred
(*FuncPtr)(10, 20); // Also valid
```

---
## 5. **`<functional>`**
- `std::function` is a general-purpose polymorphic function wrapper introduced in C++11.
  - It can store and invoke any callable object:
    - Functions
    - Lambda expressions
    - Functors (objects that overload `operator()`)
    - Member functions (with binding)
  - It provides a common interface for different callable types.
  - Commonly used for callbacks, event handling, task dispatching, and functional-style programming.
  - Improves code flexibility, reusability, and maintainability.

- Syntax: `std::function<rtype(atype..)> name()` / `std::function< ret_t (args_t)> name = f;` / `std::function< ret_t (args_t)> name(f);`


---