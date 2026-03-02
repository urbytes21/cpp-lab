// cppcheck-suppress-file [unreadVariable]
#include <iostream>
using namespace std;

class Base {
 public:
  virtual void show() { cout << "Base class\n"; }
  virtual ~Base() = default;
};

class Derived : public Base {
 public:
  void show() override { cout << "Derived class\n"; }
};

class DerivedX : public Base {
 public:
  void show() override { cout << "DerivedX class\n"; }
};

void implicitConversion() {
  cout << "\n--- Implicit Type Conversion ---\n";
  // *1. Numeric promotion (safe, no data loss)
  char c = 'A';
  int i = c;  // char → int
  float f = 3.5f;
  double d = f;  // float → double
  bool b = true;
  int b_to_int = b;  // bool → int (true=1)

  cout << "char to int: " << i << "\n";
  cout << "float to double: " << d << "\n";
  cout << "bool to int: " << b_to_int << "\n";

  // *2. Numeric conversion
  float pi = 3.14159;
  double pi_double = pi;  // Widening conversions
  int pi_int = pi;        // narrowing, may lose fractional part
  cout << "float to double (didening): " << pi_double << "\n";
  cout << "float to int (narrowing): " << pi_int << "\n";
}

void explicitConversion() {
  cout << "\n--- Explicit Type Conversion ---\n";

  double pi = 3.14159;

  // *1. C-style cast - not safe
  int pi_c = (int)pi;
  cout << "C-style cast: " << pi_c << "\n";

  // **2. static_cast - type-safe relationship + compile-time type checking**
  int pi_static = static_cast<int>(pi);
  cout << "static_cast: " << pi_static << "\n";

  //    object -> object
  Derived derived{};
  Base baseObj = static_cast<Derived>(derived);
  // DerivedX derivedx =static_cast<Derived>(derived); // ERROR

  //    object -> reference
  const Base& baseRef = static_cast<Derived&>(derived);
  // object -> ptr
  const Base* base_ptr = static_cast<Derived*>(&derived);

  // **3. const_cast: const_cast adds or removes the const qualifier**
  const double c_pi = 2.71828;
  const double* pConst = &c_pi;
  const double* pNonConst = const_cast<double*>(pConst);  // remove const
  cout << "const_cast: " << *pNonConst << " (removed const)\n";

  // **4. reinterpret_cast: reinterpret memory (unsafe)**
  // It is used to convert a pointer of some data type into a pointer of another data type,
  // even if the data types before and after conversion are different. (#static,dynamic)
  // It does not check if the pointer type and data pointed by the pointer is same or not.
  const void* pVoid = reinterpret_cast<const void*>(&pi);
  cout << "reinterpret_cast: address of pi = " << pVoid << "\n";

  // ******************** Use case: Memory-Mapped I/O ******************************
  // C ===============================================
  // #define REG_ADDR 0x000fff01
  //   volatile uint8_t* reg = reinterpret_cast<volatile uint8_t*>(REG_ADDR);
  //   *reg = 0xF;
  //   *reg = 0x1;

  // C++ ===============================================
  // #include <cstdint>
  // constexpr std::uintptr_t REG_ADDR = 0x000fff02;
  // auto* const reg = reinterpret_cast<volatile uint8_t*>(REG_ADDR);
  // *reg = 0xF;
  // *reg = 0x1;
  // ********************************************************************************

  // **5. dynamic_cast: safe cast between related classes - type-safe relationship + run-time type checking**
  // RTTI (RunTime Type Information) check
  // #include <typeinfor>
  // if(typeid(*basePtr) == typeid(Derived)){
  // Derived* derivedPtr = dynamic_cast<Derived*>(basePtr)
  // }

  Base* basePtr = new Derived();
  const Derived* derivedPtr = dynamic_cast<Derived*>(basePtr);
  if (derivedPtr)
    cout << "dynamic_cast: Success (Base* -> Derived*)\n";
  else
    cout << "dynamic_cast: Failed\n";

  Base* anotherBase = new Base();
  const Derived* wrongCast = dynamic_cast<Derived*>(anotherBase);
  if (!wrongCast)
    cout << "dynamic_cast: nullptr (invalid downcast)\n";

  delete basePtr;
  delete anotherBase;
}

void typeAliases() {
  cout << "\n--- Type Aliases ---\n";

  // *1. using - preferred
  using MyDouble = double;
  const MyDouble a = 3.14;

  // *2. typedef - old style
  typedef double OldDouble;
  OldDouble b = 2.718;

  // *3. Function pointer alias
  using FuncType = int (*)(double, char);
  auto func = [](double x, char c) {
    return static_cast<int>(x) + c;
  };
  FuncType fptr = func;
  cout << "Function pointer alias result: " << fptr(2.5, 'A') << "\n";
}

int add(int x, int y) {
  return (x + y);
}

auto add_auto(int a, int b) -> int {
  return a + b;
}

void typeDeduction() {
  cout << "\n--- Type Deduction ---\n";

  // *1. auto deduces type
  auto x = 42;           // int
  auto y = 3.14;         // double
  const auto z = x + y;  // double, const ignored in type deduction

  cout << "auto x: " << x << ", y: " << y << ", z: " << z << "\n";

  // *2. Trailing return type
  cout << "add(3,4) = " << add(3, 4) << "\n";
  cout << "add_auto(3,4) = " << add_auto(3, 4) << "\n";

  // *3. std::common_type
  std::common_type_t<int, double> val = x + y;
  cout << "common_type<int,double>: " << val << "\n";
}

#include "ExampleRegistry.h"

class CTypeConversion : public IExample {
 public:
  std::string group() const override { return "core"; }
  std::string name() const override { return "CTypeConversion"; }
  std::string description() const override { return ""; }
  void execute() override {
    implicitConversion();
    explicitConversion();

    typeAliases();
    typeDeduction();
  }
};

REGISTER_EXAMPLE(CTypeConversion, "core", "CTypeConversion");