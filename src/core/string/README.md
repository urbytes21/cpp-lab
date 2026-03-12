# 1. String Formatting

| Method            | Standard | Pros                     | Cons                         |
|------------------|----------|--------------------------|------------------------------|
| `std::format`     | C++20    | Clean, safe, Python-like | Needs newer compiler         |
| `+` concatenation | C++98    | Simple                   | Hard to format numbers       |
| `stringstream`    | C++98    | Flexible streaming       | Slow, verbose                |
| `snprintf`        | C        | Very fast, classic       | Unsafe if misused            |
https://www.geeksforgeeks.org/cpp/strings-in-cpp/
https://hackingcpp.com/cpp/std/string_basics

---

# 2. Create Strings

```cpp
std::string s = "hello";
std::string s2("hello");
std::string s3(5, 'a');     // "aaaaa"
```
---

# 3. Basic Properties

| Function     | Description           |
| ------------ | --------------------- |
| `s.size()`   | number of characters  |
| `s.length()` | same as size          |
| `s.empty()`  | check empty           |
| `s.clear()`  | remove all characters |

---

# 4. Access Characters

```cpp
s[0]        // no bounds check
s.at(0)     // bounds check
s.front()   // first char
s.back()    // last char
```

---

# 5. Modify String

## append

```cpp
s.append(" world");
s += " world";
```

## insert

```cpp
s.insert(5, "XXX");
```

## erase

```cpp
s.erase(0,2);
```

## replace

```cpp
s.replace(0,5,"hi");
```

## remove `\n`

```cpp
    std::string s = "hello\nworld\n";
    auto new_end = std::remove(s.begin(), s.end(), '\n');
    s.erase(new_end)
    // std::erase(s,'\n')
    s.erase(std::remove(s.begin(), s.end(), '\n'), s.end());
```


---

# 6. Substring

```cpp
std::string sub = s.substr(pos, len);
```

Example:

```cpp
std::string s = "abcdef";

s.substr(2,3);   // "cde"
```

Important:

```
substr() does NOT modify original string
```

---

# 7. Find / Search

## find substring

```cpp
size_t pos = s.find("abc");

if (pos != std::string::npos)
    std::cout << "found";
```

## find char

```cpp
s.find('a');
```

## find last

```cpp
s.rfind("abc");
```

---

# 8. Compare Strings

```cpp
if (a == b)
if (a != b)
if (a < b)
```

Using compare:

```cpp
a.compare(b)
```

Return:

```
0  -> equal
<0 -> smaller
>0 -> larger
```

### C++20

```cpp
s.starts_with("abc");
s.ends_with("xyz");
```

### Before C++20

#### starts_with

```cpp
s.rfind("abc",0) == 0
```

#### ends_with

```cpp
s.size() >= 3 &&
s.compare(s.size()-3,3,"xyz") == 0
```

---

# 9. Convert String

## string → int

### C++11

```cpp
int n = std::stoi(s);
```

Other:

```
stol
stoll
stof
stod
```

Example:

```cpp
double x = std::stod("3.14");
```

---

## number → string

```cpp
std::string s = std::to_string(123);
```

---

# 10. String Parsing

## split using stringstream

```cpp
#include <sstream>

std::string line = "a,b,c";
std::stringstream ss(line);
std::string item;

while(std::getline(ss,item,',')) {
    std::cout << item << std::endl;
}
```

Result

```
a
b
c
```

---

# 11. Trim Whitespace (manual)

Common pattern:

```cpp
s.erase(0, s.find_first_not_of(" \t\n\r"));
s.erase(s.find_last_not_of(" \t\n\r") + 1);
```

Removes leading/trailing spaces.

---

# 12. Convert Case

```cpp
#include <algorithm>

std::transform(s.begin(), s.end(), s.begin(), ::tolower);
std::transform(s.begin(), s.end(), s.begin(), ::toupper);
```

---

# 20. Functions Modify the String

Modify:

```
append
insert
erase
replace
clear
push_back
pop_back
```

Do NOT modify:

```
substr
find
compare
size
empty
```

Rule:

```
method() const  -> does NOT modify object
```

---

# 21. Common Bugs