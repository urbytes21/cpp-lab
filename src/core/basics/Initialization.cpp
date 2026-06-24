// cppcheck-suppress-file [unreadVariable, unusedVariable, uninitdata, uninitvar, unassignedVariable]

#include "ExampleRegistry.h"
#include "Logger.h"

/// @brief Dummy class
struct Dummy {
  Dummy() { LOG("Default ctor"); }
  explicit Dummy(int value) { LOG_S("Int ctor: " << value); }
  Dummy(const Dummy&) { LOG("Copy ctor"); }
};

/// @brief Aggregate type
struct Aggregate {
  int x;
  int y;
};

/// @brief Default Initialization
void default_ini() {
  int a;
  LOG_S("a = " << a);

  Dummy object;

  auto* p1 = new int;
  LOG_S("*p1 = " << *p1);
  auto* p2 = new Dummy;

  delete p1;
  delete p2;
}

/// @brief Value Initialization
void value_ini() {
  // int x();Dummy obj();      // Most Vexing Parse:function declaration

  int a = int();
  int b{};

  LOG_S("a = " << a);
  LOG_S("b = " << b);

  Dummy object1 = Dummy();  // value initialization x copy-initialization
  Dummy object2{};

  auto* p1 = new int();
  LOG_S("*p1 = " << *p1);

  auto* p2 = new Dummy();

  delete p1;
  delete p2;
}

/// @brief Direct Initialization
void direct_ini() {
  int a(42);

  Dummy object1(1);
  Dummy object2(static_cast<int>(2));

  LOG_S("a = " << a);
}

/// @brief Copy Initialization
void copy_ini() {
  Dummy source{1};

  Dummy object1 = source;
  Dummy object2 = Dummy{2};

  int value = 42;

  LOG_S("value = " << value);
}

/// @brief List Initialization (since C++11)
void list_ini() {
  Dummy object1{1};                         // direct-list-init
  Dummy object2 = {static_cast<Dummy>(2)};  // copy-list-init

  int values1[]{1, 2, 3};
  int values2[] = {4, 5, 6};
}

/// @brief Aggregate Initialization
void aggregate_ini() {
  Aggregate a1 = {1, 2};
  Aggregate a2{3, 4};
  Aggregate a3{.x = 3, .y = 4};

  LOG_S("a1 = {" << a1.x << ", " << a1.y << "}");
  LOG_S("a2 = {" << a2.x << ", " << a2.y << "}");
  LOG_S("a3 = {" << a3.x << ", " << a3.y << "}");
}

class Initialization : public IExample {
 public:
  std::string group() const override { return "core/basics"; }
  std::string name() const override { return "Initialization"; }
  std::string description() const override { return "Initialization Examples"; }

  void execute() override {
    default_ini();
    value_ini();
    direct_ini();
    copy_ini();
    list_ini();
    aggregate_ini();
  }
};

REGISTER_EXAMPLE(Initialization);