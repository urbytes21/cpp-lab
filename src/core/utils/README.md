## Utilities library

### 1. `<optional>`
There are several ways to represent **"no value"**:
    - `nullptr`
    - sentinel values (`-1`, empty string, etc.)
    - exceptions
    - output parameters or flags

**Drawbacks:**
  - unclear semantics
  - unsafe assumptions
  - poor readability


**`optional`** was introduced to represent data that may be absent when that absence is part of the domain logic.
```cpp
std::optional<std::string> name_opt = std::nullopt;
```