#include "ExampleRegistry.h"
#include "Logger.h"

namespace {
void conditionals() {
  LOG("Conditional Examples");
  // if-else
  int x = rand();
  LOG_S("x = " << x);
  if (x > 0) {
    LOG("x is positive");
  } else if (x < 0) {
    LOG("x is negative");
  } else {
    LOG("x is zero");
  }

  // switch
  int choice = rand() % 2 + 1;
  LOG_S("Choice = " << std::to_string(x));
  switch (choice) {
    case 1:
      LOG("Choice is 1");
      break;
    case 2:
      LOG("Choice is 2");
      break;
    default:
      LOG("Choice is something else");
      break;
  }
}

void jumps() {
  LOG("Jump Statement Examples");

  // goto
  int num = rand();
  if (num == 3)
    goto jumpLabel;
  LOG("This line will be skipped.");

jumpLabel:
  LOG("Jumped here using goto!");

  // break / continue
  for (int i = 0; i < 5; ++i) {
    if (i == 2)
      continue;  // skip 2
    if (i == 4)
      break;  // stop loop at 4
    LOG_S("i = " << i);
  }
}

int square(int n) {
  // return
  return n * n;
}

void functionCalls() {
  LOG("Function Call Examples");
  // function call
  int result = square(5);
  LOG_S("square(5) = " << result);
}

void loops() {
  LOG("Loop Examples");

  // while
  int i = 0;
  while (i < 3) {
    LOG_S("while loop i = " << i);
    ++i;
  }

  // do-while
  int j = 0;
  do {
    LOG_S("do-while loop j = " << j);
    ++j;
  } while (j < 2);

  // for(initialization; condition; update)
  for (int k = 0; k < 3; ++k) {
    LOG_S("for loop k = " << k);
  }

  // ranged-for
  const int arr[] = {10, 20, 30};
  for (int value : arr) {
    LOG_S("ranged-for value = " << value);
  }
}

void halts() {
  LOG("Halt Examples");

  // std::exit() — terminates the program normally
  // std::abort() — terminates abnormally (no cleanup)
  // Uncomment one at a time to see behavior

  // std::exit(0);
  // std::abort();
}

void exceptions() {
  LOG("Exception Handling Examples");

  // try - catch - throw
  try {
    throw std::runtime_error("Something went wrong!");
  } catch (const std::exception& e) {
    LOG_S("Caught exception: " << e.what());
  }
}
}  // namespace

class ControlFlow : public IExample {
 public:
  std::string group() const override { return "core/basics"; }
  std::string name() const override { return "ControlFlow"; }
  std::string description() const override { return "ControlFlow"; }
  void execute() override {
    conditionals();
    jumps();
    functionCalls();
    loops();
    halts();
    exceptions();
  }
};

REGISTER_EXAMPLE(ControlFlow);
