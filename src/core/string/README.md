## String Formatting

| Method            | Standard | Pros                     | Cons                         |
|------------------|----------|--------------------------|------------------------------|
| `std::format`     | C++20    | Clean, safe, Python-like | Needs newer compiler         |
| `+` concatenation | C++98    | Simple                   | Hard to format numbers       |
| `stringstream`    | C++98    | Flexible streaming       | Slow, verbose                |
| `snprintf`        | C        | Very fast, classic       | Unsafe if misused            |