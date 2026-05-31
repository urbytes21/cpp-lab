// cppcheck-suppress-file [postfixOperator]

// prefix/posfix
#include "ExampleRegistry.h"
#include "Logger.h"

namespace {
class Cents {
 public:
  explicit Cents(int cents) : cents_{cents} {}
  int getCents() const { return cents_; }

  // pre: inc -> return new
  Cents& operator++();
  Cents& operator--();

  // return old -> inc
  Cents operator++(int);
  Cents operator--(int);

 private:
  int cents_{};
};

/// @brief pre ++x
Cents& Cents::operator++() {
  LOG("");
  ++cents_;
  return *this;
}

/// @brief pre ++x
Cents& Cents::operator--() {
  LOG("");
  --cents_;
  return *this;
}

/// @brief pos x++
Cents Cents::operator++(int) {
  LOG("");
  Cents temp{*this};  // create copy
  ++(*this);          // increase origin
  return temp;        // return old
}

/// @brief pos x--
Cents Cents::operator--(int) {
  LOG("");
  Cents temp{*this};
  --(*this);
  return temp;
}

void run() {
  Cents cent{25};
  cent++;
  ++cent;
  cent--;
  --cent;
  LOG_S(cent.getCents());
}
}  // namespace

class InDecOperator : public IExample {
 public:
  std::string group() const override { return "core/overloading_operator"; }
  std::string name() const override { return "InDecOperator"; }
  std::string description() const override { return ""; }

  void execute() override { run(); }
};

REGISTER_EXAMPLE(InDecOperator);