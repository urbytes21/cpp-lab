// cppcheck-suppress-file [unreadVariable]

// Overloading operator=

#include "ExampleRegistry.h"
#include "Logger.h"

namespace {
class Cents {
 public:
  explicit Cents(int cents = 0) : cent_{cents} {}

  /// @brief Copy constructor
  Cents(const Cents& other) {
    LOG("");
    cent_ = other.cent_;
  }

  /// @brief Copy assignment
  Cents& operator=(const Cents& cents) {
    // do the copy
    LOG("");
    cent_ = cents.cent_;
    return *this;
  }

 private:
  int cent_;
};

void run() {
  Cents c1(100);  
  Cents c2;
  
  LOG("c2 = c1;");
  c2 = c1;        // c2.operator=(c1)

  LOG("Cents c3 = c1;");
  Cents c3 = c1;  // c3(c1)
}
}  // namespace

class AssignmentOperator : public IExample {
 public:
  std::string group() const override { return "core/overloading_operator"; }
  std::string name() const override { return "Assignment Operator"; }
  std::string description() const override { return ""; }

  void execute() override { run(); }
};

REGISTER_EXAMPLE(AssignmentOperator);