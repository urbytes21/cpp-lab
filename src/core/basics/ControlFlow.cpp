#include <iostream>
#include "ExampleRegistry.h"

namespace {
void conditionals() {
  std::cout << "\n--- Conditional Examples ---\n";
  // if-else
  int x = rand();
  std::cout << "x = " << x << "\n";
  if (x > 0) {
    std::cout << "x is positive\n";
  } else if (x < 0) {
    std::cout << "x is negative\n";
  } else {
    std::cout << "x is zero\n";
  }

  // switch
  int choice = rand() % 2 + 1;
  std::cout << "choice = " << x << "\n";
  switch (choice) {
    case 1:
      std::cout << "Choice is 1\n";
      break;
    case 2:
      std::cout << "Choice is 2\n";
      break;
    default:
      std::cout << "Choice is something else\n";
      break;
  }
}

void jumps() {
  std::cout << "\n--- Jump Statement Examples ---\n";

  // goto
  int num = rand();
  if (num == 3)
    goto jumpLabel;
  std::cout << "This line will be skipped.\n";

jumpLabel:
  std::cout << "Jumped here using goto!\n";

  // break / continue
  for (int i = 0; i < 5; ++i) {
    if (i == 2)
      continue;  // skip 2
    if (i == 4)
      break;  // stop loop at 4
    std::cout << "i = " << i << "\n";
  }
}

int square(int n) {
  // return
  return n * n;
}

void functionCalls() {
  std::cout << "\n--- Function Call Examples ---\n";
  // function call
  int result = square(5);
  std::cout << "square(5) = " << result << "\n";
}

void loops() {
  std::cout << "\n--- Loop Examples ---\n";

  // while
  int i = 0;
  while (i < 3) {
    std::cout << "while loop i = " << i << "\n";
    ++i;
  }

  // do-while
  int j = 0;
  do {
    std::cout << "do-while loop j = " << j << "\n";
    ++j;
  } while (j < 2);

  // for(initialization; condition; update)
  for (int k = 0; k < 3; ++k) {
    std::cout << "for loop k = " << k << "\n";
  }

  // ranged-for
  const int arr[] = {10, 20, 30};
  for (int value : arr) {
    std::cout << "ranged-for value = " << value << "\n";
  }
}

void halts() {
  std::cout << "\n--- Halt Examples ---\n";

  // std::exit() — terminates the program normally
  // std::abort() — terminates abnormally (no cleanup)
  // Uncomment one at a time to see behavior

  // std::exit(0);
  // std::abort();
}

void exceptions() {
  std::cout << "\n--- Exception Handling Examples ---\n";

  // try - catch - throw
  try {
    throw std::runtime_error("Something went wrong!");
  } catch (const std::exception& e) {
    std::cout << "Caught exception: " << e.what() << "\n";
  }
}
}  // namespace

class ControlFlow : public IExample {
 public:
  std::string group() const override { return "core"; }
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

REGISTER_EXAMPLE(ControlFlow, "core", "ControlFlow");
