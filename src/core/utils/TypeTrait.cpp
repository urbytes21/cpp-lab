#include <memory>
#include <string>
#include <type_traits>
#include <typeinfo>

#ifdef __GNUG__
#include <cxxabi.h>
#endif

#include <sstream>
#include "ExampleRegistry.h"
#include "Logger.h"

namespace type_trait {

// Utility: readable type name
template <typename T>
std::string type_name() {
#ifdef __GNUG__
  int status = 0;
  std::unique_ptr<char, void (*)(void*)> demangled(
      abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, &status),
      std::free);
  return (status == 0 && demangled) ? demangled.get() : typeid(T).name();
#else
  return typeid(T).name();
#endif
}

// Trait: has operator &=
template <typename T, typename = void>
struct HaveAndAssign : std::false_type {};

template <typename T>
struct HaveAndAssign<
    T, std::void_t<decltype(std::declval<T&>() &= std::declval<T>())>>
    : std::true_type {};

// Trait: has operator !
template <typename T, typename = void>
struct HaveNot : std::false_type {};

template <typename T>
struct HaveNot<T, std::void_t<decltype(!std::declval<T&>())>> : std::true_type {
};

// Example class WITH &=
template <typename T>
class A {
 public:
  A& operator&=(const A&) { return *this; }
};

// Example class WITHOUT &=
template <typename T>
class B {};

// Constrained class
template <typename T, std::enable_if_t<HaveAndAssign<T>::value, int> = 0>
class C {
 public:
  C() {
    std::ostringstream oss;
    oss << "C<" << type_name<T>() << "> instantiated";
    LOG(oss.str());
  }
};

// Debug printer
template <typename T>
void printTypeInfo() {
  std::ostringstream oss;
  oss << "==== Type Info ====\n"
      << "Type: " << type_name<T>() << '\n'
      << "is_bool: " << std::is_same_v<T, bool> << '\n'
      << "HaveAndAssign: " << HaveAndAssign<T>::value << '\n'
      << "HaveNot (!): " << HaveNot<T>::value;
  LOG(oss.str());
  LOG("===================");
}

void run() {
  LOG("===== Type Traits Examples =====");

  printTypeInfo<bool>();
  printTypeInfo<B<bool>>();
  printTypeInfo<A<bool>>();

  if constexpr (HaveAndAssign<A<bool>>::value) {
    LOG("A<bool> supports &=");
    C<A<bool>> c_instance;
  } else {
    LOG("B<bool> does NOT support &=");
  }

  if constexpr (HaveAndAssign<B<bool>>::value) {
    LOG("B<bool> supports &=");
  } else {
    LOG("B<bool> does NOT support &=");
  }
  LOG("================================");
}

}  // namespace type_trait

class TypeTrait : public IExample {
 public:
  std::string group() const override { return "core/utils"; }

  std::string name() const override { return "TypeTrait"; }

  std::string description() const override {
    return "Examples for <type_traits> with improved logging and SFINAE checks";
  }

  void execute() override { type_trait::run(); }
};

REGISTER_EXAMPLE(TypeTrait, "core/utils", "TypeTrait");