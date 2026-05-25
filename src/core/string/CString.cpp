#include <string.h>  // C-String
#include "Logger.h"

namespace {
void log_string_info(const char* label, const char* str, size_t size) {
  LOG_S(label << ": \"" << str << "\"" << " | size=" << size
              << " | length=" << strlen(str));
}

namespace create {
/// @brief Stack (modifiable array)
// 0x7fffc000: str2[0] = 'H'
// 0x7fffc001: str2[1] = 'e'
// 0x7fffc002: str2[2] = 'l'
// 0x7fffc003: str2[3] = 'l'
// 0x7fffc004: str2[4] = 'o'
// 0x7fffc005: str2[5] = '\0'
// (str2 starts at 0x7fffc000)

/// @brief String literal (Data / Read-only segment)
// 0x00403000: 'H'
// 0x00403001: 'e'
// 0x00403002: 'l'
// 0x00403003: 'l'
// 0x00403004: 'o'
// 0x00403005: '\0'
// (str1 -> points to 0x00403000)

// Pointer variable
// 0x7fffbff0: str1 = 0x00403000   // str1 holds address of string literal
void run() {
  LOG("=== create ===");

  /// @brief Create a string as a character array (modifiable)
  char str_array[] = "this is a string array literal";
  log_string_info("str_array", str_array, sizeof(str_array));
  str_array[0] ^= ' ';  // modify first character
  log_string_info("modified str_array", str_array, sizeof(str_array));

  /// @brief Create a pointer to a string literal const (read-only)
  const char* str_ptr = "this is a strPtr literal";
  log_string_info("str_ptr", str_ptr, sizeof(str_ptr));
  // str_ptr[0] ^= ' '; // ERROR

  /// @brief Create a string using sprintf / snprintf
  char str_formatted[50];
  int num_var = 21;
  const char text[] = "example";

  sprintf(str_formatted, "sprintf: %d",
          num_var);  // sprintf (unsafe if buffer too small)
  log_string_info("sprintf", str_formatted, sizeof(str_formatted));

  snprintf(str_formatted, sizeof(str_formatted), "snprintf %s %d", text,
           num_var);  // snprintf (safer, limits buffer size)
  log_string_info("snprintf", str_formatted, sizeof(str_formatted));
}
}  // namespace create

namespace copy {
void run() {
  LOG("=== copy ===");

  const char src[] = "CopyStr";
  char dst[50];

  /// @brief Copy full string
  strcpy(dst, src);
  log_string_info("strcpy", dst, sizeof(dst));

  /// @brief Copy first N characters
  strncpy(dst, "Hello123", 5);
  dst[5] = '\0';  // strncpy may not append '\0'
  log_string_info("strncpy", dst, sizeof(dst));
}
}  // namespace copy

namespace concat {
void run() {
  LOG("=== concat ===");

  const char part1[] = "Hello";
  const char part2[] = "World";
  char dst[50] = "";

  /// @brief Append full strings
  strcat(dst, part1);
  strcat(dst, part2);
  strcat(dst, " !!");
  log_string_info("strcat", dst, sizeof(dst));

  /// @brief Append first N characters
  strncat(dst, "1234", 3);
  log_string_info("strncat", dst, sizeof(dst));
}
}  // namespace concat

namespace compare {
void run() {
  LOG("=== compare ===");

  const char str1[] = "abc";
  const char str2[] = "abcde";

  /// @brief Compare memory
  // int memcmp(const void* ptr1, const void* ptr2, size_t num);
  int result0 = memcmp(str1, str2, sizeof(str1));
  LOG_S("memcmp(str1, str2, sizeof(str1)) = " << result0);

  /// @brief Compare full string
  int result1 = strcmp(str1, "abc");
  int result2 = strcmp(str1, str2);
  LOG_S("strcmp(str1, \"abc\") = " << result1);
  LOG_S("strcmp(str1, str2) = " << result2);

  /// @brief Compare first N characters
  int result3 = strncmp(str1, str2, 3);
  LOG_S("strncmp(str1, str2, 3) = " << result3);
}
}  // namespace compare

namespace parse {
void run() {
  LOG("=== compare ===");

  char str[] = "A,B,C,D,";
  // char* str = "A,B,C,D,"; // ERROR - string literal is read-only

  const char* delimiter = ",";

  /// @brief strtok (NOT thread-safe)
  LOG_S("=== strtok ===");
  const char* token = strtok(str, delimiter);
  while (token != nullptr) {
    LOG_S("token = " << token);

    token = strtok(nullptr, delimiter);
  }

  /// @brief strtok problem example
  {
    LOG_S("=== strtok problem example ===");

    char str1[] = "a,b,c";
    char str2[] = "1,2,3";

    // Parse str1
    const char* token1 = strtok(str1, delimiter);
    LOG_S("str1 first token  = " << token1);

    // Parse str2
    const char* token2 = strtok(str2, delimiter);
    LOG_S("str2 first token  = " << token2);

    // Continue parsing str1
    token1 = strtok(nullptr, delimiter);
    LOG_S("str1 second token = " << token1 << " (unexpected)");
  }

  /// @brief strtok_r (thread-safe / reentrant)
  LOG_S("=== strtok_r ===");

  char str2[] = "one,two,three";
  char* saveptr;
  const char* token2 = strtok_r(str2, delimiter, &saveptr);

  while (token2 != nullptr) {
    LOG_S("token = " << token2);
    token2 = strtok_r(nullptr, delimiter, &saveptr);
  }

  /// @brief strcspn
  // Find first occurrence of any character in reject set
  LOG_S("=== strcspn ===");

  const char sample[] = "hello123world";
  size_t pos = strcspn(sample, "0123456789");
  LOG_S("sample = " << sample);
  LOG_S("first digit index = " << pos);
  LOG_S("digit = " << sample[pos]);
}
}  // namespace parse

namespace number_conversion {
void run() {
  LOG_S("=== number_conversion ===");

  /// @brief String to integer
  const char str_num[] = "100";
  int num = atoi(str_num);
  LOG_S("atoi(\"100\") = " << num);

  /// @brief String to double
  const char str_num_d[] = "100.1234__123";
  double num_d = atof(str_num_d);
  LOG_S("atof(\"100.1234__123\") = " << num_d);

  /// @brief strtod
  char* end;
  num_d = strtod(str_num_d, &end);
  LOG_S("strtod = " << num_d);
  LOG_S("remaining string = " << end);
}
}  // namespace number_conversion
}  // namespace

#include "ExampleRegistry.h"

class CString : public IExample {
 public:
  std::string group() const override { return "core/string"; }
  std::string name() const override { return "C-String"; }
  std::string description() const override { return "C-String Example"; }
  void execute() override {
    create::run();
    copy::run();
    concat::run();
    compare::run();
    parse::run();
    number_conversion::run();
  }
};

REGISTER_EXAMPLE(CString);
