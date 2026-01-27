# Theory

## 1. Initialization in C++

C++ provides several ways to initialize objects. Each form has different semantics and use cases.

---

### 1.1 Default Initialization

Performed when an object is created **without any initializer**.

```cpp
T object;
new T;
```

- Built-in types: uninitialized
- Class types: default constructor is called

---

### 1.2 Value Initialization

Performed when an object is created with an **empty initializer**.

```cpp
T();
new T();
T object{};
T{};
new T{};
```

Also used in constructors:

```cpp
Class::Class() : member() {}
Class::Class() : member{} {}
```

- Built-in types: zero-initialized
- Class types: default constructor is called

---

### 1.3 Direct Initialization

Initializes an object using **explicit constructor arguments**.

```cpp
T object(arg);
T object(arg1, arg2);

T object{arg};          // since C++11
new T(args...);
static_cast<T>(other);
```

Used in constructors and lambdas:

```cpp
Class::Class() : member(args...) {}
[arg]() {};
```

---

### 1.4 Copy Initialization

Initializes an object **from another object or expression**.

```cpp
T object = other;
f(other);
return other;
throw object;
catch (T object);
```

Also used for arrays:

```cpp
T array[N] = { /* values */ };
```

---

### 1.5 List Initialization (since C++11)

Initializes objects using **brace-enclosed initializer lists**.

#### Direct List Initialization

```cpp
T object{arg1, arg2};
new T{arg1, arg2};

Class::Class() : member{arg1, arg2} {}
```

#### Copy List Initialization

```cpp
T object = {arg1, arg2};
return {arg1, arg2};
function({arg1, arg2});
```

#### Designated Initializers (since C++20)

```cpp
T object{ .des1 = arg1, .des2 = arg2 };
T object = { .des1 = arg1, .des2 = arg2 };
```

---

### 1.6 Aggregate Initialization

Initializes **aggregate types** (no user-defined constructors).

```cpp
T object = {arg1, arg2};
T object{arg1, arg2};          // since C++11
```

Designated initializers for aggregates (since C++20):

```cpp
T object = { .des1 = arg1, .des2 = arg2 };
T object{ .des1 = arg1, .des2 = arg2 };
```

- A specialized form of list-initialization