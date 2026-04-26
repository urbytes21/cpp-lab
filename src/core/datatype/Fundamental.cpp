#include <iostream>

// 	A basic type built into the core C++ language
void primative() {
  std::cout << "\n--- Primative Type Examples ---\n";
  // Boolean
  bool is_ready = true;
  std::cout << "bool: " << is_ready << "\n";

  // Character
  char c = 'A';
  unsigned char uc = 200;
  wchar_t wc = L'Ω';  // Greek Omega
  // char8_t c8 = u8'A';   // UTF-8
  char16_t c16 = u'ß';   // UTF-16
  char32_t c32 = U'中';  // UTF-32
  std::cout << "char: " << c << "\n";
  std::cout << "unsigned char: " << static_cast<int>(uc) << "\n";
  std::wcout << L"wchar_t: " << wc << L"\n";
  // std::cout << "char8_t: " << static_cast<char>(c8) << "\n";
  std::cout << "char16_t: (UTF-16 code) " << static_cast<int>(c16) << "\n";
  std::cout << "char32_t: (UTF-32 code) " << static_cast<int>(c32) << "\n";

  // Integer
  short s = -10;
  int i = 42;
  unsigned int ui = 100;
  long l = 123456L;
  long long ll = 9876543210LL;
  std::cout << "short: " << s << "\n";
  std::cout << "int: " << i << "\n";
  std::cout << "unsigned int: " << ui << "\n";
  std::cout << "long: " << l << "\n";
  std::cout << "long long: " << ll << "\n";

  // Floating Point
  float f = 3.14F;
  double d = 2.718281828;
  long double ld = 1.6180339887L;
  std::cout << "float: " << f << "\n";
  std::cout << "double: " << d << "\n";
  std::cout << "long double: " << ld << "\n";

  // Void
  std::cout << "void: (no data type, used for functions)\n";

  // pointer
  int const* ptr = nullptr;
  std::cout << "nullptr_t: " << ptr << "\n";
}

#include "ExampleRegistry.h"

class Fundamental : public IExample {
 public:
  std::string group() const override { return "core/datatype"; }
  std::string name() const override { return "Fundamental"; }
  std::string description() const override { return "Fundamental"; }
  void execute() override { primative(); }
};

REGISTER_EXAMPLE(Fundamental, "core/datatype", "Fundamental");
