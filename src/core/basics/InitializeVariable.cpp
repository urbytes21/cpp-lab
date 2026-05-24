// cppcheck-suppress-file [unreadVariable, unusedVariable, functionStatic]

#include "Logger.h"
#include "ExampleRegistry.h"

void initialize_variable();

class InitializeVariable : public IExample {
 public:
  std::string group() const override { return "core/basics"; }
  std::string name() const override { return "InitializeVariable"; }
  std::string description() const override { return "InitializeVariable"; }

  void execute() override { initialize_variable(); }
};

REGISTER_EXAMPLE(InitializeVariable);

struct Foo {
  Foo() { LOG("Default constructor/ default init"); }

  // Foo(int)
  explicit Foo(int) {
    LOG( "Constructor called with int / copy init");
  }

  Foo(const Foo& other) {
    other.dump();
    LOG( "Copy constructor called");
  }

  void dump() const {}
};

void initialize_variable() {
  LOG( "\n--- Variable Initialization Examples ---");
  // * 1) Default-initialization
  int init_default_var;
  Foo init_default_obj;

  auto* c = new unsigned char;
  *c = 0xF;  // actual init at this point for c
  delete c;

  // * 2) Value-initialization
  int init_value_var1();
  int init_value_var2{};

  // * 3) direct-init: Type var(value);
  Foo direct_init_obj(4);  // call Foo(int)
  Foo direct_init_obj2(4.3);  // look for constructor -> implicit 4.3(float) -> 4(int) -> call Foo(int)

  // * 4) Copy-init: Type var = other;
  //     1. Compiler tries to convert the value to a temporary Foo.
  //     2. If the constructor is explicit, implicit conversion is blocked -> compilation error.
  //     3. Otherwise, a temporary Foo is created and then copied/moved into the variable.
  Foo copy_init_obj = (Foo)2.3;
  // explicit cast: double 2.3 -> int 2 (implicit narrowing) -> Foo(int)
  // -> temporary Foo -> copied/moved into copyInitObj
  // Foo copyInitObjError = 2.3; // ERROR: implicit conversion blocked by explicit constructor
  // We can explicitly prevent certain conversions using = delete or using {}

  //  * 5) List-initialization (Brace init)
  // calls the constructor directly without allowing implicit conversions.
  Foo brace_init{3};
  // Foo braceInit2{3.3}; // ERORR => Prefer this way
  int ar[] = {1, 2, 3};  // aggregate init
  int ar2[]{1, 2, 3};
}