// cppcheck-suppress-file [unreadVariable]

#include <iostream>

// Simple function to demonstrate function pointers
int foo(int x) {
  std::cout << "x = " << x << std::endl;
  return x;
}

void byPtr(int* x) {
  (*x)++;
  std::cout << "x = " << *x << std::endl;
}

void byConstPtr(const int* const x) {
  // *x++;   // error
  std::cout << "x = " << *x << std::endl;
}

void byPtrConst(const int* x) {
  // *x++; // error
  std::cout << "x = " << *x << std::endl;
}

void byConstPtrConst(const int* const x) {
  // *x++; // error
  std::cout << "x = " << *x << std::endl;
}

static int global = 42;
int* returnPtr() {
  return &global;  // the object must outlive the reference.
}

void pointers() {
  std::cout << "\n--- Pointers Type Examples ---\n";
  int a = 10;
  std::cout << "a = " << a << "\n";

  // * 1. Basics
  const int* null_ptr = nullptr;
  std::cout << "Address of nullptr (null_ptr): " << null_ptr << "\n";

  // '&' gives the address of a variable
  int* ptr_a = &a;
  std::cout << "Address of a (&a): " << &a << "\n";
  std::cout << "Value stored in pointer (ptr_a): " << ptr_a << "\n";

  // '*' dereferences a pointer (accesses the value at that address)
  std::cout << "Value of a via *ptr_a: " << *ptr_a << "\n";

  // Change value of a through its pointer
  *ptr_a = 2;
  std::cout << "Value of a after *ptr_a = 2: " << a << "\n";

  // * 2. Pointer to const
  const int const_var = 100;
  const int* ptr_const_var = &const_var;
  // *ptr_const_var = 10;     // cannot modify the value through pointer
  std::cout << "Value of ptr_const_var " << *ptr_const_var << "\n";
  ptr_const_var = &a;  // can point somewhere else
  std::cout << "Value of ptr_const_var " << *ptr_const_var << "\n";

  // * 3. Const pointer
  int* const const_ptr_a = &a;
  *const_ptr_a = 10;  // can change value
  // const_ptr_a = nullptr;   //cannot point to another variable

  // * 4. Const pointer to const
  const int* const const_ptr_const_var = &a;
  // *const_ptr_const_var = 10;  // cannot modify the value through pointer
  // const_ptr_const_var = nullptr; //cannot point to another variable

  // * 5. Pointer to pointer
  int** ptr_ptr_a = new int*[10];  // dynamically allocate an array of 10 int*
  ptr_ptr_a[0] = &a;
  std::cout << "Value via pointer-to-pointer (*ptr_ptr_a[0]): " << *ptr_ptr_a[0]
            << "\n";
  delete[] ptr_ptr_a;  // always free heap memory

  // * 6. Void pointer (generic pointer)
  // void *void_ptr = static_cast<int*>(&a);
  void* void_ptr = &a;  // C-style pointer casting [cstyleCast]

  std::cout << "Value via void pointer (after casting): "
            << *static_cast<int*>(void_ptr) << "\n";

  // * 7. Function pointer
  int (*fcn_ptr)(int) = &foo;
  (*fcn_ptr)(5);  // call via dereference
  fcn_ptr(10);    // call directly

  // 8. Passing pointers
  int in = 10;
  byPtr(&in);
  byConstPtr(&in);
  byPtrConst(&in);
  byConstPtrConst(&in);

  // * 9. Return by ptr(address)
  const int* b_ptr = returnPtr();
  std::cout << "By ptr: " << *b_ptr << '\n';
}

#include "ExampleRegistry.h"

class CPointers : public IExample {
 public:
  std::string group() const override { return "core/datatype"; }
  std::string name() const override { return "Pointer"; }
  std::string description() const override { return "Compound type: Pointers"; }
  void execute() override { pointers(); }
};

REGISTER_EXAMPLE(CPointers);
