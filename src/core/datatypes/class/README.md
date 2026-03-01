## 1. Friend
- Friend declaration (classes and functions) allows certain classes or functions to access the private and protected members of another class.

### 1.1. Non Member Function
- It serves the same kind of role as the package access specifier in Java.
- `a << b` C++ tries in this order:
```cpp
1 a.operator<<(b)
2 operator<<(a, b) (non-member function)

X OP Y
operator OP (type_of_X, type_of_Y)
```
### 1.2. Member of Another Class:
- It give access to only once specific function.
### 1.3. Class
- Friend Class : I trust this class to see my private data
- It give access to all member functions of another class.