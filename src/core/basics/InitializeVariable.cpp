#include <iostream>
using namespace std;

void initialize_variable();

// A struct that runs code when its object is created
struct InitializeVariable {
  InitializeVariable() {
    cout << "\n"
         << "\n"
         << "InitializeVariable\n";
    initialize_variable();
  }
};

// All global and static objects are constructed before main() begins.
static InitializeVariable autoRunInstance;

struct Foo {
  Foo() { cout << "Default constructor/ default init\n"; }

  // Foo(int)
  explicit Foo(int) { cout << "Constructor called with int / copy init\n"; }

  Foo(const Foo& other) { std::cout << "Copy constructor called\n"; }
};

void initialize_variable() {
  cout << "\n--- Variable Initialization Examples ---\n";
  // There are there common ways to intialize a variable
  // * 1) Default-initialization
  [[maybe_unused]] int initDefaultVar;
  [[maybe_unused]] Foo initDefaultObj;

  [[maybe_unused]] unsigned char* c = new unsigned char;
  *c = 0xF;  // actual init at this point for c
  delete c;

  // * 2) Value-initialization
  [[maybe_unused]] int initValueVar1();
  [[maybe_unused]] int initValueVar2{};

  // * 3) direct-init: Type var(value);
  [[maybe_unused]] Foo directInitObj(4);  // call Foo(int)
  [[maybe_unused]] Foo directInitObj2(
      4.3);  // look for constructor -> implicit 4.3(float) -> 4(int) -> call Foo(int) ->

  // * 4) Copy-init: Type var = other;
  //     1. Compiler tries to convert the value to a temporary Foo.
  //     2. If the constructor is explicit, implicit conversion is blocked -> compilation error.
  //     3. Otherwise, a temporary Foo is created and then copied/moved into the variable.
  [[maybe_unused]] Foo copyInitObj =
      (Foo)2.3;  // explicit cast: double 2.3 -> int 2 (implicit narrowing) -> Foo(int)
                 // -> temporary Foo -> copied/moved into copyInitObj
  // Foo copyInitObjError = 2.3; // ERROR: implicit conversion blocked by explicit constructor
  // We can explicitly prevent certain conversions using = delete or using {}

  //  * 5) List-initialization (Brace init)
  // calls the constructor directly without allowing implicit conversions.
  [[maybe_unused]] Foo braceInit{3};
  // Foo braceInit2{3.3}; // ERORR => Prefer this way
  [[maybe_unused]] int ar[] = {1, 2, 3};  // aggregate init
  [[maybe_unused]] int ar2[]{1, 2, 3};
}