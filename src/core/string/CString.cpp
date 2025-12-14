#include <string.h>
#include <iostream>

namespace {

namespace InitializeString {
void run() {
  // Memory layout (addresses are illustrative):

  // Stack (modifiable array)
  // 0x7fffc000: str2[0] = 'H'
  // 0x7fffc001: str2[1] = 'e'
  // 0x7fffc002: str2[2] = 'l'
  // 0x7fffc003: str2[3] = 'l'
  // 0x7fffc004: str2[4] = 'o'
  // 0x7fffc005: str2[5] = '\0'
  // (str2 starts at 0x7fffc000)

  // Data / Read-only segment (string literal)
  // 0x00403000: 'H'
  // 0x00403001: 'e'
  // 0x00403002: 'l'
  // 0x00403003: 'l'
  // 0x00403004: 'o'
  // 0x00403005: '\0'
  // (str1 -> points to 0x00403000)

  // Pointer variable
  // 0x7fffbff0: str1 = 0x00403000   // str1 holds address of string literal

  // 1. As a character array (modifiable)
  char strArray[] = "this is a strArray literal";
  std::cout << strArray << " - size " << sizeof(strArray) << " - length "
            << strlen(strArray) << "\n";
  strArray[0] ^= ' ';
  std::cout << strArray << "\n";

  // 2. As a a pointer to a string literal const (read-only)
  char* strPtr = "this is a strPtr literal";
  std::cout << strPtr << " - size " << sizeof(strPtr) << " - length "
            << strlen(strPtr) << "\n";
  //   strPtr[0] ^= ' '; // ERROR

  // 3. Using sprintf / snprintf (string formatting)
  char strFormatted[50];
  int numVar = 21;

  // sprintf (unsafe if buffer too small)
  sprintf(strFormatted, "sprintf: %d", numVar);
  std::cout << strFormatted << " - size " << sizeof(strFormatted)
            << " - length " << strlen(strFormatted) << "\n";

  // snprintf (safer, limits buffer size)
  snprintf(strFormatted, sizeof(strFormatted), "snprintf %s %d", strArray,
           numVar);
  std::cout << strFormatted << " - size " << sizeof(strFormatted)
            << " - length " << strlen(strFormatted) << "\n";
}
}  // namespace InitializeString

namespace CopyString {
void run() {
  const char src[] = "CopyStr";
  char dst[50];

  // 1. Copy full string
  strcpy(dst, src);

  std::cout << dst << " - size " << sizeof(dst) << " - length " << strlen(dst)
            << "\n";

  // 2. Copy the number of charactor
  strncpy(dst, "Hello123", 5);
  dst[5] = '\0';  // ensure null-termination

  std::cout << dst << " - size " << sizeof(dst) << " - length " << strlen(dst)
            << "\n";
}
}  // namespace CopyString

namespace ConcatString {
void run() {
  const char part1[] = "Hello";
  const char part2[] = "World";
  char dst[50] = "";

  // 1. Append full str
  strcat(dst, part1);
  strcat(dst, part2);
  strcat(dst, " !!");
  std::cout << dst << " - size " << sizeof(dst) << " - length " << strlen(dst)
            << "\n";

  // 2. Append the number of charactors
  strncat(dst, "1234", 3);
  std::cout << dst << " - size " << sizeof(dst) << " - length " << strlen(dst)
            << "\n";
}
}  // namespace ConcatString

namespace CompareString {
void run() {
  const char str1[] = "abc";
  const char str2[] = "abcde";
  // 0. Compare memory
  // int memcmp ( const void * ptr1, const void * ptr2, size_t num );
  int result0 = memcmp(str1, str2,sizeof(str1));
  std::cout << "strcmp(str1, \"abcde\") = " << result0 << "\n";

  // 1. Compare full str
  int result1 = strcmp(str1, "abc");
  int result2 = strcmp(str1, str2);
  std::cout << "strcmp(str1, \"abc\") = " << result1 << "\n";
  std::cout << "strcmp(str1, str2) = " << result2 << "\n";

  // 2. Compare first N characters
  int result3 = strncmp(str1, str2, 3);
  std::cout << "strncmp(str1, str2, 3) = " << result3 << "\n";
}
}  // namespace CompareString

namespace ParseString {
void run() {
  char str[] = "A,B,C,D,";  // OK
                            //   char* str = "A,B,C,D,"; // ERROR - const

  // 1. Splitting a string by some delimiter
  // 1.1. strtok - not safe
  char* delimiter = ",";
  const char* token = strtok(str, delimiter);
  while (token != nullptr) {
    std::cout << "strtok - token :" << token << "\n";
    token = strtok(NULL, delimiter);
  }
  {
    std::cout << " === problem === \n";
    char str1[] = "a,b,c";
    char str2[] = "1,2,3";

    // Parse str1
    const char* token1 = strtok(str1, delimiter);  // token1 = "a"
    std::cout << "str1 first token: " << token1 << "\n";

    // Parse str2
    const char* token2 = strtok(str2, delimiter);  // token2 = "1"
    std::cout << "str2 first token: " << token2 << "\n";

    // Continue parsing str1
    token1 = strtok(nullptr, delimiter);  //  Unexpected!
    std::cout << "str1 second token: " << token1 << "\n";
  }

  // Have to Reset string for the next handle because strtok
  char str2[] = "one,two,three";
  // 1.2. strtok_r - safe
  char* saveptr;
  const char* token2 = strtok_r(str2, delimiter, &saveptr);
  while (token2 != nullptr) {
    std::cout << "strtok - token :" << token2 << "\n";
    token2 = strtok_r(NULL, delimiter, &saveptr);
  }

  // 2. strcspn: find first occurrence of any chars in reject set
  const char sample[] = "hello123world";
  size_t pos = strcspn(sample, "0123456789");  // pos = 5

  std::cout << "Sample string: " << sample << "\n";
  std::cout << "First digit from \"0123456789\" found at index: " << pos
            << "\n";
  std::cout << "The digit is: " << sample[pos] << "\n";
}
}  // namespace ParseString

namespace NumberConversion {
void run() {
  // 1. string to integer
  const char strNum[] = "100";
  int num = atoi(strNum);
  std::cout << num << "\n";

  // 2. string to double
  const char strNumD[] = "100.1234__123";
  double numD = atof(strNumD);
  std::cout << numD << "\n";

  char* end;
  numD = strtod(strNumD, &end);
  std::cout << numD << " end part:" << end << "\n";
}
}  // namespace NumberConversion
}  // namespace

struct CStringAutoRunner {
  CStringAutoRunner() {
    std::cout << "\n--- C String Example ---\n";

    InitializeString::run();
    CopyString::run();
    ConcatString::run();
    CompareString::run();
    ParseString::run();

    NumberConversion::run();
  }
};

static CStringAutoRunner instance;
